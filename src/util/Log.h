/* Copyright (c) 2010-2012 Stanford University
 * Copyright (c) 2014 Diego Ongaro
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR(S) DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <cinttypes>
#include <cstdlib>
#include <functional>
#include <string>
#include <vector>

#ifndef LOG_H_
#define LOG_H_

namespace Util {
namespace Debug {

/**
 * The levels of verbosity for log messages. Higher values are noisier.
 *
 * \since LogCabin v1.1.0. New levels may be added in future minor releases
 * (adding a new level is considered backwards-compatible), so use 'default'
 * values in switch statements.
 */
enum LogLevel {
    // If you change this enum, you should also update logLevelToString() and
    // logLevelFromString() in Core/Debug.cc.
    /**
     * This log level is just used for disabling all log messages, which is
     * really only useful in unit tests.
     */
    SILENT = 0,
    /**
     * Bad stuff that shouldn't happen. The system broke its contract to users
     * in some way or some major assumption was violated.
     */
    ERROR = 10,
    /**
     * Messages at the WARNING level indicate that, although something went
     * wrong or something unexpected happened, it was transient and
     * recoverable.
     */
    WARNING = 20,
    /**
     * A system message that might be useful for administrators and developers.
     */
    NOTICE = 30,
    /**
     * Messages at the VERBOSE level don't necessarily indicate that anything
     * went wrong, but they could be useful in diagnosing problems.
     */
    VERBOSE = 40,
};


/**
 * Return the filename given to the last successful call to setLogFilename(),
 * or the empty string if none.
 */
std::string getLogFilename();

/**
 * Open the given file by name and append future debug log messages to it.
 * Note that if a handler is set with setLogHandler, this file will not be
 * used.
 * \param filename
 *      Name of file. If it already exists, new messages will be appended at
 *      the end. If the file is already open, this will re-open it (useful for
 *      rotating logs).
 * \return
 *      Error message if errors were encountered opening the file, otherwise an
 *      empty string indicates success.
 */
std::string setLogFilename(const std::string& filename);

/**
 * Called to rotate the log file.
 * If there was a previous call to setLogFilename(), this will reopen that file
 * by name, returning any errors. Otherwise, it will do nothing.
 * \return
 *      Error message if errors were encountered in reopening the file,
 *      otherwise an empty string indicates success.
 */
std::string reopenLogFromFilename();

/**
 * Change the file on which debug log messages are written.
 *
 * Note that if a handler is set with setLogHandler, this file will not be
 * used. If a filename has been set with setLogFilename(), this will clear it.
 *
 * \param newFile
 *      Handle to open file where log messages will be written.
 * \return
 *      Handle to previous log file (initialized to stderr on process start).
 */
FILE*
setLogFile(FILE* newFile);

std::ostream& operator<<(std::ostream& ostream, LogLevel level);

/**
 * Unconditionally log the given message to stderr.
 * This is normally called by LLOG().
 * \param level
 *      The level of importance of the message.
 * \param fileName
 *      The output of __FILE__.
 * \param lineNum
 *      The output of __LINE__.
 * \param functionName
 *      The output of __FUNCTION__.
 * \param format
 *      A printf-style format string for the message. It should include a line
 *      break at the end.
 * \param ...
 *      The arguments to the format string, as in printf.
 */
void
log(LogLevel level,
    const char* fileName, uint32_t lineNum, const char* functionName,
    const char* format, ...)
__attribute__((format(printf, 5, 6)));

/**
 * A short name to be used in log messages to identify this process.
 * This defaults to the UNIX process ID.
 */
extern std::string processName;

} // namespace Debug
} // namespace Util

/**
 * Unconditionally log the given message to stderr.
 * This is normally called by ERROR(), WARNING(), NOTICE(), or VERBOSE().
 * \param level
 *      The level of importance of the message.
 * \param format
 *      A printf-style format string for the message. It should not include a
 *      line break at the end, as LOG will add one.
 * \param ...
 *      The arguments to the format string, as in printf.
 */
#define LLOG(level, format, ...) do { \
		::Util::Debug::log(level, \
				__FILE__, __LINE__, __FUNCTION__, \
				format "\n", ##__VA_ARGS__); \
} while (0)

/**
 * Log an ERROR message and abort the process.
 * \copydetails ERROR
 */
#define PANIC(format, ...) do { \
    ERROR(format " Exiting...", ##__VA_ARGS__); \
    ::abort(); \
} while (0)

/**
 * Log an ERROR message and exit the process with status 1.
 * \copydetails ERROR
 */
#define EXIT(format, ...) do { \
    ERROR(format " Exiting...", ##__VA_ARGS__); \
    ::exit(1); \
} while (0)

/**
 * Log an ERROR message.
 * \param format
 *      A printf-style format string for the message. It should not include a
 *      line break at the end, as LOG will add one.
 * \param ...
 *      The arguments to the format string, as in printf.
 */
#define ERROR(format, ...) \
    LLOG((::Util::Debug::LogLevel::ERROR), format, ##__VA_ARGS__)

/**
 * Log a WARNING message.
 * \copydetails ERROR
 */
#define WARNING(format, ...) \
    LLOG((::Util::Debug::LogLevel::WARNING), format, ##__VA_ARGS__)

/**
 * Log a NOTICE message.
 * \copydetails ERROR
 */
#define NOTICE(format, ...) \
    LLOG((::Util::Debug::LogLevel::NOTICE), format, ##__VA_ARGS__)

/**
 * Log a VERBOSE message.
 * \copydetails ERROR
 */
#define VERBOSE(format, ...) \
    LLOG((::Util::Debug::LogLevel::VERBOSE), format, ##__VA_ARGS__)

#endif /* LOG_H_ */
