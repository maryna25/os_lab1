#include "manager.h"

int           main()
{
  manager_t   manager;

  init_manager(&manager);
  set_nonblocking(0);
  fork_functions(&manager);
  return 0;
}
