#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {

  //Buffer to be read into, hardcoded size, need to figure out a work around
  char buf[18];

  //Open the file atlas.txt, only can write, creates if does not exists,
  //when writes appends to current data, gives standard permissions
  int fd0 = open("atlas.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);

  //Open the file john.txt, assumes it exists, only Reading
  int fd1 = open("john.txt", O_RDONLY);

  //Handle error if either file failed to open
  if(fd0 < 0 || fd1 < 0) {
    perror("open() error");
    close(fd0);
    close(fd1);
    return 1;
  }

  //Read the data from file descriptor and store the data in Buffer
  // Handle the error if read fails
  if(read(fd1, buf, sizeof(buf)) < 0) {
    perror("read() error");
    close(fd0);
    close(fd1);
    return 1;
  }

  //Write the data to file descriptor, get the data from buf,
  //Handle error if write fails
  if (write(fd0, buf, sizeof(buf)) < 0) {
    perror("write() error");
    close(fd0);
    close(fd1);
    return 1;
  }


  //Code completed successfully, close the file descriptors
  close(fd0);
  close(fd1);

  return 0;
}
