//todo: debug this shit

module multiplication_unit_old #(
    parameter FIFO_SIZE = 4,    //Amount of FIFO entries
    parameter ID_WIDTH = 7      //Size of the instruction "name"
)(
    // * Clock control pins
    input   wire                clk,                    //Clock
    input   wire                clk_en,                 //Enable clock
    input   wire                sync_rst,               //Synchronous reset (Doesn't depend on CLK_EN)
    
    // * FIFO pins
    input   wire                call,                   //Place an instruction in the queue
    input   wire [ID_WIDTH-1:0] instruction_ID_in,      //ID of the input instruction
    input   wire [31:0]         data_in1,               //Operand A
    input   wire [31:0]         data_in2,               //Operand B
    input   wire [1:0]          operation_in,           //Operation
    output  wire                fifo_full,              //To avoid FIFO overflows and leave the instruction in the dispatch queue instead

    // * Writeback pins
    input   wire                writeback_ack,          //Allow the next instruction to be executed
    output  wire                result_ready,           //High when the instruction finished execution and is ready for the writeback stage
    output  wire [31:0]         data_out,               //Result of the operation
    output  wire [ID_WIDTH-1:0] instruction_ID          //ID of the output instruction
);
///
    // * --- Input FIFO ---

    localparam FIFO_ADDRWIDTH = $clog2(FIFO_SIZE);

    typedef struct {
        reg [31:0] operand_a [FIFO_SIZE-1:0];
        reg [31:0] operand_b [FIFO_SIZE-1:0];
        reg [4:0] instruction_ID [FIFO_SIZE-1:0];
        reg [1:0] operation [FIFO_SIZE-1:0];
        reg [FIFO_ADDRWIDTH-1:0] head_pointer;
        reg [FIFO_ADDRWIDTH-1:0] tail_pointer;
    } multiplier_fifo;

    multiplier_fifo mult_fifo;
    assign fifo_full = (mult_fifo.head_pointer == FIFO_ADDRWIDTH'(mult_fifo.tail_pointer+1));
    wire mult_fifo_empty = (mult_fifo.head_pointer == mult_fifo.tail_pointer);
    wire head_pointer_max = (mult_fifo.head_pointer == (FIFO_ADDRWIDTH)'(FIFO_SIZE-1));
    wire tail_pointer_max = (mult_fifo.tail_pointer == (FIFO_ADDRWIDTH)'(FIFO_SIZE-1));

    always_ff @(posedge clk) begin : FIFO
        if(sync_rst) begin
            mult_fifo.head_pointer <= (FIFO_ADDRWIDTH)'(0);
            mult_fifo.tail_pointer <= (FIFO_ADDRWIDTH)'(0);
        end else if(clk_en) begin
            if(result_ready && writeback_ack) mult_fifo.head_pointer <= head_pointer_max ? (FIFO_ADDRWIDTH)'(0) : (mult_fifo.head_pointer + 1); //todo: check why this doesn't increment
            if(call && !fifo_full) begin
                mult_fifo.tail_pointer <= tail_pointer_max ? (FIFO_ADDRWIDTH)'(0) : (mult_fifo.tail_pointer + 1);
                mult_fifo.operand_a[mult_fifo.tail_pointer] <= data_in1;
                mult_fifo.operand_b[mult_fifo.tail_pointer] <= data_in2;
                mult_fifo.instruction_ID[mult_fifo.tail_pointer] <= instruction_ID_in;
                mult_fifo.operation[mult_fifo.tail_pointer] <= operation_in;
            end
        end
    end

///
    // * --- Multiplier ---

    typedef struct {
        reg [31:0] sign_adjusted_a;
        reg [31:0] sign_adjusted_b;
        reg [15:0] partial_result0 [15:0];
        reg [63:0] partial_result1 [7:0];
        reg [63:0] partial_result2 [3:0];
        reg [63:0] partial_result3 [2:0];
        reg [63:0] partial_result4 [1:0];
        reg [63:0] partial_result5;
        reg [63:0] final_result;
        reg ready_flag;
        reg [3:0] state;
    } tree_multiplier;

    typedef enum bit[3:0] {IDLE, INIT_SIGN_ADJ, PART0, PART1, PART2, PART3, PART4, PART5, END_SIGN_ADJ} STATES;

    tree_multiplier multiplier;
    wire [1:0] current_configuration = mult_fifo.operation[mult_fifo.head_pointer];
    wire [31:0] current_a = mult_fifo.operand_a[mult_fifo.head_pointer];
    wire [31:0] current_b = mult_fifo.operand_b[mult_fifo.head_pointer];

    function logic [31:0] abs(logic [31:0] data_in);
        return data_in[31] ? -data_in : data_in;
    endfunction

    wire [15:0] partial_res0_in [15:0];
    wire [63:0] partial_res1_in [7:0];
    wire [63:0] partial_res2_in [3:0];
    wire [63:0] partial_res3_in [2:0];
    wire [63:0] partial_res4_in [1:0];

    localparam logic [5:0] SHIFT_AMT [16] = '{6'd1, 6'd8, 6'd16, 6'd24, 6'd8, 6'd16, 6'd24, 6'd32, 6'd16, 6'd24, 6'd32, 6'd40, 6'd24, 6'd32, 6'd40, 6'd48};

    genvar i;
    generate
        for(i = 0; i < 16; i++) begin : PartialRES0
            assign partial_res0_in[i] = multiplier.sign_adjusted_a[i[3:2]*8+7-:8] * multiplier.sign_adjusted_b[i[1:0]*8+7-:8];
        end
        for(i = 0; i < 8; i++) begin : PartialRES1
            wire [SHIFT_AMT[i]-1:0] SEL_SHIFT_AMT1 = 'h0;
            wire [SHIFT_AMT[i+8]-1:0] SEL_SHIFT_AMT2 = 'h0;
            wire [63:0] operand1 = (SHIFT_AMT[i] == 1) ? multiplier.partial_result0[i] : {multiplier.partial_result0[i], SEL_SHIFT_AMT1};
            wire [63:0] operand2 = (SHIFT_AMT[i+8] == 1) ? multiplier.partial_result0[i+8] : {multiplier.partial_result0[i+8], SEL_SHIFT_AMT2};
            assign partial_res1_in[i] = operand1 + operand2;
        end
        for(i = 0; i < 4; i++) begin : PartialRES2
            assign partial_res2_in[i] = multiplier.partial_result1[i] + multiplier.partial_result1[i+4];
        end
        for(i = 0; i < 2; i++) begin : PartialRES3
            assign partial_res3_in[i] = multiplier.partial_result2[i] + multiplier.partial_result2[i+2];
        end
        for(i = 0; i < 1; i++) begin : PartialRES4
            assign partial_res4_in[i] = multiplier.partial_result3[i] + multiplier.partial_result3[i+1];
        end
    endgenerate

    always_ff @(posedge clk) begin
        if(sync_rst) begin
            multiplier.state <= IDLE;
            multiplier.ready_flag <= 1'b0;
        end else if(clk_en) begin
            multiplier.ready_flag <= (multiplier.state == END_SIGN_ADJ) ? 1'b1 : (writeback_ack && !multiplier.ready_flag);
            case(multiplier.state)
                IDLE: if(!mult_fifo_empty) multiplier.state <= INIT_SIGN_ADJ;
                INIT_SIGN_ADJ: begin
                    multiplier.sign_adjusted_a <= (current_configuration == 2'b11) ? current_a : abs(current_a);
                    multiplier.sign_adjusted_b <= (current_configuration[1]) ? current_b : abs(current_b);
                    multiplier.state <= PART0;
                    end
                PART0: begin
                    multiplier.partial_result0 <= partial_res0_in;
                    multiplier.state <= PART1;
                    end
                PART1: begin
                    multiplier.partial_result1 <= partial_res1_in;
                    multiplier.state <= PART2;
                    end
                PART2: begin
                    multiplier.partial_result2 <= partial_res2_in;
                    multiplier.state <= PART3;
                    end
                PART3: begin
                    multiplier.partial_result3 <= partial_res3_in;
                    multiplier.state <= PART4;
                    end
                PART4: begin
                    multiplier.partial_result4 <= partial_res4_in;
                    multiplier.state <= PART5;
                    end
                PART5: begin
                    multiplier.partial_result5 <= multiplier.partial_result4[0] + multiplier.partial_result4[1];
                    multiplier.state <= END_SIGN_ADJ;
                    end
                END_SIGN_ADJ: begin
                    case(current_configuration)
                        2'b00: multiplier.final_result <= (current_a[31] ^^ current_b[31]) ? -multiplier.partial_result5 : multiplier.partial_result5;
                        2'b01: multiplier.final_result <= (current_a[31] ^^ current_b[31]) ? -multiplier.partial_result5 : multiplier.partial_result5;
                        2'b10: multiplier.final_result <= (current_a[31]) ? -multiplier.partial_result5 : multiplier.partial_result5;
                        2'b11: multiplier.final_result <= multiplier.partial_result5;
                        default: /*nothing*/;
                    endcase
                    multiplier.state <= IDLE;
                    end
                default: /*nothing*/;
            endcase
        end
    end

    assign data_out = (|current_configuration) ? multiplier.final_result[63:32] : multiplier.final_result[31:0];
    assign instruction_ID = mult_fifo.instruction_ID[mult_fifo.head_pointer];
    assign result_ready = multiplier.ready_flag;

    ///
endmodule : multiplication_unit_old
