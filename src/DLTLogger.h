#pragma once

#include "C_DLT_LOG.h"
#include <map>
using std::map;
using std::string;

/**
 * Logs a formatted string to DLT for a DLT context ID and a DLT log level.
 * (This is the only public entry point for logging).
 * You can log formatted messages (using standard formatted strings)
*/




void DLTLog(const char* p_context, DltLogLevelType p_loglevel, const char* p_format, ...);
int DLTCtx(const char* p_context, const char* p_desc);
/**
 * Internal class implementation for DLT loggers.
 * Useless to be used directly.
 */
class DLTLogger
{
public:
    /** Returns the DLTLogger singleton instance. */
    static DLTLogger& Instance(void);

    /** DLTLogger destructor. */
    virtual ~DLTLogger();

    /** Returns the DLT logger instance corresponding to the given category.
     * If no logger instance for this category already exists, implicitly creates
     * it and returns it. (As a way of consequence, 'NULL' is never returned).
     * @param p_category A DLT category as a string.
     * @return The DLT Logger associated to the given category. */
    C_DLT_LOG* GetLoggerForCategory(string p_category, string p_desc);

    void AddCtxDesc(string key, string desc);

private:
    DLTLogger();
    /** Map associating DLT logger instances to string (categories). */
    map<string, C_DLT_LOG*> m_loggers;
};

