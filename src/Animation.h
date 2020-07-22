/* Animation.h
 *
 */

#if !defined ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include "Cel.h"

using std::string;
using std::vector;

typedef vector<Cel*> celset;
typedef celset::iterator celitr;

class Animation {
public:
	Animation();
	~Animation();
	void SetDelayInMsec(unsigned int ms);
	void AddCel(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	unsigned int GetDelayInMsec();
	Cel* GetCel(unsigned int idx);
	unsigned int GetCelCount();
	int LoadTexture(const string& path);
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	void* _texture;  // placeholder
	unsigned int _delayInMsec;
	celset _cels;
};

#endif //ANIMATION_H
