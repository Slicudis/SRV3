// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vbranching_unit__Syms.h"


VL_ATTR_COLD void Vbranching_unit___024root__trace_init_sub__TOP__0(Vbranching_unit___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_init_sub__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+32,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+33,0,"clk_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"sync_rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+35,0,"call",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+36,0,"flush",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+37,0,"inst_id_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+38,0,"unconditional_mode",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+39,0,"func3_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+40,0,"data_in1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+41,0,"data_in2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+42,0,"offset_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+43,0,"pc_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+44,0,"predicted_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBit(c+45,0,"prediction_taken",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+46,0,"real_target_address",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+47,0,"incremented_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+48,0,"flush_and_jump",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+49,0,"regfile_write",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("branching_unit", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+50,0,"ID_SIZE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+32,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+33,0,"clk_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"sync_rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+35,0,"call",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+36,0,"flush",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+37,0,"inst_id_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+38,0,"unconditional_mode",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+39,0,"func3_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+40,0,"data_in1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+41,0,"data_in2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+42,0,"offset_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+43,0,"pc_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+44,0,"predicted_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBit(c+45,0,"prediction_taken",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+46,0,"real_target_address",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+47,0,"incremented_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+48,0,"flush_and_jump",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+49,0,"regfile_write",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("stage1", VerilatedTracePrefixType::STRUCT_UNPACKED);
    tracep->declBit(c+1,0,"valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"inst_id",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+3,0,"uncond_mode",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"func3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+5,0,"data1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+6,0,"data2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"offset",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+8,0,"pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+9,0,"pred_target",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBit(c+10,0,"pred_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("stage2", VerilatedTracePrefixType::STRUCT_UNPACKED);
    tracep->declBit(c+11,0,"valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+12,0,"inst_id",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+13,0,"real_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"pred_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"pred_target",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+16,0,"real_target",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+17,0,"inc_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBit(c+18,0,"regfile_write",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declQuad(c+19,0,"subtraction",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 32,0);
    tracep->declBit(c+21,0,"not_zero",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+22,0,"overflow",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+23,0,"int_branch_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+24,0,"branch_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("stage3", VerilatedTracePrefixType::STRUCT_UNPACKED);
    tracep->declBit(c+25,0,"valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+26,0,"inst_id",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+27,0,"misprediction",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+29,0,"regfile_write",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+30,0,"target_address",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+31,0,"inc_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vbranching_unit___024root__trace_init_top(Vbranching_unit___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_init_top\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vbranching_unit___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vbranching_unit___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vbranching_unit___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vbranching_unit___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vbranching_unit___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vbranching_unit___024root__trace_register(Vbranching_unit___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_register\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vbranching_unit___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vbranching_unit___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vbranching_unit___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vbranching_unit___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vbranching_unit___024root__trace_const_0_sub_0(Vbranching_unit___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vbranching_unit___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_const_0\n"); );
    // Init
    Vbranching_unit___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vbranching_unit___024root*>(voidSelf);
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vbranching_unit___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vbranching_unit___024root__trace_const_0_sub_0(Vbranching_unit___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_const_0_sub_0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+50,(8U),32);
}

VL_ATTR_COLD void Vbranching_unit___024root__trace_full_0_sub_0(Vbranching_unit___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vbranching_unit___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_full_0\n"); );
    // Init
    Vbranching_unit___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vbranching_unit___024root*>(voidSelf);
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vbranching_unit___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vbranching_unit___024root__trace_full_0_sub_0(Vbranching_unit___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root__trace_full_0_sub_0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelfRef.branching_unit__DOT__stage1
                          .__PVT__valid));
    bufp->fullCData(oldp+2,(vlSelfRef.branching_unit__DOT__stage1
                            .__PVT__inst_id),8);
    bufp->fullBit(oldp+3,(vlSelfRef.branching_unit__DOT__stage1
                          .__PVT__uncond_mode));
    bufp->fullCData(oldp+4,(vlSelfRef.branching_unit__DOT__stage1
                            .__PVT__func3),3);
    bufp->fullIData(oldp+5,(vlSelfRef.branching_unit__DOT__stage1
                            .__PVT__data1),32);
    bufp->fullIData(oldp+6,(vlSelfRef.branching_unit__DOT__stage1
                            .__PVT__data2),32);
    bufp->fullIData(oldp+7,(vlSelfRef.branching_unit__DOT__stage1
                            .__PVT__offset),30);
    bufp->fullIData(oldp+8,(vlSelfRef.branching_unit__DOT__stage1
                            .__PVT__pc),30);
    bufp->fullIData(oldp+9,(vlSelfRef.branching_unit__DOT__stage1
                            .__PVT__pred_target),30);
    bufp->fullBit(oldp+10,(vlSelfRef.branching_unit__DOT__stage1
                           .__PVT__pred_taken));
    bufp->fullBit(oldp+11,(vlSelfRef.branching_unit__DOT__stage2
                           .__PVT__valid));
    bufp->fullCData(oldp+12,(vlSelfRef.branching_unit__DOT__stage2
                             .__PVT__inst_id),8);
    bufp->fullBit(oldp+13,(vlSelfRef.branching_unit__DOT__stage2
                           .__PVT__real_taken));
    bufp->fullBit(oldp+14,(vlSelfRef.branching_unit__DOT__stage2
                           .__PVT__pred_taken));
    bufp->fullIData(oldp+15,(vlSelfRef.branching_unit__DOT__stage2
                             .__PVT__pred_target),30);
    bufp->fullIData(oldp+16,(vlSelfRef.branching_unit__DOT__stage2
                             .__PVT__real_target),30);
    bufp->fullIData(oldp+17,(vlSelfRef.branching_unit__DOT__stage2
                             .__PVT__inc_pc),30);
    bufp->fullBit(oldp+18,(vlSelfRef.branching_unit__DOT__stage2
                           .__PVT__regfile_write));
    bufp->fullQData(oldp+19,(vlSelfRef.branching_unit__DOT__subtraction),33);
    bufp->fullBit(oldp+21,((0U != (IData)(vlSelfRef.branching_unit__DOT__subtraction))));
    bufp->fullBit(oldp+22,((1U & ((~ (IData)(((vlSelfRef.branching_unit__DOT__stage1
                                               .__PVT__data1 
                                               ^ vlSelfRef.branching_unit__DOT__stage1
                                               .__PVT__data2) 
                                              >> 0x1fU))) 
                                  & ((vlSelfRef.branching_unit__DOT__stage1
                                      .__PVT__data1 
                                      >> 0x1fU) ^ (IData)(
                                                          (vlSelfRef.branching_unit__DOT__subtraction 
                                                           >> 0x1fU)))))));
    bufp->fullBit(oldp+23,((1U & ((0U == (3U & (vlSelfRef.branching_unit__DOT__stage1
                                                .__PVT__func3 
                                                >> 1U)))
                                   ? (~ (IData)((0U 
                                                 != (IData)(vlSelfRef.branching_unit__DOT__subtraction))))
                                   : ((1U == (3U & 
                                              (vlSelfRef.branching_unit__DOT__stage1
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
                                       : ((2U == (3U 
                                                  & (vlSelfRef.branching_unit__DOT__stage1
                                                     .__PVT__func3 
                                                     >> 1U))) 
                                          && (1U & (IData)(
                                                           (vlSelfRef.branching_unit__DOT__subtraction 
                                                            >> 0x20U)))))))));
    bufp->fullBit(oldp+24,((1U & (((0U == (3U & (vlSelfRef.branching_unit__DOT__stage1
                                                 .__PVT__func3 
                                                 >> 1U)))
                                    ? (~ (IData)((0U 
                                                  != (IData)(vlSelfRef.branching_unit__DOT__subtraction))))
                                    : ((1U == (3U & 
                                               (vlSelfRef.branching_unit__DOT__stage1
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
                                        : ((2U == (3U 
                                                   & (vlSelfRef.branching_unit__DOT__stage1
                                                      .__PVT__func3 
                                                      >> 1U))) 
                                           && (1U & (IData)(
                                                            (vlSelfRef.branching_unit__DOT__subtraction 
                                                             >> 0x20U)))))) 
                                  ^ vlSelfRef.branching_unit__DOT__stage1
                                  .__PVT__func3))));
    bufp->fullBit(oldp+25,(vlSelfRef.branching_unit__DOT__stage3
                           .__PVT__valid));
    bufp->fullCData(oldp+26,(vlSelfRef.branching_unit__DOT__stage3
                             .__PVT__inst_id),8);
    bufp->fullBit(oldp+27,(vlSelfRef.branching_unit__DOT__stage3
                           .__PVT__misprediction));
    bufp->fullBit(oldp+28,(vlSelfRef.branching_unit__DOT__stage3
                           .__PVT__taken));
    bufp->fullBit(oldp+29,(vlSelfRef.branching_unit__DOT__stage3
                           .__PVT__regfile_write));
    bufp->fullIData(oldp+30,(vlSelfRef.branching_unit__DOT__stage3
                             .__PVT__target_address),30);
    bufp->fullIData(oldp+31,(vlSelfRef.branching_unit__DOT__stage3
                             .__PVT__inc_pc),30);
    bufp->fullBit(oldp+32,(vlSelfRef.clk));
    bufp->fullBit(oldp+33,(vlSelfRef.clk_en));
    bufp->fullBit(oldp+34,(vlSelfRef.sync_rst));
    bufp->fullBit(oldp+35,(vlSelfRef.call));
    bufp->fullBit(oldp+36,(vlSelfRef.flush));
    bufp->fullCData(oldp+37,(vlSelfRef.inst_id_in),8);
    bufp->fullBit(oldp+38,(vlSelfRef.unconditional_mode));
    bufp->fullCData(oldp+39,(vlSelfRef.func3_in),3);
    bufp->fullIData(oldp+40,(vlSelfRef.data_in1),32);
    bufp->fullIData(oldp+41,(vlSelfRef.data_in2),32);
    bufp->fullIData(oldp+42,(vlSelfRef.offset_in),30);
    bufp->fullIData(oldp+43,(vlSelfRef.pc_in),30);
    bufp->fullIData(oldp+44,(vlSelfRef.predicted_target),30);
    bufp->fullBit(oldp+45,(vlSelfRef.prediction_taken));
    bufp->fullIData(oldp+46,(vlSelfRef.real_target_address),30);
    bufp->fullIData(oldp+47,(vlSelfRef.incremented_pc),32);
    bufp->fullBit(oldp+48,(vlSelfRef.flush_and_jump));
    bufp->fullBit(oldp+49,(vlSelfRef.regfile_write));
}
