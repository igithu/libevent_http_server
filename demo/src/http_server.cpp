/***************************************************************************
 * 
 * Copyright (c) 2014 asy, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file http_server.cpp
 * @author asy5178@163.com
 * @date 2014/10/22 15:11:32
 * @brief 
 *  
 **/

#include <fcntl.h>
#include <signal.h>

#include "http_handler.h"
#include "util.h"

#include "http_server.h"

namespace http_server {

    using namespace http_handler;

    static int threads_size = 0;
    static pthread_t *thread_list = NULL;

    HttpServer::HttpServer() {
    }

    HttpServer::~HttpServer() {

        if (NULL != thread_list) {
            delete [] thread_list;
        }

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

    bool HttpServer::Start(int listen_port, int nthread) {

        int nfd = BindSocket(listen_port);
        if (nfd < 0) {
            return -1;
        }
        thread_list = new pthread_t(nthread);
        threads_size = nthread;

        for (int i = 0; i < nthread; ++i) {
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
            evhttp_set_gencb(httpd, DefaultHttpHandler, this);
            evhttp_set_cb(httpd, "/ex_request1", HttpHandlerEg1, NULL);
            evhttp_set_cb(httpd, "/ex_request2", HttpHandlerEg2, NULL);
            if (pthread_create(&thread_list[i], NULL, HttpServer::Dispatch, base) != 0) {
                 return -1;
             }
        }
        
        signal(SIGHUP, HttpServer::SignalHandler);
        signal(SIGTERM, HttpServer::SignalHandler);
        signal(SIGINT, HttpServer::SignalHandler);
        signal(SIGQUIT, HttpServer::SignalHandler);
        signal(SIGKILL, HttpServer::SignalHandler);

        for (int i = 0; i < nthread; ++i) {
            pthread_join(thread_list[i], NULL);
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
        // signal(SIGHUP, ChildSignalHandler);
        // signal(SIGTERM, ChildSignalHandler);
        // signal(SIGINT, ChildSignalHandler);
        // signal(SIGQUIT, ChildSignalHandler);
        signal(SIGUSR1, ChildSignalHandler);

        event_base_dispatch((struct event_base*)arg);
        return NULL;
    }

    void HttpServer::SignalHandler(int sig) {
        switch (sig) {
            case SIGTERM:
            case SIGHUP:
            case SIGQUIT:
            case SIGINT:
            case SIGSEGV:
            case SIGKILL:
                for (int i = 0; i < threads_size; ++i) {
                    DEBUG_LOG("Test kill tid, %u\n", thread_list[i]);
                    pthread_kill(thread_list[i], SIGUSR1);
                }
                break;
     }
       
    }
}  // namespace end of http_server





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
