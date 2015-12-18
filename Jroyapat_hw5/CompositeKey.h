#include "Interfaces05.h"

class CCompositeKey  {
	int key1;
	float key2;
	int key3;

	void operator=(const CompositeKey& rhs);
	bool operator<(const CompositeKey& rhs) const;
	bool operator==(const CompositeKey& rhs) const;
	void operator=(CompositeKey& rhs);
	bool operator<(CompositeKey& rhs);
	bool operator==(CompositeKey& rhs);
};