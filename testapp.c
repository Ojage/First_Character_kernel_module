#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define DEVICE "/dev/mychardev"

int main() {
int fd;
char write_buf[100] = "Hello from userspace";
char read_buf[100];
int ret;
fd = open(DEVICE, O_RDWR);
if (fd < 0) {
perror("open");
exit(EXIT_FAILURE);
}
printf("Writing to device...\n");
ret = write(fd, write_buf, strlen(write_buf));
if (ret < 0) {
perror("write");
exit(EXIT_FAILURE);
}
printf("Reading from device...\n");
ret = read(fd, read_buf, sizeof(read_buf));
if (ret < 0) {
perror("read");
exit(EXIT_FAILURE);
}
printf("Data read from device: %s\n", read_buf);
close(fd);
return 0;
}