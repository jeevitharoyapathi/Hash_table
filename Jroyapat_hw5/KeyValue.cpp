#include "KeyValue.h"


void KeyValue::setValue(int value){
 Value = value;
}
int KeyValue::getValue(){
	return Value;
}
void KeyValue::setKey(CompositeKey key){
	Key = key;
}
CompositeKey KeyValue::getKey(){
	return this->Key;
}

void KeyValue::setNext(KeyValue * next){
	Next = next;
}
KeyValue * KeyValue::getNext(){
	return Next;
}
