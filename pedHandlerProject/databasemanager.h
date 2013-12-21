#pragma once

#include <mongo/client/dbclient.h>



class DataBaseManager
{
public:
    DataBaseManager(const char* basename);
    ~DataBaseManager();
    void addPhotoInfo(std::string& user, std::string& filename);
    std::string* getJSONinfo(std::string& user);
    void printAllBase();

private:
    mongo::DBClientConnection DBConnect;


};

