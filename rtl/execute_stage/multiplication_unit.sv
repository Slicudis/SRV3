/*
    [Module]: Pipelined RV32M multiplication unit

    [Description]: This execution unit performs pipelined multiplications in
    an 8-stage pipeline. The first stage is for fetching the instruction. The
    second stage gets the absolute values of the operands if signed multiplication
    is being performed. The third stage is the start of the process of shifting and
    adding. Adders are organized a tree-like structure to reduce the amount of stages.
    The structure finishes at stage 7 and in stage 8 the result is negated if the multiplication
    is signed and the signs of the original inputs were not equal.

    Stage 1: Fetch
    Stage 2: ABS
    Stage 3: Filter, shift and add1
    Stage 4: Add2
    Stage 5: Add3
    Stage 6: Add4
    Stage 7: Add5
    Stage 8: Conditional negation
*/

module multiplication_unit #(
    parameter ID_SIZE = 7
)(
    input   wire                clk,            //Clock
    input   wire                clk_en,         //Enable clock
    input   wire                sync_rst,       //Flush the pipeline (Doesn't depend on CLK_EN)

    input   wire                flush,          //Flush the pipeline (Invalidate all stages)
    input   wire [31:0]         data_in1,       //Operand A
    input   wire [31:0]         data_in2,       //Operand B
    input   wire [1:0]          operation_in,   //Operation (RISC-V func3[1:0])
    input   wire                call,           //Validate input operation
    input   wire [ID_SIZE-1:0]  inst_id_in,     //Instruction ID (Used by the reorder buffer)

    output  wire [31:0]         data_out,       //Result
    output  wire [ID_SIZE-1:0]  inst_id_out,    //Output instruction ID (Used by the ROB)
    output  wire                output_valid    //Tell the ROB if this is a valid instruction
);

///
    // * --- Stage 1 ---

    typedef struct{
        reg [31:0] data1;
        reg [31:0] data2;
        reg [1:0] op;
        reg [ID_SIZE-1:0] inst_id;
        reg valid;
    } stage1_t;

    stage1_t stage1;

    always_ff @(posedge clk) begin : Stage1_ff
        if(sync_rst || (clk_en && flush)) begin
            stage1.valid <= 'h0;
        end else if(clk_en) begin
            stage1.data1 <= data_in1;
            stage1.data2 <= data_in2;
            stage1.op <= operation_in;
            stage1.valid <= call;
            stage1.inst_id <= inst_id_in;
        end
    end

    ///
    // * --- Stage 2 ---

    function logic [31:0] abs(input [31:0] data_in);
        return data_in[31] ? -data_in : data_in;
    endfunction

    typedef struct{
        reg [31:0] adj_data1;
        reg [31:0] adj_data2;
        reg data1_sign;
        reg data2_sign;
        reg [1:0] op;
        reg [ID_SIZE-1:0] inst_id;
        reg valid;
    } stage2_t;

    stage2_t stage2;

    always_ff @(posedge clk) begin : Stage2_ff
        if(sync_rst || (clk_en && flush)) begin
            stage2.valid <= 'h0;
        end else if(clk_en) begin
            stage2.adj_data1 <= (stage1.op[0]&stage1.op[1]) ? stage1.data1 : abs(stage1.data1);
            stage2.adj_data2 <= (stage1.op[0]&stage1.op[1]) ? stage1.data2 : abs(stage1.data2);
            stage2.data1_sign <= stage1.data1[31];
            stage2.data2_sign <= stage1.data2[31];
            stage2.op <= stage1.op;
            stage2.inst_id <= stage1.inst_id;
            stage2.valid <= stage1.valid;
        end
    end

///
    // * --- Stage 3 ---

    typedef struct{
        reg [63:0] partial_result [15:0];
        reg data1_sign;
        reg data2_sign;
        reg [1:0] op;
        reg [ID_SIZE-1:0] inst_id;
        reg valid;
    } stage3_t;

    stage3_t stage3;
    wire [31:0] stage3_filtered_data [31:0];
    wire [63:0] stage3_PartialRes_in [15:0];

    genvar i;
    generate
        for(i = 0; i < 32; i++) begin : FilterData
            assign stage3_filtered_data[i] = stage2.adj_data1 & {32{stage2.adj_data2[i]}};
        end
        for(i = 0; i < 32; i += 2) begin : Add_and_shift
            assign stage3_PartialRes_in[i>>1] = (stage3_filtered_data[i] << i) + (stage3_filtered_data[i+1] << (i+1));
        end
    endgenerate

    always_ff @(posedge clk) begin : Stage3_ff
        if(sync_rst || (clk_en && flush)) begin
            stage3.valid <= 'h0;
        end else if(clk_en) begin
            stage3.partial_result <= stage3_PartialRes_in;
            stage3.data1_sign <= stage2.data1_sign;
            stage3.data2_sign <= stage2.data2_sign;
            stage3.op <= stage2.op;
            stage3.inst_id <= stage2.inst_id;
            stage3.valid <= stage2.valid;
        end
    end

