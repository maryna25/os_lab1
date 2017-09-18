#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "manager.h"

int       init_manager(manager_t *manager)
{
  char    filename[32];

  manager->log_fd = create_log("manager.log");
  manager->ask_stop_question = 1;
  manager->number_of_functions = 2;
  manager->x = 0;
  manager->stop_symbol = 's';
  manager->functions = (function_t**) malloc(manager->number_of_functions * sizeof(function_t*));
  for(int i = 0; i < manager->number_of_functions; i++)
  {
    manager->functions[i] = (function_t*) malloc(sizeof(function_t));
    manager->functions[i]->answer = INT_MAX;
    sprintf(filename, "function_%d.log", i);
    manager->functions[i]->log_fd = create_log(filename);
  }
  return 0;
}
