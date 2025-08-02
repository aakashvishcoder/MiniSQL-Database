#include <vector>
#include <string>
#include <iostream>
#include "parse.hpp"
using namespace std;

class Parse { 
public:
    Command* parse(const vector<string>& tokens) {
        string cmd = tokens[0];
        Command* ans;
        if(tokens.empty()) {
            cout << "Empty command!" << endl;
            return nullptr;
        } else if(cmd == "CREATE") {
            ans = parseCreateTable(tokens);
        } else if(cmd == "INSERT") {
            ans = parseInsert(tokens);
        } else if(cmd == "SELECT") {
            ans = parseSelect(tokens);
        } else if(cmd == "DELETE") {
            ans = parseDelete(tokens);
        } else if (cmd == "DROP"){
            ans = parseDropTable(tokens);
        } else {
            cout << "Invalid Command! Please re-enter a command!" << endl;
            return nullptr;
        }
        return ans;
    }
private:
    Command* parseCreateTable(const vector<string>& tokens) {
        /* example command
        CREATE TABLE students (id INT, name TEXT, age INT);*/
        if (tokens.size() < 8 || tokens[1] != "TABLE" || tokens[3] != "(") {
            cout << "Invalid CREATE syntax!" << endl;
            return nullptr;
        }
        string tableName = tokens[2];
        vector<pair<string,string>> columns;
        int index = 4; 
        while(tokens[index] != ")") {
            if (index + 1 >= tokens.size()) {
                cout << "Syntax error in column definition!" << endl;
                return nullptr;
            }
            if(tokens[index] == ",") {
                index++;
                continue;
            }
            pair<string,string> column = {tokens[index],tokens[index+1]};
            columns.push_back(column);
            index+=2;
        }
        return new CreateTableCommand(tableName,columns);
    };
    Command* parseInsert(const vector<string>& tokens) {
        /* example command 
        INSERT INTO students VALUES (1, 'Alice', 20);*/ 
        if (tokens.size() < 8 || tokens[1] != "INTO" || tokens[3] != "VALUES" || tokens[4] != "(") {
            cout << "Invalid INSERT syntax!" << endl;
            return nullptr;
        }
        string tableName = tokens[2];
        int index = 4; 
        vector<string> values;
        while(tokens[index] != ")") {
            if (index + 1 >= tokens.size()) {
                cout << "Syntax error in column definition!" << endl;
                return nullptr;
            }
            if(tokens[index] == ",") {
                index++;
                continue;
            }
            values.push_back(tokens[index]);
            index++;
        }
        return new InsertCommand(tableName,values);
    };
    Command* parseSelect(const vector<string>& tokens) {
        /*example command
        SELECT name, age FROM students;*/
        if (tokens.size() < 5) {
            cout << "Invalid SELECT syntax!" << endl;
            return nullptr;
        }
        int index = 1;
        vector<string> columns;
        string tableName = tokens[tokens.size()-2];
        while(tokens[index] != "FROM") {
            if(tokens[index] == ",") {
                index++;
                continue;
            }
            columns.push_back(tokens[index]);
            index++;
        }
        return new SelectCommand(tableName,columns);
    };
    Command* parseDelete(const vector<string>& tokens) {
        /*example command
        DELETE FROM students WHERE age > 18 AND name = 'Alice';*/
        if (tokens.size() < 8 || tokens[1] != "FROM" || tokens[3] != "WHERE") {
            cout << "Invalid DELETE syntax!" << endl;
            return nullptr;
        }

        string tableName = tokens[2];
        vector<Condition> conditions;
        int index = 4;

        while (index < tokens.size()) {
            if (tokens[index] == "AND") {
                ++index;
                continue;
            }
            if (index + 2 >= tokens.size()) {
                cout << "Incomplete condition in DELETE query!" << endl;
                return nullptr;
            }
            conditions.emplace_back(tokens[index], tokens[index + 1], tokens[index + 2]);
            index += 3;
        }

        return new DeleteCommand(tableName, conditions);
    };

    Command* parseDropTable(const vector<string>& tokens) {
        /*example command
        DROP TABLE students;*/
        if (tokens.size() < 4 || tokens[1] != "TABLE") {
            cout << "Invalid DROP syntax!" << endl;
            return nullptr;
        }
        int index = 2;
        vector<string> tableNames;
        while(index < tokens.size()) {
            if(tokens[index]==",") {
                index++;
                continue;
            }
            tableNames.push_back(tokens[index]);
            index++;
        }
        return new DropTableCommand(tableNames);
    };
};