///
    // * --- Stage 4 ---

    typedef struct{
        reg [63:0] partial_result [7:0];
        reg data1_sign;
        reg data2_sign;
        reg [1:0] op;
        reg [ID_SIZE-1:0] inst_id;
        reg valid;
    } stage4_t;

    stage4_t stage4;
    wire [63:0] stage4_PartialRes_in [7:0];

    generate
        for(i = 0; i < 16; i += 2) begin : Add2
            assign stage4_PartialRes_in[i>>1] = stage3.partial_result[i] + stage3.partial_result[i+1];
        end
    endgenerate
    
    always_ff @(posedge clk) begin : Stage4_ff
        if(sync_rst || (clk_en && flush)) begin
            stage4.valid <= 'h0;
        end else if(clk_en) begin
            stage4.partial_result <= stage4_PartialRes_in;
            stage4.data1_sign <= stage3.data1_sign;
            stage4.data2_sign <= stage3.data2_sign;
            stage4.op <= stage3.op;
            stage4.inst_id <= stage3.inst_id;
            stage4.valid <= stage3.valid;
        end     
    end

///
    // * --- Stage 5 ---

    typedef struct{
        reg [63:0] partial_result [3:0];
        reg data1_sign;
        reg data2_sign;
        reg [1:0] op;
        reg [ID_SIZE-1:0] inst_id;
        reg valid; 
    } stage5_t;

    stage5_t stage5;
    wire [63:0] stage5_PartialRes_in [3:0];

    generate
        for(i = 0; i < 8; i += 2) begin : Add3
            assign stage5_PartialRes_in[i>>1] = stage4.partial_result[i] + stage4.partial_result[i+1];
        end
    endgenerate

    always_ff @(posedge clk) begin : Stage5_ff
        if(sync_rst || (clk_en && flush)) begin
            stage5.valid <= 'h0;
        end else if(clk_en) begin
            stage5.partial_result <= stage5_PartialRes_in;
            stage5.data1_sign <= stage4.data1_sign;
            stage5.data2_sign <= stage4.data2_sign;
            stage5.op <= stage4.op;
            stage5.inst_id <= stage4.inst_id;
            stage5.valid <= stage4.valid;
        end
    end

///
    // * --- Stage 6 ---

    typedef struct{
        reg [63:0] partial_result [1:0];
        reg data1_sign;
        reg data2_sign;
        reg [1:0] op;
        reg [ID_SIZE-1:0] inst_id;
        reg valid; 
    } stage6_t;

    stage6_t stage6;
    wire [63:0] stage6_PartialRes_in [1:0];

    generate
        for(i = 0; i < 4; i += 2) begin : Add4
            assign stage6_PartialRes_in[i>>1] = stage5.partial_result[i] + stage5.partial_result[i+1];
        end
    endgenerate

    always_ff @(posedge clk) begin : Stage6_ff
        if(sync_rst || (clk_en && flush)) begin
            stage6.valid <= 'h0;
        end else if(clk_en) begin
            stage6.partial_result <= stage6_PartialRes_in;
            stage6.data1_sign <= stage5.data1_sign;
            stage6.data2_sign <= stage5.data2_sign;
            stage6.op <= stage5.op;
            stage6.inst_id <= stage5.inst_id;
            stage6.valid <= stage5.valid;
        end
    end

///
    // * --- Stage 7 ---

    typedef struct{
        reg [63:0] partial_result;
        reg data1_sign;
        reg data2_sign;
        reg [1:0] op;
        reg [ID_SIZE-1:0] inst_id;
        reg valid; 
    } stage7_t;

    stage7_t stage7;

    always_ff @(posedge clk) begin : Stage7_ff
        if(sync_rst || (clk_en && flush)) begin
            stage7.valid <= 'h0;
        end else if(clk_en) begin
            stage7.partial_result <= stage6.partial_result[0] + stage6.partial_result[1];
            stage7.data1_sign <= stage6.data1_sign;
            stage7.data2_sign <= stage6.data2_sign;
            stage7.op <= stage6.op;
            stage7.inst_id <= stage6.inst_id;
            stage7.valid <= stage6.valid;
        end
    end

///
    // * --- Stage 8 ---

    typedef struct{
        reg [63:0] final_result;
        reg [ID_SIZE-1:0] inst_id;
        reg valid; 
    } stage8_t;

    stage8_t stage8;
    wire negate_result = (!(stage7.op[0] && stage7.op[1]) && stage7.data1_sign) ^^ (stage7.op[1] && stage7.data2_sign);

    always_ff @(posedge clk) begin
        if(sync_rst || (clk_en && flush)) begin : Stage8_ff
            stage8.valid <= 'h0;
        end else if(clk_en) begin
            stage8.final_result <= negate_result ? -stage7.partial_result : stage7.partial_result;
            stage8.inst_id <= stage7.inst_id;
            stage8.valid <= stage8.valid;
        end
    end

    assign data_out = (stage7.op[0] || stage7.op[1]) ? stage8.final_result[63:32] : stage8.final_result[31:0];
    assign inst_id_out = stage7.inst_id;
    assign output_valid = stage7.valid;

///
endmodule : multiplication_unit
