#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

/*
 Name: Kian McKenna
 Email: kgmckenna@crimson.ua.edu
 Course Section: Spring 2025 CS 201
 Homework #: 0
 Instructions to Compile: g++ -Wall -homework.cpp -o homework0
 Instructions to Execute: ./homework0 filename.txt
*/

using namespace std;
using namespace chrono;

int main (int argc, char* argv[]) { // argc is the number of arguments, argv is the array of arguments
    if (argc < 2) { // if there arent enough arguments return an error
        std::cerr << "Error: No filename provided." << std::endl;
        return 1;
    }

    string filename = argv[1]; // get the filename from the arguments
    ifstream file(filename); // open the file

    if (!file) { // if the file is not open return an error
        cout << filename << " does not exist." << endl;
        return 1;
    }

    vector<string> info; // create a vector to store the information
    string temp;
    string line;

    auto startRead = high_resolution_clock::now(); // start the timer

    while (getline(file, line)) { // loop through the file and get the information
        info.push_back(line); // pushes info into vector
    }

    auto endRead = high_resolution_clock::now(); // end the timer
    auto durationRead = duration_cast<milliseconds>(endRead - startRead); // get the duration of the timer

    file.close(); // close the file

    auto startSortByName = high_resolution_clock::now(); // start the timer

    sort(info.begin(), info.end()); // sort the vector

    auto endSortByName = high_resolution_clock::now(); // end the timer
    auto durationSortByName = duration_cast<milliseconds>(endSortByName - startSortByName); // get the duration of the timer

    int size = info.size(); // get the size of the vector

    string byName = "dbfile1ByName.txt"; // create a new file for sorted by name
    ofstream fileByName(byName); // open the file

    for (int i = 0; i < size; i++) { // loop through the vector and print the information
        fileByName << info.at(i) << endl;
    }
    fileByName.close(); // close the file

    file.open(filename); // open the file again

    vector<pair<int, string>> years; // create a vector to store the years
    ofstream fileByYear("dbfile1ByYear.txt"); // create a new file for sorted by year

    auto startSortByYear = high_resolution_clock::now();

    while (getline(file, line)) {
        size_t start = line.find('('); // find the start of the year
        size_t end = line.find(')'); // find the end of the year

        if (start != string::npos && end != string::npos) { // if the year is found
            try {
                int year = stoi(line.substr(start + 1, end - start - 1)); // get the year
                years.emplace_back(year, line); // add the year and the line to the vector
            } catch (const invalid_argument& e) { // if the year is not a number
                cout << "Invalid year format in line: " << line << endl;
            }
        }
    }

    sort(years.begin(), years.end()); // sort the vector

    auto endSortByYear = high_resolution_clock::now();
    auto durationSortByYear = duration_cast<milliseconds>(endSortByYear - startSortByYear); // get the duration of the timer

    for (const auto& entry : years) { // loop through the vector and print the information
        fileByYear << entry.second << endl;
    }

    auto totalTime = durationRead + durationSortByName + durationSortByYear;

    cout << "File: " << filename << endl;
    cout << "Number of records: " << info.size() << endl;
    cout << "Time taken to create collection: " << durationRead.count() << " ms" << endl;
    cout << "Time taken to sort by name: " << durationSortByName.count() << " ms" << endl;
    cout << "Time taken to sort by year: " << durationSortByYear.count() << " ms" << endl;
    cout << "Total time taken: " << totalTime.count() << " ms" << endl;


    fileByYear.close(); // close the file
    fileByName.close(); // close the file
    file.close(); // close the file

    return 0;
}