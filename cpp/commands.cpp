#include "commands.hpp"
using namespace std;

Condition::Condition(const string& col, const string& op, const string& value)
: col(col), op(op), value(value) {}

CreateTableCommand::CreateTableCommand(const string& name, const vector<pair<string,string>>& cols) 
: tableName(name), columns(cols) {}

InsertCommand::InsertCommand(const string& name, const vector<string>& vals) 
: tableName(name), values(vals) {}

SelectCommand::SelectCommand(const string& name, const vector<string>& cols) 
: tableName(name), columns(cols) {}

DeleteCommand::DeleteCommand(const string& name, const vector<Condition>& conditions)
: tableName(name), conditions(conditions) {}

DropTableCommand::DropTableCommand(const vector<string>& tableNames) 
: tableNames(tableNames) {}

