/*
    [Module]: RV32I Arithmetic Logic Unit (ALU)

    [Description]: This execution unit executes the base arithmetic RV32I instructions, like ADD or XOR.
*/
module alu #(
    ID_WIDTH = 6
)(
    input wire                  clk,                    //Clock
    input wire                  clk_en,                 //Enable clock
    input wire                  sync_rst,               //Synchronous reset (independent from CLK_EN)
    
    // * Input buffer1 pins
    input   wire                call,                   //Place an instruction in the buffer1
    input   wire [ID_WIDTH-1:0] instruction_ID_in,      //ID of the input instruction
    input   wire [31:0]         data_in1,               //Operand A
    input   wire [31:0]         data_in2,               //Operand B
    input   wire [4:0]          operation_in,           //Operation

    // * Writeback pins
    output  wire                result_valid,           //High when the instruction finished execution and is ready for the writeback stage
    output  wire [31:0]         data_out,               //Result of the operation
    output  wire [ID_WIDTH-1:0] instruction_ID          //ID of the output instruction
);
///
    // * Fetch stage

    typedef struct{
        reg [31:0] data1;
        reg [31:0] data2;
        reg [4:0] operation;
        reg [ID_WIDTH-1:0] inst_id;
        reg valid_flag;
    } input_buffer_struct;

    input_buffer_struct buffer1;

    always_ff @(posedge clk) begin : Inputbuffer
        if(sync_rst) begin
            buffer1.data1 <= 'h0;
            buffer1.data1 <= 'h0;
            buffer1.operation <= 'h0;
            buffer1.valid_flag <= 'h0;
        end else if(clk_en) begin
            buffer1.data1 <= data_in1;
            buffer1.data2 <= data_in2;
            buffer1.operation <= operation_in;
            buffer1.inst_id <= instruction_ID_in;
            buffer1.valid_flag <= call;
        end
    end

    ///
    //* Execute stage

    /*
    Structure of operation:
    [2:0] func3
    [3] func7[5]
    [4] disable_subtraction
    */
    
    wire subtraction_mode = (buffer1.operation[3] || buffer1.operation[1]) && !buffer1.operation[4];
    wire [32:0] adder_sum;
    wire adder_carry_out;
    assign {adder_carry_out, adder_sum} = buffer1.data1 + (buffer1.data2 ^ {32{subtraction_mode}}) + subtraction_mode;
    wire adder_overflow = ~(buffer1.data1[31] ^ buffer1.data2[31]) && (buffer1.data1[31] ^ adder_sum[31]);

    wire [31:0] reversed1;
    wire [31:0] reversed2;
    wire [31:0] selected1 = buffer1.operation[2] ? buffer1.data1 : reversed1;
    wire [31:0] selected2 = buffer1.operation[2] ? buffer1.data1 : reversed1;
    wire [31:0] intermediate_shift = (selected1 >> selected2[4:0]);
    wire [31:0] reversed_shift;
    wire [31:0] shifter_result = buffer1.operation[2] ? intermediate_shift : reversed_shift;
    genvar i;
    generate
        for(i = 0; i < 32; i++) begin : Reverse
            assign reversed1[i] = buffer1.data1[31-i];
            assign reversed2[i] = buffer1.data1[31-i];
            assign reversed_shift[i] = intermediate_shift[31-i];
        end
    endgenerate
    
    logic [31:0] intermediate_alu_result;
    always_comb begin : ALU_Main_Multiplexer
        case(buffer1.operation[2:0])
            3'h0: intermediate_alu_result = adder_sum[31:0];
            3'h1: intermediate_alu_result = shifter_result;
            3'h2: intermediate_alu_result = {31'h0, (adder_overflow ^ adder_sum[31])};
            3'h3: intermediate_alu_result = {31'h0, !adder_carry_out};
            3'h4: intermediate_alu_result = buffer1.data1 ^ buffer1.data2;
            3'h5: intermediate_alu_result = buffer1.operation[3] ? ($signed(buffer1.data1) >>> buffer1.data2[4:0]) : shifter_result;
            3'h6: intermediate_alu_result = buffer1.data1 | buffer1.data2;
            3'h7: intermediate_alu_result = buffer1.data1 & buffer1.data2;
            default: intermediate_alu_result = 'x;
        endcase
    end

    ///
    // * Output stage

    typedef struct{
        reg [31:0] result;
        reg [ID_WIDTH-1:0] inst_id;
        reg valid_flag;
    } output_buffer_struct;

    output_buffer_struct buffer2;

    always_ff @(posedge clk) begin : Outputbuffer1
        if(sync_rst) begin
            buffer2.result <= 'h0;
            buffer2.valid_flag <= 'h0;
            buffer2.inst_id <= 'h0;
        end else if(clk_en) begin
            buffer2.result <= intermediate_alu_result;
            buffer2.valid_flag <= buffer1.valid_flag;
            buffer2.inst_id <= buffer1.inst_id;
        end
    end

    assign data_out = buffer2.result;
    assign result_valid = buffer2.valid_flag;
    assign instruction_ID = buffer2.inst_id;

///
endmodule : alu