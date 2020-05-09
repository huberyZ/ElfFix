#include "log.h"

void log(const char *level, const char *log_format, ...) {
    time_t loacl_time;
    char time_str[128];

    time(&loacl_time);
    strftime(time_str, sizeof(time_str), "[%Y.%m.%d %X]", localtime(&loacl_time));

    va_list var_arg;
    va_start(var_arg, log_format);
    char fmt_str[2048];
    vsnprintf(fmt_str, sizeof(fmt_str), log_format, var_arg);
    va_end(var_arg);

    printf("%s:%s[%s@%s:%d] %s\n", level, time_str, __func__, 
                __FILE__, __LINE__, fmt_str);
}




