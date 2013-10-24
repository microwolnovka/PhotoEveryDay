#include <fastcgi2/component.h>                
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "DBEngine.h"

class SimpleClass : virtual public fastcgi::Component, virtual public fastcgi::Handler {
private:        
        DBEngineNS::DBEngine* dataBaseEngine;
public:
        SimpleClass(fastcgi::ComponentContext *context) :
                fastcgi::Component(context) {
        }
        virtual ~SimpleClass() {
        }

public:
        virtual void onLoad() {
                dataBaseEngine = new DBEngineNS::DBEngine();
        }
        virtual void onUnload() {
                delete dataBaseEngine;
        }
        virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context) {	
		printf("I get new reques\n");

                std::string methodStr = request->getRequestMethod();

                if (request->hasArg("id") && request->hasArg("value")){
                        std::string strId = request->getArg("id");
                        int id = atoi(strId.c_str());		
                        std::string value = request->getArg("value");
                        dataBaseEngine->setValue(id, value);
                        printf("and did what it had wanted\n");
                }
                else{
                        printf("and it was bad\n");
                        request->setStatus(400);
                }		
                request->setHeader("Header", "Head");
        }

};

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("simple_factory", SimpleClass)
FCGIDAEMON_REGISTER_FACTORIES_END()