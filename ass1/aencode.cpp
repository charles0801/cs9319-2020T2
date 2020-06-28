#include <iostream>
#include <mpfr.h>
#include <gmp.h>
#include <fstream>
#include <vector>
#include <map>
#include "real.hpp"

using namespace mpfr;


void count_symbol(std::map<char, real<256>> &symbol_count, char c) {
    if (symbol_count.find(c) == symbol_count.end()) {
        symbol_count[c] = 1;
    }
    else {
        symbol_count[c]++;
    }
}

void calc_high_range(std::map<char, real<256>> &hr_map, std::map<char, real<256>> &prob_map) {
    real<256> high_range = 0;
    for (const auto &c : prob_map) {
        high_range += c.second;
        hr_map[c.first] = high_range;
    }
}

void calc_low_range(std::map<char, real<256>> &lr_map, std::map<char, real<256>> &prob_map) {
    real<256> low_range = 0;
    for (const auto &c : prob_map) {
        lr_map[c.first] = low_range;
        low_range += c.second;
    }
}

int main() {
    std::string input;

    real<256> high = 1.0;
    real<256> low = 0.0;

    real<256> n_total_symbols = 0;
    real<256> prob_symbol = 0;
    real<256> freq_symbol = 0;


    while(std::cin >> input);
    std::map<char, real<256>> symbol_count;
    std::map<char, real<256>> symbol_prob;
    std::map<char, real<256>> hr_map;
    std::map<char, real<256>> lr_map;
    
    for (auto &c:input) {
       count_symbol(symbol_count, c);
       n_total_symbols++;
    }

    for(const auto &c : symbol_count) {
        char ch = c.first;
        freq_symbol = c.second;
        prob_symbol = freq_symbol / n_total_symbols;
        symbol_prob[c.first] = prob_symbol;
    }

    calc_high_range(hr_map, symbol_prob);
    calc_low_range(lr_map, symbol_prob);

    for (const auto &c : symbol_prob) {
        std::cout << "( " << c.first << ", " << c.second << ", " << lr_map[c.first] << " -  " << hr_map[c.first] << std::endl;
    }

}