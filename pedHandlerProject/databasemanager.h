#pragma once

#include <mongo/client/dbclient.h>
#include <vector>


class DataBaseManager
{
public:
    DataBaseManager(const char* basename);
    ~DataBaseManager();
    void addPhotoInfo(std::string& user, std::string& filename);
    std::string* getJSONinfo(std::string& user);
    void printAllBase();
    std::vector<std::string>* getUserFiles(const std::string* user);
private:
    mongo::DBClientConnection DBConnect;


};

