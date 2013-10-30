#ifndef DBENGINE_H
#define DBENGINE_H

#include <stdio.h>
#include <string>
#include <exception>

namespace DBEngineNS
{

class DBEngine{
private:
    FILE* DBFIle;
public:
    DBEngine();
    DBEngine(std::string fileName);
    bool setValue(int id, std::string value);
    std::string getValue(int id);
    ~DBEngine();
};

}

#endif // DBENGINE_H
