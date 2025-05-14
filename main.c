#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  write(STDOUT_FILENO, "msh$ ", 5);

  char buf[256];
  int n;

  buf[255] = '\0';
  while (read(0, buf, sizeof(buf)) > 0) {

    int i;
    for (i = 0; i < strlen(buf); i++) {
      write(STDOUT_FILENO, &buf[i], 1);
    }

    int process_id = fork();

    if (process_id < 0) {
      // fork failed
      exit(1);
    } else if (process_id == 0) {
      // child process
      printf("child process - pid: %d\n", getpid());
      break;

    } else {
      // parent process
      int return_code;
      return_code = waitpid(process_id, NULL, 0);
      printf("parent process - pid : %d\n", getpid());
      printf("parent process - pid of waited process: %d\n", return_code);
    }
  }
}
