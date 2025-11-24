#pragma once
#include <functional>
#include "net.h"
#include "stack/stack.h"

typedef const char* Login;
typedef const char* Password;
typedef const char* Address;

struct State
{
	typedef std::function<void(stack::DynamicStack<State>&)> UpdateResult;
	virtual UpdateResult Update() = 0;
	virtual ~State() {}
};


class Connected : public State
{
	int sock;
	stack::StaticStack<Password, Login> stack;
public:
	Connected(stack::StaticStack<int, Password, Login> stack) :
		sock{ stack.top },
		stack{ stack.Pop() } {
			
	}

	UpdateResult Update() override {
		return [](const stack::DynamicStack<State>&){};
	}

	~Connected() { }
};

class Connecting : public State
{
	int sock;
	Address address;
	stack::StaticStack<Password, Login> stack;
public:
	Connecting(stack::StaticStack<Address, Password, Login> stack) :
	address { stack.top },
	stack { stack.Pop() },
	sock{ ::socket() } {
		::connect(sock, stack.top);
	}

	UpdateResult Update() override {
		if (::checkSocketConnected(sock))
			return [stack{stack.Push<int>(sock)}](stack::DynamicStack<State>& stateStack){
				stateStack.Pop();
				stateStack.Push<Connected>(stack);
			};
		else
			return [](const stack::DynamicStack<State>&){};
	}
};




