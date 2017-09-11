#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "manager.h"
#include "function.h"

#define READ_SIDE   (0)
#define WRITE_SIDE  (1)

int       duplicate_fd(int read, int write)
{
  dup2(read, 0);
  dup2(write, 1);
}

int       fork_function(manager_t *manager, function_t *function)
{
  pid_t   cpid;
  int     pipe_req[2];
  int     pipe_ans[2];

  pipe(pipe_req);
  pipe(pipe_ans);

  dprintf(manager->log_fd, "Forking %d function\n", manager->current_function);

  cpid = fork();

  if(cpid == -1)
  {
    dprintf(manager->log_fd, "Error! %d function\n", manager->current_function);
    exit(EXIT_FAILURE);
  }
  if (cpid == 0)
  {
    close(pipe_req[WRITE_SIDE]);
    close(pipe_ans[READ_SIDE]);
    duplicate_fd(pipe_req[READ_SIDE], pipe_ans[WRITE_SIDE]);
    if (manager->current_function % 2 == 0)
      f(manager->functions[manager->current_function]->log_fd);
    else
      g(manager->functions[manager->current_function]->log_fd);
  }
  else
  {
    function->function_id = cpid;
    function->in = pipe_ans[READ_SIDE];
    function->out = pipe_req[WRITE_SIDE];
    close(pipe_req[READ_SIDE]);
    close(pipe_ans[WRITE_SIDE]);
    if (manager->current_function == manager->number_of_functions - 1)
    {
      set_nonblocking(0);
      start_manager(manager);
    }
    return(0);
  }
}

int       fork_functions(manager_t *manager)
{
  dprintf(manager->log_fd, "Forking.\n");
  for (int i = 0; i < manager->number_of_functions; i++)
  {
    manager->current_function = i;
    fork_function(manager, manager->functions[i]);
  }
}


int        kill_functions(manager_t *manager)
{
  for (int i = 0; i < manager->number_of_functions; i++)
  {
    kill(manager->functions[i]->function_id, SIGKILL);
  }

}
