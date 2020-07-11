/* Container.cpp
 *
 */

#include "Container.h"
#include "Atom.h"

Container::Container() {
}

void Container::AddAtom(Atom* atom) {
}

bool Container::AddAtomAndDontRename(Atom* atom) {
	return true;
}

bool Container::DestroyAtom(Atom* atom) {
	return true;
}

bool Container::DestroyAtomByName(const char* name) {
	return true;
}

int Container::DeleteAllAtoms() {
	return -1;
}

int Container::Shrink() {
	return -1;
}

int Container::Grow() {
	return -1;
}
