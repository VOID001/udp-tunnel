#ifndef _LOG_H
#define _LOG_H

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

extern char log_level_str[][30];
void log_debugf(const char *fn_name, char *fmt, ...);
void log_infof(const char *fn_name, char *fmt, ...);
void log_warnf(const char *fn_name, char *fmt, ...);
void log_errorf(const char *fn_name, char *fmt, ...);
void log_fatalf(const char *fn_name, char *fmt, ...);
int init_logger(char *logfile, LogLevel lv);

#endif 
