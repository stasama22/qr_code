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
      vector<int> vec = enc->perform_key();
      vector<int> val = enc->perf_right();
      for(int i = 0; i < 34; i++){
        if (std::find(vec.begin(), vec.end(), target) != vec.end()){
          vect[index] = val[i] ^ num_vec[i];
        } else{
          vect[index] = enc->random_value(0, 9);
        }
      }
    }
    vector<int> get_vect(){
      return vect;
    }
};

std::string toBinary(int n) {
  if (n == 0) return "0";
  std::string r = "";
  while (n != 0) {
      r += (n % 2 == 0 ? "0" : "1");
      n /= 2;
  }
  std::reverse(r.begin(), r.end());
}

int main(){
  int num = 0;
  std::cin >> num;
  int random_word = 0;
  std::cin >> random_word;
  QR_build qr_build(num, random_word);
  qr_build->Perfom_full_desision();
  vector<int> vec = qr_build.get_vect();
  string val = to_string(num);
  if(val.length() == 2){
    vec.insert(vec.begin(), stoi(val[1]));
    vec.insert(vec.begin(), stoi(val[0]));
  } else{
    vec.insert(vec.begin(), stoi(val[0]));
    vec.insert(vec.begin(), 0);
  }
  std::vector<std::vector<int>> matrix(12, std::vector<int>(12));
  int idx1 = 0;
  int idx2 = 0;
  int idx3 = 0;
  int idx4 = 0;
  for(int i = 0; i < vec.size(); i++){
    if(idx1 == 6 || inx2 == 6){
      if(idx1 == 6){
        idx1 = 0;
        idx3 = 0;
      } else{
        idx2 = 0;
        idx4 = 0;
      }
      break;
    }
    vall = to_Binary(vec[i]);
    matrix[idx3][idx4] = vall[0];
    matrix[idx3][idx4 + 1] = vall[1];
    matrix[idx3 + 1][idx4] = vall[2];
    matrix[idx3][idx4 + 1] = vall[3];
    idx1++;
    idx3 += 2;
    idx4 += 2;
    idx2++;
  }
  std::ofstream outFile("result.pbm");

  if (outFile.is_open()) {
      outFile << "P1\n";
      outFile << "12 12\n";

      for (int i = 0; i < 12; ++i) {
          for (int j = 0; j < 12; ++j) {
              outFile << !matrix[i][j] << " ";
          }
          outFile << "\n";
      }

      outFile.close();
      std::cout << "Файл result.pbm успешно сохранен!" << std::endl;
  } else {
      std::cerr << "Не удалось открыть файл для записи." << std::endl;
  }

  return 0;
  

}