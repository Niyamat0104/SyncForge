#ifndef SYNCFORGE_LOGGER_H
#define SYNCFORGE_LOGGER_H

typedef enum{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

/* setting minimum level that would be printed*/
void logger_set_level(LogLevel level);

void log_msg(LogLevel level , const char *fmt, ... );


/* Convience wrappers. */
#define log_debug(...) log_msg(LOG_DEBUG, __VA_ARGS__)
#define log_info(...) log_msg(LOG_INFO , __VA_ARGS__)
#define log_warn(...) log_msg(LOG_WARN , __VA_ARGS__)
#define log_error(...) log_msg(LOG_ERROR , __VA_ARGS__)

#endif
