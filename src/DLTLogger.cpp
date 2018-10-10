#include "DLTLogger.h"

#include <iterator>
#include <stdarg.h>
#include <iostream>

DLTLogger& DLTLogger::Instance(void) {
	static DLTLogger singleton;
	return singleton;
}

DLTLogger::DLTLogger() {
}

DLTLogger::~DLTLogger() {
}

C_DLT_LOG* DLTLogger::GetLoggerForCategory(string p_category,string p_desc="") {

	C_DLT_LOG* foundLogger = NULL;
	string categoryAsCPPString = p_category;
	map<string, C_DLT_LOG*>::iterator iter;

	// find the existing logger matching the given category
	iter = m_loggers.find(categoryAsCPPString);
	if (iter!=m_loggers.end()) {
		// the logger for this category has been found
		foundLogger = iter->second;
	} else {
		// no existing logger has been found for this category
		// create a new logger entry
		foundLogger = new C_DLT_LOG();
		foundLogger->init(p_category,p_desc);
		m_loggers.insert(std::pair<string, C_DLT_LOG*>(categoryAsCPPString, foundLogger));
	}
	return foundLogger;
}

void DLTLog(const char* p_context, DltLogLevelType p_loglevel, const char* p_format, ...) {
	string contextAsCMMString (p_context);
	C_DLT_LOG* logger = DLTLogger::Instance().GetLoggerForCategory(contextAsCMMString);

	if(logger)
	{
		va_list args;
		va_start (args, p_format);
		char buff[1000];
		vsnprintf(buff, sizeof(buff), p_format, args);
		va_end(args);
		string logMsg (buff);
		logger->Log(p_loglevel,logMsg);
	}
}

int DLTCtx(const char* p_context, const char* p_desc)
{
	string contextAsCMMString (p_context);
	C_DLT_LOG* logger = DLTLogger::Instance().GetLoggerForCategory(contextAsCMMString,p_desc);
	if(logger)
		return 1;
	else
		return 0;
}
