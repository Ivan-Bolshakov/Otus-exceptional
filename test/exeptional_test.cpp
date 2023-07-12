#include <gtest/gtest.h>
#include <queue>

#include "ErrorHandler.h"
#include "Command1.h"
#include "Command2.h"
#include "Command3.h"
#include "LogExceptionCommand.h"
#include "RepeatCommand.h"
#include "RepeatCommandException.h"

TEST(TestExeptional, Test)
{
	std::queue<std::shared_ptr<ICommand>> queue;
	std::shared_ptr<ICommand> cmd1 = std::make_shared<Command1>();
	std::shared_ptr<ICommand> cmd2 = std::make_shared<Command2>();
	std::shared_ptr<ICommand> cmd3 = std::make_shared<Command3>();
	
	queue.push(cmd1);
	queue.push(cmd2);
	queue.push(cmd3);
	
	ErrorHandler errorHandler(&queue);
	errorHandler.RegisterHandler<Command1, std::exception>(
		std::make_shared<LogExceptionCommand<Command1, std::exception>>());
	
	errorHandler.RegisterHandler<Command2, std::bad_alloc>(
		std::make_shared<RepeatCommand<Command2>>(1, cmd2));

	errorHandler.RegisterHandler<RepeatCommand<Command2>, RepeatCommandException<Command2>>(
		std::make_shared<LogExceptionCommand<RepeatCommand<Command2>, RepeatCommandException<Command2>>>());
	
	errorHandler.RegisterHandler<Command3, std::bad_exception>(
		std::make_shared<RepeatCommand<Command3>>(2, cmd3));

	errorHandler.RegisterHandler<RepeatCommand<Command3>, RepeatCommandException<Command3>>(
		std::make_shared<LogExceptionCommand<RepeatCommand<Command3>, RepeatCommandException<Command3>>>());
	
	while (!queue.empty())
	{
		std::shared_ptr<ICommand> cmd = queue.front();
		queue.pop();
	
		try
		{
			cmd->Execute();
		}
		catch (const std::exception& ex)
		{
			errorHandler.Handle(cmd, ex);
		}
	}
}