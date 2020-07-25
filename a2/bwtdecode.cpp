#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <chrono>

using namespace std;



int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./bwtdecode <BWT file path> <Reversed file path>" << endl;
        return -1;
    }        
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    char c;
    vector<tuple<char, int>> occ_table;
    map<char, int> c_table;
    int diff = 0;
    char cur_sym = '\n';
    int cur_index = 0;
    string result = "\n";

    if (!input) {
        cerr << "Could not open BWT file " << argv[1] << endl;
        return -1;
    }

    auto t1 = chrono::high_resolution_clock::now();
    while (input.get(c)) {
        if (c_table.find(c) != c_table.end()) {
            c_table[c]++;
        }
        else {
            c_table[c] = 1;
        }
        if (c == '\n'){ 
            cur_index = occ_table.size();
        }
        occ_table.push_back(make_tuple(c, c_table[c]-1));
    }
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    cout << "first while: " << duration << endl;
    for(auto p : c_table) {
        c_table[p.first] = diff;
        diff += p.second;
    }
    t1 = chrono::high_resolution_clock::now();
    while(true) {
        cur_index = get<1>(occ_table[cur_index]) + c_table[cur_sym];
        cur_sym = get<0>(occ_table[cur_index]);
        if (cur_sym == '\n') {
            break;
        }
        result.insert(result.begin(), cur_sym);
    }
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    cout << "second while: " << duration << endl;
    output << result;
    // enc.pop_back();
    // string dec = decodebwt(enc);
    // output << dec;
    return 0;    
}