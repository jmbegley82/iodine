/* Drawlist.cpp
 *
 */

#include "Drawlist.h"

#if !defined DLIST_ORIGINAL
#include <cstring>
#endif //DLIST_ORIGINAL

void ZeroDLEntry(dlistEntry* dle) {
	dle->tex = NULL;
#if defined DLIST_ORIGINAL
	dle->src.x = 0;
	dle->src.y = 0;
	dle->src.w = 0;
	dle->src.h = 0;
	dle->dst.x = 0;
	dle->dst.y = 0;
	dle->dst.w = 0;
	dle->dst.h = 0;
#else
	memset(dle, 0, sizeof(dle));
#endif //DLIST_ORIGINAL
}

Drawlist::Drawlist() {
	_count = MAX_DLIST_SIZE;
	Clear();  // the end result is everything is set to zero including _count
}

Drawlist::~Drawlist() {
}

bool Drawlist::Add(Texture* tex, SrcRect* src, DstRect* dst) {
	if(_count >= MAX_DLIST_SIZE) return false;  //we're full
	_entries[_count].tex = tex;
#if defined DLIST_ORIGINAL
	_entries[_count].src.x = src->x;
	_entries[_count].src.y = src->y;
	_entries[_count].src.w = src->w;
	_entries[_count].src.h = src->h;
	_entries[_count].dst.x = dst->x;
	_entries[_count].dst.y = dst->y;
	_entries[_count].dst.w = dst->w;
	_entries[_count].dst.h = dst->h;
#else
	memcpy(static_cast<void*>(&_entries[_count].src), static_cast<void*>(src), sizeof(SrcRect));
	memcpy(static_cast<void*>(&_entries[_count].dst), static_cast<void*>(dst), sizeof(DstRect));
#endif //DLIST_ORIGINAL
	++_count;
	return true;
}

void Drawlist::Clear() {
#if defined DLIST_ORIGINAL
	for(int i=0; i<_count; ++i) {
		ZeroDLEntry(&_entries[i]);
	}
#else
	memset(_entries, 0, (size_t)MAX_DLIST_SIZE * sizeof(dlistEntry));
#endif //DLIST_ORIGINAL
	Reset();
}

void Drawlist::Reset() {
	_count = 0;
}

unsigned int Drawlist::GetCount() {
	return _count;
}

dlistEntry* Drawlist::GetEntries() {
	return _entries;
}
