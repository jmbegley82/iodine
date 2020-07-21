/* AnimationSet.h
 *
 */

#if !defined ANIMATIONSET_H
#define ANIMATIONSET_H

#include <string>
#include <map>
#include "Animation.h"

using std::string;
using std::map;

typedef map<string,Animation*> animSet;
typedef animSet::iterator asetItr;

class AnimationSet {
public:
	AnimationSet();
	~AnimationSet();
	void AddAnimation(const string& name, Animation* anim); // deprecated
	//Animation* CreateAnimation(const string& name);
	Animation* GetAnimation(const string& name);
	int LoadTexture(const string& path);
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	animSet _anims;
	void* _texture;  // placeholder
};

#endif //ANIMATIONSET_H
