#include "vcf_parallel_reader.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    vector<string> args(argv + 1, argv + argc);
    std::string filename = "";
    int num_threads = 4; // Number of threads to use


    for (auto i = args.begin(); i != args.end(); ++i) {
            if (*i == "-h" || *i == "--help") {
                cout << "Syntax: -i [input-file] -j <num-threads>" << endl;
                return 0;
            } else if (*i == "-j") {
                num_threads = stoi(*++i);
            }else if (*i == "-i") {
                filename = (*++i);
            } 
    }

    //filename = "/Users/amatur/code/selbin-integration/example/p4.2000.vcf";
    
    VCFParallelReader reader(filename, num_threads);
    reader.read();

    cout<<("Input file loaded in "+to_string((clock() / (double) CLOCKS_PER_SEC))+" s. \n");

    return 0;
}