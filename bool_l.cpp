#include <cstring>
#include <algorithm>
#include "bool_l.h"

BoolVector::BoolVector (size_t len) {
    if (len <= 0){
        std::cout << "Error: ..." << '\n';
        exit(1);
    }
    num_bit = (len % 8) - 1;
    num_part = len / 8;
    b = new uint8_t [num_part * 8 + num_bit + 1];
    std::memset(b, 0, num_part * 8 + num_bit);
}
BoolVector::BoolVector(const char* str){
    size_t len = strlen(str);
    if(len == 0){
        std::cout << "The string contains zero characters" << '\n';
        exit(1);
    }

    num_bit = (len % 8) - 1;
    num_part = len / 8;
    b = new uint8_t[num_part*8 + num_bit + 1];

    std::memset(b,0,len);
    size_t index = 0;

    for(size_t part = 0; part < num_part; part++) {
        for (size_t bit = 0; bit < 8; bit++) {
            index = len - 1 - (part * 8 + bit);
            if(str[index] != 0 && str[index] != '1') {
                std::cout << "Error: Bad string" << '\n';
                exit(1);
            }
            b[part] |= ((str[index] - 0) << bit);
        }
    }

    for(size_t bit = 0; bit < num_bit; bit++) {
        index = len - 1 - (num_part * 8 + bit);
        if(str[index] != '0' && str[index] != '1') {
            std::cout << "Error: Bad string" << '\n';
            exit(1);
        }
        b[num_part] = ((str[index] - 0) << bit);

    }
}

BoolVector::BoolVector(BoolVector& c1){
    num_bit = c1.num_bit;
    num_part = c1.num_part;
    b = new uint8_t [num_part * 8 + num_bit + 1];
    std::copy(c1.b, c1.b + num_part * 8 + num_bit, b);
}
BoolVector::~BoolVector(){
    delete[] b;
}

void BoolVector::Set_1(size_t pos){
    if (pos < 0 || pos > num_bit + num_part *8 + 1){
        std::cout << "Error:..." << '\n';
        exit(1);
    }

    int inv_pos = num_part * 8 + num_bit + 1 - pos;
    b[inv_pos / 8] |= (1 << inv_pos % 8);
}
void BoolVector::Set_0(size_t pos){
    if (pos <= 0 || pos > num_bit + num_part * 8+1){
        std::cout << "Error: ..." << '\n';
        exit(1);
    }
    int inv_pos = num_part * 8 + num_bit + 1 - pos;
    b[inv_pos / 8] &= ~(1 << inv_pos % 8);
}
int BoolVector::operator[] (int pos){
    if (pos <= 0 || pos > num_bit + num_part * 8 + 1){
        std::cout << "Error: ..." << '\n';
        exit(1);
    }
    int inv_pos = num_part * 8 + num_bit + 1 - pos;
    if (bool(b[inv_pos / 8] & (1 << inv_pos % 8))){
        return 1;
    }
    else{
        return 0;
    }
}
BoolVector& BoolVector::operator= (const BoolVector& c1){
    if (this == &c1){
        return *this;
    }

    if (b != nullptr){
        delete[] b;
    }

    num_bit = c1.num_bit;
    num_part = c1.num_part;
    b = new uint8_t[num_part + 1];

    for (int i = 0; i <= num_part; i++){
        b[i] = c1.b[i];
    }

    return *this;
}
BoolVector BoolVector::operator| (BoolVector& c1){
    int _bit = 0, _byte = 0;

    bool flag = false;
    if (num_bit + 8 * num_part > c1.num_bit + 8 * c1.num_part) {
        _bit = num_bit;
        _byte = num_part;
        flag = true;
    } else {
        _bit = c1.num_bit;
        _byte = c1.num_part;
    }

    BoolVector temp(_byte * 8 + _bit + 1);

    for (int i = 0; i <= std::min(num_part, c1.num_part); i++) {
        temp.b[i] = b[i] | c1.b[i];
    }

    if (flag) {
        for (int i = c1.num_part + 1; i <= num_part; i++) {
            temp.b[i] = b[i];
        }
    }
    else {
        for (int i = num_part + 1; i <= c1.num_part; i++) {
            temp.b[i] = c1.b[i];
        }
    }

    return temp;
}
BoolVector BoolVector::operator~ (){

    BoolVector temp(num_part * 8 + num_bit + 1);

    for (int i = 0; i < num_part; ++i){
        temp.b[i] = ~b[i];
    }

    for (int i = num_bit; i >= 0; --i){
        if (bool(b[num_part] & (1 << i))){
            temp.b[num_part] &= ~(1<<i);
        }
        else{
            temp.b[num_part] |= (1 << i);
        }
    }
    return temp;
}

std::ostream& operator << (std::ostream& out, BoolVector& c1){
    for (int i = c1.num_bit; i >= 0; i--){
        if (c1.b[c1.num_part] & (1 << i)){
            out << "1";
        }
        else{
            out << "0";
        }
    }

    for (int i = c1.num_part-1; i >=0; i--){
        for (int j = 7; j >=0; j--){
            if (c1.b[i] & (1 << j)){
                out << "1";
            }
            else{
                out << "0";
            }
        }
    }

    return out;
}
std::istream& operator >> (std::istream& in, BoolVector& c1){
    size_t len = 0;
    in >> len;
    c1.num_bit = len%8;
    c1.num_part = len/8;
    delete [] c1.b;

    c1.b = new uint8_t [(c1.num_part)*8 + c1.num_bit];
    for(int i = 0; i < (c1.num_part)*8 + c1.num_bit; ++i){
        in >> c1.b[i];
    }
    return in;
}