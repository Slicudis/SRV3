#include <verilated.h>
#include <verilated_vcd_c.h>

#define MAX_SIM_TIME 199999
vluint64_t sim_time = 0;

main(int argc, char** argv, char** env) {
  printf("testing...\n");
  TARGET_TB *test = new TARGET_TB;
  Verilated::traceEverOn(true);
  VerilatedVcdC *m_trace = new VerilatedVcdC;
  test->trace(m_trace, 5);
  m_trace->open("sim.vcd");

  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);

  while (sim_time < MAX_SIM_TIME && !contextp->gotFinish()) {
    if(sim_time % 2 == 1) {
        test->sync_rst = sim_time < 3;
        test->clk_en = sim_time > 5;
    }

    //-----------------------------
    test->eval();
    m_trace->dump(sim_time);
    test->clk ^= 1;
    sim_time++;
  }

  m_trace->close();
  delete test;
  exit(EXIT_SUCCESS);
}