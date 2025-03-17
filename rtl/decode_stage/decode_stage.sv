module decode_stage #(
    parameter BTB_ENTRIES = 32,
    parameter BTB_GH_SIZE = 8
)(
    input   wire                    clk,
    input   wire                    clk_en,
    input   wire                    sync_rst,
    
    input   wire                    flush,
        
    input   wire [31:0]             instruction_in,
    input   wire [29:0]             pc_in,

    // * To issue stage

    output  reg  [14:0]             ctr_word_out,
 
    output  reg  [2:0]              func3_out,
    output  reg  [4:0]              rs1_address_out,
    output  reg  [4:0]              rs2_address_out,
    output  reg  [4:0]              writeback_address_out,

    output  wire [29:0]             btb_predicted_target_out,
    output  wire [BTB_GH_SIZE-1:0]  btb_global_history_out,
    output  wire [1:0]              btb_saturating_counter_out,
    output  wire                    prediction_taken,
    output  wire                    speculative_mode,

    output  reg  [29:0]             current_pc_out,
    output  wire [31:0]             rs1_out,
    output  wire [31:0]             rs2_out,
    output  wire                    rs1_reserved,
    output  wire                    rs2_reserved,

    // * From branching unit

    input   wire                    predictor_feedback_en,
    input   wire [29:0]             btb_address_in,
    input   wire [29:0]             btb_data_in,
    input   wire [BTB_GH_SIZE-1:0]  btb_gh_data_in,
    input   wire [1:0]              btb_sat_ctr_data_in,

    // * From commit stage

    input wire                      regfile_we,
    input wire [4:0]                regfile_writeback_addr,
    input wire [31:0]               regfile_data_in
);

    wire [15:0] decoded_ctr_word;

    reg speculative_flag;
    assign speculative_mode = speculative_flag;

    always_ff @(posedge clk) begin : Buffers_ff
        if(sync_rst) begin
            ctr_word_out <= 'h0;
        end else if(clk_en) begin
            rs1_address_out <= instruction_in[19:15];
            rs2_address_out <= instruction_in[24:20];
            writeback_address_out <= instruction_in[11:7];
            func3_out <= instruction_in[14:12];
            current_pc_out <= pc_in;
            ctr_word_out <= decoded_ctr_word;
            if(decoded_ctr_word[11]) speculative_flag <= 1'b1;
            else if(predictor_feedback_en) speculative_flag <= 1'b0;
        end
    end

    regfile register_file (
        .clk                (clk),
        .clk_en             (clk_en),
        .sync_rst           (sync_rst),
        .reserve_address    (instruction_in[11:7]),
        .rs1_address        (instruction_in[19:15]),
        .rs2_address        (instruction_in[24:20]),
        .reserve            (decoded_ctr_word[15]),
        .speculative_mode   (decoded_ctr_word[11] || speculative_mode),
        .speculative_cancel (flush),
        .write_en           (regfile_we),
        .write_address      (regfile_writeback_addr),
        .data_in            (regfile_data_in),
        .rs1_data           (rs1_out),
        .rs2_data           (rs2_out),
        .rs1_reserved       (rs1_reserved),
        .rs2_reserved       (rs2_reserved)
    );

    btb #(
        .ENTRIES(BTB_ENTRIES),
        .GH_SIZE(BTB_GH_SIZE)
    ) branch_target_buffer (
        .clk                     (clk),
        .clk_en                  (clk_en),
        .read_address_in         (pc_in),
        .read_en                 (decoded_ctr_word[11]),
        .target_address          (btb_predicted_target_out),
        .saturaring_ctr_out      (btb_saturating_counter_out),
        .global_history_out      (btb_global_history_out),
        .prediction_taken        (prediction_taken),
        .write_en                (predictor_feedback_en),
        .write_address_in        (btb_address_in),
        .data_in                 (btb_data_in),
        .sat_ctr_data_in         (btb_sat_ctr_data_in),
        .global_history_data_in  (btb_gh_data_in)
    );

    inst_decoder instruction_decoder (
        .major_opcode_in  (instruction_in[6:0]),
        .func7_bit0       (instruction_in[25]),
        .ctr_word         (decoded_ctr_word)
    );

endmodule : decode_stage