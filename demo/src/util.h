/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file util.h
 * @author aishuyu(com@baidu.com)
 * @date 2014/10/23 17:15:55
 * @brief 
 *  
 **/




#ifndef  __UTIL_H_
#define  __UTIL_H_

#include <evhttp.h>

const static char http_index_html[] = 
"<html><head><title>Congrats!</title></head>"
"<body><h1>Welcome to our HTTP server demo!%s!!</h1>"
"<p>This is a just small test page.<br> your paramter:%s </body></html>";

#define MYHTTPD_SIGNATURE   "test_httpd v 0.0.1"

void signal_handler(int sig);
void send_msg_ok(struct evhttp_request *req, const char *ret);
void assemble_str(
        const char *prefix, struct evhttp_request *req, char *output_ret);



#endif  //__UTIL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
