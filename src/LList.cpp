/* LList.cpp
 *
template <typename T> struct Litem {
	Litem<T>* prev;
	T item;
	Litem<T>* next;
};

template <class T> class LList {
public:
	LList();
	~LList(); 
	Litem<T>* GetFirst();
	Litem<T>* GetLast();
	void Remove(Litem<T>* obj);
	Litem<T>* Add(T obj);
	unsigned int GetCount();
	void Clear();
	typedef Litem<T>* iterator;
private:
	Litem<T>* _first;
	Litem<T>* _last;
	Litem<T>* _garbage;
	unsigned int _count;
};
 */

#include <cstdlib>
#include "LList.h"

template <class T> LList<T>::LList() {
	_first = _last = _garbage = NULL;
	_count = 0;
}

template <class T> LList<T>::~LList() {
	Clear();
}

template <class T> Litem<T>* LList<T>::GetFirst() {
	return _first;
}

template <class T> Litem<T>* LList<T>::GetLast() {
	return _last;
}

template <class T> Litem<T>* LList<T>::GetByIndex(unsigned int idx) {
	// TODO: untested
	Litem<T>* retval = NULL;
	if(idx < _count) {
		unsigned int middle = _count/2;
		if(idx < middle) {
			// start at beginning
			retval = _first;
			for(int i=0; i<idx; ++i) {
				retval = retval->next;
			}
		} else {
			// start at end
			retval = _last;
			for(int i=_count; i>idx+1; --i) {
				retval = retval->prev;
			}
		}
	}
	return retval;
}

template <class T> LList<T> LList<T>::GetRange(Litem<T>* start, Litem<T>* end) {
	LList<T> retval;
	Litem<T>* itr = start;
	while(itr != NULL) {
		retval.Add(itr->item);
		if(itr->item == end->item)
			break;
		itr = itr->next;
	}
	return retval;
}

template <class T> unsigned int LList<T>::GetCount() {
	return _count;
}

template <class T> Litem<T>* LList<T>::Add(T obj) {
	Litem<T>* retval = static_cast<Litem<T>*>(malloc(sizeof(Litem<T>)));
	retval->prev = _last;
	retval->item = obj;
	retval->next = NULL;
	if(!_first)
		_first = retval;
	if(_last)
		_last->next = retval;
	_last = retval;
	++_count;
	return retval;
}

template <class T> void LList<T>::Remove(Litem<T>* obj) {
	Litem<T>* prev = obj->prev;
	Litem<T>* next = obj->next;
	if(obj == _first)
		_first = next;
	if(obj == _last)
		_last = prev;
	if(prev)
		prev->next = next;
	if(next)
		next->prev = prev;
	if(_garbage)
		free(_garbage);
	_garbage = obj;
	--_count;
}

template <class T> void LList<T>::Clear() {
	for(Litem<T>* i = _first; i != NULL; i = i->next) {
		Remove(i);
	}
	if(_garbage) {
		free(_garbage);
		_garbage = NULL;
	}
	_first = _last = NULL;
	_count = 0;
}

#include "Sprite.h"
template class LList<Sprite*>;
template class LList<int>;
