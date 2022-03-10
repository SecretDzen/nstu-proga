#include <unistd.h>

#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

struct SMO {
  bool is_free = true;
  int T_wait = 0;
  int T_downtime = 0;
  int T_work_end = 0;
  int T_curr_work = 0;
};

int do_work(SMO *PC, int T_recieve);
void set_work(SMO *PC, int T_proccess, int total, int queue);
