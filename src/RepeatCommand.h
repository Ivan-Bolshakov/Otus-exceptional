#pragma once
#include "ICommand.h"
#include <memory>
#include "RepeatCommandException.h"

template <typename T>
class RepeatCommand : public ICommand
{
public:
	RepeatCommand(size_t repeatAttempt, std::shared_ptr<ICommand> cmd)
		: repeat_attempt_(repeatAttempt),
		  cmd_(cmd)
	{
	}

	void Execute() override
	{
		for (size_t i = 0; i < repeat_attempt_; i++)
		{
			try
			{
				cmd_->Execute();
			}
			catch (const std::exception &ex)
			{
				if (i == (repeat_attempt_ - 1))
					throw(RepeatCommandException<T>());
			}
		}
	}

private:
	size_t repeat_attempt_;
	std::shared_ptr<ICommand> cmd_;
};