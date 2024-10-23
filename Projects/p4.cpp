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

map<string, int> queryGradeMap;

// Store the return of this function as an unsigned long!
unsigned long djb2(string str) {
   const char *ptr = str.c_str();
   unsigned long hash = 5381;
   int c;
   while ((c = *ptr++)) {
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   }
   return hash;
}

class HashTable {
   public:
      HashTable(int size, int strat, int a = 0) : size(size), collisionStrategy(strat), a(a) {
         hashbrown.resize(size);
      }

      void insert(string key, int line) {
         int index = h1(key);
         if (hashbrown[index].first.empty()) {
            hashbrown[index].first = key;
            hashbrown[index].second.push_back(line);
         } else {
            int j = 0;
            int prev_index = index;
            int collisions = 0;
            while (!hashbrown[index].first.empty() && hashbrown[index].first != key) {
               collisions++;
               j++;
               prev_index = index;
               index = getNextIndex(key, j);
            }
            if (hashbrown[index].first.empty()) {
               hashbrown[index].first = key;
               hashbrown[index].second.push_back(line);
            } else {
               hashbrown[index].second.push_back(line);
            }
            totCollisions += collisions;
         }
         totWords++;
      }

      pair<string, pair<vector<int>, int>> search(string key) {
         int index = h1(key);
         int j = 0;
         int collisions = 0;

         while (!hashbrown[index].first.empty() && hashbrown[index].first != key) {
            collisions++;
            j++;
            index = getNextIndex(key, j);
         }

         return {hashbrown[index].first, {hashbrown[index].second, collisions}};
      }

      int totalWords() {
         return totWords;
      }

      int uniqueWords() {
         int unique = 0;
        for (const auto &entry : hashbrown) {
            if (!entry.first.empty()) {
               unique++;
            }
        }
        return unique;
      }

      int totalCollisions() {
         return totCollisions;
      }

   private:
      int h1(string key) {
         return djb2(key) % size;
      }

      int h2(string key) {
         return a - (djb2(key) % a);
      }

      int getNextIndex(string key, int j) {
         switch (collisionStrategy) {
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
      int collisionStrategy;
      int a;
      vector<pair<string, vector<int>>> hashbrown;
      int totWords = 0;
      int totCollisions = 0; 
};

void format(HashTable &hashbrown, string &str, int line) {
   if (!str.empty()) {
        for (auto &c : str) {
            c = tolower(c);
        }
        hashbrown.insert(str, line);
    }
}

int calculate_new_grade(const string& studentName) {
    return queryGradeMap[studentName] + 5;
}

int main(int argc, char* argv[]) {

   if (argc != 5 && argc != 6) {
      cout << "Incorrect usage" << endl;
      return -1;
   }

   ifstream inFS(argv[1]);
   if (!inFS) {
      cout << "File" << argv[1] << " does not exist" << endl;
      return 1;
   }
   ifstream qF(argv[2]);
   if (!qF) {
      cout << "File: " << argv[2] << " does not exist" << endl;
      return 1;
   }
   int size = stoi(argv[3]);
   int strat = (argv[4][0] == 'l' ? 1: (argv[4][0] == 'q' ? 2: 3));
   int a = (strat == 3 ? stoi(argv[5]): 0);
   HashTable hashTable(size, strat, a);
   
   string line;
   int numLine = 1;
   while (getline(inFS, line)) {
      string str;
      istringstream iss(line);
      char ch;
      while(iss.get(ch)) {
         if (isalpha(ch)) {
            str.push_back(ch);
         } else {
            format(hashTable, str, numLine);
            str.clear();
         }
      }
      format(hashTable, str, numLine);
      numLine++;
   }
   inFS.close();

   cout << "The number of words found in the file was " << hashTable.totalWords() << endl;
   cout << "The number of unique words found in the file was " << hashTable.uniqueWords() << endl;
   cout << "The number of collisions was " << hashTable.totalCollisions() << endl;

   while (getline(qF, line)) {
      istringstream iss(line);
      string input;
      iss >> input;

      auto result = hashTable.search(input);
      cout << endl;
      cout << input << " appears on lines [";
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
   qF.close();

   return 0;
}
