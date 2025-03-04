// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vbranching_unit.h for the primary calling header

#include "Vbranching_unit__pch.h"
#include "Vbranching_unit__Syms.h"
#include "Vbranching_unit___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbranching_unit___024root___dump_triggers__act(Vbranching_unit___024root* vlSelf);
#endif  // VL_DEBUG

void Vbranching_unit___024root___eval_triggers__act(Vbranching_unit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbranching_unit___024root___eval_triggers__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.set(0U, ((IData)(vlSelfRef.clk) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vbranching_unit___024root___dump_triggers__act(vlSelf);
    }
#endif
}
