#ifndef _LOGGER_H
#define _LOGGER_H

typedef enum { LOG_ERROR, LOG_WARNING, LOG_INFO } logType_t;

#define LOG_debug(fmt, ...) printLog(LOG_INFO, fmt, ##__VA_ARGS__)
#define LOG_warning(fmt, ...) printLog(LOG_WARNING, fmt, ##__VA_ARGS__)
#define LOG_error(fmt, ...) printLog(LOG_ERROR, fmt, ##__VA_ARGS__)

void printLog(logType_t type, const char *fmt, ...);

#endif // _LOGGER_H
