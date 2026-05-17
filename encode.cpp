#include <iostream>
#include <random>
#include <ctime>
#include <vector> 
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

class Encode{
private:
    int64_t num;
    int64_t key_val;
    int length;
    int n;
    std::random_device rd;
    std::mt19937 gen;
    vector<int> final_value;   
    vector<int64_t> array1 = {3037000480, 1518499861, 379624939, 69740005, 3037000}; 

public:
    Encode(int64_t n_val, int64_t k_val) : gen(rd()) {
        this->num = n_val;
        this->key_val = k_val;

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
        }        std::mt19937 gen;
    };
    vector<int> find_duplikate(std::vector<int>& vec) {
        if (vec.size() < 2) return {};

        sort(vec.begin(), vec.end());
        vector<int> duplicates;

        for (size_t i = 0; i < vec.size() - 1; ++i) {
            if (vec[i] == vec[i + 1]) {
                duplicates.push_back(vec[i]);
                vec.erase(vec.begin() + i);
                if((i + 1) < vec.size()){
                    while(vec[i] == vec[i+1] && (i + 1) < vec.size()){
                        duplicates.push_back(vec[i]);
                        vec.erase(vec.begin() + i);
                        i++;
                    }
                }
            }
        }
        return duplicates;
    }
    vector<int> prime(size_t length){
        vector<int> vect;
        for(size_t i = 7; i <= 7 + length; i++){
            vect.push_back(i);
        }
        return vect;
    }
    vector<int> perform_key(){
        vector<int> indexes;
        string key = "";
        int len = 0;
        int id = 0;

        while(true){
            int len = key.size();
            if(key_val >= 3037000499){
                key = key + to_string(key_val);
                key_val = key_val / array1[id];
                if(key_val > 30370004){
                    key_val = key_val / 1902838;
                }
                id++;
            }
            if(len > n){
                key = key.substr(0, n);
                break;
            }
            key_val *= key_val;
        }
        string value = key;
        if(n % 2 != 0){
            int l = value.size();
            if(l % 2 == 0){
                value = std::string(value.begin(), value.end() - 1);
            }
            bool flag = true;
            while(true){
                int current_len = value.size();
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
                int j = std::stoi(std::string(1, value[i + 1]));
                indexes.push_back(j);
            } else{
                string dub = value.substr(i, 2);
                int j = stoi(dub);
                indexes.push_back(j);
            }
        }
        for(int i = 0; i < indexes.size(); i++){
            if(indexes[i] >= 34){
                indexes[i] = indexes[i] % 34;
            }
        }
        int idx = 0;
        vector<int> dupl;
        while(true){
            vector<int> v = find_duplikate(indexes);
            if(v.empty() || idx >= 3){
                dupl = v;
                break;
            }
            vector<int> vecc = prime(v.size());
            for(int i = 0; i < v.size(); i++) {
                v[i] += vecc[i];
                v[i] *= v[i];
                v[i] = v[i] % 34;
                indexes.push_back(v[i]);

            }
            idx++;
        }
        if(dupl.size() != 0){
            for(int i = 0; i < dupl.size(); i++){
                sort(indexes.begin(), indexes.end());
                for(int j = 0; j < indexes.size(); j++){
                    if(indexes[j] != j){
                        indexes.push_back(j);
                        break;
                    }
                }
            }
        }
        return indexes;
    }
    vector<int> perf_right(){
        vector<int> indexes;
        string key = "";
        int len = 0;
        int id = 0;
        while(true){
            if(key_val >= 3037000499){
                key = key + to_string(key_val);
                len = key.size();
                key_val = key_val / array1[id];
                if(key_val > 30370004){
                    key_val = key_val / 1902838;
                }
                id++;
            }
            if(len > length){
                key = key.substr(0, n);
                break;
            }
            key_val *= key_val;
        }
        string value = key;
        int l = value.size();
        if(l % 2 == 0){
            value = std::string(value.begin(), value.end() - 1);
        }
        bool flag = true;
        while(true){
            int current_len = value.size();
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
        for(int i = 0; i < value.size(); i++){
            indexes.push_back(std::stoi(std::string(1, value[i])));
        }
        return indexes;
    }

};
