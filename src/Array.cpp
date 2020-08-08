/* Array.cpp
 *
 */

#include <string>
#include "Array.h"
#include "Atom.h"
#include "Sprite.h"
#include "AnimationSet.h"

#if defined DEBUGEXTRA
#include "Logger.h"
#endif //DEBUGEXTRA

#define OBJCHUNK 2

//template class Array<int>;
template class Array<Atom>;
template class Array<Sprite>;
template class Array<AnimationSet>;

template <class T>
Array<T>::Array() {
	_count = 0;
	_countMax = OBJCHUNK;
	_objects = static_cast<T**>(malloc(_countMax * sizeof(T*)));
	for(int i=0; i<_countMax; i++) {
		_objects[i] = NULL;
	}
}

template <class T>
Array<T>::~Array() {
	Clear();
	free(_objects);
}

template <class T>
void Array<T>::Add(T* obj) {
	//lol TODO fix this silliness
	Add_unsafe(obj);
}

template <class T>
T* Array<T>::GetByIndex(unsigned int idx) {
	T* retval = NULL;
	if(idx < _count) retval = _objects[idx];
	return retval;
}

template <class T>
bool Array<T>::Destroy(T* obj) {
	bool retval = false;
	for(unsigned int i=0; i<_count && !retval; i++) {
		if(_objects[i] == obj) {
			Destroy_unsafe(i);
			MakeContiguous();
			retval = true;
		}
	}
	return retval;
}

template <class T>
void Array<T>::Destroy_unsafe(unsigned int idx) {
	delete _objects[idx];
	_objects[idx] = NULL;
}

template <class T>
int Array<T>::Clear() {
	for(int i=0; i<_count; i++) {
		delete _objects[i];
		_objects[i] = NULL;
	}
	_count = 0;
	return 0;
}

template <class T>
int Array<T>::Shrink() {
#if defined DEBUGEXTRA
	Logger("Array::Shrink()");
#endif //DEBUGEXTRA
	//for now assume contiguous; also this shares a lot of code with Grow...
	int newcountmax = _count;  // the next addition will induce a Grow()
	T** newobjs = static_cast<T**>(malloc(newcountmax * sizeof(T*)));
	for(int i=0; i<_count; i++) {
		newobjs[i] = _objects[i];
	}
	free(_objects);
	_objects = newobjs;
	_countMax = newcountmax;
	return _countMax;
}

template <class T>
int Array<T>::Grow() {
#if defined DEBUGEXTRA
	Logger("Array::Grow()");
#endif //DEBUGEXTRA
	int newcountmax = _countMax + OBJCHUNK;
	T** newobjs = static_cast<T**>(malloc(newcountmax * sizeof(T*)));
	for(int i=0; i<_countMax; i++) {
		newobjs[i] = _objects[i];
	}
	for(int j=_countMax; j<newcountmax; j++) {
		newobjs[j] = NULL;
	}
	free(_objects);
	_objects = newobjs;
	_countMax = newcountmax;
	return _countMax;
}

template <class T>
int Array<T>::MakeContiguous() {
#if defined DEBUGEXTRA
	Logger("Array::MakeContiguous()");
#endif //DEBUGEXTRA
	int retval = 0;
	// load the front half with valid entries
	for(int i=0; i<_countMax; i++) {
		if(_objects[i] != NULL) {
			_objects[retval] = _objects[i];
			retval++;
		}
	}
	// zero out everything after the last valid entry
	for(int j=retval; j<_countMax; j++) {
		_objects[j] = NULL;
	}
	_count = retval;
	return retval;
}

template <class T>
int Array<T>::GetCount() {
	return _count;
}

template <class T>
int Array<T>::GetCountMax() {
	return _countMax;
}

template <class T>
void Array<T>::Add_unsafe(T* obj) {
	if(_count >= _countMax) Grow();
	_objects[_count] = obj;
	++_count;
}
