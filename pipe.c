#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

#define DATA "HELLO!"

int main(int argc, char const *argv[]) {

  //Stack allocated array to hold the file descriptors from pipe
  int pipefd[2];



  //Call pipe and handle if it fails
  if (pipe(pipefd) < 0) {
    perror("pipe error");
    return 1;
  }


  //For the process to we can communicate between parent and Child
  int pid = fork();

  //Fork errored
  if (pid < 0) {
    perror("fork() error");
    return 1;
  }

  //In child Proccess
  if (pid == 0) {
    printf("Child Proccess\n");

    //Stack allocated char array to hold read in data
    char data_buf[sizeof(DATA)];

    //Closing the write end of the pipe because we are Reading
    close(pipefd[1]);

    //Reading from the read end of the pipe and placeing the read data into
    // a char array. Handle the error if it fails.
    if(read(pipefd[0], data_buf, sizeof(data_buf)) < 0) {
      perror("read() error");
      exit(1);
    }

    printf("%s\n", data_buf );

    exit(0);
  }

  //In parent Proccess
  else {

    //Closeing the read end of the pipe because we are the writing Proccess
    close(pipefd[0]);

    //Write data to write end of the pipe. Pass in the data to be written
    //Handle error if write returns -1
    if (write(pipefd[1], DATA, sizeof(DATA)) < 0) {
      perror("write() error");
      return 1;
    }

  }

  return 0;
}
