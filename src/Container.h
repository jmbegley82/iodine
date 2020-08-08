/* Container.h
 *
 */

#if !defined CONTAINER_H
#define CONTAINER_H

#include <string>
#include <utility>

using std::string;
using std::pair;

template <class T>
class Container {
public:
	Container();					//!< Construct the Container
	~Container();					//!< Destruct the Container
	void Add(const string& name, T* obj);		//!< Add to the Container (and rename it upon name collision)
	//bool AddAndDontRename(const string& name, T* obj);	//!< Add to the Container (but fail upon name collision)
	T* Get(const string& name);
	T* GetByIndex(unsigned int idx);		//!< Get by index number (or NULL if out of bounds)
	string GetNameByIndex(unsigned int idx);
	bool Destroy(T* obj);				//!< Destroy by its pointer
	bool DestroyByName(string const& name);		//!< Destroy by its name
	void Destroy_unsafe(unsigned int idx);		//!< Destroy without the safety checks
	int Clear();					//!< Destroy all objects currently contained
	int Shrink();					//!< Attempt to shrink _objects
	int Grow();					//!< Attempt to grow _objects
	int MakeContiguous();				//!< Iterates through _objects and pushes non-null objects to front
	int GetCount();					//!< Return current number of objects within _objects
	int GetCountMax();				//!< Return current size of _objects
private:
	typedef pair<string,T*> namepair;
	bool CheckNameCollision(const string& name);	//!< Return true if name is already present within _objects
	void Add_unsafe(const string& name, T* obj);	//!< Add without all the safety checks
	namepair** _objects;
	int _count;
	int _countMax;
};

#if defined DEBUG
int Container_Test();			//!< Run internal tests
#endif //DEBUG

#endif //CONTAINER_H
