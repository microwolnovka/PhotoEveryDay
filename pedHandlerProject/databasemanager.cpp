#include "databasemanager.h"

DataBaseManager::DataBaseManager(const char* basename)
{
    try {
        DBConnect.connect(basename);
        std::cout << "connect to database is ok" << std::endl;
    } catch( const mongo::DBException &e ) {
        std::cout << "caught " << e.what() << std::endl;
    }

}

void DataBaseManager::printAllBase(){
    std::cout << "count:" << DBConnect.count("PHEDdb.info") << std::endl;
    auto cursor = DBConnect.query("PHEDdb.info", mongo::BSONObj());
    while (cursor->more())
       std::cout << cursor->next().toString() << std::endl;
    std::cout << "count:" << DBConnect.count("PHEDdb.info") << std::endl;

}

void DataBaseManager::addPhotoInfo(std::string & user, std::string & filename){
    try{
        auto obj = mongo::BSONObjBuilder().append("name", user).append("FileName", filename).obj();
        DBConnect.insert("PHEDdb.info", obj);

    } catch(const mongo::DBException &e){
        std::cout << "caught " << e.what() <<std::endl;
    }
}

std::string* DataBaseManager::getJSONinfo(std::string & user){
    try{
        std::auto_ptr<mongo::DBClientCursor> cursor =
         DBConnect.query("PHEDdb.info", BSON("name"<<user));
        std::string* result = new std::string("{\n \"photos\": [\n");
        while(cursor->more()){
            auto next = cursor->next();
            if(next.hasField ("FileName")){
                auto fileName = next.getStringField("FileName");
                result->append("\"");
                result->append(fileName);
                if(cursor->more())
                    result->append("\",\n");
                else
                    result->append("\"\n");
            }
        }
        result->append(" ]\n}");
        return result;
    }catch(const mongo::DBException &e){
        std::cout << "caught " << e.what() <<std::endl;
    }

}


std::vector<std::string>* DataBaseManager::getUserFiles(const std::string *user){
    std::auto_ptr<mongo::DBClientCursor> cursor =
     DBConnect.query("PHEDdb.info", BSON("name"<<*user));
    std::vector<std::string> *vec = new std::vector<std::string>;
    try{
        while(cursor->more()){
            auto next = cursor->next();
            if(next.hasField ("FileName")){
                auto fileName = next.getStringField("FileName");
                vec->push_back(fileName);
            }
        }
    }catch(const mongo::DBException &e){
        std::cout << "caught " << e.what() <<std::endl;
    }
    return vec;
}


DataBaseManager::~DataBaseManager(){

}

