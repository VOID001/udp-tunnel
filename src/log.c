/*************************************************************************
    > File Name: log.c
    > Author: VOID_133
    > ###################
    > Mail: ###################
    > Created Time: Wed 16 Aug 2017 11:19:38 AM CST
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "log.h"

#define MAX_BUFFER_LEN 2048
#define COLOR_TERM "\033[0m"

char *log_level_str[2][30] = {
    [0] = {
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR",
        "FATAL"
    },
    [1] = {
        "\033[1;38;5;4mDEBUG",
        "\033[1;38;5;82mINFO",
        "\033[1;38;5;11mWARN",
        "\033[1;38;5;9mERROR",
        "\033[1;38;5;9mFATAL"
    },
};

FILE *LOGFILE;
LogLevel LOGLV;

int init_logger(char *logfile, LogLevel lv) {
    LOGLV = lv;
    if(!strcmp(logfile, "stdout")) {
        LOGFILE = stdout;
        return 0;
    }
    if(!strcmp(logfile, "stderr")) {
        LOGFILE = stderr;
        return 0;
    }
    // Logging to file
    LOGFILE = fopen(logfile, "a");
    if(LOGFILE == NULL) {
        return -1;
    }
    return 0;
}

void vlogprintf(LogLevel lv, const char *file_name, const char *fn_name, int line, char *fmt, ...) {
    // first compare the LOGLEVEL, then print
    char logbuffer[MAX_BUFFER_LEN];
    struct tm *timeinfo;
    time_t rawtime;
    char *timecut;
    va_list args;

    if(lv < LOGLV)
        return ;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    timecut = asctime(timeinfo);
    timecut[strlen(timecut) - 1] = 0;

    int color = LOGFILE == stdout || LOGFILE == stderr;
    va_start(args, fmt);
    vsnprintf(logbuffer, sizeof(logbuffer), fmt, args);
    fprintf(LOGFILE, "%s\t%s %s %d: %s%s\n",
            log_level_str[color][lv], timecut, fn_name, line, logbuffer,color ? COLOR_TERM: "");
    va_end(args);

    fflush(LOGFILE);

    return;
}
