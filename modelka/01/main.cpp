#include "main.hpp"

int main() {
  double P_total_wait = 0.0;
  double P_PC1_downtime = 0.0;
  double P_PC2_downtime = 0.0;
  double P_in_sys = 0.0;

  for (int expr = 0; expr < 100; expr++) {
    SMO PC1, PC2;
    int total_recieve = 0;
    int total_proccess = 0;
    int queue = 0;
    if (expr % 2) sleep(1);

    for (int i = 0; i < 1000; i++) {
      queue++;

      srand(time(NULL));
      int T_recieve = rand() % 7 + 1;
      int T_proccess = rand() % 16 + 1;
      total_recieve += T_recieve;
      total_proccess += T_proccess;

      if (PC1.is_free) {
        queue--;
        set_work(&PC1, T_proccess, total_recieve, queue);
      } else {
        do_work(&PC1, T_recieve);
      }

      if (queue > 2) {
        if (PC2.is_free) {
          queue--;
          set_work(&PC2, T_proccess, total_recieve, queue);
        } else {
          do_work(&PC2, T_recieve);
        }
      } else {
        PC2.T_downtime += T_recieve;
      }
    }

    double total_wait = PC1.T_wait + PC2.T_wait;
    P_total_wait += total_wait / 1000.0;
    P_in_sys += total_proccess / 1000.0;

    P_PC1_downtime += PC1.T_downtime;
    P_PC2_downtime += PC2.T_downtime;
  }

  cout << "Average waiting time: " << P_total_wait / 100.0 << "s" << endl;
  cout << "Average time of task in sys: " << P_in_sys / 100.0 << "s" << endl;
  cout << "Probability of downtime PC1: " << P_PC1_downtime / 100.0 << "%"
       << endl;
  cout << "Probability of downtime PC2: " << P_PC2_downtime / 100.0 << "%"
       << endl;

  return 0;
}

void do_work(SMO *PC, int T_recieve) {
  PC->T_curr_work -= T_recieve;
  if (PC->T_curr_work <= 0) {
    PC->T_curr_work = 0;
    PC->is_free = true;
  } else {
    PC->T_wait += PC->T_curr_work;
  }
}

void set_work(SMO *PC, int T_proccess, int total, int queue) {
  PC->is_free = false;
  PC->T_curr_work = T_proccess;

  if (PC->T_work_end <= total && queue == 1) {
    PC->T_downtime += total - PC->T_work_end;
  }
  PC->T_work_end += PC->T_downtime + T_proccess;
}
