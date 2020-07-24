/* Container.h
 *
 */

#if !defined CONTAINER_H
#define CONTAINER_H

#include <string>
#include "Atom.h"

using std::string;

class Container {
public:
	Container();					//!< Construct the Container
	~Container();					//!< Destruct the Container
	void AddAtom(Atom* atom);			//!< Add an Atom to the Container (and rename it upon name collision)
	bool AddAtomAndDontRename(Atom* atom);		//!< Add an Atom to the Container (but fail upon name collision)
	Atom* GetAtomByIndex(unsigned int idx);		//!< Get Atom by index number (or NULL if out of bounds)
	bool DestroyAtom(Atom* atom);			//!< Destroy an Atom by its pointer
	bool DestroyAtomByName(string const& name);	//!< Destroy an Atom by its name
	int DestroyAllAtoms();				//!< Destroy all Atoms currently contained
	int Shrink();					//!< Attempt to shrink _objects
	int Grow();					//!< Attempt to grow _objects
	int MakeContiguous();				//!< Iterates through _objects and pushes non-null objects to front
	int GetCount();					//!< Return current number of objects within _objects
	int GetCountMax();				//!< Return current size of _objects
#if defined DEBUG
	static int Test();				//!< Run internal tests
#endif //DEBUG
private:
	bool CheckNameCollision(Atom* atom);		//!< Return true if Atom's name is already present within _objects
	void AddAtom_unsafe(Atom* atom);		//!< AddAtom without all the safety checks
	void DestroyAtom_unsafe(unsigned int idx);	//!< DestroyAtom without the safety checks
	Atom** _objects;
	int _count;
	int _countMax;
};

#endif //CONTAINER_H
