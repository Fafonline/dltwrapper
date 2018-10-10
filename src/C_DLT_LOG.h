/*
 * C_DLT_LOG.h
 *
 *  Created on: Sep 4, 2018
 *      Author: fal
 */

#ifndef LOG_C_DLT_LOG_H_
#define LOG_C_DLT_LOG_H_

#include <string>
#include <dlt.h>
class C_DLT_LOG {
public:
	C_DLT_LOG();
	virtual ~C_DLT_LOG();

	void Log(DltLogLevelType p_loglevel, std::string buffer);

	void init(std::string p_ctx,std::string p_desc);
	void release();

private:
	DltContext m_ctx;
};

#endif /* LOG_C_DLT_LOG_H_ */
