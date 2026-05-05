#include <iostream>
#include <random>
#include <ctime>
#include "encode.cpp"
class QR_build{
  private:
    int num;
    vector<int> num_vec;
    int randpm_val;
    vector<int> vect;
    Encode* enc;
  public:
    QR_build(int num, int random_num) : num(num), random_num(random_num) {
      enc = new Encode(num, random_num);
      copy_num = num;
      while(copy_num > 1){
        num_vec.push_back(copy_num % 10);
        copy_num = copy_num / 10; 
      }
    };
    void Perfom_full_desision(){
      int index = 0;
      vector<int> vec = enc.perform_key();
      vector<int> val = enc.perf_right();
      for(int i = 0; i < 34; i++){
        if (std::find(vec.begin(), vec.end(), target) != vec.end()){
          vect[index] = val[i] ^ num_vec[i];
        } else{
          vect[index] = enc.random_value(0, 9);
        }
      }
    }

};

int main(){
    int num = 0;
    std::cin >> num >> '\n';
    int random_word = 0;
    std::cin >> random_word >> '\n';
    QR_build qr_build(num, random_word);
    qr_build._print();
}