#include <iostream>
#include <cstdlib>


#include <boost/filesystem.hpp>
//#include <mongo/bson/bson.h>

bool moveFile(const std::string& src, const std::string& dest){
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


int main(){
    std::string file("/tmp/photos/0000000003");
    std::string jpgName = file + ".jpg";
    moveFile(file, jpgName);
}


