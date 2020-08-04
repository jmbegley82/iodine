/* Drawlist.h
 *
 */

#if !defined DRAWLIST_H
#define DRAWLIST_H

#include "GfxTypes.h"

#define MAX_DLIST_SIZE 1024

typedef struct {
	Texture* tex;
	SrcRect src;
	DstRect dst;
} dlistEntry;

class Drawlist {
public:
	Drawlist();
	~Drawlist();
	bool Add(Texture* tex, SrcRect* src, DstRect* dst);
	void Clear();
	void Reset();
	unsigned int GetCount();
	dlistEntry* GetEntries();
private:
	unsigned int _count;
	dlistEntry _entries[MAX_DLIST_SIZE];
};

#endif //DRAWLIST_H
