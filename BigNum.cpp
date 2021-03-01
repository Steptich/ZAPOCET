
#include "BigNum.h"
#include <iostream>

void BigNum::copyDateFrom(BigNum &src)  {
    this->size = src.size;
    this->sign = src.sign;
    //resetuj data a jejich velikot
    this->Number = nullptr;
    this->allockMemory(src.size);
    //prepis data
    for (int i = 0; i != this->size; ++i) {
        this->Number[i] = src.Number[i];
        //zkopiruj velikost a hlubokou kopii dat
    }
}

void BigNum::allockMemory(int size) {
    try{
        this->Number = new int[size];
    }
    catch(std::bad_alloc &ba){
        throw BiGgNumException(ba.what());
    }

    this->Number = new int[size]; //vytvor pole cislic o delce cisla

}

void BigNum::load(std::string str) {
    if(!this->check(str))
    {
        throw BiGgNumException ("Cislo je zadane ve spatnem formatu!");
    }

    if(str[0]=='-')
    {   //pokud cislo zacina nulou, tak je zaporne
        this->sign = 0;
        this->size = str.size()-1;
        //cislice jsou vsechny znaky az na minus
        allockMemory(size);

        for (int i = 1; i <= size ; ++i) {
            //treba zacit od prvniho indexu a ne nulteho
            this->Number[i-1] = str[i] - '0';
        }
    }
    else {
        this->sign = 1;
        this->size = str.size(); //zjisti velikost cisla
        allockMemory( size);
        for (int i = 0; i != size; ++i) {
            //uloz podle ASCII rozdilu cislice do prvku pole
            this->Number[i] = str[i] - '0';
        }
    }
    this->zerokill();//odstraneni nul pred cislem
}

BigNum::BigNum(int size) {
    this->sign = 1;;
    this->size = size;
    allockMemory(size);
    for (int i = 0; i < size; ++i) {
        this->Number[i] = 0;
    }
}

BigNum::BigNum(BigNum &other) {
    this->size = other.size;
    this->sign = other.sign;
    Number = new int[size];
    copyDateFrom(other);


}

BigNum::BigNum(BigNum &&other)
:size(other.size),sign(other.sign), Number(other.Number)
{ //prevezmi data a smaz puvodni
    other.Number = nullptr;
}

BigNum::BigNum(std::string str) {
    this->load(str);
}

BigNum::~BigNum() {
    if (size) {//aby se nespustil po move konstrukoru
        delete [] Number;
    }
}

bool BigNum::check(std::string str) {
    for (int i = 1; i < str.size() ; ++i)
    {
        if (!((47 < str[i]) && (str[i] < 58) && ( (str[0] == 45) ||
                                                  ((47 < str[0]) && (str[0] < 58)) ) ))
            return false;
        //vsechny krome nulteho prvku jsou podle ASCII cisla a
        //nulty prvek je - nebo cislo podle ASCII
    }
    return true;

}

void BigNum::input() {
    std::string str;
    std::cout << "\nZadejte cislo, ktere chcete ulozit: ";
    std::cin >> str;
    std::cout << "\n";
    this->load(str);
}

void BigNum::input_file() {
    std::string path;
    std::cout << "\nZadejte cestu k souboru ze ktereho chcete nacist: ";
    std::cin >> path;
    std::cout << "\n";
    load_from_file(path);
}

void BigNum::load_from_file(std::string path) {
    std::fstream fs;
    fs.open(path,std::ios_base::in);
    if(!fs.is_open())
    {
        throw BiGgNumException("Soubor se nepodarilo otevrit");
    }
    std::string str;
    std::getline(fs,str);
    load(str);
}

void BigNum::print() const {
    if (!sign)
    {
        std::cout<< "-";
    } else{
        std::cout<< " ";
    }
    for (int i = 0; i < this->size; ++i) {
        std::cout << Number[i];
    }
    std::cout << "\n";
}

void BigNum::nulify() {
    for (int i = 0; i < this->size; ++i) {
        Number[i]=0;
    }
}

void BigNum::zerokill() {
    //odstran nuly pred zacatkem cisla
    int counter = 0;
    for (int i = 0 ; i < size ; ++i) {
        if (Number[i] != 0){
            //kontrola jestli jsem jiz neprosel vsechny pocatecni nuly
            for (int j = 0; j < size-counter; ++j) {
                Number[j] = Number[j+counter]; //presunuti cisla dopredu
            }
            size -= counter;
            break;//konec procesu
        }
        counter++; //pocitani nul pred cislem
    }
}

