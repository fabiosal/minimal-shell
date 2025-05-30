#define _POSIX_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

const int MAX_SHELL_INPUT_LEN = 256;
const int MAX_SHELL_ARGS = 10;

void print_parsed_input_command(char *arguments[]) {
  int j = 0;
  while (arguments[j]) {
    int c = 0;
    printf("characters ASCII code for string %d:\n", j);
    while (arguments[j][c] != '\0') {
      printf("%d ", arguments[j][c]);
      c++;
    }
    printf("%d ", arguments[j][c]);

    putchar('\n');
    puts(arguments[j]);
    j++;
  }
  putchar('\n');
}

int main(int argc, char *argv[]) {

  write(STDOUT_FILENO, "msh$ ", 5);

  char buf[MAX_SHELL_INPUT_LEN];

  buf[MAX_SHELL_INPUT_LEN - 1] = '\0';
  while (read(0, buf, sizeof(buf)) > 0) {

    char *arguments[MAX_SHELL_ARGS];
    char *token = strtok(buf, " ");
    int i = 0;
    while (token) {
      arguments[i] = token;
      token = strtok(NULL, " ");
      i++;
    }

    arguments[i - 1][strlen(arguments[i - 1]) - 1] = '\0';
    arguments[i] = NULL;

    // --handle multiple white space in commands
    int j;
    for (j = 0; j < i; j++) {
      if (arguments[j][0] == '\0') {
        arguments[j] = arguments[j + 1];
      }
    }
    // --------------------------------------
    /*print_parsed_input_command(arguments);*/

    if (arguments[0] != NULL) {

      // -- buildin commands
      if (strcmp(arguments[0], "exit") == 0) {
        write(STDOUT_FILENO, "exiting minimal shell\n", 22);
        exit(EXIT_SUCCESS);
      } else if (strcmp(arguments[0], "cd") == 0) {

        errno = 0;
        if (chdir(arguments[1]) != 0) {
          perror("Error :");
        }
        // ---------------------------------
      } else {

        /*print_parsed_input_command(arguments);*/

        int process_id = fork();

        if (process_id < 0) {
          // fork failed
          exit(EXIT_FAILURE);
        } else if (process_id == 0) {
          // child process
          /*printf("child process - pid: %d\n", getpid());*/

          execvp(arguments[0], arguments);
          exit(EXIT_SUCCESS);
          // ---------------------------------

        } else {
          // parent process

          int return_code;
          return_code = waitpid(process_id, NULL, 0);

          /*printf("parent process - pid : %d\n", getpid());*/
          /*printf("parent process - pid of waited process: %d\n",
           * return_code);*/
        }
      }
    }
    write(STDOUT_FILENO, "msh$ ", 5);
    memset(buf, '\0', MAX_SHELL_INPUT_LEN);
  }
}
