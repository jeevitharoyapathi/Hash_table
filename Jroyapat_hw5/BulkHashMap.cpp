#include "BulkHashMap.h"



BulkHashMap:: BulkHashMap()
{

	HashTable = std::vector<KeyValue *>(11);
	HashSize = 11;
	CurrSize = 0;

}
void BulkHashMap::insert(std::vector<std::pair<CompositeKey, int> >& data)
{
	for (int i = 0; i < data.size(); i++)
	{
		CurrSize++;
		unsigned long index;
		KeyValue * NewKV;
		if (CurrSize < HashTable.capacity() / 2)
		{
			index = GetIndex(data[i].first);
			NewKV = new KeyValue();
			NewKV->setKey(data[i].first);
			NewKV->setValue(data[i].second);
			NewKV->setNext(NULL);
			insertintoTable(NewKV, index);
		}
		else

		{
			std::vector<KeyValue *> tempKeyValue = HashTable;
			HashSize = HashTable.capacity() * 2 + 1;
			HashTable.clear();
			HashTable.resize(HashSize);
			KeyValue * KV;
			for (int j = 0; j < tempKeyValue.capacity();j++)
			{
				KV = tempKeyValue[j];
				if (KV != NULL)
				{
					KeyValue * temp = KV;
					index = GetIndex(KV->getKey());
					NewKV = new KeyValue();
					NewKV->setKey(KV->getKey());
					NewKV->setValue(KV->getValue());
					NewKV->setNext(NULL);
					insertintoTable(NewKV, index);
					while (temp->getNext())
					{
						temp = temp->getNext();
						index = GetIndex(temp->getKey());
						NewKV = new KeyValue();
						NewKV->setKey(temp->getKey());
						NewKV->setValue(temp->getValue());
						NewKV->setNext(NULL);
						insertintoTable(NewKV, index);
					}
				}
			}
			index = GetIndex(data[i].first);
			NewKV = new KeyValue();
			NewKV->setKey(data[i].first);
			NewKV->setValue(data[i].second);
			NewKV->setNext(NULL);
			insertintoTable(NewKV, index);
		}


	}

}

void BulkHashMap::insertintoTable(KeyValue * kv, int index)
{

	if (HashTable[index] == NULL)
		HashTable[index] = kv;
	else
	{
		KeyValue * NewNext = HashTable[index];
		while (NewNext->getNext())
		{
			NewNext = NewNext->getNext();
		}
		NewNext->setNext(kv);
	}
}
unsigned long BulkHashMap::GetIndex(CompositeKey key)
{
	unsigned long  h = (unsigned long)2166136261;
	//h = (h * 16777619) ^ key.key1;
	//h = (h * 16777619) ^ (unsigned long)key.key2;
	//h = (h * 16777619) ^ key.key3;
	h = h  ^ key.key1;
	h += (h << 1) + (h << 4) + (h << 7) + (h << 8) + (h << 24);
	h = h ^ (unsigned long)key.key2;
	h += (h << 1) + (h << 4) + (h << 7) + (h << 8) + (h << 24);
	h = h  ^ key.key3;
	h += (h << 1) + (h << 4) + (h << 7) + (h << 8) + (h << 24);
	// get index according to table size
	unsigned long  index = h%HashSize;
	return index;

}
int BulkHashMap:: getValue(CompositeKey key)
{

	unsigned long  index = GetIndex(key);
	if (HashTable[index])
	{
		if (HashTable[index]->getKey().operator==(key))
		{
			return HashTable[index]->getValue();
		}
		else
		{
			KeyValue * NextValue = HashTable[index]->getNext();
			while (NextValue)
			{
				if (NextValue->getKey().operator==(key))
				{
					return NextValue->getValue();
					break;
				}
				else
					NextValue = NextValue->getNext();

			}
		}

	}
	return 0;
}