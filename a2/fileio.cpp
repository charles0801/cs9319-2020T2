#include <iostream>
#include <fstream>
using namespace std;
int main() {
    char w;
    ifstream input("test/dna-tiny.bwt");
    input.seekg(3) >> w;
    cout << w << input.tellg() << endl;
    return 0; 
}
