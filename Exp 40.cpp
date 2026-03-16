#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Permission bits:
   owner: bits 8-6 (r=4,w=2,x=1)
   group: bits 5-3
   others: bits 2-0
   stored as an int 0-0777
*/

void print_symbolic(int perm, char *out) {
    const char symbols[] = {'r','w','x'};
    int shifts[3] = {6, 3, 0}; // owner, group, others
    int pos = 0;
    for (int i=0;i<3;i++) {
        int bits = (perm >> shifts[i]) & 0x7; // three bits
        out[pos++] = (bits & 4) ? 'r' : '-';
        out[pos++] = (bits & 2) ? 'w' : '-';
        out[pos++] = (bits & 1) ? 'x' : '-';
    }
    out[pos] = '\0';
}

int read_octal_perm(const char *s) {
    // expects 3-digit octal (e.g., "755") or "0" style
    int len = (int)strlen(s);
    if (len == 0) return -1;
    int val = 0;
    // accept 1..3 digits
    for (int i = 0; i < len; ++i) {
        if (s[i] < '0' || s[i] > '7') return -1;
        val = val * 8 + (s[i] - '0');
    }
    if (val < 0 || val > 0777) return -1;
    return val;
}

void print_help() {
    printf("\n--- Linux-style permission simulation help ---\n");
    printf("Permission bits (owner/group/others):\n");
    printf(" Each of owner/group/others has r (4), w (2), x (1)\n");
    printf("Examples:\n");
    printf("  755 -> owner=rwx (7), group=rx (5), others=rx (5) -> rwxr-xr-x\n");
    printf("  644 -> owner=rw, group=r, others=r -> rw-r--r--\n");
    printf("\nUser types:\n");
    printf("  Owner: the file's owner (user who created it).\n");
    printf("  Group: users who are part of the file's group.\n");
    printf("  Others: all other users.\n");
    printf("-----------------------------------------------\n\n");
}

int main() {
    char filename[260];
    char buf[16];
    int perm = 0644; // default simulated permission
    char sym[16];

    printf("Linux Permission Simulator (Dev-C++ friendly)\n");
    printf("Enter filename to simulate permissions for: ");
    if (scanf("%259s", filename) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    // check file exists
    FILE *f = fopen(filename, "rb");
    if (f) {
        fclose(f);
        printf("File '%s' found on disk.\n", filename);
        // If file exists, keep default perm 0644. (We could try to derive read-only attr)
    } else {
        printf("File '%s' NOT found. Simulation will proceed with a virtual file.\n", filename);
    }

    while (1) {
        print_symbolic(perm, sym);
        printf("\nCurrent simulated permissions for '%s':\n", filename);
        printf("  Symbolic : %s\n", sym);
        printf("  Octal    : %03o\n", perm);
        printf("\nMenu:\n");
        printf("  1. Set permissions by octal (e.g., 755)\n");
        printf("  2. Show explanation of user types and bits\n");
        printf("  3. Help (examples)\n");
        printf("  4. Exit\n");
        printf("Choose option [1-4]: ");
        if (scanf("%s", buf) != 1) break;

        if (buf[0] == '1') {
            char in[8];
            printf("Enter octal permission (e.g., 755): ");
            if (scanf("%7s", in) != 1) { printf("Input error.\n"); continue; }
            int v = read_octal_perm(in);
            if (v < 0) {
                printf("Invalid octal permission. Use digits 0-7, up to 3 digits.\n");
            } else {
                perm = v;
                print_symbolic(perm, sym);
                printf("Permissions updated: %s (octal %03o)\n", sym, perm);
            }
        } else if (buf[0] == '2') {
            printf("\n--- User types and meaning ---\n");
            printf("OWNER (u): user who owns the file. Permissions apply to the owner.\n");
            printf("GROUP (g): group assigned to the file. Members of that group get these permissions.\n");
            printf("OTHERS (o): everyone else on the system.\n\n");
            printf("Permission bits (per class): r=4, w=2, x=1. Sum them to form the octal digit.\n");
            printf("Example: 6 (4+2) -> rw-, 5 (4+1) -> r-x, 7 (4+2+1) -> rwx\n");
            printf("-------------------------------\n");
        } else if (buf[0] == '3') {
            print_help();
        } else if (buf[0] == '4') {
            printf("Exiting.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
