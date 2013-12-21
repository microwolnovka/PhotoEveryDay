#include "phedfastcgihandler.h"

using namespace photoeveryday;

PhedFastcgiHandler::PhedFastcgiHandler(fastcgi::ComponentContext *context) :
    db("localhost"),fastcgi::Component(context), requestNumber(0) {
}

void PhedFastcgiHandler::handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    request->setHeader("Success header", "success");
   // printf("\n<==========%d==========>\n", requestNumber++);
    //printf("request has arrived:\n");
    if (request->getRequestMethod() == "POST"){
        this->handlePostRequest(request, context);
    }else{
        this->handleGetRequest(request, context);
    }

    //printf("<======================>\n");
}

void PhedFastcgiHandler::handleUploadPhotoRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    //printf("This's was photo upload!\n");
    std::string header = "X-FILE";
    header = request->getHeader(header);
    request->setHeader("Filename", header);
}

void PhedFastcgiHandler::handleInfoPhotoRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    //printf("This is info request!\n");
    //printf("We have recieved %d args!\n",request->countArgs());
    if(request->countArgs() >= 2){
        std::string name = request->getArg("user");
        std::string file = request->getArg("FileName");
        db.addPhotoInfo(name, file);
        request->setHeader("MONGO","inserted!");
    }

}

void PhedFastcgiHandler::handlePostRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    //printf("it's POST method\n");
    //printf("content length: %d\n", request->getContentLength());
    //fastcgi::DataBuffer data = request->requestBody();
    if(request->hasHeader("X-FILE")){
       this->handleUploadPhotoRequest(request, context);
    }else if(request->hasHeader("GIF")){
        this->handleMakeGifRequest(request, context);
    }else{
        this->handleInfoPhotoRequest(request, context);
    }
    //std::string buffer;
    //data.toString(buffer);
    //printf(" Request Body by the way:\n %s\n",buffer.c_str());
}

void PhedFastcgiHandler::handleMakeGifRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    //printf("make gif\n");
    if(request->hasArg("user")){
        auto user = request->getArg("user");
        //printf("USER!!%s\n",user.c_str());
        std::string* json = db.getJSONinfo(user);
        request->write(json->c_str(),json->length());
    }
}

void PhedFastcgiHandler::handleGetRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    //printf("it's GET method\n");
    if(request->hasHeader("DEBUG")){
        db.printAllBase();
    };
}

void PhedFastcgiHandler::onLoad(){
}

void PhedFastcgiHandler::onUnload(){

}

PhedFastcgiHandler::~PhedFastcgiHandler(){
}
