/* Container.cpp
 *
 */

#include <string>
#include "Container.h"
#include "Atom.h"

#if defined DEBUGEXTRA
#include "Logger.h"
#endif //DEBUGEXTRA

#define OBJCHUNK 2

Container::Container() {
	_count = 0;
	_countMax = OBJCHUNK;
	_objects = static_cast<Atom**>(malloc(_countMax * sizeof(Atom*) /*_objects*/));
	for(int i=0; i<_countMax; i++) {
		_objects[i] = NULL;
	}
}

Container::~Container() {
	DestroyAllAtoms();
	free(_objects);
}

void Container::AddAtom(Atom* atom) {
	if(CheckNameCollision(atom)) atom->SetArbitraryIdentity();
	AddAtom_unsafe(atom);
}

bool Container::AddAtomAndDontRename(Atom* atom) {
	if(CheckNameCollision(atom)) return false;
	AddAtom_unsafe(atom);
	return true;
}

Atom* Container::GetAtomByIndex(unsigned int idx) {
	//TODO:  make this remotely safe or mark it unsafe
	Atom* retval = NULL;
	if(idx < _count) retval = _objects[idx];
	return retval;
}

bool Container::DestroyAtom(Atom* atom) {
	bool retval = false;
	for(unsigned int i=0; i<_count && !retval; i++) {
		if(_objects[i] == atom) {
			DestroyAtom_unsafe(i);
			retval = true;
		}
	}
	return retval;
}

bool Container::DestroyAtomByName(string const& name) {
	bool retval = false;
	for(unsigned int i=0; i<_count && !retval; i++) {
		if(name == _objects[i]->GetIdentity()) {
			DestroyAtom_unsafe(i);
			retval = true;
		}
	}
	return retval;
}

int Container::DestroyAllAtoms() {
	for(int i=0; i<_count; i++) {
		delete _objects[i];
		_objects[i] = NULL;
	}
	_count = 0;
	return 0;
}

int Container::Shrink() {
#if defined DEBUGEXTRA
	Logger("Container::Shrink()");
#endif //DEBUGEXTRA
	//for now assume contiguous; also this shares a lot of code with Grow...
	int newcountmax = _count;  // the next addition will induce a Grow()
	//if(newcountmax < _count) return _countMax;
	Atom** newbuf = static_cast<Atom**>(malloc(newcountmax * sizeof(Atom*)));
	for(int i=0; i<_count; i++) {
		newbuf[i] = _objects[i];
	}
/*	for(int j=_count; j<newcountmax; j++) {
		newbuf[j] = NULL;
	}*/
	free(_objects);
	_objects = newbuf;
	_countMax = newcountmax;
	return _countMax;
}

int Container::Grow() {
#if defined DEBUGEXTRA
	Logger("Container::Grow()");
#endif //DEBUGEXTRA
	int newcountmax = _countMax + OBJCHUNK;
	Atom** newbuf = static_cast<Atom**>(malloc(newcountmax * sizeof(Atom*)));
	for(int i=0; i<_countMax; i++) {
		newbuf[i] = _objects[i];
	}
	for(int j=_countMax; j<newcountmax; j++) {
		newbuf[j] = NULL;
	}
	free(_objects);  // and hope like hell it doesn't delete _objects[*]
	_objects = newbuf;
	_countMax = newcountmax;
	return _countMax;
}

int Container::MakeContiguous() {
#if defined DEBUGEXTRA
	Logger("Container::MakeContiguous()");
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

int Container::GetCount() {
	return _count;
}

int Container::GetCountMax() {
	return _countMax;
}

bool Container::CheckNameCollision(Atom* atom) {
	bool retval = false;
	string id = atom->GetIdentity();
	for(int i=0; i<_count && !retval; i++) {
		if(_objects[i]->GetIdentity() == id) retval = true;
	}
	return retval;
}

void Container::AddAtom_unsafe(Atom* atom) {
	if(_count >= _countMax) Grow();
	_objects[_count] = atom;
	_count++;
}

void Container::DestroyAtom_unsafe(unsigned int idx) {
	delete _objects[idx];
	_objects[idx] = NULL;
	MakeContiguous();
}
