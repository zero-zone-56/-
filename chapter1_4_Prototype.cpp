#include <iostream>
#include <unordered_map>
using std::string;

enum Type
{
    ROBOT_CAT = 0,
    ROBOT_DOG
};

class Robot
{
protected:
    string m_prototype_name;
    float m_stateOfCharge;

public:
    // Robot() {}  //或者下面的构造函数
    Robot() = default;
    Robot(string name) : m_prototype_name(name) {}
    virtual ~Robot() {}
    virtual Robot *clone() const = 0;
    virtual void setStateOfCharge(float) = 0;
};

class RobotCat : public Robot
{
private:
    float m_CatValue = 0;

public:
    RobotCat(string name, float value) : Robot(name), m_CatValue(value)
    {
    }
    RobotCat(const RobotCat &robot)
    {
        m_CatValue = robot.m_CatValue;
    }
    virtual Robot *clone() const override
    {
        return new RobotCat(*this);
    }
    virtual void setStateOfCharge(float value) override
    {
        m_stateOfCharge = value;
        std::cout << "克隆机器猫" << std::endl;
        std::cout << "--" << m_prototype_name << "当前电量" << m_stateOfCharge << ",m_CatValue:" << m_CatValue << std::endl;
    }
};

class RobotDog : public Robot
{
private:
    float m_DogValue = 0;

public:
    RobotDog(string name, float value) : Robot(name), m_DogValue(value)
    {
    }
    RobotDog(const RobotDog &robot)
    {
        m_DogValue = robot.m_DogValue;
    }
    virtual Robot *clone() const override
    {
        return new RobotDog(*this);
    }
    virtual void setStateOfCharge(float value) override
    {
        m_stateOfCharge = value;
        std::cout << "克隆机器狗" << std::endl;
        std::cout << "--" << m_prototype_name << "当前电量" << m_stateOfCharge << ",m_DogValue:" << m_DogValue << std::endl;
    }
};

class CloneFactory
{
public: // 没写这个public,导致下面clientcode中cloneFactory引用createRobot报错
    std::unordered_map<Type, Robot *> m_prototypes;
    CloneFactory()
    {
        m_prototypes[ROBOT_CAT] = new RobotCat("机器猫", 5.0);
        m_prototypes[ROBOT_DOG] = new RobotDog("机器狗", 8.0);
    }
    ~CloneFactory()
    {
        delete m_prototypes[ROBOT_CAT];
        delete m_prototypes[ROBOT_DOG];
    }
    Robot *createRobot(Type type)
    {
        return m_prototypes[type]->clone();
    }
};

void clientcode(CloneFactory &cloneFactory)
{
    Robot *cloneRobotCat = cloneFactory.createRobot(ROBOT_CAT);
    cloneRobotCat->setStateOfCharge(90);
    delete cloneRobotCat;

    Robot *cloneRobot = cloneFactory.createRobot(ROBOT_CAT);
    cloneRobot->setStateOfCharge(80);
    delete cloneRobot;

    Robot *cloneRobotDog = cloneFactory.createRobot(ROBOT_DOG);
    cloneRobotDog->setStateOfCharge(75);
    delete cloneRobotDog;

    Robot *cloneRobotDog1 = cloneFactory.createRobot(ROBOT_DOG);
    cloneRobotDog1->setStateOfCharge(75);
    delete cloneRobotDog1;
}

int main()
{
    CloneFactory cloneFactory;
    clientcode(cloneFactory);
    return 0;
}