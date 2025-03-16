/*
    [Module]: RV32I register file & scoreboard

    [Description]: Dual-read register file with 31 registers and a scoreboard with 32 entries.

    [NOTE]: Sync_rst only resets the scoreboard. The registers will have to be reset on
    boot by the firmware.
*/

module regfile(
    input   wire        clk,
    input   wire        clk_en,
    input   wire        sync_rst,

    // * From decode stage
    input   wire        read_en,
    input   wire [4:0]  reserve_address,
    input   wire [4:0]  rs1_address,
    input   wire [4:0]  rs2_address,
    input   wire        reserve,

    // * From commit stage
    input   wire        write_en,
    input   wire [4:0]  write_address,
    input   wire [31:0] data_in,

    // * To issue stage
    output  wire [31:0] rs1_data,
    output  wire [31:0] rs2_data,
    output  wire        rs1_reserved,
    output  wire        rs2_reserved
);
    reg [31:0] register_file [31:0];

    reg scoreboard [31:1]; //1 = reserved, 0 = available
    wire scoreboard_read [31:0];
    wire scoreboard_reset_array [31:1];

    genvar i;
    generate
        for(i = 0; i < 32; i++) begin : Wire_Assignments
            if(i == 0) begin
                assign scoreboard_read[0] = 1'b0;
            end else begin
                assign scoreboard_read[i] = scoreboard[i];
                assign scoreboard_reset_array[i] = 1'b0;
            end

        end
    endgenerate

    reg [31:0] regfile_buffer1;
    reg [31:0] regfile_buffer2;
    reg scoreboard_buffer1;
    reg scoreboard_buffer2;
    reg [31:0] write_buffer;
    reg [4:0] write_address_buffer;
    reg write_flag;

    always_ff @(posedge clk) begin
        if(sync_rst) begin
            scoreboard <= scoreboard_reset_array;
        end else if(clk_en) begin
            if(read_en) begin
                regfile_buffer1 <= register_file[rs1_address];
                regfile_buffer2 <= register_file[rs2_address];
                scoreboard_buffer1 <= scoreboard_read[rs1_address];
                scoreboard_buffer2 <= scoreboard_read[rs2_address];
            end
            write_address_buffer <= write_address;
            write_flag <= write_en;
            if(write_en) begin
                write_buffer <= data_in;
                register_file[write_address] <= data_in;
                scoreboard[write_address] <= 1'b0;
            end
            if(reserve && !(write_en && (write_address == reserve_address))) begin
                scoreboard[reserve_address] <= 1'b1;
            end
        end
    end

    assign rs1_data = (write_flag && (rs1_address == write_address_buffer)) ? write_buffer : regfile_buffer1;
    assign rs2_data = (write_flag && (rs2_address == write_address_buffer)) ? write_buffer : regfile_buffer2;
    assign rs1_reserved = (write_flag && (rs1_address == write_address_buffer)) ? scoreboard_buffer1 : 'b0;
    assign rs2_reserved = (write_flag && (rs2_address == write_address_buffer)) ? scoreboard_buffer2 : 'b0;

endmodule : regfile
