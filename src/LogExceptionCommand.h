#pragma once
#include "ICommand.h"
#include <iostream>

template <typename T, typename E>
class LogExceptionCommand : public ICommand
{
public:
	void Execute() override
	{
		std::cout << "LogExceptionCommand " << typeid(T).name() << " : " << E().what() << std::endl;
	}
};