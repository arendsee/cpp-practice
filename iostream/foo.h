#ifndef __FOO_H__
#define __FOO_H__

#include <string>

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

class Foo
{
public:
    std::string name = ".";
    int age          = -99;
    char sign        = '.';

    Foo(std::string name, int age, char sign);
    Foo();
    ~Foo();
};

std::ostream& operator<<(std::ostream& os, const Foo& obj);
std::istream& operator>>(std::istream& is, Foo& obj);

#endif
