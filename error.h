#ifndef _ERR_H__INCLUDED_
#define _ERR_H__INCLUDED_
#include <iostream>

class Error{
  public:
    Error(){};
    virtual void Print();
    virtual ~Error(){};

};
class Error_FNF: public Error
{
  public:
    Error_FNF(){};
    virtual void Print();
    virtual ~Error_FNF(){};
};
class Error_MA: public Error
{
    public:
    Error_MA(){};
    virtual void Print();
    virtual ~Error_MA(){};
};


void Error::Print()
{
  std::cout<<"Произошла ошибка"<<std::endl;
};

void Error_FNF::Print()
{
  std::cout<<"Файл не найден"<<std::endl;
}; 


void Error_MA::Print()
{
  std::cout<<"Ошибка выделения памяти"<<std::endl;
}; 

#endif
