/* Sprite.h
 *
 */

#if !defined SPRITE_H
#define SPRITE_H

#include "Ticker.h"
#include "Motion.h"
#include "Introspector.h"
#include "GfxTypes.h"
#include "AnimationSet.h"
#include "Animation.h"

#define MAX_ACTIONS 3

class Sprite : public Ticker, public Motion, public Introspector {
public:
	Sprite();
	~Sprite();
	void Tick() override;
	Texture* GetTexture();
	void NextCel();
	void GetDrawSrcRect(SrcRect* src);
	void GetDrawDstRect(DstRect* dst);
	bool SetAnimationSet(const string& name);
	bool SetAnimation(const char* name);
	void SetOneshot();
	bool IsOneshot();
	bool HasExpired();
	void Expire();
	void MakeBouncy();
	bool AddAction(void (*action)(Sprite*));
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	AnimationSet* _currentAset;
	Animation* _currentAnim;
	unsigned int _currentCel;
	unsigned int _celCount;
	double _celFlipDelta;
	bool _isOneshot;
	bool _hasExpired;
	void (*_actions[MAX_ACTIONS])(Sprite*);
	unsigned int _actionCount;
};

#endif //SPRITE_H
