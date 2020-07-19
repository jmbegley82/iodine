/* StringManip.cpp
 *
 */

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <sstream>

#include "StringManip.h"

using std::string;
using std::stringstream;

/*	
namespace jmb
{
	
	namespace common {
		CommandSplit::CommandSplit(string const& cmd, string const& token) {
			string ncmd = cmd;
			size_t pos = ncmd.find(token,0);
			if(pos != string::npos) {
				left = ncmd.substr(0,pos);
				ncmd.erase(0, pos+token.length());
				right = ncmd;
			} else {
				left = "";
				right = "";
			}
		}

		CommandSplitRev::CommandSplitRev(string const& cmd, string const& token) {
			string ncmd = cmd;
			size_t pos = ncmd.rfind(token);
			if(pos != string::npos) {
				left = ncmd.substr(0,pos);
				ncmd.erase(0,pos+token.length());
				right = ncmd;
			} else {
				left = "";
				right = "";
			}
		}
*/

		void ReplaceString(string& input, string const& from, string const& to) {
			if (from.empty()) return;
			size_t start_pos = 0;
			while ((start_pos = input.find(from, start_pos)) != string::npos) {
				input.replace(start_pos, from.length(), to);
				start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
			}
		}

		string RemovePadding(string const& text) {
			// returns a string with spaces stripped from the beginning and end
			string retval = "";
			if(text != "") {
				string::const_iterator i = text.begin();
				while(i != text.end() && isspace(*i)) i++;
				string::const_iterator j = text.end()-1;
				while(j > i && isspace(*j)) j--;
				j++;
				retval = string(i, j);
			}
			return retval;
		}

		string DeQuote(string const& text) {
			string retval = "";
			// we assume that this only receives strings that begin with a quotation mark
			// but just in case, weed out the null strings.
			if(text != "") {
				string::const_iterator i = text.begin();
				string::const_iterator j = text.end() - 1;
				if(*i == '\"' && *j == '\"') {
					i++;
					//j--;
					retval = string(i, j);
				}
			}
			return retval;
		}

		bool ContainsNumericData(const string& val) {
			if(val == "") return false;  // no, patrick, nothing is not a number.
			bool retval = false;
			bool keepgoing = true;
			for(string::const_iterator i = val.begin(); i != val.end() && keepgoing; i++) {
				if(!std::isdigit(*i) && *i != '+' && *i != '-' && *i != '.') {
					keepgoing = false;
				//	retval = false;
				}
			}
			if(keepgoing) retval = true;
			return retval;
		}
/*
		bool ValidateStrtod(string const& text) {
			bool retval = true;
			string::const_iterator i = text.begin();
			while(retval && i != text.end()) {
				if(!std::isdigit(*i) && *i != '+' && *i != '-'
					&& *i != '.') retval = false;
				i++;
			}
			return retval;
		}

		string GetString(int val) {
			stringstream ss;
			ss << val;
			return ss.str();
		}

		string GetHexString(void* obj) {
			stringstream ss;
			ss << std::hex << obj;
			return ss.str();
		}

		string GetFirstWord(string const& phrase) {
			string retval = "";

			// ensure that our input doesn't begin with a space
			string stripped = RemovePadding(phrase);

			// iterate thru each character and add it to retval
			//   until we reach either a space or end of stripped
			string::const_iterator i = stripped.begin();
			while(i != stripped.end() && !isspace(*i)) {
				retval += *i;
				++i;
			}

			return retval;
		}

		string GetFirstWordEtc(string const& phrase, string & remainder) {
			string retval = "";
			remainder = "";

			// ensure that our input doesn't begin with a space
			string stripped = RemovePadding(phrase);

			// iterate thru stripped and add each character to retval
			//   until we reach either a space or the end of stripped
			string::const_iterator i = stripped.begin();
			while(i != stripped.end() && !isspace(*i)) {
				retval += *i;
				++i;
			}

			// continue iterating through the rest of the string
			//   and add everything to remainder
			while(i != stripped.end()) {
				remainder += *i;
				++i;
			}

			return retval;
		}
*/

/*	}
}
*/
