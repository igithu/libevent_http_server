/***************************************************************************
 * 
 * Copyright (c) 2014 asy, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file util.cpp
 * @author asy5178@163.com
 * @date 2014/10/23 22:42:03
 * @brief 
 *  
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

#include "util.h"

void send_msg_ok(struct evhttp_request *req, const char *ret) {
    evhttp_add_header(req->output_headers, "Server", MYHTTPD_SIGNATURE);
    evhttp_add_header(req->output_headers, "Content-Type", "text/html; charset=UTF-8");
    evhttp_add_header(req->output_headers, "Connection", "close");

    struct evbuffer *buf;
    buf = evbuffer_new();
    evbuffer_add_printf(buf, "%s", ret);
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}

void assemble_str(
        const char *prefix, struct evhttp_request *req, char *output_ret) {
    char output[2048] = "\0";
    char output_html[2048 * 2] = "\0";
    char tmp[1024];
    
    const char *uri;
    uri = evhttp_request_uri(req);

    char *decoded_uri;
    decoded_uri = evhttp_decode_uri(uri);

    sprintf(tmp, "<br>decoded_uri=%s\n", decoded_uri);
    strcat(output, tmp);

    struct evkeyvalq params;
    evhttp_parse_query(decoded_uri, &params);
    sprintf(tmp, "<br>%s: p1=%s\n", prefix, evhttp_find_header(&params, "p1"));
    strcat(output, tmp);
    sprintf(tmp, "<br>%s: p2=%s\n", prefix, evhttp_find_header(&params, "p2"));
    strcat(output, tmp);
    sprintf(tmp, "<br>%s: tid=%u\n", prefix, pthread_self());
    strcat(output, tmp);
    free(decoded_uri);

    sprintf(output_ret, http_index_html, prefix, output);
}

void signal_handler(int sig) {
     switch (sig) {
         case SIGTERM:
         case SIGHUP:
         case SIGQUIT:
         case SIGINT:
         case SIGSEGV:
             event_loopbreak(); 
             break;
     }
}

















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
