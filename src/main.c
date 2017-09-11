#include "manager.h"

int           main()
{
  manager_t   manager;

  init_manager(&manager);
  fork_functions(&manager);
  return 0;
}
