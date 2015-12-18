#include "Interfaces05.h"
#include "KeyValue.h"

class  HashMap : public IHashMap{
public:
	int CurrSize;
	std::vector<KeyValue *>  HashTable;
	int HashSize;
	HashMap();
	~HashMap() { }
	void insert(CompositeKey key, int value);
	void remove(CompositeKey key);
	bool containsKey(CompositeKey key);
	int getValue(CompositeKey key);
	int kthMinValue(int k);
	void insertintoTable(KeyValue *Kv, int index);
	unsigned long  GetIndex(CompositeKey key);
	int size();
	int HPartition(int L, int R, std::vector<KeyValue *> & Input);
	void RandomQuickSort(int L, int R, std::vector<KeyValue *> & input);
	void Exchange(int I1, int I2, std::vector<KeyValue *>& vec);
	void  QSort(int left, int right, std::vector<KeyValue *>& vec);
};