#include "../include/read_csv.h"

std::vector<case_s> read_csv(std::string path) {
    std::vector<case_s> dataset;
    case_s row(in_x, in_y, in_z, out_x, out_y, out_z);
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return dataset;
    } else {
        std::cout << "Success" << std::endl;
    }
    std::string line;
    for(int i = 0; i < header; i++) {
        std::getline(file, line);
    }
    while (std::getline(file, line)) {
        std::string cell;
        std::stringstream ss(line);
        getline(ss, cell, ',') ;//每行的第一个数据为 outputVector
        for (int i = 0; i < 10; i++) {
            row.dataout(i, 0, 0) = 0;
        }
        row.dataout(std::stoi(cell), 0, 0) = 1;

        for (int i = 0; i < 28*28 - 1; ++i ){
            std::getline(file, cell, ',');
            row.data[i] = std::stof(cell)/255;
        }
        std::getline(file, cell);
        row.data[28 * 28 - 1] = std::stof(cell)/255;
        dataset.push_back(row);
        line.clear();
    }
    file.close();
    std::cerr << "Done" << std::endl;
    return dataset;
}