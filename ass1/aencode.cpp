/* mpreal.h is a cpp wrapper for MPFR,  written by Pavel Holoborodko
 * http://www.holoborodko.com/pavel/mpfr/ 
 * The rest code is written by Qiaoyang Wang z3493295*/


#include <iostream>
#include <mpfr.h>
#include <gmp.h>
#include <fstream>
#include <vector>
#include <map>
#include "mpreal.h"

using namespace mpfr;




void count_symbol(std::map<char, mpreal> &symbol_count, char c) {
    if (symbol_count.find(c) == symbol_count.end()) {
        symbol_count[c] = 1;
    }
    else {
        symbol_count[c]++;
    }
}

void calc_high_range(std::map<char, mpreal> &hr_map, std::map<char, mpreal> &prob_map) {
    mpreal high_range = 0;
    for (const auto &c : prob_map) {
        high_range += c.second;
        hr_map[c.first] = high_range;
    }
}

void calc_low_range(std::map<char, mpreal> &lr_map, std::map<char, mpreal> &prob_map) {
    mpreal low_range = 0;
    for (const auto &c : prob_map) {
        lr_map[c.first] = low_range;
        low_range += c.second;
    }
}

void calc_probs(std::map<char, mpreal> &count_map, std::map<char, mpreal> &prob_map, mpreal n_total_symbols) {

    for(const auto &c : count_map) {
        char ch = c.first;
        mpreal freq_symbol = c.second;
        mpreal prob_symbol = freq_symbol / n_total_symbols;
        prob_map[c.first] = prob_symbol;
        std::cout << ch << " " << freq_symbol << std::endl;
    }
}

int main() {
    std::string input;

    mpfr::mpreal::set_default_prec(10000);
    mpreal::set_default_rnd(MPFR_RNDA);

    mpreal high = 1.0;
    mpreal low = 0.0;
    mpreal code_range = 1.0;
    mpreal output = 0;

    mpreal n_total_symbols = 0;
    mpreal prob_symbol = 0;
    mpreal freq_symbol = 0;


    while(std::getline(std::cin, input));
    std::map<char, mpreal> symbol_count;
    std::map<char, mpreal> symbol_prob;
    std::map<char, mpreal> hr_map;
    std::map<char, mpreal> lr_map;
    
    for (const char &c:input) {
       count_symbol(symbol_count, c);
       n_total_symbols++;
    }

    
    calc_probs(symbol_count, symbol_prob, n_total_symbols);
    calc_high_range(hr_map, symbol_prob);
    calc_low_range(lr_map, symbol_prob);

    // for (const auto &c : symbol_prob) {
    //     std::cout << "( " << c.first << ", " << c.second << ", " << lr_map[c.first] << " -  " << hr_map[c.first] << std::endl;
    // }

    //Low and High calc
    for (const auto &c : input) {
        code_range = high - low;
        high = low + code_range * hr_map[c];
        low = low + code_range * lr_map[c];
        //std::cout << c << " " << low.toString() << " " << high.toString() << std::endl; 
    }
    output = low;
    std::cout << low.toString() << " " << high.toString() << "\n";

}