/* Animation.h
 *
 */

#if !defined ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Cel.h"

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
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	unsigned int _delayInMsec;
	celset _cels;
};

#endif //ANIMATION_H
