// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vbranching_unit__Syms.h"


void Vbranching_unit___024root__trace_chg_0_sub_0(Vbranching_unit___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vbranching_unit___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_chg_0\n"); );
    // Init
    Vbranching_unit___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vbranching_unit___024root*>(voidSelf);
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vbranching_unit___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vbranching_unit___024root__trace_chg_0_sub_0(Vbranching_unit___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_chg_0_sub_0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelfRef.__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+0,(vlSelfRef.branching_unit__DOT__stage1
                             .__PVT__valid));
        bufp->chgCData(oldp+1,(vlSelfRef.branching_unit__DOT__stage1
                               .__PVT__inst_id),8);
        bufp->chgBit(oldp+2,(vlSelfRef.branching_unit__DOT__stage1
                             .__PVT__uncond_mode));
        bufp->chgCData(oldp+3,(vlSelfRef.branching_unit__DOT__stage1
                               .__PVT__func3),3);
        bufp->chgIData(oldp+4,(vlSelfRef.branching_unit__DOT__stage1
                               .__PVT__data1),32);
        bufp->chgIData(oldp+5,(vlSelfRef.branching_unit__DOT__stage1
                               .__PVT__data2),32);
        bufp->chgIData(oldp+6,(vlSelfRef.branching_unit__DOT__stage1
                               .__PVT__offset),30);
        bufp->chgIData(oldp+7,(vlSelfRef.branching_unit__DOT__stage1
                               .__PVT__pc),30);
        bufp->chgIData(oldp+8,(vlSelfRef.branching_unit__DOT__stage1
                               .__PVT__pred_target),30);
        bufp->chgBit(oldp+9,(vlSelfRef.branching_unit__DOT__stage1
                             .__PVT__pred_taken));
        bufp->chgBit(oldp+10,(vlSelfRef.branching_unit__DOT__stage2
                              .__PVT__valid));
        bufp->chgCData(oldp+11,(vlSelfRef.branching_unit__DOT__stage2
                                .__PVT__inst_id),8);
        bufp->chgBit(oldp+12,(vlSelfRef.branching_unit__DOT__stage2
                              .__PVT__real_taken));
        bufp->chgBit(oldp+13,(vlSelfRef.branching_unit__DOT__stage2
                              .__PVT__pred_taken));
        bufp->chgIData(oldp+14,(vlSelfRef.branching_unit__DOT__stage2
                                .__PVT__pred_target),30);
        bufp->chgIData(oldp+15,(vlSelfRef.branching_unit__DOT__stage2
                                .__PVT__real_target),30);
        bufp->chgIData(oldp+16,(vlSelfRef.branching_unit__DOT__stage2
                                .__PVT__inc_pc),30);
        bufp->chgBit(oldp+17,(vlSelfRef.branching_unit__DOT__stage2
                              .__PVT__regfile_write));
        bufp->chgQData(oldp+18,(vlSelfRef.branching_unit__DOT__subtraction),33);
        bufp->chgBit(oldp+20,((0U != (IData)(vlSelfRef.branching_unit__DOT__subtraction))));
        bufp->chgBit(oldp+21,((1U & ((~ (IData)(((vlSelfRef.branching_unit__DOT__stage1
                                                  .__PVT__data1 
                                                  ^ vlSelfRef.branching_unit__DOT__stage1
                                                  .__PVT__data2) 
                                                 >> 0x1fU))) 
                                     & ((vlSelfRef.branching_unit__DOT__stage1
                                         .__PVT__data1 
                                         >> 0x1fU) 
                                        ^ (IData)((vlSelfRef.branching_unit__DOT__subtraction 
                                                   >> 0x1fU)))))));
        bufp->chgBit(oldp+22,((1U & ((0U == (3U & (vlSelfRef.branching_unit__DOT__stage1
                                                   .__PVT__func3 
                                                   >> 1U)))
                                      ? (~ (IData)(
                                                   (0U 
                                                    != (IData)(vlSelfRef.branching_unit__DOT__subtraction))))
                                      : ((1U == (3U 
                                                 & (vlSelfRef.branching_unit__DOT__stage1
                                                    .__PVT__func3 
                                                    >> 1U)))
                                          ? (((~ (IData)(
                                                         ((vlSelfRef.branching_unit__DOT__stage1
                                                           .__PVT__data1 
                                                           ^ vlSelfRef.branching_unit__DOT__stage1
                                                           .__PVT__data2) 
                                                          >> 0x1fU))) 
                                              & ((vlSelfRef.branching_unit__DOT__stage1
                                                  .__PVT__data1 
                                                  >> 0x1fU) 
                                                 ^ (IData)(
                                                           (vlSelfRef.branching_unit__DOT__subtraction 
                                                            >> 0x1fU)))) 
                                             ^ (IData)(
                                                       (vlSelfRef.branching_unit__DOT__subtraction 
                                                        >> 0x1fU)))
                                          : ((2U == 
                                              (3U & 
                                               (vlSelfRef.branching_unit__DOT__stage1
                                                .__PVT__func3 
                                                >> 1U))) 
                                             && (1U 
                                                 & (IData)(
                                                           (vlSelfRef.branching_unit__DOT__subtraction 
                                                            >> 0x20U)))))))));
        bufp->chgBit(oldp+23,((1U & (((0U == (3U & 
                                              (vlSelfRef.branching_unit__DOT__stage1
                                               .__PVT__func3 
                                               >> 1U)))
                                       ? (~ (IData)(
                                                    (0U 
                                                     != (IData)(vlSelfRef.branching_unit__DOT__subtraction))))
                                       : ((1U == (3U 
                                                  & (vlSelfRef.branching_unit__DOT__stage1
                                                     .__PVT__func3 
                                                     >> 1U)))
                                           ? (((~ (IData)(
                                                          ((vlSelfRef.branching_unit__DOT__stage1
                                                            .__PVT__data1 
                                                            ^ vlSelfRef.branching_unit__DOT__stage1
                                                            .__PVT__data2) 
                                                           >> 0x1fU))) 
                                               & ((vlSelfRef.branching_unit__DOT__stage1
                                                   .__PVT__data1 
                                                   >> 0x1fU) 
                                                  ^ (IData)(
                                                            (vlSelfRef.branching_unit__DOT__subtraction 
                                                             >> 0x1fU)))) 
                                              ^ (IData)(
                                                        (vlSelfRef.branching_unit__DOT__subtraction 
                                                         >> 0x1fU)))
                                           : ((2U == 
                                               (3U 
                                                & (vlSelfRef.branching_unit__DOT__stage1
                                                   .__PVT__func3 
                                                   >> 1U))) 
                                              && (1U 
                                                  & (IData)(
                                                            (vlSelfRef.branching_unit__DOT__subtraction 
                                                             >> 0x20U)))))) 
                                     ^ vlSelfRef.branching_unit__DOT__stage1
                                     .__PVT__func3))));
        bufp->chgBit(oldp+24,(vlSelfRef.branching_unit__DOT__stage3
                              .__PVT__valid));
        bufp->chgCData(oldp+25,(vlSelfRef.branching_unit__DOT__stage3
                                .__PVT__inst_id),8);
        bufp->chgBit(oldp+26,(vlSelfRef.branching_unit__DOT__stage3
                              .__PVT__misprediction));
        bufp->chgBit(oldp+27,(vlSelfRef.branching_unit__DOT__stage3
                              .__PVT__taken));
        bufp->chgBit(oldp+28,(vlSelfRef.branching_unit__DOT__stage3
                              .__PVT__regfile_write));
        bufp->chgIData(oldp+29,(vlSelfRef.branching_unit__DOT__stage3
                                .__PVT__target_address),30);
        bufp->chgIData(oldp+30,(vlSelfRef.branching_unit__DOT__stage3
                                .__PVT__inc_pc),30);
    }
    bufp->chgBit(oldp+31,(vlSelfRef.clk));
    bufp->chgBit(oldp+32,(vlSelfRef.clk_en));
    bufp->chgBit(oldp+33,(vlSelfRef.sync_rst));
    bufp->chgBit(oldp+34,(vlSelfRef.call));
    bufp->chgBit(oldp+35,(vlSelfRef.flush));
    bufp->chgCData(oldp+36,(vlSelfRef.inst_id_in),8);
    bufp->chgBit(oldp+37,(vlSelfRef.unconditional_mode));
    bufp->chgCData(oldp+38,(vlSelfRef.func3_in),3);
    bufp->chgIData(oldp+39,(vlSelfRef.data_in1),32);
    bufp->chgIData(oldp+40,(vlSelfRef.data_in2),32);
    bufp->chgIData(oldp+41,(vlSelfRef.offset_in),30);
    bufp->chgIData(oldp+42,(vlSelfRef.pc_in),30);
    bufp->chgIData(oldp+43,(vlSelfRef.predicted_target),30);
    bufp->chgBit(oldp+44,(vlSelfRef.prediction_taken));
    bufp->chgIData(oldp+45,(vlSelfRef.real_target_address),30);
    bufp->chgIData(oldp+46,(vlSelfRef.incremented_pc),32);
    bufp->chgBit(oldp+47,(vlSelfRef.flush_and_jump));
    bufp->chgBit(oldp+48,(vlSelfRef.regfile_write));
}

void Vbranching_unit___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_cleanup\n"); );
    // Init
    Vbranching_unit___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vbranching_unit___024root*>(voidSelf);
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
