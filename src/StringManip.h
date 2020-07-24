/* StringManip.h
 *
 */

#ifndef STRINGMANIP_H
#define STRINGMANIP_H

#include <string>

using std::string;

/**
 * @brief Iterate through input and replace instances of string 'from' to string 'to'
 */
void ReplaceString(string& input, const string& from, const string& to);
string RemovePadding(const string& text);	//!< Return string 'text' with leading and trailing spaces removed
string DeQuote(const string& text);		//!< Return string 'text' without quotation marks enclosing it if applicable
bool ContainsNumericData(const string& val);	//!< Return true if 'val' contains only numbers, periods, and signs

/*
bool ValidateStrtod(const string& text);
string GetString(int val);
string GetHexString(void* object);
string GetFirstWord(const string& phrase);
string GetFirstWordEtc(const string& phrase, string& remainder);
*/

#if defined DEBUG
int StringManip_Test();				//!< Run tests
#endif //DEBUG

#endif //STRINGMANIP_H
