// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vbranching_unit.h for the primary calling header

#include "Vbranching_unit__pch.h"
#include "Vbranching_unit___024root.h"

VL_ATTR_COLD void Vbranching_unit___024root___eval_static(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_static\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vbranching_unit___024root___eval_initial(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_initial\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vbranching_unit___024root___eval_final(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_final\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbranching_unit___024root___dump_triggers__stl(Vbranching_unit___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vbranching_unit___024root___eval_phase__stl(Vbranching_unit___024root* vlSelf);

VL_ATTR_COLD void Vbranching_unit___024root___eval_settle(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_settle\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vbranching_unit___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../rtl/../rtl/branching_unit.sv", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vbranching_unit___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbranching_unit___024root___dump_triggers__stl(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___dump_triggers__stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vbranching_unit___024root___stl_sequent__TOP__0(Vbranching_unit___024root* vlSelf);
VL_ATTR_COLD void Vbranching_unit___024root____Vm_traceActivitySetAll(Vbranching_unit___024root* vlSelf);

VL_ATTR_COLD void Vbranching_unit___024root___eval_stl(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vbranching_unit___024root___stl_sequent__TOP__0(vlSelf);
        Vbranching_unit___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vbranching_unit___024root___stl_sequent__TOP__0(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___stl_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.branching_unit__DOT__subtraction = (0x1ffffffffULL 
                                                  & ((QData)((IData)(vlSelfRef.branching_unit__DOT__stage1
                                                                     .__PVT__data1)) 
                                                     - (QData)((IData)(vlSelfRef.branching_unit__DOT__stage1
                                                                       .__PVT__data2))));
    vlSelfRef.real_target_address = (vlSelfRef.branching_unit__DOT__stage3
                                     .__PVT__taken ? vlSelfRef.branching_unit__DOT__stage3
                                     .__PVT__target_address
                                      : vlSelfRef.branching_unit__DOT__stage3
                                     .__PVT__inc_pc);
    vlSelfRef.incremented_pc = vlSelfRef.branching_unit__DOT__stage3
        .__PVT__inc_pc;
    vlSelfRef.flush_and_jump = vlSelfRef.branching_unit__DOT__stage3
        .__PVT__misprediction;
    vlSelfRef.regfile_write = vlSelfRef.branching_unit__DOT__stage3
        .__PVT__regfile_write;
}

VL_ATTR_COLD void Vbranching_unit___024root___eval_triggers__stl(Vbranching_unit___024root* vlSelf);

VL_ATTR_COLD bool Vbranching_unit___024root___eval_phase__stl(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_phase__stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vbranching_unit___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vbranching_unit___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbranching_unit___024root___dump_triggers__act(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___dump_triggers__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbranching_unit___024root___dump_triggers__nba(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___dump_triggers__nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vbranching_unit___024root____Vm_traceActivitySetAll(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root____Vm_traceActivitySetAll\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vbranching_unit___024root___ctor_var_reset(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___ctor_var_reset\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->clk_en = VL_RAND_RESET_I(1);
    vlSelf->sync_rst = VL_RAND_RESET_I(1);
    vlSelf->call = VL_RAND_RESET_I(1);
    vlSelf->flush = VL_RAND_RESET_I(1);
    vlSelf->inst_id_in = VL_RAND_RESET_I(8);
    vlSelf->unconditional_mode = VL_RAND_RESET_I(1);
    vlSelf->func3_in = VL_RAND_RESET_I(3);
    vlSelf->data_in1 = VL_RAND_RESET_I(32);
    vlSelf->data_in2 = VL_RAND_RESET_I(32);
    vlSelf->offset_in = VL_RAND_RESET_I(30);
    vlSelf->pc_in = VL_RAND_RESET_I(30);
    vlSelf->predicted_target = VL_RAND_RESET_I(30);
    vlSelf->prediction_taken = VL_RAND_RESET_I(1);
    vlSelf->real_target_address = VL_RAND_RESET_I(30);
    vlSelf->incremented_pc = VL_RAND_RESET_I(32);
    vlSelf->flush_and_jump = VL_RAND_RESET_I(1);
    vlSelf->regfile_write = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage1.__PVT__valid = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage1.__PVT__inst_id = VL_RAND_RESET_I(8);
    vlSelf->branching_unit__DOT__stage1.__PVT__uncond_mode = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage1.__PVT__func3 = VL_RAND_RESET_I(3);
    vlSelf->branching_unit__DOT__stage1.__PVT__data1 = VL_RAND_RESET_I(32);
    vlSelf->branching_unit__DOT__stage1.__PVT__data2 = VL_RAND_RESET_I(32);
    vlSelf->branching_unit__DOT__stage1.__PVT__offset = VL_RAND_RESET_I(30);
    vlSelf->branching_unit__DOT__stage1.__PVT__pc = VL_RAND_RESET_I(30);
    vlSelf->branching_unit__DOT__stage1.__PVT__pred_target = VL_RAND_RESET_I(30);
    vlSelf->branching_unit__DOT__stage1.__PVT__pred_taken = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage2.__PVT__valid = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage2.__PVT__inst_id = VL_RAND_RESET_I(8);
    vlSelf->branching_unit__DOT__stage2.__PVT__real_taken = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage2.__PVT__pred_taken = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage2.__PVT__pred_target = VL_RAND_RESET_I(30);
    vlSelf->branching_unit__DOT__stage2.__PVT__real_target = VL_RAND_RESET_I(30);
    vlSelf->branching_unit__DOT__stage2.__PVT__inc_pc = VL_RAND_RESET_I(30);
    vlSelf->branching_unit__DOT__stage2.__PVT__regfile_write = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__subtraction = VL_RAND_RESET_Q(33);
    vlSelf->branching_unit__DOT__stage3.__PVT__valid = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage3.__PVT__inst_id = VL_RAND_RESET_I(8);
    vlSelf->branching_unit__DOT__stage3.__PVT__misprediction = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage3.__PVT__taken = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage3.__PVT__regfile_write = VL_RAND_RESET_I(1);
    vlSelf->branching_unit__DOT__stage3.__PVT__target_address = VL_RAND_RESET_I(30);
    vlSelf->branching_unit__DOT__stage3.__PVT__inc_pc = VL_RAND_RESET_I(30);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
