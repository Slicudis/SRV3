// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vbranching_unit__pch.h"
#include "Vbranching_unit.h"
#include "Vbranching_unit___024root.h"

// FUNCTIONS
Vbranching_unit__Syms::~Vbranching_unit__Syms()
{
}

Vbranching_unit__Syms::Vbranching_unit__Syms(VerilatedContext* contextp, const char* namep, Vbranching_unit* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(18);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}
