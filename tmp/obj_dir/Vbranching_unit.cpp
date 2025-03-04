// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vbranching_unit__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vbranching_unit::Vbranching_unit(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vbranching_unit__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , clk_en{vlSymsp->TOP.clk_en}
    , sync_rst{vlSymsp->TOP.sync_rst}
    , call{vlSymsp->TOP.call}
    , flush{vlSymsp->TOP.flush}
    , inst_id_in{vlSymsp->TOP.inst_id_in}
    , unconditional_mode{vlSymsp->TOP.unconditional_mode}
    , func3_in{vlSymsp->TOP.func3_in}
    , prediction_taken{vlSymsp->TOP.prediction_taken}
    , flush_and_jump{vlSymsp->TOP.flush_and_jump}
    , regfile_write{vlSymsp->TOP.regfile_write}
    , data_in1{vlSymsp->TOP.data_in1}
    , data_in2{vlSymsp->TOP.data_in2}
    , offset_in{vlSymsp->TOP.offset_in}
    , pc_in{vlSymsp->TOP.pc_in}
    , predicted_target{vlSymsp->TOP.predicted_target}
    , real_target_address{vlSymsp->TOP.real_target_address}
    , incremented_pc{vlSymsp->TOP.incremented_pc}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vbranching_unit::Vbranching_unit(const char* _vcname__)
    : Vbranching_unit(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vbranching_unit::~Vbranching_unit() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vbranching_unit___024root___eval_debug_assertions(Vbranching_unit___024root* vlSelf);
#endif  // VL_DEBUG
void Vbranching_unit___024root___eval_static(Vbranching_unit___024root* vlSelf);
void Vbranching_unit___024root___eval_initial(Vbranching_unit___024root* vlSelf);
void Vbranching_unit___024root___eval_settle(Vbranching_unit___024root* vlSelf);
void Vbranching_unit___024root___eval(Vbranching_unit___024root* vlSelf);

void Vbranching_unit::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vbranching_unit::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vbranching_unit___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vbranching_unit___024root___eval_static(&(vlSymsp->TOP));
        Vbranching_unit___024root___eval_initial(&(vlSymsp->TOP));
        Vbranching_unit___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vbranching_unit___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vbranching_unit::eventsPending() { return false; }

uint64_t Vbranching_unit::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vbranching_unit::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vbranching_unit___024root___eval_final(Vbranching_unit___024root* vlSelf);

VL_ATTR_COLD void Vbranching_unit::final() {
    Vbranching_unit___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vbranching_unit::hierName() const { return vlSymsp->name(); }
const char* Vbranching_unit::modelName() const { return "Vbranching_unit"; }
unsigned Vbranching_unit::threads() const { return 1; }
void Vbranching_unit::prepareClone() const { contextp()->prepareClone(); }
void Vbranching_unit::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vbranching_unit::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vbranching_unit___024root__trace_decl_types(VerilatedVcd* tracep);

void Vbranching_unit___024root__trace_init_top(Vbranching_unit___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vbranching_unit___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vbranching_unit___024root*>(voidSelf);
    Vbranching_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vbranching_unit___024root__trace_decl_types(tracep);
    Vbranching_unit___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vbranching_unit___024root__trace_register(Vbranching_unit___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vbranching_unit::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vbranching_unit::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vbranching_unit___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
