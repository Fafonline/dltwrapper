/*
 * C_DLT_LOG.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: fal
 */

#include "C_DLT_LOG.h"


C_DLT_LOG::C_DLT_LOG() {
	// TODO Auto-generated constructor stub

}

C_DLT_LOG::~C_DLT_LOG() {
	// TODO Auto-generated destructor stub
	release();
}

void C_DLT_LOG::init(std::string p_ctx,std::string p_desc) {
	DLT_REGISTER_CONTEXT(m_ctx,p_ctx.c_str(),p_desc.c_str());
}

void C_DLT_LOG::release() {
	DLT_UNREGISTER_CONTEXT(m_ctx);
}

#include <iostream>
void C_DLT_LOG::Log(DltLogLevelType p_loglevel,std::string p_buffer) {
	DLT_LOG(m_ctx,p_loglevel,DLT_STRING(p_buffer.c_str()));
	std::cout << p_buffer.c_str() << std::endl;
}


