#include <iostream>
#include <string>
#include <vector>

// Receiver
class Kitchen
{
private:
    Kitchen() {} // 写成了Kitchen(),应该写为 Kitchen 类的私有构造函数添加了空实现 Kitchen() {}

public:
    static Kitchen *getInstance()
    {
        static Kitchen *instance = new Kitchen();
        return instance;
    }

    void prepareFood(const std::string &food)
    {
        std::cout << "厨房:正在准备(" << food << ")\n";
    }
};

//
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

class Order : public Command
{
private:
    Kitchen *m_kitchen;
    std::vector<std::string> m_foods;

public:
    virtual ~Order() {}
    Order(Kitchen *kitchen, std::vector<std::string> food)
        : m_kitchen(kitchen), m_foods(food) {}
    virtual void execute() const override
    {
        std::cout << "订单:需要厨房进行处理...\n";
        for (const std::string &item : m_foods)
        {
            m_kitchen->prepareFood(item);
        }
    }
};

class Waitress
{
private:
    Command *m_command;

public:
    ~Waitress() { delete m_command; }
    void orderUp(Command *command)
    {
        std::cout << "服务员:...提交订单...";
        m_command = command;
        m_command->execute();
    }
};

class Client
{
public:
    void orderFood(Waitress &waitress, std::vector<std::string> foods)
    {
        waitress.orderUp(new Order(Kitchen::getInstance(), foods)); // Kitchen是单例
    }
};

int main()
{
    Client client;
    Waitress waitress;
    client.orderFood(waitress, {"鱼", "虾", "蟹"});

    return 0;
}