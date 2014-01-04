#pragma once

#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>
//#include <boost/filesystem.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "databasemanager.h"
#include "jsonFormatter.h"
#include "glog/logging.h"

namespace photoeveryday{

class PhedFastcgiHandler : virtual public fastcgi::Component, virtual public fastcgi::Handler {

public:
    PhedFastcgiHandler(fastcgi::ComponentContext *context);
    virtual ~PhedFastcgiHandler();

public:
    virtual void onLoad();
    virtual void onUnload();
    virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
    virtual void handlePostRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
    virtual void handleGetRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
    virtual void handleUploadPhotoRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
    virtual void handleInfoPhotoRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
    virtual void handleMakeMovieRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
    virtual void handleUserInfoRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
private:
    bool moveFile(const std::string& src, const std::string& dest);
    bool makeMovie(const std::string& srcFolder);
    volatile unsigned int requestNumber;
    DataBaseManager db;
    jsonFormatter formatter;
};

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("phed_factory", PhedFastcgiHandler)
FCGIDAEMON_REGISTER_FACTORIES_END()

}

