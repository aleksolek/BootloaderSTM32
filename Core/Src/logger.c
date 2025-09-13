#include "logger.h"
#include "usart.h"
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define LOG_MAX_LENGTH 150
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define RED "\033[0;31m"
#define RESET "\033[0m\r\n"

void printLog(logType_t type, const char *fmt, ...) {
  char log[LOG_MAX_LENGTH];
  const char *color = NULL;
  va_list args;
  va_start(args, fmt);
  uint32_t length = vsnprintf(log, sizeof(log), fmt, args);
  va_end(args);

  if (length <= 0) {
    return;
  }
  switch (type) {
  case LOG_INFO:
    color = GREEN;
    break;
  case LOG_WARNING:
    color = YELLOW;
    break;
  case LOG_ERROR:
    color = RED;
    break;
  default:
	color = "";
    break;
  }
  char final[LOG_MAX_LENGTH];
  int written = snprintf(final, sizeof(final), "%s%s%s", color, log, RESET);
  if (written >= sizeof(final)) {
    int reset_len = strlen(RESET);
    memcpy(final + sizeof(final) - reset_len - 1, RESET, reset_len);
    final[sizeof(final) - 1] = '\0';
  }
  for (char *p = final; *p; p++) {
    UART_putChar(DEBUG_UART, *p);
  }
}
