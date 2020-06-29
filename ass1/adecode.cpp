#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "mpreal.h"

using namespace mpfr;

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

void calc_probs(std::map<char, mpreal> &count_map, std::map<char, mpreal> &prob_map, mpreal n_symbols) {

    for(const auto &c : count_map) {
        char ch = c.first;
        mpreal freq_symbol = c.second;
        mpreal prob_symbol = freq_symbol / n_symbols;
        prob_map[c.first] = prob_symbol;
    }
}

int main (void) {
    mpfr::mpreal::set_default_prec(10000);
    mpreal::set_default_rnd(MPFR_RNDA);
    int n_lines = 0;
    int curr_lines = 0;

    std::string input;

    std::map<char, mpreal> hr_map;
    std::map<char, mpreal> lr_map;
    std::map<char, mpreal> freqs;
    std::map<char, mpreal> probs;
    std::vector<std::string> text;

    mpreal n_symbols = 0;
    mpreal freq_symbol = 0;

    mpreal encode_num = 0;
    mpreal range = 0;
    mpreal high_value = 0;
    mpreal low_value = 0;

    std::string num_str;


    while(std::getline(std::cin, input)) {
        text.push_back(input);
    }

    for (int x = 0; x < text.size(); ++x) {
        if (x < text.size() - 1) {
            char a = text[x][0];
            std::string b = text[x].substr(2);
            freq_symbol = std::stoi(b);
            n_symbols += freq_symbol;
            // if(isspace(a)) a = '\s';
            freqs[a] = freq_symbol;
        }
        else {
             for(const auto &c : text[x]) {
                if (isspace(c)) {
                    break;
                }
                num_str.push_back(c);
            }
        }
    }

    
    
    calc_probs(freqs, probs, n_symbols);
    calc_low_range(lr_map, probs);
    calc_high_range(hr_map, probs);

    encode_num = num_str;

    mpreal output_counter = 0;

    std::map<char, mpreal>::iterator it = lr_map.begin();
    while (it != lr_map.end()) {
        if(output_counter >= n_symbols) break;
        high_value = hr_map[it->first];
        low_value = it->second;
        if (encode_num >= low_value && encode_num < high_value) {
            std::cout << it->first;  
            ++output_counter;   
            range = high_value - low_value;
            encode_num = (encode_num - low_value) / range;
            it = lr_map.begin();
            continue;
        }
        ++it;
    }

}