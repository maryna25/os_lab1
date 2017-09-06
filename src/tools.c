#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "manager.h"

int       create_log(char *filename)
{
  return open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
}

int set_nonblocking(int fd)
{
  //int flags;

  //flags = fcntl(fd, F_GETFL, 0); //Get the file access mode and the file status flags
  return fcntl(fd, F_SETFL, O_NONBLOCK); //Set the file status flags to the value specified by arg
}
