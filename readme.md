# Slicudis RISC-V III (SRV3) (W.I.P)
This is an open source RV32IMZfencei CPU that features **out of order execution**.\
The hardware is written on Systen Verilog (IEEE-1800-2017+).

## Out of order execution
SRV3 uses a hybrid algorithm that uses features from Scoreboarding and Tomasulo's algorithm.\
\
Here's a comparasion between different execution algorithms:

- **In-order execution:** In-order issue, In-order execute, In-order commit
- **Scoreboarding:** In-order issue, Out-of-order execute, Out-of-order commit
- **Tomasulo's:** Out-of-order issue, Out-of-order execute, In-order commit
- **SRV3:** In-order issue, Out-of-order execute, In-order commit


## Hardware organization
SRV3 features a 6-stage pipeline: Fetch, Decode, Issue, Execute, Writeback and Commit.\
\
The modules are organized in the following hierarchy:
```
core.sv:
    fetch_stage.sv
    decode_stage.sv:
                regfile.sv
                inst_decoder.sv
                btb.sv
    issue_stage.sv
    execute_stage.sv:
                alu.sv
                multiplication_unit.sv
                branching_unit.sv
                division_unit.sv
                memory_unit.sv
    reorder_buffer.sv
```
The following diagram shows the structure of SRV3:

![SRV3](docs/SRV3.png)

## Current state of the project

- [ ] core.sv
- [x] fetch_stage.sv
- [ ] decode_stage.sv
- [x] regfile.sv
- [x] inst_decoder.sv
- [x] btb.sv
- [ ] issue_stage.sv
- [ ] execute_stage.sv
- [x] alu.sv
- [x] multiplication_unit.sv
- [x] branching_unit.sv
- [ ] division_unit.sv
- [ ] memory_unit.sv
- [x] reorder_buffer.sv

- [ ] test and debug
