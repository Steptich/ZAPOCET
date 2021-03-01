
#include <iostream>
#include "BigNum.h"

using namespace std;

int main() {
    try{ // zkusebni blok
        cout << "Start of try block\n";
        BigNum TRY("845*5645");
    }
    catch(BiGgNumException &e){ //handler vyjimky typu BigNumException
        cout << "BigNumException exception caught: " << e.what() << "\n";
    }

    try{
       BigNum IT;
       IT.load_from_file("BadPath");
    }
    catch(BiGgNumException &e){ //handler vyjimky typu BigNumException
        cout << "BigNumException exception caught: " << e.what() << "\n";
    }
    try{
        BigNum NOW;
        cout << NOW(-1);
    }
    catch(BiGgNumException &e){ //handler vyjimky typu BigNumException
        cout << "BigNumException exception caught: " << e.what() << "\n";
    }
    //zachyti chybu typu bad_alloc
    catch (bad_alloc &ba) {cout << "Memory allocation problem: " << ba.what() << "\n";}

    try {
        BigNum A("-1654651321654"), F("5415648451651");
        BigNum U = A + F;
        U.print();
        std::cout << A;
        BigNum B, C, D;
        B.input();
        C.load_from_file("C:\\WORK\\CLionProjects\\PRC\\ZAPOCET\\C.txt");
        C.print();
        D.input_file();
        D.print();
        if (A != C) {
            std::cout << "A a C nejsou stejne\n";
        } else {
            std::cout << "A a C jsou stejne\n";
        }
        if (A > F) {
            std::cout << "A je vetsi nez F\n";
        } else {
            std::cout << "A je mensi nebo rovno F\n";
        }
        BigNum E;
        E = A + F;
        E.print();
        ++E;
        std::cout << E;
        --E;
        E.print();
        BigNum O = A / F;
        O.print();
    }
    catch(BiGgNumException &e){ //handler vyjimky typu BigNumException
        cout << "BigNumException exception caught: " << e.what() << "\n";
    }
    //zachyti chybu typu bad_alloc
    catch (bad_alloc &ba) {cout << "Memory allocation problem: " << ba.what() << "\n";}
    cout << "End of guarded block\n\n";
    return 0;
}
