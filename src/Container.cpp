/* Container.cpp
 *
 */

#include <string>
#include "Container.h"

#if defined DEBUGEXTRA
#include "Logger.h"
#endif //DEBUGEXTRA

#define OBJCHUNK 2

template <class T>
Container<T>::Container() {
	_count = 0;
	_countMax = OBJCHUNK;
	_objects = static_cast<T**>(malloc(_countMax * sizeof(T*)));
	_names = static_cast<string*>(malloc(_countMax * sizeof(string)));
	for(int i=0; i<_countMax; i++) {
		_objects[i] = NULL;
		_names[i] = NULL;
	}
}

template <class T>
Container<T>::~Container() {
	DestroyAll();
	free(_objects);
	free(_names);
}

template <class T>
void Container<T>::Add(const string& name, T* obj) {
	if(CheckNameCollision(name)) {
		Destroy(obj);
	}
	Add_unsafe(name, obj);
}

/*
bool Container::AddAtomAndDontRename(Atom* atom) {
	if(CheckNameCollision(atom)) return false;
	AddAtom_unsafe(atom);
	return true;
}
*/

template <class T>
T* Container<T>::GetByIndex(unsigned int idx) {
	//TODO:  make this remotely safe or mark it unsafe
	T* retval = NULL;
	if(idx < _count) retval = _objects[idx];
	return retval;
}

template <class T>
bool Container<T>::Destroy(T* obj) {
	bool retval = false;
	for(unsigned int i=0; i<_count && !retval; i++) {
		if(_objects[i] == obj) {
			Destroy_unsafe(i);
			retval = true;
		}
	}
	return retval;
}

template <class T>
bool Container<T>::DestroyByName(const string& name) {
	bool retval = false;
	for(unsigned int i=0; i<_count && !retval; i++) {
		if(name == _names[i]) {
			Destroy_unsafe(i);
			retval = true;
		}
	}
	return retval;
}

template <class T>
int Container<T>::DestroyAll() {
	for(int i=0; i<_count; i++) {
		delete _objects[i];
		delete _names[i];
		_objects[i] = NULL;
		_names[i] = NULL;
	}
	_count = 0;
	return 0;
}

template <class T>
int Container<T>::Shrink() {
#if defined DEBUGEXTRA
	Logger("Container::Shrink()");
#endif //DEBUGEXTRA
	//for now assume contiguous; also this shares a lot of code with Grow...
	int newcountmax = _count;  // the next addition will induce a Grow()
	//if(newcountmax < _count) return _countMax;
	T** newobjs = static_cast<T**>(malloc(newcountmax * sizeof(T*)));
	string* newnames = static_cast<string*>(malloc(newcountmax * sizeof(string)));
	for(int i=0; i<_count; i++) {
		newobjs[i] = _objects[i];
		newnames[i] = _names[i];
	}
	free(_objects);
	free(_names);
	_objects = newobjs;
	_names = newnames;
	_countMax = newcountmax;
	return _countMax;
}

template <class T>
int Container<T>::Grow() {
#if defined DEBUGEXTRA
	Logger("Container::Grow()");
#endif //DEBUGEXTRA
	int newcountmax = _countMax + OBJCHUNK;
	T** newobjs = static_cast<T**>(malloc(newcountmax * sizeof(T*)));
	string* newnames = static_cast<string*>(malloc(newcountmax * sizeof(string)));
	for(int i=0; i<_countMax; i++) {
		newobjs[i] = _objects[i];
		newnames[i] = _names[i];
	}
	for(int j=_countMax; j<newcountmax; j++) {
		newobjs[j] = NULL;
		newnames[j] = "";
	}
	free(_objects);  // and hope like hell it doesn't delete _objects[*]
	free(_names);
	_objects = newobjs;
	_names = newnames;
	_countMax = newcountmax;
	return _countMax;
}

template <class T>
int Container<T>::MakeContiguous() {
#if defined DEBUGEXTRA
	Logger("Container::MakeContiguous()");
#endif //DEBUGEXTRA
	int retval = 0;
	// load the front half with valid entries
	for(int i=0; i<_countMax; i++) {
		if(_objects[i] != NULL) {
			_objects[retval] = _objects[i];
			_names[retval] = _names[i];
			retval++;
		}
	}
	// zero out everything after the last valid entry
	for(int j=retval; j<_countMax; j++) {
		_objects[j] = NULL;
		_names[j] = NULL;
	}
	_count = retval;
	return retval;
}

template <class T>
int Container<T>::GetCount() {
	return _count;
}

template <class T>
int Container<T>::GetCountMax() {
	return _countMax;
}

template <class T>
bool Container<T>::CheckNameCollision(const string& name) {
	bool retval = false;
	for(int i=0; i<_count && !retval; i++) {
		if(_names[i] == name) retval = true;
	}
	return retval;
}

template <class T>
void Container<T>::Add_unsafe(const string& name, T* obj) {
	if(_count >= _countMax) Grow();
	_objects[_count] = obj;
	_names[_count] = name;
	_count++;
}

template <class T>
void Container<T>::Destroy_unsafe(unsigned int idx) {
	delete _objects[idx];
	delete _names[idx];
	_objects[idx] = NULL;
	_names[idx] = NULL;
	MakeContiguous();
}
