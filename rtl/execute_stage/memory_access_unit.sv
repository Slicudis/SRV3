module memory_access_unit #(
    parameter ID_SIZE = 8
)(
    input   wire                clk,
    input   wire                clk_en,
    input   wire                sync_rst,

    // * Internal core connections

    input   wire                call,
    input   wire [ID_SIZE-1:0]  inst_id_in,
    input   wire                operation, //0 = read, 1 = write
    input   wire [31:0]         data_in,
    input   wire [31:0]         rs1_data,
    input   wire [11:0]         offset_immediate,
    input   wire [3:0]          data_type,

    output  wire                stall,
    output  wire [31:0]         data_out,

    // * Data bus connections

    input   wire                bus_data_ready,
    input   wire                data_cache_busy,
    input   wire                external_bus_lock,

    output  wire [31:0]         bus_data_out,
    output  wire                bus_lock,
    output  wire                bus_write,
    output  wire                bus_read
);

///
    // * --- Stage 1 ---

    typedef struct{
        reg [ID_SIZE-1:0] inst_id;
        reg [31:0] store_data;
        reg [31:0] base;
        reg [11:0] offset;
        reg [2:0] data_type;
        reg operation;
        reg valid;
    } stage1_t;

    stage1_t stage1;

    always_ff @(posedge clk) begin : Stage1_ff
        if(sync_rst) begin
            stage1.valid <= 'b0;
        end else if(clk_en) begin
            stage1.inst_id <= inst_id_in;
            stage1.store_data <= data_in;
            stage1.base <= rs1_data;
            stage1.offset <= offset_immediate;
            stage1.data_type <= data_type;
            stage1.operation <= operation;
            stage1.valid <= call;
        end
    end

///
    // * --- Stage 2 ---

    typedef struct{
        reg valid;
        reg [ID_SIZE-1:0] inst_id;
        reg [29:0] address;
        reg [31:0] store_data;
        reg [3:0] byte_mask;
        reg [2:0] data_type;
        reg operation;
    } stage2_t;

    stage2_t stage2;

    wire [31:0] calculated_address = stage1.base + {{20{stage1.offset[11]}}, stage1.offset};
    logic [3:0] calculated_mask;
    logic [31:0] adjusted_data;

    always_comb begin
        case(data_type[1:0])
            2'h0: begin
                calculated_mask = 4'b1000 >> calculated_address[1:0];
                adjusted_data = stage1.store_data >> (calculated_address[1:0]<<3);
                end
            2'h1: begin
                calculated_mask = 4'b1100 >> (calculated_address[1]<<1);
                adjusted_data = {stage1.store_data[7:0], stage1.store_data[15:8]} >> (calculated_address[1]<<1);
                end 
            2'h2: begin
                calculated_mask = 4'b1111;
                adjusted_data = {stage1.store_data[7:0], stage1.store_data[15:8], stage1.store_data[23:16], stage1.store_data[31:24]};
                end
            default: begin
                calculated_mask = 'x;
                adjusted_data = 'x;
                end
        endcase
    end
    

    always_ff @(posedge clk) begin : Stage2_ff
        if(sync_rst) begin
            stage2.valid <= 'b0;
        end else if(clk_en) begin
            stage2.valid <= stage1.valid;
            stage2.inst_id <= stage1.inst_id;
            stage2.store_data <= adjusted_data;
            stage2.address <= calculated_address[31:2];
            stage2.byte_mask <= calculated_mask;
        end
    end

endmodule : memory_access_unit