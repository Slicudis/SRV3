module branching_unit #(
    parameter ID_SIZE = 8
)(
    input   wire                clk,
    input   wire                clk_en,
    input   wire                sync_rst,

    // * From dispatch stage
    input   wire                call,
    input   wire                flush,
    input   wire [ID_SIZE-1:0]  inst_id_in,
    input   wire                unconditional_mode,
    input   wire [2:0]          func3_in,
    input   wire [31:0]         data_in1,
    input   wire [31:0]         data_in2,
    input   wire [29:0]         offset_in,
    input   wire [29:0]         pc_in,
    input   wire [29:0]         predicted_target,
    input   wire                prediction_taken,

    // * To ROB
    output  wire [29:0]         real_target_address,
    output  wire [31:0]         incremented_pc,
    output  wire                flush_and_jump,
    output  wire                regfile_write
);

///
    // * --- Stage 1 ---

    typedef struct{
        reg valid;
        reg [ID_SIZE-1:0] inst_id;
        reg uncond_mode;
        reg [2:0] func3;
        reg [31:0] data1;
        reg [31:0] data2;
        reg [29:0] offset;
        reg [29:0] pc;
        reg [29:0] pred_target;
        reg pred_taken;
    } stage1_t;

    stage1_t stage1;

    always_ff @(posedge clk) begin : Stage1_ff
        if(sync_rst || (clk_en && flush)) begin
            stage1.valid <= 'h0;
        end else if(clk_en) begin
            stage1.valid <= call;
            stage1.inst_id <= inst_id_in;
            stage1.uncond_mode <= unconditional_mode;
            stage1.func3 <= func3_in;
            stage1.data1 <= data_in1;
            stage1.data2 <= data_in2;
            stage1.offset <= offset_in;
            stage1.pc <= pc_in;
            stage1.pred_target <= predicted_target;
            stage1.pred_taken <= prediction_taken;
        end
    end

///
    // * --- Stage 2 ---

    typedef struct{
        reg valid;
        reg [ID_SIZE-1:0] inst_id;
        reg real_taken;
        reg pred_taken;
        reg [29:0] pred_target;
        reg [29:0] real_target;
        reg [29:0] inc_pc;
        reg regfile_write;
    } stage2_t;

    stage2_t stage2;
    wire [32:0] subtraction = stage1.data1 - stage1.data2;
    wire not_zero = |subtraction[31:0];
    wire overflow = ~(stage1.data1[31] ^ stage1.data2[31]) & (stage1.data1[31] ^ subtraction[31]);

    logic int_branch_taken;
    wire branch_taken = int_branch_taken ^ stage1.func3[0];
    always_comb begin
        case(stage1.func3[2:1])
            2'h0: int_branch_taken = ~not_zero;
            2'h1: int_branch_taken = overflow ^ subtraction[31];
            2'h2: int_branch_taken = subtraction[32];
            default: int_branch_taken = 'x;
        endcase
    end

    always_ff @(posedge clk) begin : Stage2_ff
        if(sync_rst || (clk_en && flush)) begin
            stage2.valid <= 'h0;
        end else if(clk_en) begin
            stage2.valid <= stage1.valid;
            stage2.inst_id <= stage1.inst_id;
            stage2.real_taken <= branch_taken | stage1.uncond_mode;
            stage2.pred_taken <= stage1.pred_taken;
            stage2.pred_target <= stage1.pred_target;
            stage2.real_target <= stage1.pc + stage1.offset;
            stage2.inc_pc <= stage1.pc + 'h1;
            stage2.regfile_write <= stage1.uncond_mode;
        end
    end

///
    // * --- Stage 3 ---

    typedef struct{
        reg valid;
        reg [ID_SIZE-1:0] inst_id;
        reg misprediction;
        reg taken;
        reg regfile_write;
        reg [29:0] target_address;
        reg [29:0] inc_pc;
    } stage3_t;

    stage3_t stage3;

    always_ff @(posedge clk) begin : Stage3_ff
        if(sync_rst) begin
            stage3.valid <= 'h0;
        end else if(clk_en) begin
            stage3.inst_id <= stage2.inst_id;
            stage3.misprediction <= (stage2.pred_taken ^ stage2.real_taken) || (stage2.real_target != stage2.pred_target);
            stage3.taken <= stage2.real_taken;
            stage3.regfile_write <= stage2.regfile_write;
            stage3.target_address <= stage2.real_target;
            stage3.inc_pc <= stage2.inc_pc;
        end
    end

    assign real_target_address = stage3.taken ? stage3.target_address : stage3.inc_pc;
    assign incremented_pc = {stage3.inc_pc, 2'b0};
    assign flush_and_jump = stage3.misprediction;
    assign regfile_write = stage3.regfile_write;

///
endmodule : branching_unit