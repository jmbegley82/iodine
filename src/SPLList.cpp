/* SPLList.cpp
 *
template <typename T> struct Litem {
	Litem<T>* prev;
	T item;
	Litem<T>* next;
};

template <class T> class SPLList {
public:
	SPLList();
	~SPLList(); 
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
#include "SPLList.h"

template <class T> SPLList<T>::SPLList() {
	_first = _last = _garbage = NULL;
	_count = 0;
}

template <class T> SPLList<T>::~SPLList() {
	Clear();
}

template <class T> Litem<T>* SPLList<T>::GetFirst() {
	return _first;
}

template <class T> Litem<T>* SPLList<T>::GetLast() {
	return _last;
}

template <class T> unsigned int SPLList<T>::GetCount() {
	return _count;
}

template <class T> Litem<T>* SPLList<T>::Add(T obj) {
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

template <class T> void SPLList<T>::Remove(Litem<T>* obj) {
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

template <class T> void SPLList<T>::Clear() {
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
template class SPLList<Sprite*>;