#include "user.h"

void main(void) {
    while (1) {
    prompt:
        printf("> ");
        char cmdline[128];

        for (int i = 0;; i++) {
            char c = getchar();
            if (i == sizeof(cmdline) - 1) {
                printf("\ntoo long command!\n");
                goto prompt;
            }
            else if (c == '\r') {
                putchar('\n');
                cmdline[i] = '\0';
                break;
            } else {
                putchar(c);
                cmdline[i] = c;
            }
        }
        if (strcmp(cmdline, "ping") == 0) printf("pong\n");
        else printf("unknown command: %s\n", cmdline);
    }
}
