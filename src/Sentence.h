/* Sentence.h
 *
 */

#if !defined SENTENCE_H
#define SENTENCE_H

#include <string>

using std::string;

class Sentence {
public:
	Sentence(const string& cmd);
	string declarator, subject, op, target;
#if defined DEBUG
	static int Test();
#endif //DEBUG
};

#endif //SENTENCE_H
