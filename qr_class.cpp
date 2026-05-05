#include <iostream>
#include <random>
#include <ctime>
#include "encode.cpp"
class QR_build{
  private:
    int num;
    int randpm_val;
  public:
    QR_build(int num, int random_num) : num(num), random_num(random_num) {};

};

int main(){
    int num = 0;
    std::cin >> num >> '\n';
    int random_word = 0;
    std::cin >> random_word >> '\n';
    QR_build qr_build(num, random_word);
    qr_build._print();
}