#include <iostream>
#include <random>
#include <ctime>
#include <vector> 
#include <string>
#include <cstring>
using namespace std;

class Encode{
private:
    int num;
    int key_val;
    int length;
    int n;
    vector<int> final_value;
    std::random_device rd;
    std::mt19937 gen(rd());
    vector<int> array = {2, 3, 5, 7, 11, 17, 67};

public:
    Encode(int num, int random_val) : num(num), key_val(key_val) {
        std::string s = std::to_string(num);
        length = s.size();
        n = 34 - length;
        n *= 2;
    };
    int random_value(int l, int r){
        std::uniform_int_distribution<> distrib(l, r);
        return distrib(gen);
    };
    void put_value(vector<int> vec){
        for(int i = 0; i < vec.size(); i++){
            final_value[vec[i]] = random_value(0, 9);
        }
    };
    vector<int> find_duplikate(vector<int> vec){
        std::sort(vec.begin(), vec.end());

        std::vector<int> duplicates;
        for (size_t i = 0; i < vec.size() - 1; ++i) {
            if (vec[i] == vec[i + 1]) {
                duplicates.push_back(vec[i]);
                vec.erase(vec.begin() + i);
                while (i < vec.size() - 1 && vec[i] == vec[i + 1]) {
                    vec.erase(vec.begin() + i);
                    duplicates.push_back(vec[i]);
                    i++;
                }
            }
        }
        return vec;
    };
    void perform_key(){
        vector<int> indexes;
        string key = "";
        int len = 0;
        while(true){
            key = to_string(key_val);
            int len = key.size();
            if(len > n){
                break;
            }
            key_val *= key_val;
        }
        value = to_string(key_val);
        if(n % 2 != 0){
            l = value.size();
            if(l % 2 == 0){
                value = std::string(value.begin(), value.end() - 1);
            }
            bool flag = true;
            while(true){
                current_len = value.size();
                if(n == current_len){
                    break;
                } else{
                    if (flag){
                        value = std::string(value.begin() + 1, value.end());
                        flag = false;
                    } else{
                        value = std::string(value.begin(), value.end() - 1);
                    }
                }
            }
        }
        for(int i = 0; i < value.size(); i+=2){
            if(value[i] == '0'){
                int j = stoi(value[i + 1]);
                indexes.push_back
            } else{
                int j = stoi(value[i:i+1]);//мб не включительно
                indexes.push_back(j);
            }
        }
        for(int i = 0; i < indexes.size(); i++){
            if(indexes[i] >= 34){
                indexes[i] = indexes[i] % 34;
            }
        }
        while(true){
            vector<int> v = find_duplikate(indexes);
            if(v.empty()){
                break;
            }
            for(int i = 0; i < v.size(); i++) {
                v[i] += prime(i);
                v[i] *= v[i];
                v[i] = v[i] % 34;
                indexes.push_back(v[i]);
            }
        }
    }
    vector<int> perf_right(){
        vector<int> indexes;
        string key = "";
        int len = 0;
        while(true){
            key = to_string(key_val);
            int len = key.size();
            if(len > length){
                break;
            }
            key_val *= key_val;
        }
        value = to_string(key_val);
        if(length % 2 != 0){
            l = value.size();
            if(l % 2 == 0){
                value = std::string(value.begin(), value.end() - 1);
            }
            bool flag = true;
            while(true){
                current_len = value.size();
                if(length == current_len){
                    break;
                } else{
                    if (flag){
                        value = std::string(value.begin() + 1, value.end());
                        flag = false;
                    } else{
                        value = std::string(value.begin(), value.end() - 1);
                    }
                }
            }
        }
        for(int i = 0; i < value.size(); i++){
            indexes[i] = stoi(value[i]);
        }
        return indexes;
    }

};