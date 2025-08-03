#include "commands.cpp"
#include "database.cpp"
#include "parse.cpp"
#include "tokenize.cpp"
using namespace std;

int main() {
    Database d;
    char start;

    cout << "Would you like to start? (y/n): ";
    cin >> start;
    cin.ignore(); 

    while (start == 'y') {
        string command;
        cout << ">> ";
        getline(cin, command);

        vector<string> tokenized = tokenize(command);
        Parse parser;
        Command* cmd = parser.parse(tokenized);

        if (!cmd) {
            cout << "Command parsing failed.\n";
        } else {
            if (auto* create = dynamic_cast<CreateTableCommand*>(cmd)) {
                d.createTable(create->tableName, create->columns);
            } else if (auto* insert = dynamic_cast<InsertCommand*>(cmd)) {
                d.insert(insert->tableName, insert->values);
            } else if (auto* select = dynamic_cast<SelectCommand*>(cmd)) {
                d.selectRows(select->tableName, select->columns);
            } else if (auto* del = dynamic_cast<DeleteCommand*>(cmd)) {
                d.deleteRows(del->tableName, del->conditions);
            } else if (auto* drop = dynamic_cast<DropTableCommand*>(cmd)) {
                d.dropTable(drop->tableNames);
            } else {
                cout << "Unknown command type.\n";
            }
            delete cmd;
        }

        cout << "\nWould you like to enter another command? (y/n): ";
        cin >> start;
        cin.ignore(); 
    }

    return 0;
}
