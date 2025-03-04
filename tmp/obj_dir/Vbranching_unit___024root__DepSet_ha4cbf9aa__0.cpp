// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vbranching_unit.h for the primary calling header

#include "Vbranching_unit__pch.h"
#include "Vbranching_unit___024root.h"

void Vbranching_unit___024root___eval_act(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
}

void Vbranching_unit___024root___nba_sequent__TOP__0(Vbranching_unit___024root* vlSelf);

void Vbranching_unit___024root___eval_nba(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vbranching_unit___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void Vbranching_unit___024root___nba_sequent__TOP__0(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___nba_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.sync_rst) {
        vlSelfRef.branching_unit__DOT__stage3.__PVT__valid = 0U;
    } else if (vlSelfRef.clk_en) {
        vlSelfRef.branching_unit__DOT__stage3.__PVT__inst_id 
            = vlSelfRef.branching_unit__DOT__stage2
            .__PVT__inst_id;
        vlSelfRef.branching_unit__DOT__stage3.__PVT__misprediction 
            = ((vlSelfRef.branching_unit__DOT__stage2
                .__PVT__pred_taken ^ vlSelfRef.branching_unit__DOT__stage2
                .__PVT__real_taken) | (vlSelfRef.branching_unit__DOT__stage2
                                       .__PVT__real_target 
                                       != vlSelfRef.branching_unit__DOT__stage2
                                       .__PVT__pred_target));
        vlSelfRef.branching_unit__DOT__stage3.__PVT__taken 
            = vlSelfRef.branching_unit__DOT__stage2
            .__PVT__real_taken;
        vlSelfRef.branching_unit__DOT__stage3.__PVT__regfile_write 
            = vlSelfRef.branching_unit__DOT__stage2
            .__PVT__regfile_write;
        vlSelfRef.branching_unit__DOT__stage3.__PVT__target_address 
            = vlSelfRef.branching_unit__DOT__stage2
            .__PVT__real_target;
        vlSelfRef.branching_unit__DOT__stage3.__PVT__inc_pc 
            = vlSelfRef.branching_unit__DOT__stage2
            .__PVT__inc_pc;
    }
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
    if (((IData)(vlSelfRef.sync_rst) | ((IData)(vlSelfRef.clk_en) 
                                        & (IData)(vlSelfRef.flush)))) {
        vlSelfRef.branching_unit__DOT__stage2.__PVT__valid = 0U;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__valid = 0U;
    } else if (vlSelfRef.clk_en) {
        vlSelfRef.branching_unit__DOT__stage2.__PVT__valid 
            = vlSelfRef.branching_unit__DOT__stage1
            .__PVT__valid;
        vlSelfRef.branching_unit__DOT__stage2.__PVT__inst_id 
            = vlSelfRef.branching_unit__DOT__stage1
            .__PVT__inst_id;
        vlSelfRef.branching_unit__DOT__stage2.__PVT__real_taken 
            = (1U & ((((0U == (3U & (vlSelfRef.branching_unit__DOT__stage1
                                     .__PVT__func3 
                                     >> 1U))) ? (~ (IData)(
                                                           (0U 
                                                            != (IData)(vlSelfRef.branching_unit__DOT__subtraction))))
                        : ((1U == (3U & (vlSelfRef.branching_unit__DOT__stage1
                                         .__PVT__func3 
                                         >> 1U))) ? 
                           (((~ (IData)(((vlSelfRef.branching_unit__DOT__stage1
                                          .__PVT__data1 
                                          ^ vlSelfRef.branching_unit__DOT__stage1
                                          .__PVT__data2) 
                                         >> 0x1fU))) 
                             & ((vlSelfRef.branching_unit__DOT__stage1
                                 .__PVT__data1 >> 0x1fU) 
                                ^ (IData)((vlSelfRef.branching_unit__DOT__subtraction 
                                           >> 0x1fU)))) 
                            ^ (IData)((vlSelfRef.branching_unit__DOT__subtraction 
                                       >> 0x1fU))) : 
                           ((2U == (3U & (vlSelfRef.branching_unit__DOT__stage1
                                          .__PVT__func3 
                                          >> 1U))) 
                            && (1U & (IData)((vlSelfRef.branching_unit__DOT__subtraction 
                                              >> 0x20U)))))) 
                      ^ vlSelfRef.branching_unit__DOT__stage1
                      .__PVT__func3) | vlSelfRef.branching_unit__DOT__stage1
                     .__PVT__uncond_mode));
        vlSelfRef.branching_unit__DOT__stage2.__PVT__pred_taken 
            = vlSelfRef.branching_unit__DOT__stage1
            .__PVT__pred_taken;
        vlSelfRef.branching_unit__DOT__stage2.__PVT__pred_target 
            = vlSelfRef.branching_unit__DOT__stage1
            .__PVT__pred_target;
        vlSelfRef.branching_unit__DOT__stage2.__PVT__real_target 
            = (0x3fffffffU & ((IData)(vlSelfRef.branching_unit__DOT__stage1
                                      .__PVT__pc) + (IData)(vlSelfRef.branching_unit__DOT__stage1
                                                            .__PVT__offset)));
        vlSelfRef.branching_unit__DOT__stage2.__PVT__inc_pc 
            = (0x3fffffffU & ((IData)(1U) + (IData)(vlSelfRef.branching_unit__DOT__stage1
                                                    .__PVT__pc)));
        vlSelfRef.branching_unit__DOT__stage2.__PVT__regfile_write 
            = vlSelfRef.branching_unit__DOT__stage1
            .__PVT__uncond_mode;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__valid 
            = vlSelfRef.call;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__inst_id 
            = vlSelfRef.inst_id_in;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__uncond_mode 
            = vlSelfRef.unconditional_mode;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__func3 
            = vlSelfRef.func3_in;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__data1 
            = vlSelfRef.data_in1;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__data2 
            = vlSelfRef.data_in2;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__offset 
            = vlSelfRef.offset_in;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__pc 
            = vlSelfRef.pc_in;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__pred_target 
            = vlSelfRef.predicted_target;
        vlSelfRef.branching_unit__DOT__stage1.__PVT__pred_taken 
            = vlSelfRef.prediction_taken;
    }
    vlSelfRef.branching_unit__DOT__subtraction = (0x1ffffffffULL 
                                                  & ((QData)((IData)(vlSelfRef.branching_unit__DOT__stage1
                                                                     .__PVT__data1)) 
                                                     - (QData)((IData)(vlSelfRef.branching_unit__DOT__stage1
                                                                       .__PVT__data2))));
}

