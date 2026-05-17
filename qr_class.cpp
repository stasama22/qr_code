#include <iostream>
#include <random>
#include <memory>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "encode.cpp"

using namespace std;

class QR_build{
  private:
    int64_t num;
    vector<int> num_vec;
    int64_t random_val;
    vector<int> vect;
    std::unique_ptr<Encode> enc;
  public:
    QR_build(int64_t num, int64_t random_val) : num(num), random_val(random_val), vect(34) {
      enc = std::make_unique<Encode>(num, random_val);
      int64_t copy_num = num;
      while(copy_num > 0){
        num_vec.push_back(copy_num % 10);
        copy_num = copy_num / 10; 
      }
    };
    void Perfom_full_desision(){
      int index = 0;
      int index1 = 0;
      vector<int> vec = enc->perform_key();
      vector<int> val = enc->perf_right();
      for(int i = 0; i < 34; i++){
        if (std::find(vec.begin(), vec.end(), i) == vec.end()){
          vect[i] = val[index] ^ num_vec[index1];
          index++;
          index1++;
        } else{
          vect[i] = enc->random_value(0, 9);
        }
      }
    }
    vector<int> get_vect(){
      return vect;
    }
};

void saveToBMP(const std::string& filename, const std::vector<std::vector<int>>& matrix, int scale) {
    int src_size = 12;
    int out_size = src_size * scale;

    std::ofstream f(filename, std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "Не удалось создать BMP файл!" << std::endl;
        return;
    }

    int row_size = out_size * 3;
    int padding = (4 - (row_size % 4)) % 4;
    int file_size = 54 + (row_size + padding) * out_size;

    unsigned char header[54] = {0};
    header[0] = 'B'; header[1] = 'M'; 
    header[2] = file_size;       header[3] = file_size >> 8;   header[4] = file_size >> 16;   header[5] = file_size >> 24;
    header[10] = 54;                  
    header[14] = 40;                  
    header[18] = out_size;       header[19] = out_size >> 8;   header[20] = out_size >> 16;   header[21] = out_size >> 24;
    
    int32_t neg_height = -out_size;
    header[22] = neg_height;     header[23] = neg_height >> 8; header[24] = neg_height >> 16; header[25] = neg_height >> 24;
    header[26] = 1;                   
    header[28] = 24;                  

    f.write(reinterpret_cast<char*>(header), 54);

    for (int i = 0; i < src_size; ++i) {
        for (int r = 0; r < scale; ++r) {
            for (int j = 0; j < src_size; ++j) {
                unsigned char color = (matrix[i][j] == 1) ? 255 : 0;
                
                for (int c = 0; c < scale; ++c) {
                    f.put(color);
                    f.put(color);
                    f.put(color);
                }
            }
            for (int p = 0; p < padding; ++p) f.put(0);
        }
    }

    f.close();
    std::cout << "\nКартинка " << filename << " успешно сохранена!" << std::endl;
}

int main(){
  int64_t num = 0;
  std::cin >> num;
  int64_t random_word = 0;
  std::cin >> random_word;
  QR_build qr_build(num, random_word);
  qr_build.Perfom_full_desision();
  vector<int> vec = qr_build.get_vect();
  
  string val = to_string(num);
  string len = to_string(val.length());
  if(val.size() > 9){
    vec.insert(vec.begin(), stoi(std::string(1, len[1])));
    vec.insert(vec.begin(), stoi(std::string(1, len[0])));
  } else{
    vec.insert(vec.begin(), stoi(std::string(1, len[0])));
    vec.insert(vec.begin(), 0);
  }
  for(int i = 0; i < vec.size(); i++){
    std::cout << vec[i] << ' ';
  }
  std::vector<int> flat_vector;
  flat_vector.reserve(144);

  for (int i = 0; i < 36; ++i) {
      for (int bit = 3; bit >= 0; --bit) {
          flat_vector.push_back((vec[i] >> bit) & 1);
      }
  }

  std::vector<std::vector<int>> matrix(12, std::vector<int>(12));

  for (int b = 0; b < 36; ++b) {
      int block_row = b / 6;
      int block_col = b % 6;

      int r = block_row * 2;
      int c = block_col * 2;

      int idx = b * 4;

      matrix[r][c] = flat_vector[idx];
      matrix[r][c+1] = flat_vector[idx+1];
      matrix[r+1][c] = flat_vector[idx+2];
      matrix[r+1][c+1] = flat_vector[idx+3];
  }

  saveToBMP("qr_code.bmp", matrix, 20);
  return 0;
  

}
