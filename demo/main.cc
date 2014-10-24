/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_http_server.cpp
 * @author aishuyu(com@baidu.com)
 * @date 2014/10/21 15:47:39
 * @brief 
 *  
 **/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>  
#include <string.h> 

#include <sys/queue.h>
#include <event.h>

#include <evhttp.h>
#include <signal.h>

const static char http_index_html[] = 
"<html><head><title>Congrats!</title></head>"
"<body><h1>Welcome to our HTTP server demo!%s!!</h1>"
"<p>This is a just small test page.<br> your paramter:%s </body></html>";

#define MYHTTPD_SIGNATURE   "test_httpd v 0.0.1"

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
    // sprintf(tmp, "<br>uri=%s\n", uri);
    // strcat(output, tmp);

    // sprintf(tmp, "<br>uri=%s\n", req->uri);
    // strcat(output, tmp);

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
    free(decoded_uri);

    // char *post_data = (char *) EVBUFFER_DATA(req->input_buffer);
    // sprintf(tmp, "post_data=%s\n", post_data);

    // strcat(output, tmp);
    sprintf(output_ret, http_index_html, prefix, output);

}

void httpd_handler(struct evhttp_request *req, void *arg) {
    char output_html[2048 * 2] = "\0";
    assemble_str("default", req, output_html);
    // strcat(output_html, http_html_hdr);
    // strcat(output_html, http_index_html);
    send_msg_ok(req, output_html);
}

void httpd_handler_example1(struct evhttp_request *req, void *arg) {
    char output_html[2048 * 2] = "\0";
    assemble_str("example1", req, output_html);
    // strcat(output_html, http_html_hdr);
    // strcat(output_html, http_index_html);
    send_msg_ok(req, output_html);
}

void httpd_handler_example2(struct evhttp_request *req, void *arg) {
    char output_html[2048 * 2] = "\0";
    assemble_str("example2", req, output_html);
    // strcat(output_html, http_html_hdr);
    // strcat(output_html, http_index_html);
    send_msg_ok(req, output_html);
}

void show_help() {
    char *help = "written by Min (http://hoss)\n\n";
//        "-l <ip_addr> interface to listen on, default is 0.0.0.0\n";
    fprintf(stderr, help);
}

void signal_handler(int sig) {
     switch (sig) {
         case SIGTERM:
         case SIGHUP:
         case SIGQUIT:
         case SIGINT:
         case SIGSEGV:
             event_loopbreak();  //终止侦听event_dispatch()的事件侦听循环，执行之后的代码
             break;
     }
}

int main(int argc, char *argv[]) {
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

    // char *httpd_option_listen = "0.0.0.0";
    char *httpd_option_listen = "cq01-rdqa-pool211.cq01.baidu.com";
    int httpd_option_port = 8999;
    int httpd_option_daemon = 0;
    int httpd_option_timeout = 120; //in seconds

    int c;
    while ((c = getopt(argc, argv, "l:p:dt:h")) != -1) {
        switch (c) {
            case 'l' :
                httpd_option_listen = optarg;
                break;
            case 'p' :
                httpd_option_port = atoi(optarg);
                break;
            case 'd' :
                httpd_option_daemon = 1;
                break;
            case 't' :
                httpd_option_timeout = atoi(optarg);
                break;
            case 'h' :
            default :
                show_help();
                exit(EXIT_SUCCESS);
        }
    }

    if (httpd_option_daemon) {
        pid_t pid;
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid > 0) {
            //生成子进程成功，退出父进程
            exit(EXIT_SUCCESS);
        }
    }

    event_init();
    struct evhttp *httpd;
    httpd = evhttp_start(httpd_option_listen, httpd_option_port);
    evhttp_set_timeout(httpd, httpd_option_timeout);

    evhttp_set_gencb(httpd, httpd_handler, NULL);
    //也可以为特定的URI指定callback
    evhttp_set_cb(httpd, "/ex1", httpd_handler_example1, NULL);
    evhttp_set_cb(httpd, "/ex2", httpd_handler_example2, NULL);

    //循环处理events
    event_dispatch();

    evhttp_free(httpd);
    return 0;
}




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
