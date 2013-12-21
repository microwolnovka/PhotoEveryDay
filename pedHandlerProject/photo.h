#pragma once

#include <string>
#include "databasemanager.h"

class Photo
{
public:
    Photo();
    static unsigned int getNextUniqId();


private:
    unsigned int id;
    unsigned int PhotoPath;
    volatile static unsigned int nextUniqId;
};

