#pragma once
#include <string> 
#include <vector>
#include <unordered_map>
#include "commands.hpp"
using namespace std;

struct Table {
    vector<pair<string,string>> schema; // {column name, type}
    vector<vector<string>> rows; // data rows
    Table(const vector<pair<string,string>>& schema);
};

class Database {
public:
    void createTable(const string& name, const vector<pair<string,string>>& schema);
    void insert(const string& name, const vector<string>& values);
    void deleteRows(const string& tableName, const vector<Condition>& conditions);
    void selectRows(const string& tableName, const vector<string>& columns, const vector<Condition>& conditions);
    void dropTable(const vector<string>& tableNames);
    bool tableExists(const string& name);
private:
    unordered_map<string,Table> tables;
};