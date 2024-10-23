#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <climits>

using namespace std;

void help() {
    cout << "command list:" << endl
         << "\tprint" << endl
         << "\tcols" << endl
         << "\tsearch * | col_name val" << endl
         << "\tmin col_name" << endl
         << "\tmax col_name" << endl
         << "\tavg col_name" << endl;
}

void cols() {
    cout << "Id" << endl;
    cout << "Last name" << endl;
    cout << "First name" << endl;
    cout << "Weight" << endl;
    cout << "Empty" << endl;
    cout << "Age" << endl;
}

void search(const string& fileName, const string& col_name, const string& val, int colWidth) {
    ifstream inFS(fileName);
    string line;

    bool search = false;

    while (getline(inFS, line)){
        istringstream iss(line);
        string character;
        bool match = false;

        while (getline(iss, character, ',')){
            if (col_name == "*" || character == val){
                match = true;
                break;
            }
        }
        if(getline(iss, character)){
            if (col_name == "*" || character == val){
                match = true;
                break;
            }
        }
        if (match){
            search = true;
            istringstream iss(line);
            string tru;

            while (getline(iss, tru, ',')){
                cout << setw(colWidth) << tru;
            }
            cout << endl;
        }
    }

    if (!search){
        cout << "No results" << endl;
    }

    inFS.close();
}

void findValue(const string& filename, const string& operation, const string& colName){
    ifstream inputFile(filename);
    string line;
    int colIndex = -1;
    double minValue = 1000;
    double maxValue = 0;
    double sum = 0;
    int count = 0;

    if (getline(inputFile, line)) {
        istringstream iss(line);
        string columnName;

        for (int i = 0; getline(iss, columnName, ','); ++i) {
            if (columnName == colName) {
                colIndex = i;
                break;
            } 

        }
    }

    if (colIndex == -1) {
        cout << "Invalid column \"" << colName << "\"" << endl;
        return;
    }

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string field;
        double value;

        for (int i = 0; getline(iss, field, ','); ++i) {
            if (i == colIndex){
                value = stod(field);
                if (value < minValue) {
                    minValue = value;
                }

                if (value > maxValue) {
                    maxValue = value;
                }

                sum += value;
                ++count;

                break;
            }
        }
    }

    inputFile.close();

    if (count > 0) {
        double average = sum / count;

        if (operation == "min") {
            cout << "The min for col \"" << colName << "\" = " << minValue << endl;
        } else if (operation == "max") {
            cout << "The max for col \"" << colName << "\" = " << maxValue << endl;
        } else if (operation == "avg") {
            cout << "The avg for col \"" << colName << "\" = " << average << endl;
        }

    } else {
        cout << "N/A" << endl;
    }
}

void header(string fileName, int colWidth) {
    ifstream inFS;
    inFS.open(fileName);
    string line;
    getline(inFS, line);
    string token;
    istringstream iss(line);
    while (getline(iss, token, ',')) {     
        cout << setw(colWidth) << token << flush;
    }
    cout << endl;
}

void print(string fileName, int colWidth) {
    string line;
    ifstream inFS;
    inFS.open(fileName);
    while (getline(inFS, line)) {
        string token;
        istringstream iss(line);
        while (getline(iss, token, ',')) {     
            cout << setw(colWidth) << token << flush;
        }
        cout << endl;
    }

    inFS.clear();
    inFS.seekg(0);

    inFS.close();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
      cout << "Usage: ./a database.csv #col_width" << endl;
      return 1;
    }

    ifstream inFS;

    int colWidth = atoi(argv[2]);
    string fileName = argv[1];

    inFS.open(fileName);

    if (!inFS.is_open()) {
        cout << "Failed to open \"" << fileName << "\"" << endl;
        return 2;
    }

    string line;

    while (1) {

        cout << "Enter command or \"help\" for a command list" << endl;
        getline(cin, line);

        istringstream iss(line);

        string command;
        iss >> command;

        if (command == "quit") {
            break;
        }
        else if (command == "help") {
            help();
        } 
        else if (command == "print") {
            print(fileName, colWidth);
        } 
        else if (command == "cols") {
            cols();
        } else if (command == "search") {
            header(fileName, colWidth);
            string col_name;
            string val;

            iss >> quoted(col_name) >> quoted (val);
            
            search(fileName, col_name, val, colWidth);
        } 
        else if (command == "min" || command == "max" || command == "avg") {
            string col_name;

            iss >> quoted(col_name);

            findValue(fileName, command, col_name);
        }
        else cout << "Invalid command" << endl;

    }

    inFS.close();

    return 0;
}