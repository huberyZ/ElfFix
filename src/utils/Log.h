
#ifndef __LOG_H__
#define __LOG_H__

//common log
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define INFO "INFO"
#define ERR "ERROR"
#define DBG "DEBUG"
#define WARN "WARNING"

void log(const char *level, const char *log_format, ...);

#define Logd(format, ...) log(DBG, format, ##__VA_ARGS__)
#define Loge(format, ...) log(ERR, format, ##__VA_ARGS__)
#define Logi(format, ...) log(INFO, format, ##__VA_ARGS__)
#define Logw(format, ...) log(WARN, format, ##__VA_ARGS__)

#endif
