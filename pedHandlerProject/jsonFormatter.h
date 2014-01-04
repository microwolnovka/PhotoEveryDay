#pragma once
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <vector>

class jsonFormatter{

public:
   std::string* vectorToJSON (std::vector<std::string>* files);
};



