/*************************************************************************
    > File Name: util.c
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

char log_level_str[][30] = {
    "\033[1;38;5;4mDEBUG",
    "\033[1;38;5;82mINFO",
    "\033[1;38;5;11mWARN",
    "\033[1;38;5;9mERROR",
    "\033[1;38;5;9mFATAL"
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

void vlogprintf(LogLevel lv, const char *fn_name, char *fmt, va_list ap) {
    // first compare the LOGLEVEL, then print
    char logbuffer[MAX_BUFFER_LEN];
    struct tm *timeinfo;
    time_t rawtime;
    char *timecut;

    if(lv < LOGLV)
        return ;

    time(&rawtime); 
    timeinfo = localtime(&rawtime); 
    timecut = asctime(timeinfo);
    timecut[strlen(timecut) - 1] = 0;

    vsprintf(logbuffer, fmt, ap);
    fprintf(LOGFILE, "%s\t%s %s: %s\n", log_level_str[lv], timecut, fn_name, logbuffer);
    fflush(LOGFILE);

    return ;
}

// Below are logging functions
void log_infof(const char *fn_name, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);     
    vlogprintf(INFO, fn_name, fmt, ap);
    va_end(ap);

    return ;
}

void log_errorf(const char *fn_name, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);     
    vlogprintf(ERROR, fn_name, fmt, ap);
    va_end(ap);

    return ;
}

void log_warnf(const char *fn_name, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);     
    vlogprintf(WARN, fn_name, fmt, ap);
    va_end(ap);

    return ;
}

void log_debugf(const char *fn_name, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);     
    vlogprintf(DEBUG, fn_name, fmt, ap);
    va_end(ap);

    return ;
}

// fatal error will make the program exit right now
void log_fatalf(const char *fn_name, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);     
    vlogprintf(FATAL, fn_name, fmt, ap);
    va_end(ap);
    exit(-1);
}
