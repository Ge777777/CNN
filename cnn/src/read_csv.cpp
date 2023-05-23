#include "../include/read_csv.h"

std::vector<case_s> read_csv (std::string path){
    std::vector<case_s> dataset;
    case_s row(28,28,1,10,1,1);
    std::ifstream file (path);
    if (!file.is_open()){
        std::cout << "File not found!" << std::endl;
        return dataset;
    } else {
        std::cout << "OK" << std::endl;
    }
    std::string line;
    if(getline(file, line)) //跳过第一行(目录行，没有意义）
    {

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string str;
            if(getline(ss,str, ',')) //每行的第一个数据为dataout
            {
               for(int i = 0; i < 10; i++){
                     row.dataout(0,0,i) = 0;
               }
               row.dataout(0,0,std::stoi(str)) = 1;
            }
            //剩余的数据
            int i = 0;
            while (std::getline(ss, str, ',')) {
                row.data[i] = std::stod(str);
                i++;
            }
            dataset.push_back(row);
        }
        file.close();
    }
    return dataset;
}