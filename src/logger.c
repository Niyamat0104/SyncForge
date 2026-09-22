#include <logger.h>

#include <stdio.h>
#include <stdarg.h>
static LogLevel g_min_level = LOG_INFO;
static const char *level_label(LogLevel level) {
    switch(level) {
        case LOG_DEBUG: return "DEBUG";
        case LOG_INFO : return "INFO";
        case LOG_WARN : return "WARN";
        case LOG_ERROR : return "ERROR";
        default : return "LOG";

    }
}

void logger_set_level(LogLevel level) {
    g_min_level = level;
}
void log_msg(LogLevel level, const char *fmt,...) {
    if(level < g_min_level) {
        return ;
    }

    FILE *stream = (level >= LOG_WARN) ? stderr : stdout;
    fprintf(stream , "[%s]",level_label(level));
    va_list args;
    va_start(args,fmt);
    vfprintf(stream,fmt,args);
    va_end(args);
    fprintf(stream,"\n"); 

}