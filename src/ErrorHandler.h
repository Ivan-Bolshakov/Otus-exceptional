#pragma once
#include "ICommand.h"
#include "LogExceptionCommand.h"

#include <queue>
#include <exception>
#include <memory>
#include <map>

class ErrorHandler
{
	struct ErrorHandlerValueParams
	{
		std::string Exception;
		std::shared_ptr<ICommand> HandlerCmd;
	};

public:
	ErrorHandler(std::queue<std::shared_ptr<ICommand>> *cmds) : cmds_(cmds)
	{
	}

	void Handle(std::shared_ptr<ICommand> cmd, const std::exception &ex)
	{
		std::string exception_name = typeid(ex).name();
		auto result = handlers_.equal_range(typeid(*cmd.get()).name());
		for (auto it = result.first; it != result.second; it++)
		{
			if (exception_name == it->second.Exception)
			{
				cmds_->push(it->second.HandlerCmd);
				break;
			}
		}
	}

	template <typename T, typename E>
	void RegisterHandler(std::shared_ptr<ICommand> cmd)
	{
		ErrorHandlerValueParams p;
		p.Exception = typeid(E).name();
		p.HandlerCmd = cmd;

		handlers_.insert({typeid(T).name(), p});
	}

private:
	std::queue<std::shared_ptr<ICommand>> *cmds_;
	std::multimap<std::string, ErrorHandlerValueParams> handlers_;
};
