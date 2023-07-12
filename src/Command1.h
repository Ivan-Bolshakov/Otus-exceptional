#pragma once
#include "ICommand.h"
#include <iostream>

class Command1 : public ICommand
{
public:
	void Execute() override
	{
		std::cout << "Execute Command 1" << std::endl;
		throw std::exception();
	}
};