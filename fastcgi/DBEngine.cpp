#include "DBEngine.h"
using namespace DBEngineNS;

DBEngine::DBEngine(){
	DBEngine::DBFIle = fopen("superDataBase.DB","a+");
	if (NULL == DBEngine::DBFIle){
		throw new std::exception();
	}
}

DBEngine::DBEngine(std::string fileName){
	DBEngine::DBFIle = fopen(fileName.c_str(),"a+");
	if (NULL == DBEngine::DBFIle){
		throw new std::exception();
	}
}


bool DBEngine::setValue(int id, std::string value){
	fprintf(DBFIle, "%d = %s\n", id, value.c_str());
}

std::string DBEngine::getValue(int id){

}

DBEngine::~DBEngine(){
	fclose(DBFIle);
}