#pragma once
#include "ICommand.h"
#include <exception>

class Command3 : public ICommand
{
public:
    void Execute() override
    {
        std::cout << "Execute Command 3" << std::endl;
        throw std::bad_exception();
    }
};