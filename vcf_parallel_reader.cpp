#include "vcf_parallel_reader.h"

VCFParallelReader::VCFParallelReader(const std::string& filename, int num_threads)
    : filename(filename), num_threads(num_threads), done(false) {}

void VCFParallelReader::read() {
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Determine file size
    file.seekg(0, std::ios::end);
    std::streampos file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Calculate chunk size
    std::streampos chunk_size = file_size / num_threads;

    // Start threads to process chunks
    for (int i = 0; i < num_threads; ++i) {
        std::streampos start = i * chunk_size;
        std::streampos end = (i == num_threads - 1) ? file_size : start + chunk_size;
        threads.emplace_back(&VCFParallelReader::process_chunk, this, start, end);
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    file.close();
}

void VCFParallelReader::process_chunk(std::streampos start, std::streampos end) {
    std::ifstream chunk_file(filename);
    chunk_file.seekg(start);

    std::string line;
    while (std::getline(chunk_file, line) && chunk_file.tellg() <= end) {
        // Process the line
        if (line[0] == '#') {
            continue; // Skip headers
        }

        // Here you would parse the VCF line
        std::lock_guard<std::mutex> lock(file_mutex);
        //std::cout << "Thread " << std::this_thread::get_id() << " processing line: " << line << std::endl;
        
        
        //std::cout << "Thread " << std::this_thread::get_id() << " processing line: " << line.substr(6,10) << std::endl;

    }

    chunk_file.close();
}
