#include "testclass.h"

Test::Test()
{
    this->foo = "Cheese from Testclass";
}

/*Test::~Test()
{
    delete this->foo;
}*/

const char* Test::getFoo()
{
    return this->foo;
}