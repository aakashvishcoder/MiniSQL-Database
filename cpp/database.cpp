#include <vector>
#include <string>
#include <iostream>
#include "database.hpp"
using namespace std;

Table::Table(const vector<pair<string,string>>& schema)
: schema(schema) {}

class Database {
private:
    unordered_map<string,Table> tables;
public:
    void createTable(const string& name, const vector<pair<string,string>>& schema) {
        if(tables.find(name) == tables.end()) {
            tables[name] = Table(schema);
        } else {
            cout << "Table already exists!" << endl;
        }
    }
    void insert(const string& name, const vector<string>& values) {
        if(tables.find(name) == tables.end()) {
            cout << "Table not found in database!" << endl;
            return;
        }
        Table& table = tables[name];
        if(values.size() != table.schema.size()) {
            cout << "Mismatched sizes!" << endl;
            return;
        }
        table.rows.push_back(values);
    }
    void deleteRows(const string& tableName, const vector<Condition>& conditions) {
        if(tables.find(tableName) == tables.end()) {
            cout << "Table not found in database!" << endl;
            return;
        }

        Table& table = tables[tableName];

        unordered_map<string, int> colIndex;
        for (int i = 0; i < table.schema.size(); i++) {
            colIndex[table.schema[i].first] = i;
        }

        auto& rows = table.rows;
        for (auto it = rows.begin(); it != rows.end(); ) {
            bool shouldDelete = true;

            for (const Condition& c : conditions) {
                int colIdx = colIndex[c.col];
                string rowValue = (*it)[colIdx];
                string colType = table.schema[colIdx].second;

                bool conditionMet = false;

                if (colType == "INT") {
                    int rowValInt = stoi(rowValue);
                    int condValInt = stoi(c.value);

                    if (c.op == "=") conditionMet = (rowValInt == condValInt);
                    else if (c.op == ">") conditionMet = (rowValInt > condValInt);
                    else if (c.op == "<") conditionMet = (rowValInt < condValInt);
                } else {
                    if (c.op == "=") conditionMet = (rowValue == c.value);
                }

                if (!conditionMet) {
                    shouldDelete = false;
                    break;
                }
            }

            if (shouldDelete) {
                it = rows.erase(it); // erase returns new iterator
            } else {
                it++;
            }
        }

        cout << "Rows deleted if matched." << endl;
    }
    void selectRows(const string& tableName, const vector<string>& columns, const vector<Condition>& conditions = {}) {
        if (tables.find(tableName) == tables.end()) {
            cout << "Table not found!" << endl;
            return;
        }

        Table& table = tables[tableName];

        unordered_map<string, int> colIndex;
        for (int i = 0; i < table.schema.size(); i++) {
            colIndex[table.schema[i].first] = i;
        }

        for (const auto& col : columns) {
            if (colIndex.find(col) == colIndex.end()) {
                cout << "Invalid column in SELECT: " << col << endl;
                return;
            }
        }

        for (const auto& col : columns) {
            cout << col << "\t";
        }
        cout << endl;

        for (const auto& row : table.rows) {
            bool match = true;

            for (const auto& cond : conditions) {
                int idx = colIndex[cond.col];
                string val = row[idx];
                string type = table.schema[idx].second;
                bool conditionMet = false;

                if (type == "INT") {
                    int valInt = stoi(val);
                    int condInt = stoi(cond.value);
                    if (cond.op == "=") conditionMet = (valInt == condInt);
                    else if (cond.op == "<") conditionMet = (valInt < condInt);
                    else if (cond.op == ">") conditionMet = (valInt > condInt);
                } else {
                    if (cond.op == "=") conditionMet = (val == cond.value);
                }

                if (!conditionMet) {
                    match = false;
                    break;
                }
            }

            if (match) {
                for (const auto& col : columns) {
                    cout << row[colIndex[col]] << "\t";
                }
                cout << endl;
            }
        }
    }
    void dropTable(const vector<string>& tableNames) {
        for (const string& name : tableNames) {
            if (tables.erase(name)) {
                cout << "Table removed: " << name << endl;
            } else {
                cout << "Table not found: " << name << endl;
            }
        }
    }
    bool tableExists(const string& name) {
        return tables.find(name) != tables.end();
    }
};