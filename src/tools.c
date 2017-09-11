#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "manager.h"

int       create_log(char *filename)
{
  return open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
}

int set_nonblocking(int fd)
{
  return fcntl(fd, F_SETFL, O_NONBLOCK); //Set the file status flags to the value specified by arg
}

char       getch()
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
