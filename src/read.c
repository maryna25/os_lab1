#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "function.h"
#include "manager.h"

#define BUF_SIZE (16)

int       read_number()
{
  char    buffer[BUF_SIZE];
  int     res, number;

  res = 0;
  do
    res = read(0, buffer, BUF_SIZE - 1);
  while (res <= 0);

  number = atoi(buffer);
  return number;
}

int       read_answer(manager_t *manager, int *queue, int i)
{
  char    buffer[BUF_SIZE];
  int     res;

  res = read(queue[i], buffer, BUF_SIZE - 1);
  if (res > 0)
  {
    queue[i] = 0;
    manager->functions[i]->answer = atoi(buffer);
    dprintf(manager->log_fd, "Function %d;Answer = %d\n", i, manager->functions[i]->answer);
    dprintf(1, "Function %d;Answer = %d\n", i, manager->functions[i]->answer);
  }
  return manager->functions[i]->answer;
}

int       getch()
{
  char    ch;
  struct termios org_opts, new_opts;

  tcgetattr(STDIN_FILENO, &org_opts);
  memcpy(&new_opts, &org_opts, sizeof(new_opts));
  new_opts.c_lflag &= ~(ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
  return ch;
}

int       user_answer(manager_t *manager)
{
  char    answer;
  int     res;

  answer = getch();
  if (answer == manager->stop_symbol)
  {
    dprintf(manager->log_fd, "System was stopped by user.\n");
    return 1;
  }
  return 0;
}
