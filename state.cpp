// state.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

class state
{
public:
    virtual void handle() = 0;

protected:
    void changeState(state*) {}
};

class concreteStateA:public state
{
public:
    void handle()
    {
        cout << "concreteStateA" << "\n";
        state* _stateB = new concreteStateA();
        changeState(_stateB);
    }

    void changeState(state* _stateb)
    {
        _stateb->handle();

    }
};

class concreteStateB :public state
{
public:
    void handle()
    {
        cout << "concreteStateB" << "\n";
        state* _stateA = new concreteStateA();
        changeState( _stateA);
    }
    void changeState(state* _statea) 
    {
        _statea->handle();

    }

};

class context
{
public:
    void request()
    {
        _state = new concreteStateB();
        _state->handle();
    }

private:
    state* _state;

};

int main()
{
    context cxt;

    cxt.request();
   
    std::cout << "Hello World!\n";
}
