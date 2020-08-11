/* LList.h
 *
 */

#if !defined LLIST_H
#define LLIST_H

/*
typedef struct LLitem LLitem;

struct LLitem {
	LLitem* prev;
	void* item;
	LLitem* next;
};
*/

template <class T> class LLitem {
public:
	LLitem(LLitem* prev, T item, LLitem* next);
	LLitem* prev;
	T* item;
	LLitem* next;
	bool done;
};

template <class T> class LList {
public:
	LList();
	~LList();
	void Add(T item);
	LLitem<T>* Get(unsigned int index);
	void Remove(LLitem<T>* item);
	void Compact();
private:
	LLitem<T>** _llitems;
	unsigned int _nextFreeSlot;
	unsigned int _countMax;
};

#if defined DEBUG
int LList_Test();
#endif //DEBUG

#endif //LLIST_H
