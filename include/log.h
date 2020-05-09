
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

#define logd(format, ...) log(DBG, format, ##__VA_ARGS__)
#define loge(format, ...) log(ERR, format, ##__VA_ARGS__)
#define logi(format, ...) log(INFO, format, ##__VA_ARGS__)
#define logw(format, ...) log(WARN, format, ##__VA_ARGS__)

#endif
