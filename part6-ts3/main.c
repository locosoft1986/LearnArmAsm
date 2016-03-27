#include "ts.h"



void cmain(void)
{
  init();
  while(1) {
    task_switch();
  }
}
