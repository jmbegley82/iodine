/* LList.cpp
 *
 */

#define LLIST_CHUNK_SIZE 64

#include <cstdlib>
#include <cassert>
#include "LList.h"

template <class T> LList<T>::LList() {
	_llitems = static_cast<LLitem<T>*>(malloc(LLIST_CHUNK_SIZE * sizeof(LLitem<T>)));
	for(int i=0; i<LLIST_CHUNK_SIZE; ++i) {
		_llitems[i].prev = NULL;
		_llitems[i].next = NULL;
		_llitems[i].status = 0;
	}
	_nextFreeSlot = 0;
	_countMax = LLIST_CHUNK_SIZE;
}

template <class T> LList<T>::~LList() {
	free(_llitems);
}

template <class T> void LList<T>::Add(T item) {
	if(_nextFreeSlot == _countMax) {
		Compact();
		//assert(0);
	}
	LLitem<T>* prev = NULL;
	LLitem<T>* next = NULL;
	int prevIdx = _nextFreeSlot - 1;
	if(prevIdx >= 0) {
		prev = &_llitems[prevIdx];
	}
	assert(_llitems[_nextFreeSlot].status == 0);
	_llitems[_nextFreeSlot].prev = prev;
	_llitems[_nextFreeSlot].next = next;
	_llitems[_nextFreeSlot].status = 1;
	_llitems[_nextFreeSlot].item = item;
	if(prevIdx >= 0) {
		prev->next = &_llitems[_nextFreeSlot];
	}
	++_nextFreeSlot;
}

template <class T> LLitem<T>* LList<T>::Get(unsigned int index) {
	LLitem<T>* retval = NULL;
	if(index < _nextFreeSlot && _nextFreeSlot > 0) {
		//retval = &_llitems[index];
		int realidx = 0;
		LList<T>::iterator i = GetFirst();
		while(retval == NULL && realidx < _nextFreeSlot && i != NULL) {
			if(realidx == index) {
				retval = i;
			} else {
				++realidx;
				i = i->next;
			}
		}
	}
	return retval;
}

template <class T> LLitem<T>* LList<T>::GetFirst() {
	LLitem<T>* retval = NULL;
	if(_nextFreeSlot > 0) {
		//retval = &_llitems[0];
		int realidx = 0;
		while(retval == NULL && realidx < _nextFreeSlot) {
			if(_llitems[realidx].status == 1) {
				retval = &_llitems[realidx];
			} else {
				++realidx;
			}
		}
		//this should probably be unnecessary, but i'd rather just add it now
		//while(retval->prev != NULL) {
		//	retval = retval->prev;
		//}
		// TODO:check to make sure it's actually the first
		//assert(retval->prev == NULL);
	}
	return retval;
}

template <class T> LLitem<T>* LList<T>::GetLast() {
	LLitem<T>* retval = NULL;
	if(_nextFreeSlot > 0) {
		retval = &_llitems[_nextFreeSlot - 1];
		// TODO:check to make sure it's actually the last
		while(retval->next != NULL) {
			retval = retval->next;
		}
		assert(retval->next == NULL);
	}
	return retval;
}

template <class T> int LList<T>::GetCount() {
	int retval = 0;
	for(int i=0; i<_nextFreeSlot; ++i) {
		if(_llitems[i].status == 1) ++retval;
	}
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
	//item->prev = NULL;
	//item->next = NULL;
	item->status = -1;
}

template <class T> void LList<T>::Compact() {
	unsigned int realcount = 0;
	for(int i=0; i<_nextFreeSlot; ++i) {
		//assert(_llitems[i].status == 1 || _llitems[i].status == -1);
		if(_llitems[i].status == -1) {
			// garbage-collect
		} else if (_llitems[i].status == 1) {
			if(i != realcount) {
				_llitems[realcount].prev = _llitems[i].prev;
				_llitems[realcount].item = _llitems[i].item;
				_llitems[realcount].next = _llitems[i].next;
				_llitems[realcount].status = _llitems[i].status;
			}
			++realcount;
		}
	
	}
	// the following code should be prefaced with a check to see if it's necessary/beneficial
	LLitem<T>* newset = static_cast<LLitem<T>*>(malloc((realcount + LLIST_CHUNK_SIZE) * sizeof(LLitem<T>)));
	for(int i=0; i<realcount; ++i) {
		newset[i].prev = _llitems[i].prev;
		newset[i].item = _llitems[i].item;
		newset[i].next = _llitems[i].next;
		newset[i].status = _llitems[i].status;
	}
	for(int i=realcount; i<realcount+LLIST_CHUNK_SIZE; ++i) {
		newset[i].prev = NULL;
		newset[i].next = NULL;
		newset[i].status = 0;
	}
	free(_llitems);
	_llitems = newset;
}

template <class T> void LList<T>::Clear() {
	free(_llitems);
	_llitems = static_cast<LLitem<T>*>(malloc(LLIST_CHUNK_SIZE * sizeof(LLitem<T>)));
	_nextFreeSlot = 0;
	_countMax = LLIST_CHUNK_SIZE;
}

#if defined DEBUG
#include "Atom.h"
template class LList<Atom*>;
#endif //DEBUG

#include "Sprite.h"
template class LList<Sprite*>;