void Vbranching_unit___024root___eval_triggers__act(Vbranching_unit___024root* vlSelf);

bool Vbranching_unit___024root___eval_phase__act(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_phase__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vbranching_unit___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vbranching_unit___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vbranching_unit___024root___eval_phase__nba(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_phase__nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vbranching_unit___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbranching_unit___024root___dump_triggers__nba(Vbranching_unit___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vbranching_unit___024root___dump_triggers__act(Vbranching_unit___024root* vlSelf);
#endif  // VL_DEBUG

void Vbranching_unit___024root___eval(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vbranching_unit___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../rtl/../rtl/branching_unit.sv", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vbranching_unit___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../rtl/../rtl/branching_unit.sv", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vbranching_unit___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vbranching_unit___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vbranching_unit___024root___eval_debug_assertions(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_debug_assertions\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelfRef.clk_en & 0xfeU))) {
        Verilated::overWidthError("clk_en");}
    if (VL_UNLIKELY((vlSelfRef.sync_rst & 0xfeU))) {
        Verilated::overWidthError("sync_rst");}
    if (VL_UNLIKELY((vlSelfRef.call & 0xfeU))) {
        Verilated::overWidthError("call");}
    if (VL_UNLIKELY((vlSelfRef.flush & 0xfeU))) {
        Verilated::overWidthError("flush");}
    if (VL_UNLIKELY((vlSelfRef.unconditional_mode & 0xfeU))) {
        Verilated::overWidthError("unconditional_mode");}
    if (VL_UNLIKELY((vlSelfRef.func3_in & 0xf8U))) {
        Verilated::overWidthError("func3_in");}
    if (VL_UNLIKELY((vlSelfRef.offset_in & 0xc0000000U))) {
        Verilated::overWidthError("offset_in");}
    if (VL_UNLIKELY((vlSelfRef.pc_in & 0xc0000000U))) {
        Verilated::overWidthError("pc_in");}
    if (VL_UNLIKELY((vlSelfRef.predicted_target & 0xc0000000U))) {
        Verilated::overWidthError("predicted_target");}
    if (VL_UNLIKELY((vlSelfRef.prediction_taken & 0xfeU))) {
        Verilated::overWidthError("prediction_taken");}
}
#endif  // VL_DEBUG

std::string VL_TO_STRING(const Vbranching_unit_branching_unit__DOT__stage1_t__struct__0& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root::VL_TO_STRING\n"); );
    // Body
    std::string out;
    out += "'{valid:" + VL_TO_STRING(obj.__PVT__valid);
        out += ", inst_id:" + VL_TO_STRING(obj.__PVT__inst_id);
        out += ", uncond_mode:" + VL_TO_STRING(obj.__PVT__uncond_mode);
        out += ", func3:" + VL_TO_STRING(obj.__PVT__func3);
        out += ", data1:" + VL_TO_STRING(obj.__PVT__data1);
        out += ", data2:" + VL_TO_STRING(obj.__PVT__data2);
        out += ", offset:" + VL_TO_STRING(obj.__PVT__offset);
        out += ", pc:" + VL_TO_STRING(obj.__PVT__pc);
        out += ", pred_target:" + VL_TO_STRING(obj.__PVT__pred_target);
        out += ", pred_taken:" + VL_TO_STRING(obj.__PVT__pred_taken);
        out += "}";
    return out;
}

std::string VL_TO_STRING(const Vbranching_unit_branching_unit__DOT__stage2_t__struct__0& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root::VL_TO_STRING\n"); );
    // Body
    std::string out;
    out += "'{valid:" + VL_TO_STRING(obj.__PVT__valid);
        out += ", inst_id:" + VL_TO_STRING(obj.__PVT__inst_id);
        out += ", real_taken:" + VL_TO_STRING(obj.__PVT__real_taken);
        out += ", pred_taken:" + VL_TO_STRING(obj.__PVT__pred_taken);
        out += ", pred_target:" + VL_TO_STRING(obj.__PVT__pred_target);
        out += ", real_target:" + VL_TO_STRING(obj.__PVT__real_target);
        out += ", inc_pc:" + VL_TO_STRING(obj.__PVT__inc_pc);
        out += ", regfile_write:" + VL_TO_STRING(obj.__PVT__regfile_write);
        out += "}";
    return out;
}

std::string VL_TO_STRING(const Vbranching_unit_branching_unit__DOT__stage3_t__struct__0& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root::VL_TO_STRING\n"); );
    // Body
    std::string out;
    out += "'{valid:" + VL_TO_STRING(obj.__PVT__valid);
        out += ", inst_id:" + VL_TO_STRING(obj.__PVT__inst_id);
        out += ", misprediction:" + VL_TO_STRING(obj.__PVT__misprediction);
        out += ", taken:" + VL_TO_STRING(obj.__PVT__taken);
        out += ", regfile_write:" + VL_TO_STRING(obj.__PVT__regfile_write);
        out += ", target_address:" + VL_TO_STRING(obj.__PVT__target_address);
        out += ", inc_pc:" + VL_TO_STRING(obj.__PVT__inc_pc);
        out += "}";
    return out;
}
