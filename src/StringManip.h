/* StringManip.h
 *
 */

#ifndef STRSPLIT_H
#define STRSPLIT_H

#include <string>

/*
namespace jmb {
	
	namespace common {
		
		class CommandSplit {
		public:
			CommandSplit(std::string const &cmd, std::string const &token);
			std::string left, right;
		};

		class CommandSplitRev {
		public:
			CommandSplitRev(std::string const& cmd, std::string const& token);
			std::string left, right;
		};
*/		

		void ReplaceString(std::string& input, std::string const& from, std::string const& to);
		std::string RemovePadding(std::string const& text);
		std::string DeQuote(std::string const& text);
		bool ContainsNumericData(const std::string& val);
		//bool ValidateStrtod(std::string const& text);
		//std::string GetString(int val);
		//std::string GetHexString(void* object);
		//std::string GetFirstWord(std::string const& phrase);
		//std::string GetFirstWordEtc(std::string const& phrase, std::string & remainder);
#if defined DEBUG
		int StringManip_Test();
#endif //DEBUG
/*	}
	
}
*/
#endif //STRSPLIT_H
