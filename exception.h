/*
Z. Roth
exception.h

This contains an exception class that acts as a simple way to throw exceptions
within the classes overload operators.
*/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

class new_exception: public exception
{
    virtual const char* what() const throw()
    {
        return "Error! Missing or incorrect data!";
    }
} new_throw;

#endif