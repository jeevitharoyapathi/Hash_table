#pragma once
#include "Interfaces05.h"

// creating keyvalue pair to store next ptr 
class KeyValue
{
public:
	CompositeKey Key;
	int Value;
	KeyValue * Next;
	//virtual void test();
	KeyValue(){ Next = NULL; }
	~KeyValue(){}
	CompositeKey getKey();
	void setKey(CompositeKey Key);
	int getValue();
	void setValue(int value);
	KeyValue * getNext();
	void setNext(KeyValue * next);
};