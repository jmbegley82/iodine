/* Drawlist.cpp
 *
 */

#include "Drawlist.h"

void ZeroDLEntry(dlistEntry* dle) {
	dle->tex = NULL;
	dle->src.x = 0;
	dle->src.y = 0;
	dle->src.w = 0;
	dle->src.h = 0;
	dle->dst.x = 0;
	dle->dst.y = 0;
	dle->dst.w = 0;
	dle->dst.h = 0;
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
	_entries[_count].src.x = src->x;
	_entries[_count].src.y = src->y;
	_entries[_count].src.w = src->w;
	_entries[_count].src.h = src->h;
	_entries[_count].dst.x = dst->x;
	_entries[_count].dst.y = dst->y;
	_entries[_count].dst.w = dst->w;
	_entries[_count].dst.h = dst->h;
	++_count;
	return true;
}

void Drawlist::Clear() {
	for(int i=0; i<_count; ++i) {
		ZeroDLEntry(&_entries[i]);
	}
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
