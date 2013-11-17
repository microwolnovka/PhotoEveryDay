#include <iostream>
#include <cstdlib>
#include <mongo/client/dbclient.h>
//#include <mongo/bson/bson.h>

void run() {
  mongo::DBClientConnection c;
  c.connect("localhost");
  mongo::BSONObj p = mongo::BSONObjBuilder().append("name", "Joe").append("age", 33).obj();
  c.insert("tutorial.persons", p);
  std::cout << "count:" << c.count("tutorial.persons") << std::endl;

  auto cursor =
   c.query("tutorial.persons", mongo::BSONObj());
  while (cursor->more())
     std::cout << cursor->next().toString() << std::endl;
}

int main(){
    try {
        run();
        std::cout << "connected ok" << std::endl;
    } catch( const mongo::DBException &e ) {
        std::cout << "caught " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

