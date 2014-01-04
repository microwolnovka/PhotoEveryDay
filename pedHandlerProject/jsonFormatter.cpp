#include "jsonFormatter.h"
using namespace rapidjson;
std::string* jsonFormatter::vectorToJSON(std::vector<std::string> *files){
        rapidjson::Document fromScratch;

        // define the document as an object rather than an array
       fromScratch.SetObject();

        // create a rapidjson array type with similar syntax to std::vector
        rapidjson::Value array(rapidjson::kArrayType);

        // must pass an allocator when the object may need to allocate memory
        rapidjson::Document::AllocatorType& allocator = fromScratch.GetAllocator();

        // chain methods as rapidjson provides a fluent interface when modifying its objects
        //array.PushBack("hello", allocator).PushBack("world", allocator);

        for (std::string file : *files)
            array.PushBack(file.c_str() ,allocator);       // May look a bit strange, allocator is needed for potentially realloc. We normally uses the document's.
        fromScratch.AddMember("files", array, allocator);
        // Convert JSON document to string
        GenericStringBuffer< UTF8<> > buffer;
        Writer< GenericStringBuffer< UTF8<> > > writer(buffer);

        fromScratch.Accept(writer);


        std::string *str = new std::string(buffer.GetString());
               // new std::string( "jsa");
        //printf("JSON: %s\n", str);
        return str;
}


