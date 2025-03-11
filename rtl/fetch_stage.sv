module fetch_stage(
    input   wire        clk,                //Clock
    input   wire        clk_en,             //Enable clock
    input   wire        sync_rst,           //Synchronous reset
    input   wire        write_en,           //Write enable
    input   wire [29:0] data_in,            //Write data
    output  wire [29:0] data_out,           //Data out to pipeline
    output  wire [29:0] forwarded_data_out  //Data out to instruction address
);
    reg [29:0] pc;
    wire [29:0] next_pc = write_en ? (data_in) : (pc + 1);

    always_ff @(posedge clk) begin
        if(sync_rst) pc <= 30'h3fffffff;
        else if(clk_en) pc <= next_pc;
    end
    
    assign data_out = pc;
    assign forwarded_data_out = next_pc;

endmodule : fetch_stage

