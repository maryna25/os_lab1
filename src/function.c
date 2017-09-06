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

int       f(int log_fd)
{
  FILE    *file;
  int     number;

  number = read_number();
  dprintf(log_fd, "x = %d\n", number);

  if(number < -10)
    action(1, 60);
  else if (number < -5)
    action(4, 8);
  else if (number < 0)
    action(1, 0);
  else if (number == 0)
    while(42);
  else if (number < 5)
    action(1, 1);
  else
    while(42);

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
    while(42);
  else if (number == 0)
    action(1, 0);
  else if (number < 5)
    while(42);
  else
    action(1, 2);

  exit(EXIT_SUCCESS);
}
