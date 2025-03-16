module btb #(
    parameter ENTRIES = 128,
    parameter LH_SIZE = 4
)(
    input   wire                clk,
    input   wire                clk_en,
    
    input   wire                pre_read_en,
    input   wire [29:0]         pre_read_address_in,

    input   wire [29:0]         read_address_in,
    input   wire                read_en,

    output  wire [29:0]         target_address,
    output  wire [1:0]          saturaring_ctr_out,
    output  wire [ENTRIES-1:0]  local_history_out,
    output  wire                prediction_taken,

    input   wire                write_en,
    input   wire [29:0]         write_address_in,
    input   wire [29:0]         data_in,
    input   wire [1:0]          sat_ctr_data_in,
    input   wire [LH_SIZE-1:0]  local_history_data_in
);
    // * Target address cache
    localparam BTB_ADDRWIDTH = $clog2(ENTRIES);

    reg [29:0] btb_memory [ENTRIES-1:0];
    reg [29-BTB_ADDRWIDTH:0] btb_tag [ENTRIES-1:0];

    reg [29:0] btb_output_buffer;
    reg btb_miss_buffer;

    // * Branch predictor with saturating counters and local history
    localparam SAT_CTR_AMT = 2**LH_SIZE;

    reg [LH_SIZE-1:0] local_history [ENTRIES-1:0];
    reg [1:0] saturating_ctr [ENTRIES-1:0][SAT_CTR_AMT-1:0];

    reg [LH_SIZE-1:0] lh_buffer;
    reg [1:0] sat_ctr_buffer;

    reg write_flag;
    reg [BTB_ADDRWIDTH-1:0] entry_write_address_buffer;
    reg [LH_SIZE-1:0] lh_data_in_buffer;
    reg [1:0] sat_ctr_data_in_buffer;
    reg [29:0] btb_data_in_buffer;

    always_ff @(posedge clk) begin
        if(clk_en) begin
            write_flag <= write_en;
            if(pre_read_en) begin
                lh_buffer <= (pre_read_address_in[BTB_ADDRWIDTH-1:0] == entry_write_address_buffer) ?
                lh_data_in_buffer :
                local_history[pre_read_address_in[BTB_ADDRWIDTH-1:0]];
            end
            if(read_en) begin
                btb_output_buffer <= btb_memory[read_address_in[BTB_ADDRWIDTH-1:0]];

                btb_miss_buffer <= btb_tag[read_address_in[29:BTB_ADDRWIDTH]] != read_address_in[29:BTB_ADDRWIDTH];

                sat_ctr_buffer <= (read_address_in[BTB_ADDRWIDTH-1:0] == entry_write_address_buffer) ?
                                        sat_ctr_data_in_buffer :
                                        saturating_ctr[read_address_in[BTB_ADDRWIDTH-1:0]][lh_buffer];
            end
            if(write_en) begin
                btb_memory[write_address_in[BTB_ADDRWIDTH-1:0]] <= data_in;
                btb_tag[write_address_in[BTB_ADDRWIDTH-1:0]] <= write_address_in[29:BTB_ADDRWIDTH];
                entry_write_address_buffer <= write_address_in[BTB_ADDRWIDTH-1:0];
                lh_data_in_buffer <= local_history_data_in;
                sat_ctr_data_in_buffer <= sat_ctr_data_in;
                btb_data_in_buffer <= data_in;
            end
        end
    end

    wire btb_miss = (read_address_in[BTB_ADDRWIDTH-1:0] == entry_write_address_buffer) ?
                        1'b1 :
                        btb_miss_buffer;

    wire [1:0] selected_saturating_counter = (read_address_in[BTB_ADDRWIDTH-1:0] == entry_write_address_buffer) ?
                                                sat_ctr_data_in :
                                                sat_ctr_buffer;

    assign prediction_taken = !btb_miss && selected_saturating_counter[1];

    assign target_address = (read_address_in[BTB_ADDRWIDTH-1:0] == entry_write_address_buffer) ? 
                                btb_data_in_buffer :
                                btb_output_buffer;

    assign saturaring_ctr_out = selected_saturating_counter;
    assign local_history_out = (read_address_in[BTB_ADDRWIDTH-1:0] == entry_write_address_buffer) ?
                                lh_data_in_buffer :
                                lh_buffer;

endmodule : btb

//todo: remake this in a way that makes all the memory be able to be inferred in M9K BRAM