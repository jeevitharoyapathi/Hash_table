#include "Factory05.h"
#include "HashMap.h"
#include "BulkHashMap.h"

Factory05::Factory05()
{
}

Factory05::~Factory05()
{
}
 
void * Factory05::create(std::string name)
{
  if(name == "IHashMap1"){
    return  new HashMap();
  } else if(name == "IHashMap2"){
	  return new HashMap();
  } else if(name == "IHashMap3"){
	  return new HashMap();
  } else if(name == "IHashMap4"){
	  return new HashMap();
  } else if(name == "IBulkHashMap"){
	  return new BulkHashMap();
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory05();  
}

}
