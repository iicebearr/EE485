#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(void) {
  pid_t process_id;

  if (fork() == 0) {
    if (fork() == 0)
      printf("Process A\n");
    else {
      process_id = wait(NULL);
      printf("Process B\n");
    }
  }
  else {
    process_id = wait(NULL);
    if (fork() == 0)
      printf("Process C\n");
    printf("Process D\n");
  }
  printf("end\n");
  return 0;
}
