#include <iostream>

class State
{
public:
    virtual void getCandy() = 0;
    virtual void returnCoin() = 0;
    virtual void putCoin() = 0;
};

class NoCoinState : public State
{
public:
    virtual void getCandy() override
    {
        std::cout << "请先投币\n";
    }
    virtual void returnCoin() override
    {
        std::cout << "你并没有投币\n";
    }
    virtual void putCoin() override
    {
        std::cout << "投币成功\n";
    }
};

class HaveCoinState : public State
{
public:
    virtual void getCandy() override
    {
        std::cout << "糖果投放中....\n";
    }
    virtual void returnCoin() override
    {
        std::cout << "硬币退回中....\n";
    }
    virtual void putCoin() override
    {
        std::cout << "重复投币....\n";
    }
};

class CandyMachine
{
private:
    State *m_currentState;
    State *m_haveCoinState;
    State *m_noCoinState;

public:
    CandyMachine()
    {
        m_haveCoinState = new HaveCoinState();
        m_noCoinState = new NoCoinState();
        m_currentState = m_noCoinState;
        std::cout << "糖果机:当前状态为--->" << typeid(*m_currentState).name() << std::endl; // 这个输出有点不对
    }
    ~CandyMachine()
    {
        delete m_haveCoinState;
        delete m_noCoinState;
    }
    void putCoin()
    {
        std::cout << "糖果机:putCoin" << std::endl;
        m_currentState->putCoin();
        transitionTo(m_haveCoinState);
    }
    void getCandy()
    {
        std::cout << "糖果机:getCandy" << std::endl;
        m_currentState->getCandy();
        transitionTo(m_noCoinState);
    }
    void returnCoin()
    {
        std::cout << "糖果机:returnCoin" << std::endl;
        m_currentState->returnCoin();
        transitionTo(m_noCoinState);
    }

private:
    void transitionTo(State *state)
    {
        m_currentState = state;
        std::cout << "糖果机:当前状态为--->" << typeid(*m_currentState).name() << std::endl;
    }
};

int main()
{
    CandyMachine *candyMachine = new CandyMachine();
    candyMachine->getCandy();
    candyMachine->returnCoin();
    candyMachine->putCoin();
    candyMachine->getCandy();
    candyMachine->returnCoin();
    candyMachine->putCoin();
    delete candyMachine;
    return 0;
}