#pragma once
#include <vector>
#include <string> 
#include "commands.hpp"
using namespace std;

class Parser {
public:
    Command* parse(const vector<string>& tokens);

private:
    Command* parseCreateTable(const vector<string>& tokens);
    Command* parseInsert(const vector<string>& tokens);
    Command* parseSelect(const vector<string>& tokens);
    Command* parseDelete(const vector<string>& tokens);
    Command* parseDropTable(const vector<string>& tokens);
};
