#include <iostream>

#pragma once

class BoolVector{
    uint8_t* b = nullptr;
    std::size_t num_bit = 0;
    std::size_t num_part = 0;
public:
    explicit BoolVector(size_t len = 1);
    explicit BoolVector(const char*);
    BoolVector(BoolVector& );
    ~BoolVector();

   void Set_1(size_t);    // устанавливает указанный бит в 1
   void Set_0(size_t);    // устанавливает указанный бит в 0
   int operator[] (int);
   BoolVector& operator= (const BoolVector&);
   BoolVector operator| (BoolVector& );
   BoolVector operator~ ();
   /*BoolVector operator& ();

    // Дополнительно
    int weight();    //вес вектора
    BoolVector operator << (int);    //сдвиг на k бит влево
    BoolVector operator >> (int);     //сдвиг на k бит вправо*/
    friend std::ostream& operator << (std::ostream&, BoolVector&);
    friend std::istream& operator >> (std::istream&, BoolVector&);
};

/*
// Класс булева матрица
class BoolM
{ BoolVector *v;
    int m, n; // m – количество строк, n – количество столбцов
public:
    BoolM(int k, int l);    // формируется нулевая булева матрица размера kl
    BoolM(BoolM&);

    BoolVector & operator[] (int);
    BoolM operator= (BoolM& );
    friend std::ostream& operator << (std::ostream&, BoolM&);
    // Дополнительно
    void diagonal0();    // обнулить главную диагональ
    int *matrix_max();   // найти количество единиц в каждом столбце матрицы
};
*/