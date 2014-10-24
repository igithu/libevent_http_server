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


#include "http_server.h"

using namespace http_server;

int main(int argc, char *argv[]) {
    
    HttpServer http_server;
    http_server.Start(8889, 10);

}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
