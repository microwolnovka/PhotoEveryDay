#include "phedfastcgihandler.h"

using namespace photoeveryday;

bool PhedFastcgiHandler::moveFile(const std::string& src, const std::string& dest){
  boost::filesystem3::path srcPath(src);
  boost::filesystem3::path destPath(dest);

  try {
    rename(srcPath, destPath);
  }
  catch (...)
  {
    return false;
  }

  return exists(destPath);
}

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

void PhedFastcgiHandler::handleUploadPhotoRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("This's was photo upload!\n");
    std::string header = "X-FILE";
    header = request->getHeader(header);
    request->setHeader("Filename", header);
}

void PhedFastcgiHandler::handleInfoPhotoRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("This is info request!\n");
    printf("We have recieved %d args!\n",request->countArgs());
    if(request->countArgs() >= 2){
        auto name = request->getArg("user");
        auto file = request->getArg("FileName");
        std::string jpgName = file + ".jpeg";
        printf("jpgName: %s\n", jpgName.c_str());
        if(moveFile(file, jpgName)){
            printf("renamed\n");
        }
        auto obj = mongo::BSONObjBuilder().append("name", name).append("FileName", jpgName).obj();
        DBConnect.insert("PHEDdb.info", obj);
        request->setHeader("MONGO","inserted!");
    }
}

void PhedFastcgiHandler::handlePostRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("it's POST method\n");
    printf("content length: %d\n", request->getContentLength());
    fastcgi::DataBuffer data = request->requestBody();
    if(request->hasHeader("X-FILE")){
       this->handleUploadPhotoRequest(request, context);
    }else{
        this->handleInfoPhotoRequest(request, context);
    }
    std::string buffer;
    data.toString(buffer);
    printf("Request Body by the way:\n %s\n",buffer.c_str());
}

void PhedFastcgiHandler::handleGetRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("it's GET method\n");
    if(request->hasHeader("DEBUG")){
        printf("were ");
        std::cout << "count:" << DBConnect.count("PHEDdb.info") << std::endl;

        auto cursor = DBConnect.query("PHEDdb.info", mongo::BSONObj());
        while (cursor->more())
            std::cout << cursor->next().toString() << std::endl;

    }
    std::cout << "count:" << DBConnect.count("PHEDdb.info") << std::endl;
}

void PhedFastcgiHandler::onLoad(){
    DBConnect.connect("localhost");

    std::cout << "count:" << DBConnect.count("PHEDdb.info") << std::endl;
}

void PhedFastcgiHandler::onUnload(){

}

PhedFastcgiHandler::~PhedFastcgiHandler(){
}
