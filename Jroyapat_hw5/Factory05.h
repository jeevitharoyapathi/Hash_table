#pragma once

#include "ObjectFactory.h"

class Factory05 : public ObjectFactory {
public:
  Factory05();
  virtual ~Factory05();
  virtual void * create(std::string interface_name);
};
