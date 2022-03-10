#include "main.hpp"

int main() {
  SMO PC1, PC2;

  int total_recieve = 0;
  int total_proccess = 0;
  int queue = 0;

  /*
  cout << "| STEP | Int Rec | Int Proc | Tot Rec | Queue | Tot Wait |"
       << "| PC1 Free | PC1 Downtime | PC1 Work End |"
       << "| PC2 Free | PC2 Downtime | PC2 Work End |" << endl;
  */
  for (int i = 0; i < 100; i++) {
    queue++;

    sleep(1);
    srand(time(NULL));
    int T_recieve = rand() % 7 + 1;
    int T_proccess = rand() % 16 + 1;
    total_recieve += T_recieve;
    total_proccess += T_proccess;

    if (!PC1.is_free) queue -= do_work(&PC1, T_recieve);
    if (!PC2.is_free) queue -= do_work(&PC2, T_recieve);
    if (PC1.is_free) set_work(&PC1, T_proccess, total_recieve, queue);

    if (queue > 2) {
      if (PC2.is_free) set_work(&PC2, T_proccess, total_recieve, queue);
    } else {
      PC2.T_downtime += T_recieve;
    }
    /*
    printf("|%6d|%9d|%10d|", i, T_recieve, T_proccess);
    printf("%9d|%7d|%10d|", total_recieve, queue, PC1.T_wait + PC2.T_wait);
    printf("|%10d|%14d|%14d|", PC1.is_free, PC1.T_downtime, PC1.T_work_end);
    printf("|%10d|%14d|%14d|\n", PC2.is_free, PC2.T_downtime, PC2.T_work_end);
    */
  }

  int total_wait = PC1.T_wait + PC2.T_wait;
  double P_total_wait = total_wait / 100.0;
  double P_in_sys = total_proccess / 100.0;
  double P_PC1_downtime = PC1.T_downtime / 100.0;
  double P_PC2_downtime = PC2.T_downtime / 100.0;

  cout << "Average waiting time: " <<  P_total_wait << "sec" << endl;
  cout << "Average time of task in sys: " << P_in_sys << "sec" << endl;
  cout << "Probability of downtime PC1: " << P_PC1_downtime << endl;
  cout << "Probability of downtime PC2: " << P_PC2_downtime << endl;

  return 0;
}

int do_work(SMO *PC, int T_recieve) {
  int is_work_done = 0;

  PC->T_curr_work -= T_recieve;
  if (PC->T_curr_work <= 0) {
    PC->T_curr_work = 0;
    PC->is_free = true;
    is_work_done = 1;
  } else {
    PC->T_wait += PC->T_curr_work;
  }

  return is_work_done;
}

void set_work(SMO *PC, int T_proccess, int total, int queue) {
  PC->is_free = false;
  PC->T_curr_work = T_proccess;

  if (PC->T_work_end <= total && queue == 1) {
    PC->T_downtime += total - PC->T_work_end;
  }
  PC->T_work_end += PC->T_downtime + T_proccess;
}
