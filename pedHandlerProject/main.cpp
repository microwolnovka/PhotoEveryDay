#include <iostream>
#include <cstdlib>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <vector>

#include <boost/filesystem/v2/operations.hpp>
//#include <mongo/bson/bson.h>

bool moveFile1(const std::string& src, const std::string& dest){
  boost::filesystem2::path srcPath(src);
  boost::filesystem2::path destPath(dest);

  copy_file(srcPath, destPath);

  try {
      //copy_file(srcPath, destPath);
  }
  catch (...)
  {
    printf("error copyFIle\n");
    return false;
  }

  return exists(destPath);
}

using namespace rapidjson;

int main(){
    std::string file("/data/images/0000000003");
    std::string jpgName = file + ".jpg";
    moveFile1(file, jpgName);

}


