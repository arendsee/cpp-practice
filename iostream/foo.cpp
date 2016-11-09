#include "foo.h"

Foo::Foo(std::string name, int age, char sign) :
    name(name),
    age(age),
    sign(sign)
{ }

Foo::Foo() { }

Foo::~Foo() { }

std::istream& operator>>(std::istream& is, Foo& obj)
{
    std::string name;
    int age;
    char sign;
    if( is >> name >> age >> sign ){
        obj.name = name;
        obj.age  = age;
        obj.sign = sign;
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Foo& obj)
{
    os << obj.name << "\t" << obj.age << "\t" << obj.sign << "\n";
    return os;
}
