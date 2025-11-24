#include <iostream>
#include "stack/stack.h"
#include "testclasses.h"
#include "states.h"

int main(int argc, char* argv[]) {
    char stateBuffer[4096];
    char contextBuffer[4096];

    auto contextStack = stack::StaticStack<> { contextBuffer }
    .Push<Login>("Nagibator666")
    .Push<Password>("123")
    .Push<Address>("127.0.0.1:1234");

    stack::DynamicStack<State> stateStack{ stateBuffer };
    
    stateStack.Push<Connecting>(contextStack);

    
    try {
        while(true) {
            auto result = stateStack.Top().Update();
            result(stateStack);
        }
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    
    stateStack.Pop();

    return 0;
}