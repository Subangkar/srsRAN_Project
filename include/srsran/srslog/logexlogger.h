//
// Created by subangkar on 2/25/25.
//

#ifndef LOGEXLOGGER_H
#define LOGEXLOGGER_H

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

namespace LogexLogger {

inline const char* getFilename(const char* path)
{
  const char* file = std::strrchr(path, '/');
  if (file)
    return file + 1;
  file = std::strrchr(path, '\\');
  if (file)
    return file + 1;
  return path;
}

inline void log(const char* file, int line, const char* fmt, ...)
{
  // Get the current time and format it
  std::time_t t = std::time(nullptr);
  char        timeStr[20];
  std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

  // Print the log header with time, filename, and line number
  std::printf(">>> [%s] %s:%d: ", timeStr, getFilename(file), line);

  // Process the variable arguments and print the formatted message
  va_list args;
  va_start(args, fmt);
  std::vprintf(fmt, args);
  va_end(args);

  // End the log with a newline
  std::printf("\n");
}

} // namespace LogexLogger

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b)      CONCAT_IMPL(a, b)

// Convenience macro for logging that automatically provides file and line info
#define LOG(fmt, ...) LogexLogger::log(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_ONCE(fmt, ...)                                                                                             \
  do {                                                                                                                 \
    static bool CONCAT(_log_once_, __LINE__) = false;                                                                  \
    if (!CONCAT(_log_once_, __LINE__)) {                                                                               \
      CONCAT(_log_once_, __LINE__) = true;                                                                             \
      LOG(fmt, ##__VA_ARGS__);                                                                                         \
    }                                                                                                                  \
  } while (0)

#endif // LOGEXLOGGER_H
