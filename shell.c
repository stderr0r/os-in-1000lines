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

void cmd_cat(int argc, char *argv[]) {
    static char buf[256];
    for (int i = 1; i < argc; i++) {
        int len = readfile(argv[i], buf, sizeof(buf));
        if (len != -1) {
            buf[len] = '\0';
            printf("%s\n", buf);
        }
    }
}

void cmd_write(int argc, char *argv[]) {
    if (argc < 3) {
        printf("usage: write <filename> <text>\n");
        return;
    }
    char buf[256];
    int pos = 0;

    for (int i = 2; i < argc; i++) {
        const char *s = argv[i];
        while (*s != '\0') {
            buf[pos++] = *s++;
        }
        if (i < argc-1) buf[pos++] = ' ';
    }
    buf[pos] = '\0';
    writefile(argv[1], buf, pos);

}

void cmd_ls(void) {
    char buf[256];
    int len = listfiles(buf, sizeof(buf));
    if (len > 0) {
        buf[len] = '\0';
        printf("%s", buf);
    }
}

void cmd_touch(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: touch <filename>\n");
        return;
    }
    if (createfile(argv[1]) != 0) {
        printf("failed to create file: %s\n", argv[1]);
    }
}

void cmd_rm(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: rm <filename>\n");
        return;
    }
    if (deletefile(argv[1]) != 0) {
        printf("failed to delete file: %s\n", argv[1]);
    }
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
        else if (!strcmp(argv[0], "cat")) cmd_cat(argc, argv);
        else if (!strcmp(argv[0], "write")) cmd_write(argc, argv);
        else if (!strcmp(argv[0], "ls")) cmd_ls();
        else if (!strcmp(argv[0], "touch")) cmd_touch(argc, argv);
        else if (!strcmp(argv[0], "rm")) cmd_rm(argc, argv);
        else printf("unknown command: %s\n", cmdline);
    }
}
