#ifndef VCF_PARALLEL_READER_H
#define VCF_PARALLEL_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

class VCFParallelReader {
public:
    VCFParallelReader(const std::string& filename, int num_threads);
    void read();
    void process_chunk(std::streampos start, std::streampos end);

private:
    std::string filename;
    int num_threads;
    std::vector<std::thread> threads;
    std::mutex file_mutex;
    std::condition_variable cv;
    bool done;
    std::ifstream file;
};

#endif // VCF_PARALLEL_READER_H
