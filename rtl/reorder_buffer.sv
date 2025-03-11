module reorder_buffer #(
    parameter ENTRIES = 32,
    parameter ID_WIDTH = 8,

    parameter ALU_FIFO_SIZE = 4,
    parameter MUL_FIFO_SIZE = 4,
    parameter DIV_FIFO_SIZE = 4,
    parameter MEM_FIFO_SIZE = 4
)(
    input   wire                clk,
    input   wire                clk_en,
    input   wire                sync_rst,
    
    // * Issue stage connections
    input   wire                allocate,
    input   wire                speculative_mode,
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
    output  wire                stall_alu,

    // * Multiplier connections
    input   wire [ID_WIDTH-1:0] multiplier_inst_id,
    input   wire [31:0]         multiplier_data,
    input   wire                multiplier_result_valid,
    output  wire                stall_multiplier,

    // * Divider connections
    input   wire [ID_WIDTH-1:0] divider_inst_id,
    input   wire [31:0]         divider_data,
    input   wire                divider_result_valid,
    output  wire                stall_divider,

    // * Memory unit connections
    input   wire [ID_WIDTH-1:0] memory_unit_inst_id,
    input   wire [31:0]         memory_unit_data,
    input   wire                memory_unit_data_valid,
    output  wire                stall_memory_unit,

    // * Writeback/flush and branch pins
    output  wire                regfile_we,
    output  wire [31:0]         data_out,
    output  wire [4:0]          writeback_address
);

