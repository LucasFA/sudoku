#include <vector>
#include <string>
#include "auxiliaryFunctions.hpp"

namespace aux_functions{
    //helper for importing string into board type
    std::vector<std::string> split(const std::string &s, char splitterChar){
        std::vector<std::string> sol;
        std::size_t lastSubstringSectionStartsAt = 0;
        for(std::size_t i = 0; i < s.size(); ++i){
            if(s[i] == splitterChar) {
                sol.push_back(s.substr(lastSubstringSectionStartsAt, i - lastSubstringSectionStartsAt));
                lastSubstringSectionStartsAt = i + 1;
            }
        }
        std::string temp = s.substr(lastSubstringSectionStartsAt, s.size() - lastSubstringSectionStartsAt);
        if (!temp.empty()) 
            sol.push_back(temp);
        return sol;
    }
    
}