#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Memento
{
    friend class Hero; // 如果少了这一行,Hero类的restore函数中memento->m_state就会报错

private:
    unsigned int m_state;
    std::string m_date;

public:
    Memento(unsigned int state) : m_state(state)
    {
        std::time_t now = std::time(0);
        m_date = std::ctime(&now);
    }
    std::string getDate()
    {
        return m_date;
    }
};

// Originator
class Hero
{
private:
    unsigned int m_state;

public:
    Hero(unsigned int state) : m_state(state)
    {
        std::cout << "英雄:我的初始状态为" << m_state << std::endl;
    }
    void fight()
    {
        std::cout << "英雄:被砍了一刀\n";
        m_state -= rand() % 20;
        std::cout << "英雄:当前状态变为:" << m_state << std::endl;
    }
    Memento *save()
    {
        return new Memento(m_state);
    }
    void restore(Memento *memento)
    {
        m_state = memento->m_state;
        std::cout << "英雄:当前状态恢复为" << m_state << std::endl;
    }
};

// caretaker
class Caretaker
{
private:
    Hero *m_hero;
    std::vector<Memento *> m_mementos;

public:
    Caretaker(Hero *hero) : m_hero(hero) {}
    ~Caretaker()
    {
        for (auto item : m_mementos)
            delete item;
    }
    void backup()
    {
        std::cout << "管理者:正在保存英雄的状态...\n";
        m_mementos.push_back(m_hero->save());
    }
    void undo()
    {
        if (!m_mementos.size())
            return;
        Memento *memento = m_mementos.back();
        m_mementos.pop_back();
        std::cout << "管理者:英雄状态恢复为" << memento->getDate() << std::endl;
        m_hero->restore(memento);
        delete memento;
    }
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Hero *hero = new Hero(100);
    Caretaker *caretaker = new Caretaker(hero);

    caretaker->backup();
    hero->fight();
    caretaker->backup();
    hero->fight();
    caretaker->undo();

    delete hero;
    delete caretaker;
    return 0;
}