/* Gfx.cpp
 *
 */

#include <string>
#include <SDL_image.h>
#include "Gfx.h"
#include "System.h"

using std::string;

Texture* LoadTextureFromFile(const string& path) {
	Texture* retval = NULL;
	string realpath = string(GetInstallDir()) + path;
	SDL_Surface* surf = IMG_Load(realpath.c_str());
	retval = SDL_CreateTextureFromSurface(System::GetRenderer(), surf);
	SDL_FreeSurface(surf);
	return retval;
}

void DestroyTexture(Texture* tex) {
	SDL_DestroyTexture(tex);
}
