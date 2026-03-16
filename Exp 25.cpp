#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <windows.h>

int main() {
    int fd;
    char buffer[100];

    /* ---------- OPEN FILE ---------- */
    fd = _open("sample.txt", _O_CREAT | _O_RDWR, _S_IREAD | _S_IWRITE);
    if (fd < 0) {
        printf("File open error!\n");
        return 1;
    }

    /* ---------- WRITE ---------- */
    char text[] = "Hello OS System Calls!";
    _write(fd, text, sizeof(text));

    /* ---------- LSEEK ---------- */
    _lseek(fd, 0, SEEK_SET);

    /* ---------- READ ---------- */
    _read(fd, buffer, sizeof(text));
    buffer[sizeof(text)] = '\0';
    printf("Data Read: %s\n", buffer);

    /* ---------- STAT ---------- */
    struct _stat info;
    if (_stat("sample.txt", &info) == 0) {
        printf("\nFile Size: %ld bytes\n", info.st_size);
        printf("Last Modified: %ld\n", info.st_mtime);
    } else {
        printf("stat error!\n");
    }

    _close(fd);

    /* ---------- DIRECTORY LISTING (Windows API) ---------- */
    printf("\nDirectory Listing:\n");

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory.\n");
        return 1;
    }

    do {
        printf("%s\n", findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData));

    FindClose(hFind);

    return 0;
}
