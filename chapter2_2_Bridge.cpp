#include <iostream>
#include <string>

// 实现
class Device
{
public:
    virtual ~Device() {}
    virtual std::string turnOn() const = 0;
    virtual std::string turnOff() const = 0;
    virtual std::string mute() const = 0;
};

class TV : public Device
{
public:
    ~TV() {}
    std::string turnOn() const override
    {
        return "TV:开机...";
    }
    std::string turnOff() const override
    {
        return "TV:关机...";
    }
    std::string mute() const override
    {
        return "TV:静音...";
    }
};

class Radio : public Device
{
public:
    ~Radio() {}
    std::string turnOn() const override
    {
        return "Radio:开机...";
    }
    std::string turnOff() const override
    {
        return "Radio:关机...";
    }
    std::string mute() const override
    {
        return "Radio:静音...";
    }
};

// 抽象
class BaseRemoteController
{
protected:
    Device *m_implementation;

public:
    ~BaseRemoteController() {}
    BaseRemoteController(Device *implemention)
        : m_implementation(implemention)
    {
    }

public:
    virtual std::string sendTurnOn()
    {
        return "基础遥控器发出TurnOn: " + m_implementation->turnOn();
    }
    virtual std::string sendTurnOff()
    {
        return "基础遥控器发出TurnOff: " + m_implementation->turnOff();
    }
};
class AdvancedRemoteController : public BaseRemoteController
{
public:
    ~AdvancedRemoteController() {}
    AdvancedRemoteController(Device *implemention)
        : BaseRemoteController(implemention)
    {
    }

public:
    virtual std::string sendTurnOn()
    {
        return "高级遥控器发出TurnOn: " + m_implementation->turnOn();
    }
    virtual std::string sendTurnOff()
    {
        return "高级遥控器发出TurnOff: " + m_implementation->turnOff();
    }
    virtual std::string sendMute()
    {
        return "高级遥控器发出Mute: " + m_implementation->mute();
    }
};

int main()
{
    Radio radio;
    BaseRemoteController baseRC(&radio);
    std::cout << baseRC.sendTurnOn() << std::endl;
    std::cout << baseRC.sendTurnOff() << std::endl;

    std::cout << "---------------------------" << std::endl;

    AdvancedRemoteController advanceRC(&radio);
    std::cout << advanceRC.sendTurnOn() << std::endl;
    std::cout << advanceRC.sendMute() << std::endl;
    std::cout << advanceRC.sendTurnOff() << std::endl;
    return 0;
}
