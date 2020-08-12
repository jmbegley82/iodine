/* LList.h
 *
 */

#if !defined LLIST_H
#define LLIST_H

template <typename T> struct LLitem {
	LLitem<T>* prev;
	T item;
	LLitem<T>* next;
	int status;  // -1 = garbage, 0 = unused, 1 = used
};

template <class T> class LList {
public:
	LList();
	~LList();
	void Add(T item);
	LLitem<T>* Get(unsigned int index);
	LLitem<T>* GetFirst();
	LLitem<T>* GetLast();
	int GetCount();
	void Remove(LLitem<T>* item);
	void Compact();
	//void Grow();
	typedef LLitem<T>* iterator;
private:
	LLitem<T>* _llitems;
	unsigned int _nextFreeSlot;
	unsigned int _countMax;
};



#if defined DEBUG
int LList_Test();
#endif //DEBUG

#endif //LLIST_H
