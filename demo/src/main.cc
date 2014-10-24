/***************************************************************************
 * 
 * Copyright (c) 2014 asy, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file main.cc
 * @author asy5178@163.com
 * @date 2014/10/23 17:26:59
 * @brief 
 *  
 **/

#include <string>
#include <exception>

#include <getopt.h> 
#include <stdlib.h>

#include "http_server.h"

using namespace http_server;
using std::string;

void print_usage() {
    fprintf(stderr, 
            "    --h,   --help        this help\n"
            "    --p,   --port        the port, must be int!\n"
            "    --n,   --nthreads    the thread num, must be int!\n"
           );
}

void print_warning_info(const char *info) {
    fprintf(stderr, info);
    print_usage();
}

void parse_cmd_line(
        int argc, char *const argv[], int *port, int *nthread) {
    const char * opt_string = "pnh:";
    struct option longopts[] = {
        {"help", 0, NULL, 'h'},
        {"port", 1, NULL, 'p'},
        {"nthread", 1, NULL, 'n'},
        {0, 0, 0, 0}
    };

    int opt = 0;
    while ((opt = getopt_long(argc, argv, opt_string, longopts, NULL)) != -1) {
        // remove the string and if use -p or -n, maybe result to core dump,
        // maybe my environment problem
        string ss_tmp(optarg);
        switch (opt) {
            case 'p':
            {
                *port = atoi(optarg);
                break;
            }
            case 'n':
            {
                *nthread = atoi(optarg);
                break;
            }
            case 'h': 
            {
               print_usage();
               exit(1);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int port = 0, nthread = 0;

    try {
        parse_cmd_line(argc, argv, &port, &nthread);
    } catch (std::exception&) {
        fprintf(stderr, "Invalid option -p, -n\n");
        print_usage();
        exit(1);
    }

    if (0 == port) {
        fprintf(stderr,"--p, --port use the port, must be int!\n");
        exit(1);
    }

    if (0 == nthread) {
        fprintf(stderr, "--n,  --nthread   thread num, must be int!\n");
        exit(1);
    }

    HttpServer http_server;
    http_server.Start(port, nthread);

}




/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
