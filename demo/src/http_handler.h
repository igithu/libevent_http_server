/***************************************************************************
 * 
 * Copyright (c) 2014 asy, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file http_handler.h
 * @author asy5178@163.com
 * @date 2014/10/23 23:08:30
 * @brief 
 *  
 **/




#ifndef  __HTTP_HANDLER_H_
#define  __HTTP_HANDLER_H_

#include <evhttp.h>

namespace http_handler {

void HttpHandlerEg1(struct evhttp_request *req, void *arg);

void HttpHandlerEg2(struct evhttp_request *req, void *arg);

}














#endif  //__HTTP_HANDLER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
