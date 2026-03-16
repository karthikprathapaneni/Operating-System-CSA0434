#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[100];

    // --- OPEN FILE ---
    fd = open("example.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        printf("Error opening file!\n");
        return 1;
    }
    printf("File opened successfully (fd = %d)\n", fd);

    // --- WRITE TO FILE ---
    char text[] = "Hello! This is a UNIX system call demo.\n";
    write(fd, text, sizeof(text));
    printf("Data written to file.\n");

    // --- MOVE FILE POINTER TO START ---
    lseek(fd, 0, SEEK_SET);

    // --- READ FROM FILE ---
    read(fd, buffer, sizeof(text));
    printf("Data read from file: %s\n", buffer);

    // --- CLOSE FILE ---
    close(fd);
    printf("File closed successfully.\n");

    return 0;
}
