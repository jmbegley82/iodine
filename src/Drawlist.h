/* Drawlist.h
 *
 */

#if !defined DRAWLIST_H
#define DRAWLIST_H

#include "GfxTypes.h"

#define MAX_DLIST_SIZE 2048

typedef struct {
	Texture* tex;
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
} dlistEntry;

class Drawlist {
public:
	Drawlist();
	~Drawlist();
	void Add(Texture* tex, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	void Process(Renderer* renderer);
private:
	unsigned int _count;
	dlistEntry _entries[MAX_DLIST_SIZE];
};

#endif //DRAWLIST_H
