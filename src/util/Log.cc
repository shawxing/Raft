/* Copyright (c) 2011-2012 Stanford University
 * Copyright (c) 2014-2015 Diego Ongaro
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

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <mutex>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

#include "Log.h"
#include "StringUtil.h"

namespace Util {
namespace Debug {
std::string processName = StringUtil::format("%u", getpid());

namespace Internal {

/**
 * Protects #logPolicy, #isLoggingCache, and #logFilename.
 */
std::mutex mutex;

/**
 * Filename of currently open stream, if known.
 * Protected by #mutex.
 */
std::string logFilename;

/**
 * Where log messages go (unless logHandler is set).
 */
FILE* stream = stderr;

/**
 * Convert a log level to a (static) string.
 * PANICs if the string is not a valid log level (case insensitive).
 */
const char*
logLevelToString(LogLevel level)
{
    switch (level) {
        case LogLevel::SILENT:  return "SILENT";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::NOTICE:  return "NOTICE";
        case LogLevel::VERBOSE: return "VERBOSE";
    }
    log(LogLevel::ERROR, __FILE__, __LINE__, __FUNCTION__,
        "%d is not a valid log level.\n",
        static_cast<int>(level));
    abort();
}

/**
 * Convert a string to a log level.
 * PANICs if the string is not a valid log level (case insensitive).
 */
LogLevel
logLevelFromString(const std::string& level)
{
    if (strcasecmp(level.c_str(), "SILENT")  == 0)  return LogLevel::SILENT;
    if (strcasecmp(level.c_str(), "ERROR")   == 0)   return LogLevel::ERROR;
    if (strcasecmp(level.c_str(), "WARNING") == 0) return LogLevel::WARNING;
    if (strcasecmp(level.c_str(), "NOTICE")  == 0)  return LogLevel::NOTICE;
    if (strcasecmp(level.c_str(), "VERBOSE") == 0) return LogLevel::VERBOSE;
    log(LogLevel::ERROR, __FILE__, __LINE__, __FUNCTION__,
        "'%s' is not a valid log level.\n", level.c_str());
    abort();
}

/**
 * Return the number of characters of __FILE__ that make up the path prefix.
 * That is, __FILE__ plus this value will be the relative path from the top
 * directory of the code tree.
 */
size_t
calculateLengthFilePrefix()
{
    const char* start = __FILE__;
    const char* match = strstr(__FILE__, "Util/Debug.cc");
    assert(match != NULL);
    return size_t(match - start);
}

/// Stores result of calculateLengthFilePrefix().
const size_t lengthFilePrefix = calculateLengthFilePrefix();

/**
 * Strip out the common prefix of a filename to get a path from the project's
 * root directory.
 * \param fileName
 *      An absolute or relative filename, usually the value of __FILE__.
 * \return
 *      A nicer way to show display 'fileName' to the user.
 *      For example, this file would yield "Core/Debug.cc".
 */
const char*
relativeFileName(const char* fileName)
{
    // Remove the prefix only if it matches that of __FILE__. This check is
    // needed in case someone compiles different files using different paths.
    if (strncmp(fileName, __FILE__, lengthFilePrefix) == 0)
        return fileName + lengthFilePrefix;
    else
        return fileName;
}

} // namespace Internal
using namespace Internal; // NOLINT

std::string
getLogFilename()
{
    std::lock_guard<std::mutex> lockGuard(mutex);
    return logFilename;
}

std::string
setLogFilename(const std::string& filename)
{
    FILE* next = fopen(filename.c_str(), "a");
    if (next == NULL) {
        return StringUtil::format(
            "Could not open %s for writing debug log messages: %s",
            filename.c_str(),
            strerror(errno));
    }
    FILE* old;
    {
        std::lock_guard<std::mutex> lockGuard(mutex);
        old = stream;
        stream = next;
        logFilename = filename;
    }
    if (old != stdout && old != stderr) {
        if (fclose(old) != 0) {
            WARNING("Failed to close previous debug log file descriptor: %s",
                    strerror(errno));
        }
    }
    return {};
}

std::string
reopenLogFromFilename()
{
    std::string filename = getLogFilename();
    if (filename.empty())
        return {};
    else
        return setLogFilename(filename);
}

FILE*
setLogFile(FILE* newFile)
{
    std::lock_guard<std::mutex> lockGuard(mutex);
    logFilename.clear();
    FILE* old = stream;
    stream = newFile;
    return old;
}

std::ostream&
operator<<(std::ostream& ostream, LogLevel level)
{
    ostream << logLevelToString(level);
    return ostream;
}

void
log(LogLevel level,
    const char* fileName, uint32_t lineNum, const char* functionName,
    const char* format, ...)
{
    va_list ap;
    // Don't use Core::Time here since it could potentially call PANIC.
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);

    // Failures are a little annoying here, since we can't exactly log
    // errors that come up.
    char formattedSeconds[64]; // a human-readable string now.tv_sec
    bool ok = false;
    { // First, try gmtime and strftime.
        struct tm calendarTime;
        if (gmtime_r(&now.tv_sec, &calendarTime) != NULL) {
            ok = (strftime(formattedSeconds,
                           sizeof(formattedSeconds),
                           "%F %T",
                           &calendarTime) > 0);
        }
    }
    if (!ok) { // If that failed, use the raw number.
        snprintf(formattedSeconds,
                 sizeof(formattedSeconds),
                 "%010lu",
                 now.tv_sec);
        formattedSeconds[sizeof(formattedSeconds) - 1] = '\0';
    }

    // This ensures that output on stderr won't be interspersed with other
    // output. This normally happens automatically for a single call to
    // fprintf, but must be explicit since we're using two calls here.
    flockfile(stream);

    fprintf(stream, "%s.%06lu %s:%d in %s() %s[%s]: ",
            formattedSeconds, now.tv_nsec / 1000,
            relativeFileName(fileName), lineNum, functionName,
            logLevelToString(level),
            processName.c_str());

    va_start(ap, format);
    vfprintf(stream, format, ap);
    va_end(ap);

    funlockfile(stream);

    fflush(stream);
}

} // namespace Util::Debug
} // namespace Util
