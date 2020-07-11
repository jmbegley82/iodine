/* Container.h
 *
 */

#if !defined CONTAINER_H
#define CONTAINER_H

#include "Atom.h"

class Container {
public:
	Container();					//!< Construct the Container
	void AddAtom(Atom* atom);			//!< Add an Atom to the Container (and rename it upon name collision)
	bool AddAtomAndDontRename(Atom* atom);		//!< Add an Atom to the Container (but fail upon name collision)
	bool DestroyAtom(Atom* atom);			//!< Destroy an Atom by its pointer
	bool DestroyAtomByName(const char* name);	//!< Destroy an Atom by its name
	int DeleteAllAtoms();				//!< Destroy all Atoms currently contained
	int Shrink();					//!< Attempt to shrink _objects
	int Grow();					//!< Attempt to grow _objects
#if defined DEBUG
	static int Test();				//!< Run internal tests
#endif //DEBUG
private:
	Atom** _objects;
	int _count;
	int _countMax;
};

#endif //CONTAINER_H
