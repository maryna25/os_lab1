#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "manager.h"

int       reading_is_on(manager_t *manager, int *queue)
{
  int     finished_functions_count;

  finished_functions_count = 0;
  for (int i = 0; i < manager->number_of_functions; i++)
  {
    if (manager->functions[i]->answer == 0)
      return -1;
    if (queue[i] == 0)
      finished_functions_count++;
  }

  if (finished_functions_count == manager->number_of_functions)
    return -1;

  return 0;
}

int       polling_functions(manager_t *manager)
{
  int     *queue;

  dprintf(manager->log_fd, "Polling functions\n");

  queue = (int*) malloc(manager->number_of_functions * sizeof(int));
  for (int i = 0; i < manager->number_of_functions; i++)
    queue[i] = manager->functions[i]->in;

  while(reading_is_on(manager, queue) == 0)
  {
    if (user_answer(manager))
       break;
    for(int i = 0; i < manager->number_of_functions; i++)
      if (queue[i] != 0)
        read_answer(manager, queue, i);
  }
}

int       write_turn(manager_t *manager)
{
  dprintf(manager->log_fd, "Write turn\n");
  for (int i = 0; i < manager->number_of_functions; i++)
  {
    dprintf(manager->functions[i]->out, "%d", manager->x);
    set_nonblocking(manager->functions[i]->in);
  }
}

int       compute(manager_t *manager)
{
  int     res;

  dprintf(manager->log_fd, "Computing\n");
  res = 0;
  for (int i = 0; i < manager->number_of_functions; i++)
  {
    if (manager->functions[i]->answer == 0)
      return 0;
    else if (manager->functions[i]->answer != INT_MAX)
      if (res == 0)
        res = manager->functions[i]->answer;
      else
        res = res & manager->functions[i]->answer;
  }
  return res;
}

int       start_manager(manager_t *manager)
{
  int     res;
  write_turn(manager);
  polling_functions(manager);
  kill_functions(manager);
  res = compute(manager);
  dprintf(manager->log_fd, "Result = %d\n", res);
  return 0;
}
