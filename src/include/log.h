#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>

// The most verbose is shown on top -- DEBUG
typedef enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
    FATAL = 4,
}LogLevel;

// char log_level_str[][10] = {
//     {'D', 'E', 'B', 'U', 'G', 0},
//     {'I', 'N', 'F', 'O', 0},
//     {'W', 'A', 'R', 'N', 0},
//     {'E', 'R', 'R', 'O', 'R', 0},
//     {'F', 'A', 'T', 'A', 'L', 0}
// };

#define log_debugf(...) vlogprintf(DEBUG, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_infof(...) vlogprintf(INFO, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_warnf(...) vlogprintf(WARN, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_errorf(...) vlogprintf(ERROR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_fatalf(...) vlogprintf(FATAL, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

int init_logger(char *logfile, LogLevel lv);
void vlogprintf(LogLevel lv, const char *file_name, const char *fn_name, int line, char *fmt, ...);

#endif 
