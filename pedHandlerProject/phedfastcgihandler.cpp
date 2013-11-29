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
    printf("content length: %d\n", request->getContentLength());
    printf("tmp info: %d\n", request->countCookie()); std::vector<std::string> fileNames;// = new std::vector<std::string>;
    request->remoteFiles(fileNames);
    for(auto i: fileNames){ printf("%s\n", i.c_str());}
    fastcgi::DataBuffer data = request->requestBody();
    auto st= request->getQueryString();
    std::string headers = "X-FILE";
    headers = request->getHeader(headers);
    printf("QuerySTring: %s\nHeaders: %s\n",st.c_str(),headers.c_str());
    std::string buffer;
    request->headerNames(fileNames);
    for(auto i: fileNames){ printf("%s\n", i.c_str());}
    data.toString(buffer);
    printf(" Request Body by the way: %s",buffer.c_str());
    printf("data is empty: %d\n", data.empty());
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
