// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vbranching_unit.h for the primary calling header

#ifndef VERILATED_VBRANCHING_UNIT___024ROOT_H_
#define VERILATED_VBRANCHING_UNIT___024ROOT_H_  // guard

#include "verilated.h"
#include "Vbranching_unit___024root.h"


class Vbranching_unit__Syms;
struct Vbranching_unit_branching_unit__DOT__stage1_t__struct__0 {
    CData/*0:0*/ __PVT__valid;
    CData/*7:0*/ __PVT__inst_id;
    CData/*0:0*/ __PVT__uncond_mode;
    CData/*2:0*/ __PVT__func3;
    IData/*31:0*/ __PVT__data1;
    IData/*31:0*/ __PVT__data2;
    IData/*29:0*/ __PVT__offset;
    IData/*29:0*/ __PVT__pc;
    IData/*29:0*/ __PVT__pred_target;
    CData/*0:0*/ __PVT__pred_taken;

    bool operator==(const Vbranching_unit_branching_unit__DOT__stage1_t__struct__0& rhs) const {
        return __PVT__valid == rhs.__PVT__valid
            && __PVT__inst_id == rhs.__PVT__inst_id
            && __PVT__uncond_mode == rhs.__PVT__uncond_mode
            && __PVT__func3 == rhs.__PVT__func3
            && __PVT__data1 == rhs.__PVT__data1
            && __PVT__data2 == rhs.__PVT__data2
            && __PVT__offset == rhs.__PVT__offset
            && __PVT__pc == rhs.__PVT__pc
            && __PVT__pred_target == rhs.__PVT__pred_target
            && __PVT__pred_taken == rhs.__PVT__pred_taken;
    }
    bool operator!=(const Vbranching_unit_branching_unit__DOT__stage1_t__struct__0& rhs) const {
        return !(*this == rhs);
    }
};
struct Vbranching_unit_branching_unit__DOT__stage2_t__struct__0 {
    CData/*0:0*/ __PVT__valid;
    CData/*7:0*/ __PVT__inst_id;
    CData/*0:0*/ __PVT__real_taken;
    CData/*0:0*/ __PVT__pred_taken;
    IData/*29:0*/ __PVT__pred_target;
    IData/*29:0*/ __PVT__real_target;
    IData/*29:0*/ __PVT__inc_pc;
    CData/*0:0*/ __PVT__regfile_write;

    bool operator==(const Vbranching_unit_branching_unit__DOT__stage2_t__struct__0& rhs) const {
        return __PVT__valid == rhs.__PVT__valid
            && __PVT__inst_id == rhs.__PVT__inst_id
            && __PVT__real_taken == rhs.__PVT__real_taken
            && __PVT__pred_taken == rhs.__PVT__pred_taken
            && __PVT__pred_target == rhs.__PVT__pred_target
            && __PVT__real_target == rhs.__PVT__real_target
            && __PVT__inc_pc == rhs.__PVT__inc_pc
            && __PVT__regfile_write == rhs.__PVT__regfile_write;
    }
    bool operator!=(const Vbranching_unit_branching_unit__DOT__stage2_t__struct__0& rhs) const {
        return !(*this == rhs);
    }
};
struct Vbranching_unit_branching_unit__DOT__stage3_t__struct__0 {
    CData/*0:0*/ __PVT__valid;
    CData/*7:0*/ __PVT__inst_id;
    CData/*0:0*/ __PVT__misprediction;
    CData/*0:0*/ __PVT__taken;
    CData/*0:0*/ __PVT__regfile_write;
    IData/*29:0*/ __PVT__target_address;
    IData/*29:0*/ __PVT__inc_pc;

    bool operator==(const Vbranching_unit_branching_unit__DOT__stage3_t__struct__0& rhs) const {
        return __PVT__valid == rhs.__PVT__valid
            && __PVT__inst_id == rhs.__PVT__inst_id
            && __PVT__misprediction == rhs.__PVT__misprediction
            && __PVT__taken == rhs.__PVT__taken
            && __PVT__regfile_write == rhs.__PVT__regfile_write
            && __PVT__target_address == rhs.__PVT__target_address
            && __PVT__inc_pc == rhs.__PVT__inc_pc;
    }
    bool operator!=(const Vbranching_unit_branching_unit__DOT__stage3_t__struct__0& rhs) const {
        return !(*this == rhs);
    }
};

class alignas(VL_CACHE_LINE_BYTES) Vbranching_unit___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(clk_en,0,0);
    VL_IN8(sync_rst,0,0);
    VL_IN8(call,0,0);
    VL_IN8(flush,0,0);
    VL_IN8(inst_id_in,7,0);
    VL_IN8(unconditional_mode,0,0);
    VL_IN8(func3_in,2,0);
    VL_IN8(prediction_taken,0,0);
    VL_OUT8(flush_and_jump,0,0);
    VL_OUT8(regfile_write,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN(data_in1,31,0);
    VL_IN(data_in2,31,0);
    VL_IN(offset_in,29,0);
    VL_IN(pc_in,29,0);
    VL_IN(predicted_target,29,0);
    VL_OUT(real_target_address,29,0);
    VL_OUT(incremented_pc,31,0);
    IData/*31:0*/ __VactIterCount;
    QData/*32:0*/ branching_unit__DOT__subtraction;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    Vbranching_unit_branching_unit__DOT__stage1_t__struct__0 branching_unit__DOT__stage1;
    Vbranching_unit_branching_unit__DOT__stage2_t__struct__0 branching_unit__DOT__stage2;
    Vbranching_unit_branching_unit__DOT__stage3_t__struct__0 branching_unit__DOT__stage3;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vbranching_unit__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vbranching_unit___024root(Vbranching_unit__Syms* symsp, const char* v__name);
    ~Vbranching_unit___024root();
    VL_UNCOPYABLE(Vbranching_unit___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

std::string VL_TO_STRING(const Vbranching_unit_branching_unit__DOT__stage1_t__struct__0& obj);
std::string VL_TO_STRING(const Vbranching_unit_branching_unit__DOT__stage2_t__struct__0& obj);
std::string VL_TO_STRING(const Vbranching_unit_branching_unit__DOT__stage3_t__struct__0& obj);

#endif  // guard