///
    typedef struct{
        reg [31:0] writeback_data;
        reg [ID_WIDTH-1:0] inst_id;
    } fifo_entry_t;

    localparam ALU_FIFO_PTR_WIDTH = $clog2(ALU_FIFO_SIZE);
    reg [ALU_FIFO_PTR_WIDTH-1:0] alu_head_ptr;
    reg [ALU_FIFO_PTR_WIDTH-1:0] alu_tail_ptr;
    wire alu_head_ptr_max = (alu_head_ptr == (ALU_FIFO_PTR_WIDTH)'(ALU_FIFO_SIZE-1));
    wire alu_tail_ptr_max = (alu_tail_ptr == (ALU_FIFO_PTR_WIDTH)'(ALU_FIFO_SIZE-1));
    wire alu_fifo_full = (alu_tail_ptr_max ? (alu_tail_ptr + 1) : 'h0) == alu_head_ptr;
    wire alu_fifo_empty = (alu_head_ptr == alu_tail_ptr);
    fifo_entry_t alu_fifo [ALU_FIFO_SIZE-1:0];

    always_ff @(posedge clk) begin : ALU_FIFO_ff
        if(sync_rst) begin
            alu_head_ptr <= 'h0;
            alu_tail_ptr <= 'h0;
        end else if(clk_en) begin
            if(!alu_fifo_full && alu_result_valid) begin
                alu_tail_ptr <= alu_tail_ptr_max ? 'h0 : (alu_tail_ptr + 1);
                alu_fifo[alu_tail_ptr].writeback_data <= alu_data;
                alu_fifo[alu_tail_ptr].inst_id <= alu_inst_id;
            end
            if(!alu_fifo_empty && fifo_pop_selectors[0]) begin
                alu_head_ptr <= alu_head_ptr_max ? 'h0 : (alu_head_ptr + 1);
            end
        end
    end

    assign stall_alu = alu_fifo_full;

///
    localparam MUL_FIFO_PTR_WIDTH = $clog2(MUL_FIFO_SIZE);
    reg [MUL_FIFO_PTR_WIDTH-1:0] mul_head_ptr;
    reg [MUL_FIFO_PTR_WIDTH-1:0] mul_tail_ptr;
    wire mul_head_ptr_max = (mul_head_ptr == (MUL_FIFO_PTR_WIDTH)'(MUL_FIFO_SIZE-1));
    wire mul_tail_ptr_max = (mul_tail_ptr == (MUL_FIFO_PTR_WIDTH)'(MUL_FIFO_SIZE-1));
    wire mul_fifo_full = (mul_tail_ptr_max ? (mul_tail_ptr + 1) : 'h0) == mul_head_ptr;
    wire mul_fifo_empty = (mul_head_ptr == mul_tail_ptr);
    fifo_entry_t mul_fifo [MUL_FIFO_SIZE-1:0];

    always_ff @(posedge clk) begin : MUL_FIFO_ff
        if(sync_rst) begin
            mul_head_ptr <= 'h0;
            mul_tail_ptr <= 'h0;
        end else if(clk_en) begin
            if(!mul_fifo_full && multiplier_result_valid) begin
                mul_tail_ptr <= mul_tail_ptr_max ? 'h0 : (mul_tail_ptr + 1);
                mul_fifo[mul_tail_ptr].writeback_data <= multiplier_data;
                mul_fifo[mul_tail_ptr].inst_id <= multiplier_inst_id;
            end
            if(!mul_fifo_empty && fifo_pop_selectors[1]) begin
                mul_head_ptr <= mul_head_ptr_max ? 'h0 : (mul_head_ptr + 1);
            end
        end
    end

    assign stall_multiplier = mul_fifo_full;

///
    localparam DIV_FIFO_PTR_WIDTH = $clog2(DIV_FIFO_SIZE);
    reg [DIV_FIFO_PTR_WIDTH-1:0] div_head_ptr;
    reg [DIV_FIFO_PTR_WIDTH-1:0] div_tail_ptr;
    wire div_head_ptr_max = (div_head_ptr == (DIV_FIFO_PTR_WIDTH)'(DIV_FIFO_PTR_WIDTH-1));
    wire div_tail_ptr_max = (div_tail_ptr == (DIV_FIFO_PTR_WIDTH)'(DIV_FIFO_PTR_WIDTH-1));
    wire div_fifo_full = (div_tail_ptr_max ? (div_tail_ptr + 1) : 'h0) == div_head_ptr;
    wire div_fifo_empty = (div_head_ptr == div_tail_ptr);
    fifo_entry_t div_fifo [DIV_FIFO_SIZE-1:0];

    always_ff @(posedge clk) begin : DIV_FIFO_ff
        if(sync_rst) begin
            div_head_ptr <= 'h0;
            div_tail_ptr <= 'h0;
        end else if(clk_en) begin
            if(!div_fifo_full && divider_result_valid) begin
                div_tail_ptr <= div_tail_ptr_max ? 'h0 : (div_tail_ptr + 1);
                div_fifo[div_tail_ptr].writeback_data <= divider_data;
                div_fifo[div_tail_ptr].inst_id <= divider_inst_id;
            end
            if(!div_fifo_empty && fifo_pop_selectors[2]) begin
                div_head_ptr <= div_head_ptr_max ? 'h0 : (mul_head_ptr + 1);
            end
        end
    end

    assign stall_divider = div_fifo_full;

///
    localparam MEM_FIFO_PTR_WIDTH = $clog2(MEM_FIFO_SIZE);
    reg [MEM_FIFO_PTR_WIDTH-1:0] mem_head_ptr;
    reg [MEM_FIFO_PTR_WIDTH-1:0] mem_tail_ptr;
    wire mem_head_ptr_max = (mem_head_ptr == (MEM_FIFO_PTR_WIDTH)'(MEM_FIFO_PTR_WIDTH-1));
    wire mem_tail_ptr_max = (mem_tail_ptr == (MEM_FIFO_PTR_WIDTH)'(MEM_FIFO_PTR_WIDTH-1));
    wire mem_fifo_full = (mem_tail_ptr_max ? (mem_tail_ptr + 1) : 'h0) == mem_head_ptr;
    wire mem_fifo_empty = (mem_head_ptr == mem_tail_ptr);
    fifo_entry_t mem_fifo [MEM_FIFO_SIZE-1:0];

    always_ff @(posedge clk) begin : MEM_FIFO_ff
        if(sync_rst) begin
            mem_head_ptr <= 'h0;
            mem_tail_ptr <= 'h0;
        end else if(clk_en) begin
            if(!mem_fifo_full && memory_unit_data_valid) begin
                mem_tail_ptr <= mem_tail_ptr_max ? 'h0 : (mem_tail_ptr + 1);
                mem_fifo[mem_tail_ptr].writeback_data <= memory_unit_data;
                mem_fifo[mem_tail_ptr].inst_id <= memory_unit_inst_id;
            end
            if(!mem_fifo_empty && fifo_pop_selectors[3]) begin
                mem_head_ptr <= mem_head_ptr_max ? 'h0 : (mul_head_ptr + 1);
            end
        end
    end

    assign stall_memory_unit = mem_fifo_full;

///
    function ID_less_than(
        input [ID_WIDTH-1:0] a,
        input [ID_WIDTH-1:0] b
    );
        return (a[ID_WIDTH-2:0] < b[ID_WIDTH-2:0]) ^^ (a[ID_WIDTH-1] ^^ b[ID_WIDTH-1]);
    endfunction

    wire [1:0] fifo_mux_sel;
    wire [3:0] fifo_pop_selectors;

    wire sel_alu =  (ID_less_than(alu_fifo[alu_head_ptr].inst_id, mul_fifo[mul_head_ptr].inst_id) || mul_fifo_empty) &&
                    (ID_less_than(alu_fifo[alu_head_ptr].inst_id, div_fifo[div_head_ptr].inst_id) || div_fifo_empty) &&
                    (ID_less_than(alu_fifo[alu_head_ptr].inst_id, mem_fifo[mem_head_ptr].inst_id) || mem_fifo_empty) &&
                    !alu_fifo_empty;

    wire sel_mul =  (ID_less_than(mul_fifo[mul_head_ptr].inst_id, alu_fifo[alu_head_ptr].inst_id) || alu_fifo_empty) &&
                    (ID_less_than(mul_fifo[mul_head_ptr].inst_id, div_fifo[div_head_ptr].inst_id) || div_fifo_empty) &&
                    (ID_less_than(mul_fifo[mul_head_ptr].inst_id, mem_fifo[mem_head_ptr].inst_id) || mem_fifo_empty) &&
                    !mul_fifo_empty;

    wire sel_div =  (ID_less_than(div_fifo[div_head_ptr].inst_id, alu_fifo[alu_head_ptr].inst_id) || alu_fifo_empty) &&
                    (ID_less_than(div_fifo[div_head_ptr].inst_id, mul_fifo[mul_head_ptr].inst_id) || mul_fifo_empty) &&
                    (ID_less_than(div_fifo[div_head_ptr].inst_id, mem_fifo[mem_head_ptr].inst_id) || mem_fifo_empty) &&
                    !div_fifo_empty;

    wire sel_mem =  (ID_less_than(div_fifo[div_head_ptr].inst_id, alu_fifo[alu_head_ptr].inst_id) || alu_fifo_empty) &&
                    (ID_less_than(div_fifo[div_head_ptr].inst_id, mul_fifo[mul_head_ptr].inst_id) || mul_fifo_empty) &&
                    (ID_less_than(div_fifo[div_head_ptr].inst_id, mem_fifo[mem_head_ptr].inst_id) || mem_fifo_empty) &&
                    !mem_fifo_empty;

    generate
        wire [3:0] eucp = {sel_div, sel_mem, sel_mul, sel_alu};
        wire [3:0] ihb = -(eucp) & eucp;
        wire [1:0] encode_vals [3:0];
        wire [1:0] ored_vals [3:0];

        for(i = 0; i < 4; i++) begin : BitScanForwards
            assign encode_vals[i] = i[1:0] & {2{ihb[i]}};
            if(i == 0) assign ored_vals[i] = encode_vals[i];
            else assign ored_vals[i] = encode_vals[i] | ored_vals[i-1];
        end

        assign fifo_mux_sel = ored_vals[3];
        assign fifo_pop_selectors = ihb;
    endgenerate

    logic [31:0] entry_input_data;
    logic [ID_WIDTH-1:0] target_id;

    always_comb begin : InputDataMux
        case(fifo_mux_sel)
            2'b00: begin    //ALU
                entry_input_data = alu_fifo[alu_head_ptr].writeback_data;
                target_id = alu_fifo[alu_head_ptr].inst_id;
                end
            2'b01: begin    //Multiplier
                entry_input_data = mul_fifo[mul_head_ptr].writeback_data;
                target_id = mul_fifo[mul_head_ptr].inst_id;
                end
            2'b10: begin    //Memory
                entry_input_data = mem_fifo[mem_head_ptr].writeback_data;
                target_id = mem_fifo[mem_head_ptr].inst_id;
                end
            2'b11: begin    //Divider
                entry_input_data = div_fifo[div_head_ptr].writeback_data;
                target_id = div_fifo[div_head_ptr].inst_id;
                end
            default: begin
                entry_input_data = 'x;
                target_id = 'x;
                end
        endcase
    end

///
    localparam PTR_WIDTH = $clog2(ENTRIES);

    typedef struct{
        reg [31:0] data;
        reg [4:0] wb_address;       //Writeback address
        reg [ID_WIDTH-1:0] inst_id;
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

            always_ff @(posedge clk) begin
                if(sync_rst || (clk_en && flush_speculative && branch_result_ready)) begin
                    entry[i].valid <= 'b0;
                    entry[i].speculative_mode <= 'b0;
                end else if(clk_en) begin
                    if(allocate && !rob_full && (i == tail_ptr)) begin
                        entry[i].valid <= 'b1;
                        entry[i].ready <= 'b0;
                        entry[i].speculative_mode <= speculative_mode;
                        entry[i].inst_id <= instruction_id;
                        entry[i].wb_address <= writeback_address_in;
                    end else if((entry[i].inst_id == target_id) && (|fifo_pop_selectors)) begin
                        entry[i].ready <= 'b1;
                        entry[i].data <= entry_input_data;
                    end
                    if((branch_result_ready && !flush_speculative)) entry[i].speculative_mode <= 'b0;
                end
            end

        end
    endgenerate
    
    assign regfile_we = entry[head_ptr].ready && entry[head_ptr].valid && !entry[head_ptr].speculative_mode;
    assign writeback_address = entry[head_ptr].wb_address;
    assign data_out = entry[head_ptr].data;

endmodule : reorder_buffer
