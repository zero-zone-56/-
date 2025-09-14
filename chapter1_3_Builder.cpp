#include <iostream>
#include <vector>
#include <string>

class SimpleHouse
{
public:
    std::vector<std::string> m_parts;
    void printParts() const
    {
        std::cout << "Simple,包括: " << std::endl;
        for (auto i : m_parts)
            std::cout << i << std::endl;
        std::cout << "-----------------" << std::endl;
    }
    //  virtual ~SimpleHouse();  //不能写析构函数
};

class Builder
{
public:
    virtual ~Builder() {}
    virtual void reset() = 0;
    virtual void makeBaseHouse() = 0;
    virtual void makeGarage() = 0;
    virtual void makePool() = 0;
};

class SimpleHouseBuilder : public Builder
{
private:
    SimpleHouse *m_simpleHouse;

public:
    SimpleHouseBuilder()
    {
        reset();
    }
    virtual void reset() override
    {
        m_simpleHouse = new SimpleHouse();
    }
    virtual ~SimpleHouseBuilder()
    {
        delete m_simpleHouse;
    }
    virtual void makeBaseHouse() override
    {
        m_simpleHouse->m_parts.push_back("BaseHouse");
    }
    virtual void makeGarage() override
    {
        m_simpleHouse->m_parts.push_back("Garage");
    }
    virtual void makePool() override
    {
        m_simpleHouse->m_parts.push_back("Pool");
    }
    SimpleHouse *getResult()
    {
        SimpleHouse *result = m_simpleHouse;
        reset();
        return result;
    }
};

class Director
{
private:
    Builder *m_builder;

public:
    void setBuilder(Builder *builder)
    {
        m_builder = builder;
    }
    void makeSimpleHouse()
    {
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
    }
    void makeFullFuncHouse()
    {
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
        m_builder->makePool();
    }
};

void client(Director *director)
{
    std::cout << "客户自己设计流程: " << std::endl;
    SimpleHouseBuilder *builder = new SimpleHouseBuilder();
    builder->makeBaseHouse();
    builder->makeGarage();
    // builder->getResult(); // 写多了这一行,导致字符串没有写进数组
    SimpleHouse *simpleHouse = builder->getResult();
    simpleHouse->printParts();
    delete simpleHouse;

    std::cout << "主管负责设计流程: " << std::endl;
    director->setBuilder(builder);
    director->makeFullFuncHouse();
    simpleHouse = builder->getResult();
    simpleHouse->printParts();
    delete simpleHouse;
    delete builder;
}
int main()
{
    Director director;
    client(&director);
    return 0;
}
