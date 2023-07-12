#pragma once
#include "ICommand.h"
#include <exception>

class Command2 : public ICommand
{
public:
	void Execute() override
	{
		std::cout << "Execute Command 2" << std::endl;
		throw std::bad_alloc();
	}
};