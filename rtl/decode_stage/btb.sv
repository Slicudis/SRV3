module btb #(
    parameter ENTRIES = 128,
    parameter GH_SIZE = 4
)(
    input   wire                clk,
    input   wire                clk_en,
    
    input   wire [29:0]         read_address_in,
    input   wire                read_en,

    output  wire [29:0]         target_address,
    output  wire [1:0]          saturaring_ctr_out,
    output  wire [ENTRIES-1:0]  global_history_out,
    output  wire                prediction_taken,

    input   wire                write_en,
    input   wire [29:0]         write_address_in,
    input   wire [29:0]         data_in,
    input   wire [1:0]          sat_ctr_data_in,
    input   wire [GH_SIZE-1:0]  global_history_data_in
);
    // * Target address cache
    localparam BTB_ADDRWIDTH = $clog2(ENTRIES);

    reg [29:0] btb_memory [ENTRIES-1:0];
    reg [29-BTB_ADDRWIDTH:0] btb_tag [ENTRIES-1:0];

    reg [29:0] btb_output_buffer;
    reg [29-BTB_ADDRWIDTH:0] tag_output_buffer;
    reg [29-BTB_ADDRWIDTH:0] compare_tag_buffer;

    // * Branch predictor with saturating counters and local history
    localparam SAT_CTR_AMT = 2**GH_SIZE;

    reg [GH_SIZE-1:0] global_history;
    reg [1:0] saturating_ctr [SAT_CTR_AMT-1:0];

    reg [GH_SIZE-1:0] gh_buffer;
    reg [1:0] sat_ctr_buffer;

    reg write_flag;
    reg [BTB_ADDRWIDTH-1:0] entry_write_address_buffer;
    reg [GH_SIZE-1:0] gh_data_in_buffer;
    reg [1:0] sat_ctr_data_in_buffer;
    reg [29:0] btb_data_in_buffer;

    wire [GH_SIZE-1:0] gh_forwarded = (write_flag) ? gh_data_in_buffer : global_history;

    always_ff @(posedge clk) begin
        if(clk_en) begin
            write_flag <= write_en;
            if(read_en) begin
                btb_output_buffer <= btb_memory[read_address_in[BTB_ADDRWIDTH-1:0]];
                tag_output_buffer <= btb_tag[read_address_in[29:BTB_ADDRWIDTH]];
                compare_tag_buffer <= read_address_in[29-BTB_ADDRWIDTH:0];
                gh_buffer <= gh_forwarded;
                sat_ctr_buffer <= saturating_ctr[gh_forwarded];
            end
            if(write_en) begin
                btb_memory[write_address_in[BTB_ADDRWIDTH-1:0]] <= data_in;
                btb_tag[write_address_in[BTB_ADDRWIDTH-1:0]] <= write_address_in[29:BTB_ADDRWIDTH];
                entry_write_address_buffer <= write_address_in[BTB_ADDRWIDTH-1:0];
                gh_data_in_buffer <= global_history_data_in;
                sat_ctr_data_in_buffer <= sat_ctr_data_in;
                btb_data_in_buffer <= data_in;
            end
        end
    end

    wire btb_miss = ((read_address_in[BTB_ADDRWIDTH-1:0] == entry_write_address_buffer) && write_en) ?
                        1'b1 :
                        (tag_output_buffer != compare_tag_buffer);

    assign prediction_taken = !btb_miss && sat_ctr_buffer[1];

    assign target_address = ((read_address_in[BTB_ADDRWIDTH-1:0] == entry_write_address_buffer) && write_flag) ? 
                                btb_data_in_buffer :
                                btb_output_buffer;

    assign saturaring_ctr_out = sat_ctr_buffer;
    assign global_history_out = gh_buffer;

endmodule : btb

//todo: remake this in a way that makes all the memory be able to be inferred in M9K BRAM