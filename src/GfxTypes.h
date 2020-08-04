/* GfxTypes.h
 *
 */

#if !defined GFXTYPES_H
#define GFXTYPES_H

// the following is compiler-friendly nonsense for the moment
//typedef double Texture;

#include <SDL_render.h>
#include <SDL_rect.h>

typedef SDL_Window Window;
typedef SDL_Renderer Renderer;
typedef SDL_Texture Texture;

/*
typedef struct {
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
} SrcRect;

typedef struct {
	int x;
	int y;
	unsigned int w;
	unsigned int h;
} DstRect;
*/

typedef SDL_Rect SrcRect;
typedef SDL_Rect DstRect;

#endif //GFXTYPES_H
