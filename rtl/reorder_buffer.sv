module reorder_buffer #(
    parameter ENTRIES = 32,
    parameter ID_WIDTH = 8
)(
    input   wire        clk,
    input   wire        clk_en,
    input   wire        sync_rst,
    
    // * Issue stage connections
    input   wire        push,
    input   wire [2:0]  exe_unit_id,
    input   wire [4:0]  writeback_address,
    output  wire        rob_full,

    // * ALU connections
    input   wire [31:0] alu_data,
    input   wire        alu_result_valid,
    output  wire        stall_alu,

    // * Multiplier connections
    input   wire [31:0] multiplier_data,
    input   wire        multiplier_result_valid,
    output  wire        stall_multiplier,

    // * Divider connections
    input   wire [31:0] divider_data,
    input   wire        divider_result_valid,
    output  wire        stall_divider,

    // * Memory unit connections
    input   wire [31:0] memory_unit_data,
    input   wire        memory_unit_data_valid,
    input   wire        memory_unit_store_valid,

    // * Writeback/flush and branch pins
    output  wire        regfile_we,
    output  wire [31:0] data_out,
    output  wire        flush_and_branch,
    output  wire [29:0] target_address,
    output  wire        store_buffer_valid
);
    localparam PTR_WIDTH = $clog2(ENTRIES);

    typedef struct{
        reg [31:0] data;
        reg [4:0] wb_address;       //Writeback address
        reg [ID_WIDTH-1:0] inst_id;
        reg [1:0] exe_unit_sel;     //0=ALU, 1=MUL, 2=DIV, 3=MEM
        reg speculative_mode;
        reg valid;
    } entry_t;

    entry_t entry[ENTRIES-1:0];
    reg [PTR_WIDTH-1:0] head_ptr;
    reg [PTR_WIDTH-1:0] tail_ptr;
    

endmodule : reorder_buffer