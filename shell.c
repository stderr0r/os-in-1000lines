#include "shell.h"
#include "user.h"

int split_args(char *line, char *argv[]) {
    int argc = 0;
    while (*line == ' ') line++;
    while (*line && argc < MAX_ARGS) {
        argv[argc++] = line;
        while (*line && *line != ' ' && *line != '\r' && *line != '\n') line++;
        if (*line == '\0') break;
        *line++ = '\0';
        while (*line == ' ') line++;
    }

    if (argc < MAX_ARGS) argv[argc] = NULL;
    return argc;
}

void cmd_echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc-1) putchar(' ');
    }
    putchar('\n');
}

void main(void) {
    char *argv[MAX_ARGS];

    while (1) {
        char *cmdline = readline("$ ");
        int argc = split_args(cmdline, argv);
        if (argc == 0) continue;

        if (!strcmp(argv[0], "ping")) printf("pong\n");
        else if (!strcmp(argv[0], "exit")) exit();
        else if (!strcmp(argv[0], "echo")) cmd_echo(argc, argv);
        else printf("unknown command: %s\n", cmdline);
    }
}