BigNum BigNum::absValue() {
    BigNum A = *this;
    A.sign = 1;
    return  A;
}

int &BigNum::operator()(int i){
        if ( i < 0 || i >= size){
            throw BiGgNumException("Index is out of range");
        }
        return this->Number[this->size-1-i];
    }

BigNum &BigNum::operator=(BigNum &rhs) {
    if (this != &rhs)//pokud nemaji stejnou adresu
    {
        this->copyDateFrom(rhs);
        //zkopiruj pravou stranu, ne jenom ukazatel
    }

}

BigNum &BigNum::operator=(BigNum &&rhs) {
    if(this == &rhs){
        return *this; //pokud jiz mam tak rovnou vratim
    }
    this->Number = rhs.Number; //predani dat, ukazuji na to stejne
    this->size   = rhs.size;
    this->sign   = rhs.sign;
    rhs.Number = nullptr; //prava strana jiz nebudee ukazovat jinam

}

bool BigNum::operator==(const BigNum &rhs) {
    if (this==&rhs)
    {
        return true;
        //pokud stejne adresy, tak je to ta sama vec
    }
    if ((this->size != rhs.size) || (this->sign != rhs.sign))
    {
        return false;
        //pokud nemaji stejny pocet cislic, nebo znamenko, ani stejna byt nemohou
    }
    for (int i = 0; i < rhs.size; ++i) {
        if (this->Number[i]!=rhs.Number[i])
        {
            return false;
            //pokud najdu cislici co se lisi tak nejsou stejna
        }
    }

    return true;
}

bool BigNum::operator!=(const BigNum &rhs) {
    return !(*this == rhs); //pouzivam negaci ==
}

bool BigNum::operator <(const BigNum &rhs) {
    if (*this==rhs){
        return false; //kdyz rovna tak rovnou vim ze nejde
    }
    if (this->sign < rhs.sign){
        return true; //pokud nase zapor a druhe klad, tka je jiste mensi
    }
    if (this->sign > rhs.sign) {
        return false;
    }
    //pokud stejna znamenka tak rozhoduje size
    if (this->size < rhs.size)
    {
        if (this->sign)
        {
            //pokud klad a mensi delka tak je mensi
            return true;
        }
        else {
            //pokud zapor ale mensi delka, tak je vetsi
            return false;
        }
    }
    if (this->size > rhs.size)
    {
        if (this->sign)
        {
            //pokud klad a delsi delka tak je vetsi
            return false;
        }
        else {
            //pokud zapor ale delsi delka, tak je mensi
            return true;
        }
    }
    //pokud stejne znamenko i stejne delky, treba postupne porovnat rady
    for (int i = 0; i < size; ++i) {
        if(this->Number[i] < rhs.Number[i]){
            if (this->sign)
            {
                //pokud klad a mensi cislice tak je mensi
                return true;
            }
            else {
                //pokud zapor ale mensi cislice, tal ke vetsi
                return false;
            }

        }
        else if (this->Number[i] > rhs.Number[i]){
            if (this->sign)
            {
                //pokud klad a vetsi cislice tak je vetsi
                return false;
            }
            else {
                //pokud zapor ale vetsi cislice, tak je mensi
                return true;
            }

        }
        //kdyz jsou si rovny cyklus jede dal
    }
    //pokud se projelo cele cislo a vsechny stejne, tak nemuze byt mensi
    return false;
}

bool BigNum::operator >(const BigNum &rhs) {
    return !(*this <= rhs);
}

bool BigNum::operator <=(const BigNum &rhs) {
    return (  (*this == rhs) || (*this < rhs) );
}

bool BigNum::operator >=(const BigNum &rhs) {
    return !(*this < rhs);
}

BigNum BigNum::operator++() {
    BigNum Jednicka ("1");
    *this = *this + Jednicka;
    return *this;
}

BigNum BigNum::operator--() {
    BigNum Jednicka ("1");
    *this = *this - Jednicka;
    return *this;
}

BigNum BigNum::operator-=( BigNum &rhs) {
    *this = *this - rhs;
    return *this;
}

