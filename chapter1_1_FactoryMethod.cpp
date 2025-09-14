#include <iostream>

class Transport
{
public:
    virtual ~Transport() {};
    virtual void deliver() const = 0;
};

class Truck : public Transport
{
public:
    void deliver() const override
    {
        std::cout << "卡车正在运输中" << std::endl;
    }
};

class Ship : public Transport
{
public:
    void deliver() const override
    {
        std::cout << "轮船正在运输中" << std::endl;
    }
};

class Logistic
{
public:
    virtual ~Logistic() {}
    virtual Transport *factoryMethod() const = 0; // 虚拟构造器
    void dosomething() const
    {
        // Truck *truck = new Truck();
        // truck->deliver();
        // delete truck;
        Transport *transport = factoryMethod();
        transport->deliver();
        delete transport;
    }
};

class TruckLogistic : public Logistic
{
public:
    virtual ~TruckLogistic() {};
    virtual Transport *factoryMethod() const override
    {
        return new Truck();
    }
};

class ShipLogistic : public Logistic
{
public:
    virtual ~ShipLogistic() {};
    virtual Transport *factoryMethod() const override
    {
        return new Ship();
    }
};

int main()
{
    // Logistic *logistic = new Logistic();
    // logistic->dosomething();
    TruckLogistic *truckLogistic = new TruckLogistic();
    truckLogistic->dosomething();
    ShipLogistic *shipLogistic = new ShipLogistic();
    shipLogistic->dosomething();

    delete truckLogistic;
    delete shipLogistic;

    return 0;
}