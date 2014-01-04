#include "phedfastcgihandler.h"

using namespace photoeveryday;


PhedFastcgiHandler::PhedFastcgiHandler(fastcgi::ComponentContext *context) :
    db("localhost"),fastcgi::Component(context), requestNumber(0),formatter() {

    google::InitGoogleLogging("PhotoServer");
}

void PhedFastcgiHandler::handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("\n<==========%d==========>\n", requestNumber++);
    printf("request has arrived:\n");
    if (request->getRequestMethod() == "POST"){
        this->handlePostRequest(request, context);
    }else{
        this->handleGetRequest(request, context);
    }
    printf("<======================>\n");
}

bool PhedFastcgiHandler::moveFile(const std::string& src, const std::string& dest){
    boost::filesystem2::path srcPath(src);
    boost::filesystem2::path destPath(dest);
    if (!exists(destPath)){
        boost::filesystem2::create_directory(destPath);
    }
    int counter = 1;
    char buff[100];
    sprintf(buff, "%simage%d.jpg", dest.c_str(), counter);
    std::string newDest = buff;
    while(boost::filesystem2::exists(newDest)){
        counter++;
        sprintf(buff, "%simage%d.jpg", dest.c_str(), counter);
        newDest = buff;
    }

    boost::filesystem2::path newDestPath(newDest);

    printf("newDest: %s\n", newDest.c_str());

    try {
          rename(srcPath, newDestPath);
    }
    catch (...)
    {
        printf("error copyFIle\n");
        LOG(ERROR) << "can't registr new photo in " << newDestPath;
        return false;
    }

    LOG_IF(INFO, exists(newDestPath)) << "registred new photo in " << newDestPath;

    return exists(newDestPath);
}

bool PhedFastcgiHandler::makeMovie(const std::string& srcFolder){
    const std::string srcPath = srcFolder;
    const std::string destPath = srcFolder;
    const std::string destFileName = "movie.avi";

    chdir(srcPath.c_str());

    std::string rmComand = "rm ";
    rmComand.append(destPath);
    rmComand.append(destFileName);


    std::string createCommand = "avconv -r 3 -f image2 -i image%d.jpg ";
    createCommand.append(destPath);
    createCommand.append(destFileName);

    try{
        system(rmComand.c_str());
        system(createCommand.c_str());
    }catch(...){
        LOG(ERROR) << "can't create new video in " << destPath;
        return false;
    }
    printf("movieCreated!\n");
    LOG(INFO) << "created new video in"  << destPath << " name: " << destFileName;
    return true;
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
    if(request->hasArg("user") && request->hasArg("FileName")){
        std::string name = request->getArg("user");
        std::string file = request->getArg("FileName");
        db.addPhotoInfo(name, file);
        request->setHeader("MONGO","inserted!");

        std::string src = "/data/images/";
        std::string dest = src + request->getArg("user") + "/";
        src.append(request->getArg("FileName"));
        printf("src: %s\n", src.c_str());
        printf("des: %s\n", dest.c_str());
        bool result = moveFile(src, dest);
        printf("file moved: %d\n", result);
    }
}

void PhedFastcgiHandler::handlePostRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("it's POST method\n");
    printf("content length: %d\n", request->getContentLength());
    fastcgi::DataBuffer data = request->requestBody();
    if(request->hasHeader("X-FILE")){
       this->handleUploadPhotoRequest(request, context);
    }else if(request->hasHeader("AVI")){
        this->handleMakeMovieRequest(request, context);
    }else{
        this->handleInfoPhotoRequest(request, context);
    }
    std::string buffer;
    data.toString(buffer);
    printf(" Request Body by the way:\n %s\n",buffer.c_str());
}

void PhedFastcgiHandler::handleMakeMovieRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("make movie\n");
    if(request->hasArg("user")){
        auto user = request->getArg("user");
        std::string srcPath = "/data/images/" + user + "/";
        makeMovie(srcPath);
    }
}

void PhedFastcgiHandler::handleUserInfoRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    if(request->hasArg("user")){
        std::string user = request->getArg("user");
        auto v = db.getUserFiles(&user);
        std::string* json = formatter.vectorToJSON(v);
        request->write(json->c_str(),json->length());
        delete v;
        delete json;
    }
}



void PhedFastcgiHandler::handleGetRequest(fastcgi::Request *request, fastcgi::HandlerContext *context){
    printf("it's GET method\n");
    if(request->hasHeader("DEBUG")){
        db.printAllBase();
    }else{
        this->handleUserInfoRequest(request, context);
    }
}

void PhedFastcgiHandler::onLoad(){
}

void PhedFastcgiHandler::onUnload(){

}

PhedFastcgiHandler::~PhedFastcgiHandler(){
}
/* TODO:
 *make gif
 *logger...
 *
*/
