#include "HashMap.h"
typedef int a;

HashMap::HashMap()
{
	HashTable = std::vector<KeyValue *>(11);
	HashSize = 11;
	CurrSize = 0;
}

void HashMap::insert(CompositeKey key, int value)
{ 
	int z = 5;
	int *p;
	p = &z;
	//FNV method to  get hash value
	CurrSize++;
	unsigned long index;
	KeyValue * NewKV;
	if (CurrSize < HashTable.capacity() / 2)
	{
		index = GetIndex(key);
		NewKV = new KeyValue();
		NewKV->setKey(key);
		NewKV->setValue(value);
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
		for (int j = 0; j < tempKeyValue.capacity(); j++)
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
		index = GetIndex(key);
		NewKV = new KeyValue();
		NewKV->setKey(key);
		NewKV->setValue(value);
		NewKV->setNext(NULL);
		insertintoTable(NewKV, index);
	}

}
void HashMap::remove(CompositeKey key)
{
	unsigned long index = GetIndex(key);
	if (HashTable[index])
	{
		if (HashTable[index]->getKey().operator==(key))
		{
			if (HashTable[index]->getNext())
				HashTable[index] = HashTable[index]->getNext();
			else
				HashTable[index] = NULL;
			CurrSize--;
		}
		else
		{
			KeyValue * Temp = HashTable[index]->getNext();
			KeyValue * Prev = HashTable[index];
			while (Temp)
			{
				if (Temp->getKey().operator==(key))
				{
					Prev->setNext(Temp->getNext());
					CurrSize--;
					break;

				}
				Prev = Temp;
				Temp = Temp->getNext();
			}

		}


	}


}

void HashMap::insertintoTable(KeyValue * kv, int index)
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
unsigned long HashMap::GetIndex(CompositeKey key)
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

bool HashMap::containsKey(CompositeKey key)
{
	unsigned long index = GetIndex(key);
	if (HashTable[index])
	{
		if (HashTable[index]->getKey().operator==(key))
			return true;
		else
		{
			KeyValue * Temp = HashTable[index]->getNext();
			while (Temp)
			{
				if (Temp->getKey().operator==(key))
				{
					return true;
					break;
				}
				Temp = Temp->getNext();
			}

		}
	}

	return false;
}
int HashMap::getValue(CompositeKey key)
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



int HashMap::HPartition(int Left, int Right, std::vector<KeyValue *>& vec)

{
	int p = (Left + Right) / 2;
	if (vec[Right]->getKey().operator< (vec[p]->getKey()))
		Exchange(p, Right, vec);
	if (vec[Right]->getKey().operator<(vec[Left]->getKey()))
		Exchange(Left, Right, vec);
	if (vec[p]->getKey().operator<(vec[Left]->getKey()))
		Exchange(Left, p, vec);

	if (vec[p]->getKey().operator<(vec[Left]->getKey()))
	{
		if (vec[Right]->getKey().operator<(vec[Left]->getKey()))
			p = Right;
		else p = Left;
	}
	else {
		if (vec[Right]->getKey().operator<(vec[Left]->getKey()))

			p = Left;
		else if (vec[Right]->getKey().operator<(vec[p]->getKey()))

			p = Right;

	}
	CompositeKey Pivot = vec[p]->getKey();
	Exchange(Left, p, vec);
	int L = Left;
	int R = Right;
	while (L < R)
	{
		while ((Pivot.operator<(vec[R]->getKey() )) && (L < R))
		{
			R--;
		}
		while (((vec[L]->getKey().operator<(Pivot)) || vec[L]->getKey().operator==(Pivot)) && (L < R))
		{
			L++;
		}
		if (L < R)
			Exchange(L, R, vec);

	}
	Exchange(Left, R, vec);
	return R;
}
void HashMap::RandomQuickSort(int Left, int Right, std::vector<KeyValue * >& vec)
{
	if (Left < Right)
	{
		int Count = Right - Left + 1;
		if (Count <= 3)
			QSort(Left, Right, vec);
		else
		{
			int q = HPartition(Left, Right, vec);
			RandomQuickSort(Left, q - 1, vec);
			RandomQuickSort(q + 1, Right, vec);
		}
	}

}

void   HashMap::QSort(int left, int right, std::vector<KeyValue *>& vec)
{
	int size = right - left + 1;
	if (size <= 1)
		return;
	if (size == 2) {
		if (vec[right]->getKey().operator<(vec[left]->getKey()))
			Exchange(left, right, vec);
		return;
	}
	else
	{
		if (vec[right-1]->getKey().operator<(vec[left]->getKey()))
			Exchange(left, right - 1, vec);
		if (vec[right]->getKey().operator<(vec[left]->getKey()))
			Exchange(left, right, vec);
		if (vec[right]->getKey().operator<(vec[right-1]->getKey()))
			Exchange(right - 1, right, vec);
	}
}
void HashMap::Exchange(int I1, int I2, std::vector<KeyValue *>& vec)
{

	KeyValue * Temp = vec[I1];
	vec[I1] = vec[I2];
	vec[I2] = Temp;

}

int HashMap::kthMinValue(int k)
{
	int count = 0;
	std::vector<KeyValue *> Tempvector;// = HashTable;
	//RandomQuickSort(0, Tempvector.size() - 1, Tempvector);
	for (int i = 0; i < HashSize; i++)
	{

		if (HashTable[i] != NULL)// && Tempvector.size() < k+1)
		{
			Tempvector.push_back(HashTable[i]);
			KeyValue * NextValue = HashTable[i]->getNext();
			while (NextValue != NULL)
			{
				Tempvector.push_back(NextValue);
				NextValue = NextValue->getNext();
			}
			/*if (Tempvector.size() >= k+1)

			{
				RandomQuickSort(0, Tempvector.size()-1, Tempvector);
				break;
			}*/
		}
	}
	RandomQuickSort(0, Tempvector.size() - 1, Tempvector);
	return Tempvector[k]->getValue();

}

int HashMap::size()
{

	return CurrSize;
}