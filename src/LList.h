/* LList.h
 *
 */

#if !defined SPLLIST_H
#define SPLLIST_H

template <typename T> struct Litem {
	Litem<T>* prev;
	T item;
	Litem<T>* next;
};

template <class T> class LList {
public:
	LList();
	~LList(); 
	Litem<T>* GetFirst();
	Litem<T>* GetLast();
	Litem<T>* GetByIndex(unsigned int idx);
	LList<T> GetRange(Litem<T>* start, Litem<T>* end);
	unsigned int GetCount();
	Litem<T>* Add(T obj);
	void Remove(Litem<T>* obj);
	void Clear();
	typedef Litem<T>* iterator;
private:
	Litem<T>* _first;
	Litem<T>* _last;
	Litem<T>* _garbage;
	unsigned int _count;
};

#if defined DEBUG
int LList_Test();
#endif //DEBUG

#endif //SPLLIST_H