BigNum BigNum::operator+=( BigNum &rhs) {
    *this = *this + rhs;
    return *this;
}

BigNum operator+(BigNum &A, BigNum &B) {

    int size;
    //vytvor nulova cisla a udelej ho o jedna delsi nez delsi cislo
    if (A.GetSize() >= B.GetSize()){
        size = A.GetSize();

    }
    else {
        size = B.GetSize();
    }
    BigNum C(size+1), D(size+1);
    if(A.sign!=B.sign){
        //soucet ruznych znemenek je rozdil a prevladne znamenko vetsiho cisla
        //v abs hodnote
        //chceme aby cislo absolutne vetsi stalo prvni
        if( A.absValue() > B.absValue() )
        {
            for (int i = 0 ; i < A.size ; ++i) {
                C(i) = A(i);
            }
            for (int i = 0 ; i < B.size ; -++i) {
                D(i) = B(i);
            }
            C.sign = A.sign;

        }
        else{
            for (int i = 0 ; i < B.size ; ++i) {
                C(i) = B(i);
            }
            for (int i = 0 ; i < A.size ; -++i) {
                D(i) = A(i);
            }
            C.sign = B.sign;
        }
        int overten = 0; //pokud rozdil prekorcil 10 ovlivni dalsi rad o 1
        for (int i = 0 ; i <= size  ; ++i) {
            //jdu od prvni cislice neboli posledniho prvku pole az do zacatku
            //moje nova cisla maji size+1 takze proto <=size
            if(C(i)-D(i) - overten < 0)
            {
                C(i) = C(i)- D(i) - overten + 10;
                overten = 1;
            }
            else{
                C(i) = C(i) - D(i) - overten;
                overten = 0;
            }
        }
    }
    else{
        //soucet stejnych znamenek nemeni znamenko
        //prekopiruj, jsou nyni stejne size puvodni cisla
        for (int i = 0 ; i < A.size ; ++i) {
            C(i) = A(i);
        }
        for (int i = 0 ; i < B.size ; -++i) {
            D(i) = B(i);
        }
        int overten = 0; //prebytek souctu daneho radu

        for (int i = 0 ; i <= size  ; ++i) {
            //jdu od prvni cislice neboli posledniho prvku pole az do zacatku
            //moje nova cisla maji size+1 takze proto <=size
            if(C(i)+D(i) + overten >= 10)
            {
                C(i) = C(i)+ D(i) + overten - 10;
                overten = 1;
            }
            else{
                C(i) = C(i) + D(i) + overten;
                overten = 0;
            }
        }
    }
    C.zerokill();
    return C;
}

BigNum operator-(BigNum &A, BigNum &B) {
    BigNum C = B;
    C.sign = !C.sign; // pri rozdilu zmen znamenko druhemu a proved soucet
    return A + C;
}

BigNum operator*(BigNum &A, BigNum &B) {
    //nasobeni vlastne rada souctu puvodniha cisla A B-krat
    BigNum C ("0");
    BigNum D = A.absValue(); //nasobim kladna cisla a vysledne znamenko urcim potom
    for (BigNum counter ("0"); counter < B.absValue()   ; ++counter ) {
         C = C + D ;
    }
    if (A.sign != B.sign)
    {
        C.sign = 0; //kdyz  +*-  tak -
    }else{
        C.sign = 1; //kdyz obe stejna, tak vysledek kladny
    }
    return C;
}

BigNum operator/(BigNum &A, BigNum &B) {
    //kolikrat se maximalne  vejde B do A?
    //budu zjistovat kolikratt musim secit B aby to presahlo
    BigNum counter ("0");
    BigNum sum ("0");
    BigNum C = B.absValue();
    while (A>=sum){
        sum += C;
        ++counter;
    }
    --counter; //kompenzace posledniho cyklu
    if (A.sign != B.sign)
    {
        counter.sign = 0; //kdyz  +*-  tak -
    }else{
        counter.sign = 1; //kdyz obe stejna, tak vysledek kladny
    }
    return counter;
}

std::ostream &operator<<(std::ostream &os, BigNum &A) {
    if (!A.sign)
    {
        os << "-";
    } else{
        os << " ";
    }
    for (int i = 0; i < A.size; ++i) {
        os << A.Number[i];
    }
    os << "\n";
    return os;
}









