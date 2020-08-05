/* Sprite.h
 *
 */

#if !defined SPRITE_H
#define SPRITE_H

#include "Ticker.h"
#include "Motion.h"
#include "Introspector.h"
#include "GfxTypes.h"

class Sprite : public Ticker, public Motion, public Introspector {
public:
	Sprite();
	~Sprite();
	void Tick() override;
	Texture* GetTexture();
	void GetDrawSrcRect(SrcRect* src);
	void GetDrawDstRect(DstRect* dst);
	bool SetAnimationSet(const string& name);
	bool SetAnimation(const string& name);
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	AnimationSet* _currentAset;
	Animation* _currentAnim;
	unsigned int _currentCel;
	unsigned int _celCount;
};

#endif //SPRITE_H
