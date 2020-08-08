/* Array.h
 *
 */

#if !defined ARRAY_H
#define ARRAY_H

//#include <string>
//#include <utility>

//using std::string;
//using std::pair;

template <class T>
class Array {
public:
	Array();					//!< Construct the Array
	~Array();					//!< Destruct the Array
	void Add(T* obj);
	T* GetByIndex(unsigned int idx);		//!< Get by index number (or NULL if out of bounds)
	bool Destroy(T* obj);				//!< Destroy by its pointer
	void Destroy_unsafe(unsigned int idx);		//!< Destroy without the safety checks
	int Clear();					//!< Destroy all objects currently contained
	int Shrink();					//!< Attempt to shrink _objects
	int Grow();					//!< Attempt to grow _objects
	int MakeContiguous();				//!< Iterates through _objects and pushes non-null objects to front
	int GetCount();					//!< Return current number of objects within _objects
	int GetCountMax();				//!< Return current size of _objects
private:
	void Add_unsafe(T* obj);
	T** _objects;
	int _count;
	int _countMax;
};

#if defined DEBUG
int Array_Test();			//!< Run internal tests
#endif //DEBUG

#endif //ARRAY_H
