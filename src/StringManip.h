/* StringManip.h
 *
 */

#ifndef STRINGMANIP_H
#define STRINGMANIP_H

#include <string>

using std::string;

void ReplaceString(string& input, const string& from, const string& to);
string RemovePadding(const string& text);
string DeQuote(const string& text);
bool ContainsNumericData(const string& val);

/*
bool ValidateStrtod(const string& text);
string GetString(int val);
string GetHexString(void* object);
string GetFirstWord(const string& phrase);
string GetFirstWordEtc(const string& phrase, string& remainder);
*/

#if defined DEBUG
int StringManip_Test();
#endif //DEBUG

#endif //STRINGMANIP_H
