/* LList.cpp
 *
 */

/*
template <class T> class LLitem {
public:
	LLitem(LLitem* prev, T* item, LLitem* next);
	LLitem* prev;
	T* item;
	LLitem* next;
};

template <class T> class LList {
public:
	LList();
	~LList();
	void Add(const T* item);
	LLitem* Get(unsigned int index);
private:
	LLitem** _llitems;
};
 */

#define LLIST_CHUNK_SIZE 64

#include <cstdlib>
#include "LList.h"

template <class T> LLitem<T>::LLitem(LLitem<T>* prev, T item, LLitem<T>* next) {
	this->prev = prev;
	this->item = &item;
	this->next = next;
	this->done = false;
}

template <class T> LList<T>::LList() {
	_llitems = static_cast<LLitem<T>**>(malloc(LLIST_CHUNK_SIZE * sizeof(LLitem<T>*)));
	for(int i=0; i<LLIST_CHUNK_SIZE; ++i) {
		_llitems[i] = NULL;
	}
	_nextFreeSlot = 0;
	_countMax = LLIST_CHUNK_SIZE;
}

template <class T> LList<T>::~LList() {
	// TODO:  anything
}

template <class T> void LList<T>::Add(T item) {
	if(_nextFreeSlot == _countMax) {
		// need to increase size to accomodate additional items
	}
	LLitem<T>* prev;
	LLitem<T>* next;
	int prevIdx = _nextFreeSlot - 1;
	if(prevIdx > 0) {
		prev = _llitems[prevIdx];
	}
	LLitem<T>* llitem = new LLitem<T>(prev, item, NULL);
	_llitems[_nextFreeSlot] = llitem;
	++_nextFreeSlot;
}

template <class T> LLitem<T>* LList<T>::Get(unsigned int index) {
	LLitem<T>* retval = NULL;
	if(index < _nextFreeSlot) retval = _llitems[index];
	return retval;
}

template <class T> void LList<T>::Remove(LLitem<T>* item) {
	// deal with the item itself
	LLitem<T>* prev = item->prev;
	LLitem<T>* next = item->next;
	if(prev != NULL) {
		prev->next = next;
	}
	if(next != NULL) {
		next->prev = prev;
	}
	// mark the item for garbage collection
	item->prev = NULL;
	item->next = NULL;
	item->done = true;
}

template <class T> void LList<T>::Compact() {
	unsigned int realcount = 0;
	for(int i=0; i<_nextFreeSlot; ++i) {
		if(_llitems[i]->done) {
			// redrum
			delete _llitems[i];
		} else {
			// this entry survives
			_llitems[realcount] = _llitems[i];
			++realcount;
		}
	}
	// the following code should be prefaced with a check to see if it's necessary/beneficial
	LLitem<T>** newset = static_cast<LLitem<T>**>(malloc((realcount + LLIST_CHUNK_SIZE) * sizeof(LLitem<T>*)));
	for(int i=0; i<realcount; ++i) {
		newset[i] = _llitems[i];
	}
	for(int i=realcount; i<realcount+LLIST_CHUNK_SIZE; ++i) {
		newset[i] = NULL;
	}
	free(_llitems);
	_llitems = newset;
}

#if defined DEBUG
#include "Atom.h"
template class LList<Atom*>;
#endif //DEBUG
