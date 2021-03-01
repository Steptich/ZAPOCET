
#ifndef ZAPOCET_BIGNUM_H
#define ZAPOCET_BIGNUM_H

#include <fstream>
#include <iostream>
#include "BugNumException.h"

class BigNum{
    int size; //delka cisla
    int *Number; //pole cislic
    bool sign; // + je 1 a - je 0
    void copyDateFrom(BigNum &src) ;
    void allockMemory(int size);
    void load(std::string);
public:
    BigNum() : size(0), sign(1), Number(nullptr){}
    BigNum(int size); //konstruktor pro nulove cislo velikosti size
    BigNum(BigNum &other); //kopirovaci konstruktor
    BigNum(BigNum &&other); //move konstruktor
    BigNum(std::string str);
    ~BigNum();
    bool check(std::string str);
    int GetSize() const {return size;}
    void input();
    void input_file();
    void load_from_file(std::string);
    void print() const ;
    void nulify();
    void zerokill();
    BigNum absValue();
    //beru od konce index
    int & operator() (int i);
    BigNum & operator =(BigNum &rhs);
    BigNum & operator =(BigNum &&rhs);
    bool  operator == (const BigNum &rhs);
    bool  operator != (const BigNum &rhs);
    bool  operator <  (const BigNum &rhs);
    bool  operator >  (const BigNum &rhs);
    bool  operator <= (const BigNum &rhs);
    bool  operator >= (const BigNum &rhs);
    BigNum  operator ++ ();
    BigNum  operator -- ();
    BigNum  operator += ( BigNum &rhs);
    BigNum  operator -= ( BigNum &rhs);
    friend BigNum operator + (BigNum &A, BigNum &B);
    friend BigNum operator - (BigNum &A, BigNum &B);
    friend BigNum operator * (BigNum &A, BigNum &B);
    friend BigNum operator / (BigNum &A, BigNum &B);
    friend std::ostream & operator << (std::ostream &os, BigNum &A);
};

#endif //ZAPOCET_BIGNUM_H
