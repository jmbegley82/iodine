/* Container.h
 *
 */

#if !defined CONTAINER_H
#define CONTAINER_H

#include <string>

using std::string;

template <class T>
class Container {
public:
	Container();					//!< Construct the Container
	~Container();					//!< Destruct the Container
	void Add(const string& name, T* obj);		//!< Add to the Container (and rename it upon name collision)
	//bool AddAndDontRename(const string& name, T* obj);	//!< Add to the Container (but fail upon name collision)
	T* GetByIndex(unsigned int idx);		//!< Get by index number (or NULL if out of bounds)
	bool Destroy(T* obj);				//!< Destroy by its pointer
	bool DestroyByName(string const& name);		//!< Destroy by its name
	int DestroyAll();				//!< Destroy all objects currently contained
	int Shrink();					//!< Attempt to shrink _objects
	int Grow();					//!< Attempt to grow _objects
	int MakeContiguous();				//!< Iterates through _objects and pushes non-null objects to front
	int GetCount();					//!< Return current number of objects within _objects
	int GetCountMax();				//!< Return current size of _objects
#if defined DEBUG
	static int Test();				//!< Run internal tests
#endif //DEBUG
private:
	bool CheckNameCollision(const string& name);	//!< Return true if name is already present within _objects
	void Add_unsafe(const string& name, T* obj);	//!< Add without all the safety checks
	void Destroy_unsafe(unsigned int idx);		//!< Destroy without the safety checks
	T** _objects;
	string* _names;
	int _count;
	int _countMax;
};

#endif //CONTAINER_H
