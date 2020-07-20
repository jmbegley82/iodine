/* Sentence.cpp
 *
 */

#include <string>
#include <cassert>
#include "Sentence.h"
#include "StringManip.h"

Sentence::Sentence(string const& cmd) {
	declarator = subject = op = target = "";

	string ncmd = cmd;
	size_t pos = ncmd.find("=");
	if(pos != string::npos) {
		if(pos > 0) {
			pos--;
			op = ncmd.substr(pos,1);
			if(op == "+") {
				op = "+=";
			} else if(op == "-") {
				op = "-=";
			} else if(op == "*") {
				op = "*=";
			} else if(op == "/") {
				op = "/=";
			} else if(op == "^") {
				op = "^=";
			} else if(op == ":") {
				op = ":=";
			} else {
				op = "=";
				pos++;
			}
		} else {
			op = "=";
		}

		subject = ncmd.substr(0, pos);
		// op is set
		size_t offset = subject.length() + op.length();
		size_t length = ncmd.length() - offset;
		target = ncmd.substr(offset, length);
	} else {
		// no operator found; set subject to whole cmd
		subject = cmd;
	}

	// at this point, subject op and target are set
	// now see if there appears to be a declarator
	//
	if(subject != "") {
		// subjEnd = position of last non-space in subject
		int declBegin = -1;
		int declEnd   = -1;
		int subjBegin = -1;
		int subjEnd   = subject.length() - 1;

		//const char* subj = subject.c_str();
		while(subjEnd >= 0 && isspace(subject[subjEnd])) subjEnd--;
		assert(subjEnd >= 0);  // otherwise, subject was empty

		subjBegin = subjEnd;
		while(subjBegin > 0 && !isspace(subject[subjBegin])) subjBegin--;
		declEnd = subjBegin;
		while(declEnd > 0 && isspace(subject[declEnd])) declEnd--;
		declBegin = declEnd;
		while(declBegin > 0 && !isspace(subject[declBegin])) declBegin--;

		if(declEnd != 0) {
			declarator = subject.substr(declBegin, (declEnd + 1) - declBegin);
			subjBegin++;
		}
		subject = subject.substr(subjBegin, (subjEnd + 1) - subjBegin);
	}

	if(declarator == "" && op == "") {
		target = ""; // for good measure
		subject = cmd;
	}
	//subject = RemovePadding(subject);
	target = RemovePadding(target);
}


