#include "tokenize.hpp"
#include <sstream>
#include <cctype>

vector<string> tokenize(const string& input) {
    vector<string> tokens;
    string token="";
    bool inString = 0;
    for(int i = 0; i < input.length(); i++) {
        char c = input[i];
        if(c == '\'') { //string input
            token+=c;
            inString = !inString;
        } else if (inString) { //checks in between the ' '
            token+=c;
        } else if(c == ' ') {
            if(!token.empty()) {
                tokens.push_back(token);
                token="";
            }
        } else if(c=='(' || c==';' || c==')' || c==',') {
            if(!token.empty()) {
                tokens.push_back(token);
                token="";
            }
            tokens.push_back(string(1,c)); //converts the character into a string
        } else { //all other cases
            token+=c;
        }
    }
    return tokens;
}