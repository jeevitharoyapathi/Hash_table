#pragma once
#include "Interfaces05.h"
#include "KeyValue.h"

class BulkHashMap : public IBulkHashMap {
	
public:
	std::vector<KeyValue*> HashTable;
	int HashSize;
	int CurrSize;
	BulkHashMap();
	~BulkHashMap() { }
	void insert(std::vector<std::pair<CompositeKey, int> >& data);
	int getValue(CompositeKey key);
	void insertintoTable(KeyValue *Kv, int index);
	unsigned long  GetIndex(CompositeKey key);
};