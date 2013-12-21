#pragma once

#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "databasemanager.h"

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
    virtual void handleMakeGifRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
private:
    bool moveFile(const std::string& src, const std::string& dest);
    volatile unsigned int requestNumber;
    DataBaseManager db;
};

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("phed_factory", PhedFastcgiHandler)
FCGIDAEMON_REGISTER_FACTORIES_END()

}

