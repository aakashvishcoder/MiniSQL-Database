#pragma once
#include <vector>
#include <string>
using namespace std;

struct Command { //base class
    virtual ~Command() = default; //ensures that the correct destructor is called
};

struct Condition {
    string col;
    string op;
    string value;
    Condition(const string& col, const string& op, const string& value);
};

struct CreateTableCommand : public Command {
    string tableName;
    vector<pair<string,string>> columns;
    CreateTableCommand(const string& name, const vector<pair<string,string>>& cols);
};

struct InsertCommand : public Command {
    string tableName;
    bool selectAll = true; //always true
    vector<string> values;
    InsertCommand(const string& name, const vector<string>& vals);
};

struct SelectCommand : public Command {
    string tableName;
    vector<string> columns;
    SelectCommand(const string& name, const vector<string>& cols);
};

struct DeleteCommand : public Command {
    string tableName;
    vector<Condition> conditions;
    DeleteCommand(const string& name, const vector<Condition>& conditions);
};

struct DropTableCommand : public Command {
    vector<string> tableNames;
    DropTableCommand(const vector<string>& tableNames);
};