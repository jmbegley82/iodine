/* CelString.cpp
 *
 */

#include <string>
#include "CelString.h"

/*
CelString(const string& cmd);
bool isValid;
unsigned int x, y, w, h;
 */

using std::string;

CelString::CelString(const string& cmd) {
	// format:  123,456,789,10
	// spaces are not tolerated
	// characters that aren't in the above format string aren't allowed
	if(IsValidCelString(cmd)) {
		// certified to contain four numbers separated by three commas
		// X
		string::const_iterator start = cmd.begin();
		string::const_iterator end = cmd.begin()+1;
		while(*end != ',') end++;
		string xstr = string(start,end);
		x = std::stoi(xstr);
		// Y
		end++;
		start = end;
		while(*end != ',') end++;
		y = std::stoi(string(start,end));
		// W
		end++;
		start = end;
		while(*end != ',') end++;
		w = std::stoi(string(start,end));
		// H
		end++;
		start = end;
		h = std::stoi(string(start,cmd.end()));
		isValid = true;
	} else {
		isValid = false;
		x = y = w = h = 0;
	}
}

bool CelString::IsValidCelString(const string& cmd) {
	bool retval = true;
	bool previouslyComma = false;
	unsigned int commaCount = 0;
	if(cmd == "") return false;  // get the empty string case out of the way
	for(string::const_iterator i = cmd.begin(); i != cmd.end() && retval; i++) {
		if(i == cmd.begin() || i == cmd.end()-1) {
			// the first and last character must not be comma
			if(*i == ',') return false;
		}
		if(previouslyComma && *i == ',') return false;  // no consecutive commas
		if(std::isdigit(*i)) {
			previouslyComma = false;
		} else if(*i == ',') {
			previouslyComma = true;
			commaCount++;
		} else return false;  // anything that isn't a comma or number is bunk
	}
	if(commaCount != 3) return false;
	return true;
}
