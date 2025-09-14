#include <iostream>
#include <string>

// 接口:具体被包裹的类,以及装饰类
class Beverage
{
public:
    virtual ~Beverage() {}
    virtual std::string Operation() const = 0;
};
// 具体的被装饰者
class Americano : public Beverage
{
public:
    ~Americano() {}
    std::string Operation() const
    {
        return "美式咖啡";
    }
};
// 装饰
// 基础部分(可能包含额外部分)
class Ingredient : public Beverage
{
protected:
    Beverage *m_beverage;

public:
    ~Ingredient() {}
    Ingredient(Beverage *beverage) : m_beverage(beverage) {}
    std::string Operation() const override
    {
        return m_beverage->Operation(); // 核心代码,不是用来被基类覆盖
    }
};
// 额外部分(需要委托基类,完成基础部分)
class Whip : public Ingredient
{
public:
    Whip(Beverage *beverage) : Ingredient(beverage) {}
    ~Whip() {}
    std::string Operation() const override
    {
        // 在基类的operation之前、之后都可以增加额外的操作
        return "奶昔(" + Ingredient::Operation() + ")";
    }
};
class Moka : public Ingredient
{
public:
    Moka(Beverage *beverage) : Ingredient(beverage) {}
    ~Moka() {}
    std::string Operation() const override
    {
        // 在基类的operation之前、之后都可以增加额外的操作
        return "摩卡(" + Ingredient::Operation() + ")";
    }
};

void ClientCode(Beverage *beverage)
{
    std::cout << "执行结果: " << beverage->Operation();
}

int main()
{
    std::cout << "一杯普通的美式咖啡" << std::endl;
    Beverage *americano = new Americano();
    ClientCode(americano);

    std::cout << std::endl
              << std::endl;

    std::cout << "一杯双份摩卡+奶昔的美式咖啡" << std::endl;
    Beverage *whip1 = new Whip(americano); // 我把指针名写成跟对象名是一样的,导致报错
    Beverage *moka1 = new Moka(whip1);
    Beverage *moka2 = new Moka(moka1);
    ClientCode(moka2);

    delete americano;
    delete whip1;
    delete moka1;
    delete moka2;

    return 0;
}