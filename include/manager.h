#ifndef MANAGER_H_
#define MANAGER_H_

typedef struct  function_s
{
  int           in;
  int           out;
  int           log_fd;
  int           function_id;
  int           answer;
}               function_t;

typedef struct  manager_s
{
  function_t    **functions;
  int           number_of_functions;
  int           current_function;
  int           log_fd;
  int           pipe_req[2];
  int           x;
  char          stop_symbol;
  int           ask_stop_question;
  int           finished_functions_count;
}               manager_t;

int     create_log(char *filename);
int     init_manager(manager_t *manager);

int     start_manager(manager_t *manager);

int     fork_functions(manager_t *manager);
int     kill_functions(manager_t *manager);

int     set_nonblocking(int fd);
char    getch();

int     read_answer(manager_t *manager, int *queue, int i);
int     user_answer(manager_t *manager);

#endif
