#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include "manager.h"

int       init_manager(manager_t *manager)
{
  char    filename[32];
  char    buffer[16];

  manager->log_fd = create_log("manager.log");

  dprintf(0, "Enter number of functions: ");
  read(1, buffer, 15);
  manager->number_of_functions = atoi(buffer);
  dprintf(0, "Enter stop symbol: ");
  read(1, buffer, 2);
   manager->stop_symbol = buffer[0];
  dprintf(0, "Enter x: ");
  read(1, buffer, 15);
  manager->x = atoi(buffer);

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
