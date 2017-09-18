#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

int       action(int time, int value)
{
  sleep(time);
  dprintf(1, "%d", value);
}

int       hang()
{
  while(42)
    sleep(300);
}

int       f(int log_fd)
{
  FILE    *file;
  int     number;

  number = read_number();
  dprintf(log_fd, "x = %d\n", number);

  if(number < -10)
    action(1, 60);
  else if (number < -5)
    action(6, 8);
  else if (number < 0)
    action(1, 0);
  else if (number == 0)
    hang();
  else if (number < 5)
    action(1, 1);
  else
    hang();

  exit(EXIT_SUCCESS);
}

int       g(int log_fd)
{
  FILE    *file;
  int     number;

  number = read_number();
  dprintf(log_fd, "x = %d\n", number);

  if(number < -10)
    action(4, 13);
  else if (number < -5)
    action(1, 8);
  else if (number < 0)
    hang();
  else if (number == 0)
    action(1, 0);
  else if (number < 5)
    hang();
  else
    action(1, 2);

  exit(EXIT_SUCCESS);
}
