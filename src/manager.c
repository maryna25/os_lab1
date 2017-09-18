#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include "manager.h"

int       reading_is_on(manager_t *manager, int *queue)
{
  int     finished_functions_count;

  finished_functions_count = 0;
  for (int i = 0; i < manager->number_of_functions; i++)
    if (queue[i] == 0)
      finished_functions_count++;

  if (finished_functions_count == manager->number_of_functions)
    return 0;

  return 1;
}

char        ask_user(manager_t *manager)
{
  char      answer;

  printf("\nDo you want to continue or do not ask anymore?(y/n/d)");
  do
    answer = getchar();
  while (answer != 'y' && answer != 'n' && answer != 'd');

  if (answer == 'd')
    manager->ask_stop_question = 0;

  return answer;
}

int         polling_functions(manager_t *manager)
{
  int       *queue;
  time_t    time1, time2;

  dprintf(manager->log_fd, "Polling functions\n");

  queue = (int*) malloc(manager->number_of_functions * sizeof(int));
  for (int i = 0; i < manager->number_of_functions; i++)
    queue[i] = manager->functions[i]->in;

  time1 = time(NULL);

  while(42)
  {
    if (user_answer(manager))
       break;
    for(int i = 0; i < manager->number_of_functions; i++)
      if (queue[i] != 0)
        if(read_answer(manager, queue, i) == 0 || !reading_is_on(manager, queue))
          return 0;

    if (manager->ask_stop_question)
    {
      time2 = time(NULL);
      if (time2 - time1 >= 1)
      {
        if (ask_user(manager) == 'n')
        {
          dprintf(manager->log_fd, "System was stopped by user.\n");
          return 0;
        }
        time1 = time(NULL);
      }
    }
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
  dprintf(1, "\nResult = %d\n", res);
  return 0;
}
