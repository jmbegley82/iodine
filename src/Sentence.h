/* Sentence.h
 *
 */

#if !defined SENTENCE_H
#define SENTENCE_H

#include <string>

using std::string;

/**
 * @brief Sentence is used to parse single text-based commands
 * @details With few exceptions, all valid text commands will be in the form of the Sentence.  What makes a string a valid
 * Command will vary from place to place, and may not necessarily include Sentences at all, but they are probably going to be
 * a large part of any script.  Valid Sentences can be in the following forms:  Single-word, in which the Subject is the word
 * given and Declarator, Op and Target are empty; Two-word, in which the first word is the Declarator and the second word is
 * the Subject; Three-word, where the Subject is the one word to the right of the Operator, Operator is one of =, +=, -=, *=,
 * /=, or ^=, and Target is everything to the right of the Operator; and Four-word, which is like Three-word but with an
 * additional word before the Subject.
 *
 * Examples of format:
 * Process						(Subject="Process")
 * Integer val						(Declarator="Integer", Subject="val")
 * val = 3.14						(Subject="val", Target="3.14")
 * Double val = 3.14					(Declarator="Double", Subject="val", Op="=", Target="3.14")
 * String val = "Three point one four one five niner"	(Decl.="String", Subject="val", Op="=", Target=etc. etc. etc.)
 * delete val						(Declarator="delete", Subject="val")
 *
 */
class Sentence {
public:
	explicit Sentence(const string& cmd);	//!< Sentence ctor and main function
	string declarator = "";			//!< Potentially-misnamed often-unused first word of a 4-section Sentence
	string subject = "";			//!< Subject is the word to the left of the operator
	string op = "";				//!< Op(erator) is the first of (= += -= *= /= ^=) from left in cmd
	string target = "";			//!< Target is everything to the right of the Operator
#if defined DEBUG
	static int Test();			//!< Run tests
#endif //DEBUG
};

#endif //SENTENCE_H
