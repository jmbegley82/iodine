/* Gfx.h
 *
 */

#if !defined GFX_H
#define GFX_H

#include <string>
#include "GfxTypes.h"

using std::string;

Texture* LoadTextureFromFile(const string& path);
void DestroyTexture(Texture* tex);

#endif //GFX_H
