#include "ts.h"



void cmain(void)
{
  while(1) {
    init();
    task_switch();
  }
}
