/* Drawlist.cpp
 *
 */

#include "Drawlist.h"

void ZeroDLEntry(dlistEntry* dle) {
	dle->tex = NULL;
	dle->x = 0;
	dle->y = 0;
	dle->w = 0;
	dle->h = 0;
}

Drawlist::Drawlist() {
	for(int i=0; i<MAX_DLIST_SIZE; ++i) {
		ZeroDLEntry(&_entries[i]);
	}
	_count = 0;
}

Drawlist::~Drawlist() {
}

void Drawlist::Add(Texture* tex, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	if(_count >= MAX_DLIST_SIZE) return;  //we're full
	_entries[_count].tex = tex;
	_entries[_count].x = x;
	_entries[_count].y = y;
	_entries[_count].w = w;
	_entries[_count].h = h;
	++_count;
}

void Drawlist::Process(Renderer* renderer) {
	for(int i=0; i<_count; ++i) {
		//TODO:draw
		//zero
		ZeroDLEntry(&_entries[i]);
	}
	_count = 0;
}
