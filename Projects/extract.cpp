#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <vector>
#include <list>
#include <map>

using namespace std;

map<string, int> query_grade_map;

unsigned long djb2(string str) {
    const char *ptr = str.c_str();
    unsigned long hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

class HashTable {
public:
    HashTable(int size, int collision_strategy, int a = 0)
        : size(size), collision_strategy(collision_strategy), a(a) {
        table.resize(size);
    }

    void insert(string key, int line) {
        int index = h1(key);

        if (table[index].first.empty()) {
            table[index].first = key;
            table[index].second.push_back(line);
        } else {
            int j = 0;
            int prev_index = index;
            int collisions = 0;

            while (!table[index].first.empty() && table[index].first != key) {
                collisions++;
                j++;
                prev_index = index;
                index = get_next_index(key, j);
            }

            if (table[index].first.empty()) {
                table[index].first = key;
                table[index].second.push_back(line);
            } else {
                table[index].second.push_back(line);
            }

            total_collisions += collisions;
        }
        total_words++;
    }

    pair<string, pair<vector<int>, int>> search(string key) {
        int index = h1(key);
        int j = 0;
        int collisions = 0;

        while (!table[index].first.empty() && table[index].first != key) {
            collisions++;
            j++;
            index = get_next_index(key, j);
        }

        return {table[index].first, {table[index].second, collisions}};
    }

    int get_total_words() {
        return total_words;
    }

    int get_distinct_words() {
        int distinct = 0;
        for (const auto &entry : table) {
            if (!entry.first.empty()) {
                distinct++;
            }
        }
        return distinct;
    }

    int get_total_collisions() {
        return total_collisions;
    }

private:
    int h1(string key) {
        return djb2(key) % size;
    }

    int h2(string key) {
        return a - (djb2(key) % a);
    }

    int get_next_index(string key, int j) {
        switch (collision_strategy) {
        case 1:
            return (h1(key) + j) % size;
        case 2:
            return (h1(key) + j * j) % size;
        case 3:
            return (h1(key) + j * h2(key)) % size;
        default:
            return -1;
        }
    }

    int size;
    int collision_strategy;
    int a;
    vector<pair<string, vector<int>>> table;
    int total_words = 0;
    int total_collisions = 0;
};

void process_word(HashTable &hash_table, string &word, int line) {
    if (!word.empty()) {
        for (auto &c : word) {
            c = tolower(c);
        }
        hash_table.insert(word, line);
    }
}

int calculate_new_grade(const string& student_name) {
    return query_grade_map[student_name] + 5;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        cerr<< "Error: Not enough command-line arguments.\n";
        return 1;
    }

    string input_file = argv[1];
    string query_file = argv[2];
    int size = stoi(argv[3]);
    int collision_strategy = (argv[4][0] == 'l' ? 1 : (argv[4][0] == 'q' ? 2 : 3));
    int a = (collision_strategy == 3 ? stoi(argv[5]) : 0);

    HashTable hash_table(size, collision_strategy, a);

    ifstream in(input_file);
    if (!in) {
        cerr << "Error: Unable to open input file.\n";
        return 1;
    }

    string line;
    int line_number = 1;
    while (getline(in, line)) {
        string word;
        istringstream iss(line);
        char c;
        while (iss.get(c)) {
            if (isalpha(c)) {
                word.push_back(c);
            } else {
                process_word(hash_table, word, line_number);
                word.clear();
            }
        }
        process_word(hash_table, word, line_number);
        line_number++;
    }
    in.close();

    cout << "The number of words found in the file was " << hash_table.get_total_words() << '\n';
    cout << "The number of unique words found in the file was " << hash_table.get_distinct_words() << '\n';
    cout << "The number of collisions was " << hash_table.get_total_collisions() << '\n';

    ifstream queries(query_file);
    if (!queries) {
        cerr << "Error: Unable to open query file.\n";
        return 1;
    }

    while (getline(queries, line)) {
        istringstream iss(line);
        string query;
        iss >> query;

        auto result = hash_table.search(query);
        cout << endl;
        cout << query << " appears on lines [";
        if (!result.second.first.empty()) {
            for (size_t i = 0; i < result.second.first.size(); ++i) {
                if (i > 0) {
                    cout << ",";
                }
                cout << result.second.first[i];
            }
        }
        cout << "]\nThe search had " << result.second.second << " collisions\n";
        
    }
    queries.close();

    return 0;
}
