/***************************************************************************
 * 
 * Copyright (c) 2014 asy, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file http_handler.cpp
 * @author asy5178@163.com
 * @date 2014/10/23 23:09:29
 * @brief 
 *  
 **/

#include <signal.h>
#include <pthread.h>

#include "util.h"
#include "http_handler.h"

namespace http_handler {

void HttpHandlerEg1(struct evhttp_request *req, void *arg) {
    char output_html[2048 * 2] = "\0";
    assemble_str("example1", req, output_html);
    send_msg_ok(req, output_html);
}

void HttpHandlerEg2(struct evhttp_request *req, void *arg) {
    char output_html[2048 * 2] = "\0";
    assemble_str("example2", req, output_html);
    send_msg_ok(req, output_html);
}

void DefaultHttpHandler(struct evhttp_request *req, void *arg) {
    char output_html[2048 * 2] = "\0";
    assemble_str("default", req, output_html);
    send_msg_ok(req, output_html);
}

void ChildSignalHandler(int sig) {
     switch (sig) {
         case SIGTERM:
         case SIGHUP:
         case SIGQUIT:
         case SIGINT:
         case SIGSEGV:
         case SIGKILL:
         case SIGUSR1:
             event_loopbreak(); 
             DEBUG_LOG("Exit tid %u\n", pthread_self());
             pthread_exit(0);
             break;
     }
}


}  // end of namespace http_handler 




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
