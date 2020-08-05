/* Animation.h
 *
 */

#if !defined ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include "Cel.h"
#include "GfxTypes.h"

using std::string;
using std::vector;

typedef vector<Cel*> celset;		//!< container for individual cels
typedef celset::iterator celitr;	//!< relevant iterator for celset

class Animation {
public:
	Animation();					//!< Animation ctor
	~Animation();					//!< Animation dtor
	int AnmCommand(const string& cmd);		//!< Process text-strings relevant to this object
	void SetDelayInMsec(unsigned int ms);		//!< Set delay between frames
	void AddCel(unsigned int x, unsigned int y,
			unsigned int w, unsigned int h);//!< Create a new Cel with given parameters
	unsigned int GetDelayInMsec();			//!< Get delay between frames
	Cel* GetCel(unsigned int idx);			//!< Get Cel by index (or NULL if out of bounds)
	unsigned int GetCelCount();			//!< Get current number of Cels
	bool LoadTexture(const string& path);		//!< Set this Animation's spritesheet texture
	Texture* GetTexture();				//!< Get this Animation's spritesheet texture
	int LoadScript(const string& path);		//!< Open text file and pass its lines to AnmCommand
#if defined DEBUG
	static int Test();				//!< Run tests
#endif //DEBUG
private:
	Texture* _texture;  // placeholder
	unsigned int _delayInMsec;
	celset _cels;
};

#endif //ANIMATION_H
