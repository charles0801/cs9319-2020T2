#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <chrono>
#include <cmath>
#include <unordered_map>
using namespace std;

#define BUFFER_SIZE 40000
#define GAP_SIZE 3
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./bwtdecode <BWT file path> <Reversed file path>" << endl;
        return -1;
    }        
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    ios_base::sync_with_stdio(false);

    unordered_map<char, vector<int>> occ_table;
    unordered_map<char, int> c_table;

    int diff = 0;
    char cur_sym = '\n';
    int cur_index = 0;
    string result = "\n";

    if (!input) {
        cerr << "Could not open BWT file " << argv[1] << endl;
        return -1;
    }

    // while (input.get(c)) {
    //     if (c_table.find(c) != c_table.end()) {
    //         c_table[c]++;
    //     }
    //     else {
    //         c_table[c] = 1;
    //     }
    //     if (c == '\n'){ 
    //         cur_index = occ_table.size();
    //     }
    //     occ_table.push_back(make_tuple(c, c_table[c]-1));
    // }
    int fp = 0;
    int gap_count = 0;
    unsigned long long int loop = 0;
    while(!input.eof()) {
        string buffer(GAP_SIZE, '\0'); 
        input.read(&buffer[0], GAP_SIZE);
        gap_count++;
        char last_char;
        for (char c : buffer) {
            if (c == '\000')
                break;
            c_table[c]++;
            
            if (c == '\n') {
                cur_index = fp;
            }
            fp += 1;
            last_char = c;

        }
        if (input.eof()) {
            break;
        }
        if(last_char == 'A')
            occ_table['A'].push_back(c_table['A']-1);
        else
            occ_table['A'].push_back(c_table['A']);
        if(last_char == 'T')
            occ_table['T'].push_back(c_table['T']-1);
        else
            occ_table['T'].push_back(c_table['T']);
        if(last_char == 'C')
            occ_table['C'].push_back(c_table['C']-1);
        else
            occ_table['C'].push_back(c_table['C']);
        if(last_char == 'G')
            occ_table['G'].push_back(c_table['G']-1);
        else
            occ_table['G'].push_back(c_table['G']);
        
    }

    if (input.eof()) {
        input.clear();
        input.seekg(0, std::ios::beg);
    }

    string s {"\nACGT"};
    for(auto p : s) {
        int tmp = c_table[p];
        c_table[p] = diff;
        diff += tmp;
    }

    bool first_loop = true;
    int out_buffer_size = fp / 10;
    int out_buffer_count;
    unordered_map<int, string> buffer;
    string out_buffer;
    buffer.reserve(out_buffer_size);
    int buffered_operation = 0;
    int sum_op = 0;
    cout << "sum operation" << fp << "\n";
    while(true) {
        string buf_string(GAP_SIZE, '\0');
        int i_occ = floor(double(cur_index+1) / double(GAP_SIZE));
        int upper_occ = ceil(double(cur_index+1) / double(GAP_SIZE));

        int buf_p = 0;
        if(i_occ <= 0) {
            i_occ = 0;
        }
        else {
            buf_p = i_occ * GAP_SIZE - 1;
        }

        int search_len = 0;

        auto findIt = buffer.find(i_occ);
        search_len = cur_index - buf_p;
        if (findIt != buffer.end()) {
            buf_string = findIt->second;
            // ++buffered_operation;
        } else {
            if (buffer.size() >= BUFFER_SIZE) {
                buffer.erase(buffer.begin());
            }
            input.clear();
            input.seekg(buf_p, ios::beg);
            input.read(&buf_string[0], GAP_SIZE);
            buffer[i_occ] = buf_string;
        }
    
        cur_sym = buf_string[search_len];

        if(cur_sym == '\n'){
            if (!first_loop)
                break;
            cur_index = 0;
        } 
        else {
            if (i_occ > 0)
                cur_index = occ_table[cur_sym][i_occ-1];
            else
                cur_index = 0;
            for(int i = 0; i < search_len; ++i) {
                if(buf_string[i] == cur_sym) {
                    cur_index++;
                }
            }
            cur_index += c_table[cur_sym]; 
        }
        first_loop = false;
        auto ob_it = out_buffer.rbegin();
        
        out_buffer.push_back(cur_sym);
        // int w_counter = 0;
        // if (out_buffer.size() > out_buffer_size) {
        //     w_counter++;
        //     fp -= out_buffer_size;
        //     output.seekp(fp, ios::beg);
        //     output << out_buffer;
        //     out_buffer.clear();
        // }
        
    }
    output << out_buffer;
    cout << buffered_operation <<"\n";
    return 0;    
}