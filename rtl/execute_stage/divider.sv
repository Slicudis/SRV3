module divider #(
    parameter ID_SIZE = 8
)(
    input   wire                clk,
    input   wire                clk_en,
    input   wire                sync_rst,

    input   wire                call,
    input   wire [ID_SIZE-1:0]  inst_id_in,
    input   wire [1:0]          operation,
    input   wire [31:0]         data_in1,
    input   wire [31:0]         data_in2,
    output  wire                fifo_full,

    output  wire [31:0]         data_out,
    output  wire [ID_SIZE-1:0]  inst_id_out
);

    typedef struct{
        reg [31:0] data1;
        reg [31:0] data2;
        reg [ID_SIZE-1:0] inst_id;
        reg [1:0] operation;
    } fifo_entry_t;

endmodule : divider