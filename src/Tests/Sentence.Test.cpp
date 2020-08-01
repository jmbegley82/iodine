/* Sentence.Test.cpp
 *
 */

#if defined DEBUG

#include <string>
#include "Sentence.h"
#include "Logger.h"

void sdetail(Sentence* st) {
	char msg[128];
	const char* decl = st->declarator.c_str();
	const char* subj = st->subject.c_str();
	const char* op = st->op.c_str();
	const char* target = st->target.c_str();
	sprintf(msg, "Sentence::Test:  decl=\"%s\", subj=\"%s\", op=\"%s\", target=\"%s\"", decl, subj, op, target);
	Logger(msg);
}

int Sentence::Test() {
	char msg[128];
	sprintf(msg, "Sentence::Test:  Sentence 1:  \"var testSubj = 1\"");
	Sentence s1("var testSubj=1");
	sdetail(&s1);
	Sentence s2("testSubj ^= 2");
	sdetail(&s2);
	Sentence s3("What testSubj");
	sdetail(&s3);
	Sentence s4("testSubj");
	sdetail(&s4);
	return 0;
}

#endif //DEBUG
