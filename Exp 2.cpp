#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int src, dest;
    char buffer[1024];
    int bytesRead;

    // Open source file
    src = open("C:\\Users\\LENOVO\\Documents\\input.txt", O_RDONLY);
    if (src < 0) {
        printf("Error: Cannot open source file!\n");
        return 1;
    }

    // Create/Open destination file
    dest = open("output1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        printf("Error: Cannot create destination file!\n");
        close(src);
        return 1;
    }

    // Read from source and write to destination
    while ((bytesRead = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytesRead);
    }

    printf("File copied successfully using system calls.\n");

    // Close both files
    close(src);
    close(dest);

    return 0;
}
