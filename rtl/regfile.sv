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

    input   wire        write_en,
    input   wire        reserve,

    input   wire [4:0]  reserve_address,
    input   wire [4:0]  rs1_address,
    input   wire [4:0]  rs2_address,
    input   wire [4:0]  write_address,
    input   wire [31:0] data_in,

    output  wire [31:0] rs1_data,
    output  wire [31:0] rs2_data,

    output  wire        rs1_reserved,
    output  wire        rs2_reserved,
    output  wire        write_reserved
);
    reg [31:0] register_file [31:1];
    wire [31:0] regfile_read [31:0];
    wire [31:0] regfile_reset_array [31:1];

    reg scoreboard [31:1]; //1 = reserved, 0 = available
    wire scoreboard_read [31:0];
    wire scoreboard_reset_array [31:1];

    genvar i;
    generate
        for(i = 0; i < 32; i++) begin : Wire_Assignments
            if(i == 0) begin
                assign regfile_read[0] = 32'h0;
                assign scoreboard_read[0] = 1'b0;
            end else begin
                assign regfile_read[i] = register_file[i];
                assign scoreboard_read[i] = scoreboard[i];
                assign regfile_reset_array[i] = 32'h0;
                assign scoreboard_reset_array[i] = 1'b0;
            end

        end
    endgenerate

    always_ff @(posedge clk) begin
        if(sync_rst) begin
            scoreboard <= scoreboard_reset_array;
        end else if(clk_en) begin
            if(write_en) begin
                register_file[write_address] <= data_in;
                scoreboard[write_address] <= 1'b0;
            end
            if  (reserve && !(write_en && (write_address == reserve_address))) begin
                scoreboard[reserve_address] <= 1'b1;
            end
        end
    end

    assign rs1_data = regfile_read[rs1_address];
    assign rs2_data = regfile_read[rs2_address];
    assign rs1_reserved = scoreboard_read[rs1_address];
    assign rs2_reserved = scoreboard_read[rs2_address];
    assign write_reserved = scoreboard_read[write_address];

endmodule : regfile
