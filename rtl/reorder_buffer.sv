module reorder_buffer #(
    parameter ENTRIES = 32,
    parameter ID_WIDTH = 8
)(
    input   wire                clk,
    input   wire                clk_en,
    input   wire                sync_rst,
    
    // * Issue stage connections
    input   wire                allocate,
    input   wire                speculative_mode,
    input   wire [1:0]          exe_unit_id,
    input   wire [4:0]          writeback_address_in,
    input   wire [ID_WIDTH-1:0] instruction_id,
    output  wire                rob_full,

    // * Branching unit connections
    input   wire                branch_result_ready,
    input   wire                flush_speculative,  //0 = Validate speculative instructions

    // * ALU connections
    input   wire [ID_WIDTH-1:0] alu_inst_id,
    input   wire [31:0]         alu_data,
    input   wire                alu_result_valid,

    // * Multiplier connections
    input   wire [ID_WIDTH-1:0] multiplier_inst_id,
    input   wire [31:0]         multiplier_data,
    input   wire                multiplier_result_valid,

    // * Divider connections
    input   wire [ID_WIDTH-1:0] divider_inst_id,
    input   wire [31:0]         divider_data,
    input   wire                divider_result_valid,

    // * Memory unit connections
    input   wire [ID_WIDTH-1:0] memory_unit_inst_id,
    input   wire [31:0]         memory_unit_data,
    input   wire                memory_unit_data_valid,

    // * Writeback/flush and branch pins
    output  wire                regfile_we,
    output  wire [31:0]         data_out,
    output  wire [4:0]          writeback_address
);
    localparam PTR_WIDTH = $clog2(ENTRIES);

    typedef struct{
        reg [31:0] data;
        reg [4:0] wb_address;       //Writeback address
        reg [ID_WIDTH-1:0] inst_id;
        reg [1:0] exe_unit_sel;     //0=ALU, 1=MUL, 2=DIV, 3=MEM
        reg speculative_mode;
        reg valid;
        reg ready;
    } entry_t;

    entry_t entry[ENTRIES-1:0];
    reg [PTR_WIDTH-1:0] head_ptr;
    reg [PTR_WIDTH-1:0] tail_ptr;

    wire head_ptr_max = (head_ptr == (PTR_WIDTH)'(ENTRIES-1));
    wire tail_ptr_max = (tail_ptr == (PTR_WIDTH)'(ENTRIES-1));

    assign rob_full = (tail_ptr_max ? 'h0 : (tail_ptr + 1)) == head_ptr;
    
    always_ff @(posedge clk) begin : Ptr_ff
        if(sync_rst) begin
            head_ptr <= 'h0;
            tail_ptr <= 'h0;
        end else if(clk_en) begin
            if(allocate && !rob_full) begin
                tail_ptr <= tail_ptr_max ? (PTR_WIDTH)'(0) : (tail_ptr + 1);
            end
            if(entry[head_ptr].ready && entry[head_ptr].valid && !entry[head_ptr].speculative_mode) begin
                head_ptr <= head_ptr_max ? (PTR_WIDTH)'(0) : (head_ptr + 1);
            end
        end
    end

    genvar i;
    generate
        for(i = 0; i < ENTRIES; i++) begin : Entries_ff

            logic selected_exe_available;
            logic [ID_WIDTH-1:0] selected_inst_id;
            logic [31:0] selected_exe_data;

            always_comb begin : Unit_sel_mux
                case(entry[i].exe_unit_sel)
                    2'h0: begin
                        selected_exe_available = alu_result_valid;
                        selected_inst_id = alu_inst_id;
                        selected_exe_data = alu_data;
                        end
                    2'h1: begin
                        selected_exe_available = multiplier_result_valid;
                        selected_inst_id = multiplier_inst_id;
                        selected_exe_data = multiplier_data;
                        end
                    2'h2: begin
                        selected_exe_available = divider_result_valid;
                        selected_inst_id = divider_inst_id;
                        selected_exe_data = divider_data;
                        end
                    2'h3: begin
                        selected_exe_available = memory_unit_data_valid;
                        selected_inst_id = memory_unit_inst_id;
                        selected_exe_data = memory_unit_data;
                    end
                    default: /*nothing*/;
                endcase
            end

            always_ff @(posedge clk) begin
                if(sync_rst || (clk_en && entry[i].speculative_mode && flush_speculative)) begin
                    entry[i].valid <= 'b0;
                    entry[i].speculative_mode <= 'b0;
                end else if(clk_en) begin
                    if(allocate && (i == tail_ptr)) begin
                        entry[i].valid <= 'b1;
                        entry[i].wb_address <= writeback_address_in;
                        entry[i].exe_unit_sel <= exe_unit_id;
                        entry[i].speculative_mode <= speculative_mode;
                        entry[i].ready <= 'b0;
                        entry[i].inst_id <= instruction_id;
                    end else begin
                        if(branch_result_ready) entry[i].speculative_mode <= 'b0;
                        if(entry[i].valid && !entry[i].ready && selected_exe_available && (selected_inst_id == entry[i].inst_id)) begin
                            entry[i].data <= selected_exe_data;
                            entry[i].ready <= 'b1;
                        end
                    end
                end
            end

        end
    endgenerate
    
    assign regfile_we = entry[head_ptr].ready && entry[head_ptr].valid && !entry[head_ptr].speculative_mode;
    assign writeback_address = entry[head_ptr].wb_address;
    assign data_out = entry[head_ptr].data;

endmodule : reorder_buffer
