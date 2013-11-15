#include "phedfastcgihandler.h"

using namespace photoeveryday;

PhedFastcgiHandler::PhedFastcgiHandler(fastcgi::ComponentContext *context) :
    fastcgi::Component(context), requestNumber(0) {
}

void PhedFastcgiHandler::handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    request->setHeader("Success header", "success");
    printf("\n<==========%d==========>\n", requestNumber++);
    printf("request has arrived:\n");
    if (request->getRequestMethod() == "POST"){
        this->handlePostRequest(request, context);
    }else{
        this->handleGetRequest(request, context);
    }

    printf("<======================>\n");
}

void PhedFastcgiHandler::handlePostRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("it's POST method\n");

}

void PhedFastcgiHandler::handleGetRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("it's GET method\n");
}


void PhedFastcgiHandler::onLoad(){
}
void PhedFastcgiHandler::onUnload(){
}

PhedFastcgiHandler::~PhedFastcgiHandler(){
}
