/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file http_server.cpp
 * @author aishuyu(com@baidu.com)
 * @date 2014/10/22 15:11:32
 * @brief 
 *  
 **/

#include <fcntl.h>
#include <signal.h>
#include <pthread.h>

#include "http_handler.h"
#include "util.h"

#include "http_server.h"

namespace http_server {

    using namespace http_handler;

    HttpServer::HttpServer() {
    }

    HttpServer::~HttpServer() {
        for (int i = 0; i < remember_event_base_.size(); ++i) {
            struct event_base *cur_base = remember_event_base_[i];
            if (NULL != cur_base) {
                event_base_free(cur_base);
            }
        }

        for (int i = 0; i < remember_evhttp_.size(); ++i) {
            struct evhttp *cur_http = remember_evhttp_[i];
            if (NULL != cur_http) {
                evhttp_free(cur_http);
            }
        }
    }

    bool HttpServer::Start(int listen_port, int nthreads) {

        int nfd = BindSocket(listen_port);
        if (nfd < 0) {
            return -1;
        }
        pthread_t threads[nthreads];

        for (int i = 0; i < nthreads; ++i) {
            struct event_base *base = event_init();
            if (NULL == base) {
                return -1;
            }
            remember_event_base_.push_back(base);

            struct evhttp *httpd = evhttp_new(base);
            if (NULL == httpd) {
                return -1;
            }
            remember_evhttp_.push_back(httpd);

            if (evhttp_accept_socket(httpd, nfd) != 0) {
                return -1;
            }
            evhttp_set_timeout(httpd, 30/*timeout*/);
            evhttp_set_cb(httpd, "/ex_request1", HttpHandlerEg1, NULL);
            evhttp_set_cb(httpd, "/ex_request2", HttpHandlerEg2, NULL);
            if (pthread_create(&threads[i], NULL, HttpServer::Dispatch, base) != 0) {
                 return -1;
             }
        }

        for (int i = 0; i < nthreads; ++i) {
            pthread_join(threads[i], NULL);
        }

        return true;
    }

    int HttpServer::BindSocket(int port) {
        int nfd = socket(AF_INET, SOCK_STREAM, 0);
        if (nfd < 0) {
            return -1;
        }

        const int one = 1;
        setsockopt(nfd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        if (bind(nfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            return -1;
        }

        if (listen(nfd, 10240) < 0) {
            return -1;
        }

        int flags = 0;
        if ((flags = fcntl(nfd, F_GETFL, 0)) < 0 ||
            fcntl(nfd, F_SETFL, flags | O_NONBLOCK) < 0) {
            return -1;
        }
        
        return nfd;     
    }


    void *HttpServer::Dispatch(void *arg) {
        signal(SIGHUP, signal_handler);
        signal(SIGTERM, signal_handler);
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, signal_handler);

        event_base_dispatch((struct event_base*)arg);
        return NULL;
    }

}  // namespace end of http_server





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
