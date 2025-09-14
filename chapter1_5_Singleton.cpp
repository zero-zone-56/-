#include <iostream>
#include <thread>
#include <mutex>

class Singleton
{
private:
    std::string m_value;
    Singleton(const std::string value) : m_value(value) {}
    ~Singleton() {}

public:
    Singleton(Singleton &other) = delete;
    Singleton(const Singleton &other) = delete;
    void operator=(const Singleton &) = delete;

    static Singleton *getInstance(const std::string &value);

    std::string value() const
    {
        return m_value;
    }

private:
    static Singleton *m_instance;
    static std::mutex m_mutex;
};
// 静态的代码在外部定义
std::mutex Singleton::m_mutex;
Singleton *Singleton::m_instance = nullptr;
Singleton *Singleton::getInstance(const std::string &value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_instance == nullptr)
    {
        m_instance = new Singleton(value);
    }
    return m_instance;
    // 下面是另一种方法
    //  static Singleton *instance = new Singleton(value);
    //  return instance;
}

void Cat()
{
    Singleton *singleton = Singleton::getInstance("Cat");
    std::cout << singleton->value() << std::endl;
}

void Dog()
{
    Singleton *singleton = Singleton::getInstance("Dog");
    std::cout << singleton->value() << std::endl;
}

int main()
{
    std::thread t1(Cat);
    std::thread t2(Dog);

    t1.join();
    t2.join();

    return 0;
}