#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>

#define DATA "HELLO!"

int main(int argc, char const *argv[]) {

  //Stack allocated array to hold the file descriptors from pipe
  int pipefd[2];

  //Call pipe and handle if it fails
  if (pipe(pipefd) < 0) {
    perror("pipe error");
    return 1;
  }

  //Printing the fd assigned by kernal, numbers arbirary
  // fd 0 reserved for STDIN
  // fd 1 reserved for STDOUT
  // fd 2 resevered for STDERR
  printf("pipefd[0] = %d\n", pipefd[0] );
  printf("pipefd[1] = %d\n", pipefd[1] );

  //Calling the write sys call, takes a file descriptor to write to, the data
  // to be written, and the size of the data to be written
  // Returns -1 on failure
  if (write(pipefd[1], DATA, sizeof(DATA)) < 0) {
    perror("write() error");
    return 1;
  }

  //Char array to hold the data read from pipe
  char data_buf[sizeof(DATA)];


  //Calling the read sys call, takes the file descriptor to read from, the
  //location to place the read data, and the size of the location to place data
  // Returns -1 on failure
  if(read(pipefd[0], data_buf, sizeof(data_buf)) < 0) {
    perror("read() error");
    return 1;
  }

  printf("%s\n", data_buf );

  return 0;

}
