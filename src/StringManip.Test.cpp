/* StringManip.Test.cpp
 *
 */

#if defined DEBUG

#include <string>
#include <cstdio>
#include <cassert>
#include "StringManip.h"
#include "Logger.h"

using std::string;

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
	sprintf(msg, "Sentence::Test:  Sentence 1:  \"var anus = 1\"");
	Sentence s1("var anus = 1");
	sdetail(&s1);
	Sentence s2("anus = 2");
	sdetail(&s2);
	Sentence s3("What anus");
	sdetail(&s3);
	Sentence s4("anus");
	sdetail(&s4);
	return 0;
}

int RemovePadding_Test() {
	string testee = "    This sentence should no longer have any spaces surrounding it.      ";
	testee = RemovePadding(testee);
	testee = "RemovePadding_Test:  \"" + testee + "\"";
	Logger(testee.c_str());

	testee = "";
	testee = RemovePadding(testee);
	testee = "RemovePadding_Test:  \"" + testee + "\"";
	Logger(testee.c_str());

	return 0;
}

int DeQuote_Test() {
	string testee = "       \"This sentence is surrounded by one set of quotation marks!\"  ";
	testee = DeQuote(RemovePadding(testee));
	testee = "DeQuote_Test:  \"" + testee + "\"";
	Logger(testee.c_str());
	testee = "";
	testee = DeQuote(RemovePadding(testee));
	testee = "DeQuote_Test:  \"" + testee + "\"";
	Logger(testee.c_str());
	return 0;
}

int ContainsValidNumber_Test() {
	string test1 = "3.14159";
	string test2 = "10000000000000000";
	string test3 = "-1";
	string test4 = "eleventy";
	assert(ContainsNumericData(test1) && ContainsNumericData(test2) && ContainsNumericData(test3)
			&& !ContainsNumericData(test4));
	Logger("ContainsValidNumber_Test():  passed!");
	return 0;
}

int StringManip_Test() {
	int retval = 0;
	retval += Sentence::Test();
	retval += RemovePadding_Test();
	retval += DeQuote_Test();
	retval += ContainsValidNumber_Test();
	return retval;
}

#endif //DEBUG
