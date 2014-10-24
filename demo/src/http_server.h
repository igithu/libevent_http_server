/***************************************************************************
 * 
 * Copyright (c) 2014 asy, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file http_server.h
 * @author asy5178@163.com
 * @date 2014/10/22 15:01:18
 * @brief 
 *  
 **/




#ifndef  __HTTP_SERVER_H_
#define  __HTTP_SERVER_H_

#include <vector>

#include <event.h>
#include <evhttp.h>

namespace http_server {
    using std::vector;
    class HttpServer {
        public:
            HttpServer();

            ~HttpServer();

            bool Start(int listen_port, int nthreads);

        private:
            static void *Dispatch(void *arg);

            int BindSocket(int port);
            
        private:
            // 
            vector<struct event_base *> remember_event_base_;
            vector<struct evhttp *> remember_evhttp_;
    };
}  // end of namespace














#endif  //__HTTP_SERVER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
