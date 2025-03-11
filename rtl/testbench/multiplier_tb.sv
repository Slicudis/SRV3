module multiplier_tb(
    input clk,
    input clk_en,
    input sync_rst
);
    wire [1:0] operation_in = 0;
    logic [31:0] data_in1 = 'h1;//'h3de;
    logic [31:0] data_in2 = 'h1;//'h57e;

    wire call = result_ready || (cycle_count == 1);

    wire flush = 0;
    wire result_ready;
    wire [31:0] data_out;
    wire [7:0] inst_id_in;

    wire [7:0] inst_id_out;
    wire output_valid;

    int cycle_count = 0; // @suppress "Register initialization in declaration. Consider using an explicit reset instead."
    always_ff @(posedge clk) if(clk_en) cycle_count <= cycle_count + 1;

    wire [31:0] actual_mult_result = data_in1 * data_in2;

    //int failed = 0;

    always @(posedge clk) begin
        //if(failed == 0) begin
            //data_in1 <= $urandom_range(0, 4096);
            //data_in2 <= $urandom_range(0, 4096);
            //if(actual_mult_result == data_out) $display("Passed: %H * %H = %H", $signed(data_in1), $signed(data_in2), $signed(data_out));
            //else begin
            //    $display("Failed: %H * %H != %H (= %H)", $signed(data_in1), $signed(data_in2), $signed(data_out), $signed(actual_mult_result));
            //    failed <= 1;
            //end
        //end
    end

    multiplication_unit #(
        .ID_SIZE(8)
    ) pipelined_multiplier_instance (
        .clk(clk),
        .clk_en(clk_en),
        .sync_rst(sync_rst),
        .flush(flush),
        .data_in1(data_in1),
        .data_in2(data_in2),
        .operation_in(operation_in),
        .call(call),
        .inst_id_in(inst_id_in),
        .data_out(data_out),
        .inst_id_out(inst_id_out),
        .output_valid(output_valid)
    );

endmodule : multiplier_tb
