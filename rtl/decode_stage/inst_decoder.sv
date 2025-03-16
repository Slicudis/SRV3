module inst_decoder(
    input   wire    [6:0]   major_opcode_in,
    input   wire            func7_bit0,
    output  logic   [15:0]  ctr_word
);

    logic [15:0] int_ctr_word;

    always_comb begin
        casez(major_opcode_in[6:2])
            5'b01100: int_ctr_word = 16'b1_0_0_0_0_00_0_0_00_00_1_00 | func7_bit0; //OP type
            5'b00100: int_ctr_word = 16'b1_0_0_0_0_00_0_0_01_00_1_00;              //OP-IMM type
            5'b00000: int_ctr_word = 16'b1_0_0_0_0_00_0_0_00_00_1_10;              //Load type
            5'b01000: int_ctr_word = 16'b1_1_0_1_0_00_0_1_00_00_1_10;              //Store type
            5'b11000: int_ctr_word = 16'b0_0_0_0_1_01_0_0_00_00_0_00;              //Branch type
            5'b11011: int_ctr_word = 16'b1_0_0_1_1_00_0_0_11_01_1_00;              //JAL type
            5'b11001: int_ctr_word = 16'b1_0_0_1_1_10_1_0_11_01_1_00;              //JALR type
            5'b01101: int_ctr_word = 16'b1_0_0_1_0_00_0_0_10_10_1_00;              //LUI type
            5'b00101: int_ctr_word = 16'b1_0_0_1_0_00_0_0_10_01_1_00;              //AUIPC type
            5'b00011: int_ctr_word = 16'b0_0_0_0_0_00_0_0_00_00_1_10;              //MISC-MEM type
            default:  int_ctr_word = 16'b0_0_0_0_0_00_0_0_00_00_0_00;              //DEFAULT NOP
        endcase
    end

    assign ctr_word = &major_opcode_in[1:0] ? int_ctr_word : 'h0;

/*
    [1:0]   data_exe_unit_sel: ALU, MUL, MEM, DIV
    [2]     call_data_exe_unit
    [4:3]   data1_sel: rs1, pc, 0x00000000
    [6:5]   data2_sel: rs2, I-Imm, U-imm, 0x00000004
    [7]     mem_offset_sel: I-Imm, S-Imm
    [8]     branch_base_sel: pc, rs1
    [10:9]  branch_offset_sel: J-imm, B-imm, I-imm
    [11]    call_branching_unit
    [12]    unconditional_mode (Branching unit) / store_mode / force_add
    [13]    fence_mode (LSU)
    [14]    force_dest_0 / icache_flush (if fence_mode == 1)
    [15]    regfile_we
*/

endmodule : inst_decoder