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
        std::stringstream ss(line);
        std::string str;
        if (getline(ss, str, ',')) //每行的第一个数据为 dataout
        {
            for (int i = 0; i < 10; i++) {
                row.dataout(0, 0, i) = 0;
            }
            row.dataout(0, 0, std::stoi(str)) = 1;
        }
        //剩余的数据
        for (int i = 0; i < 28*28 - 1; i++){
            std::getline(ss, str, ',');
            row.data[i] = std::stoi(str);
        }
        std::getline(ss, str, '\n');
        row.data[28*28 - 1] = std::stoi(str);
        dataset.push_back(row);
    }

    file.close();
    return dataset;
}