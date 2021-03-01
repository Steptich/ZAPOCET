
#ifndef ZAPOCET_BUGNUMEXCEPTION_H
#define ZAPOCET_BUGNUMEXCEPTION_H

#include<exception>
#include<string>
class BiGgNumException: public std::exception{
    std::string message;
public:
    BiGgNumException(std::string msg) : message(msg){}
    virtual const char*what() const noexcept{return message.c_str();}
};
#endif //ZAPOCET_BUGNUMEXCEPTION_H
