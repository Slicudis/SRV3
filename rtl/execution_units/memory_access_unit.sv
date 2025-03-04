module memory_access_unit(
    input   wire            clk,
    input   wire            clk_en,
    input   wire            sync_rst,

    // * Internal core connections

    input   wire            call,
    input   wire [3:0]      operation,
    input   wire [31:0]     data_in,
    input   wire [31:0]     bus_data_in,
    input   wire [31:0]     rs1_data,
    input   wire [11:0]     offset_immediate,
    input   wire [3:0]      data_size,

    output  wire            busy,
    output  wire [31:0]     data_out,

    // * Data bus connections

    input   wire            bus_data_ready,
    input   wire            data_cache_busy,
    input   wire            external_bus_lock,
    input   wire            forced_external_bus_lock,
    input   wire            external_bus_write,

    output  wire [31:0]     bus_data_out,
    output  wire            bus_lock,
    output  wire            bus_write,
    output  wire            bus_read
);
    reg [2:0] state;
    reg reservation_status;

    reg [31:0] rs1_buffer;
    reg [31:0] data_in_buffer;
    reg []

endmodule : memory_access_unit