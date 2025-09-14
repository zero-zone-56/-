#include <iostream>

class Chair
{
public:
    virtual ~Chair() {}
    virtual void sitOn() const = 0;
};

class ModernChair : public Chair
{
public:
    virtual ~ModernChair() {}
    virtual void sitOn() const override
    {
        std::cout << "ModernChair坐" << std::endl;
    }
};

class ChineseChair : public Chair
{
public:
    virtual ~ChineseChair() {}
    virtual void sitOn() const override
    {
        std::cout << "ChineseChair坐" << std::endl;
    }
};

class Table
{
public:
    virtual ~Table() {}
    virtual void putOn() const = 0;
};

class ModernTable : public Table
{
public:
    virtual ~ModernTable() {}
    virtual void putOn() const override
    {
        std::cout << "ModernTable放" << std::endl;
    }
};

class ChineseTable : public Table
{
public:
    virtual ~ChineseTable() {}
    virtual void putOn() const override
    {
        std::cout << "ChineseTable放" << std::endl;
    }
};

class FurnitureFactory
{
public:
    virtual ~FurnitureFactory() {}
    virtual Chair *createChair() const = 0;
    virtual Table *createTable() const = 0;
};

class ModernStyleFactory : public FurnitureFactory
{
public:
    virtual Chair *createChair() const override
    {
        return new ModernChair();
    }
    virtual Table *createTable() const override
    {
        return new ModernTable();
    }
};

class ChineseStyleFactory : public FurnitureFactory
{
public:
    virtual Chair *createChair() const override
    {
        return new ChineseChair();
    }
    virtual Table *createTable() const override
    {
        return new ChineseTable();
    }
};

class Client
{
private:
    FurnitureFactory *m_factory;

public:
    // Client(FurnitureFactory *factory) : m_factory(factory) {}
    Client(FurnitureFactory *factory)
    {
        set_factory(factory);
    }
    virtual ~Client() {}
    void buyFurniture()
    {
        // ModernChair *modernChair = new ModernChair();
        // ChineseTable *chineseTable = new ChineseTable();
        Chair *chair = m_factory->createChair();
        Table *table = m_factory->createTable();
        chair->sitOn();
        table->putOn();
        delete chair;
        delete table;
    }
    void set_factory(FurnitureFactory *factory)
    {
        m_factory = factory;
    }
};

int main()
{
    ModernStyleFactory modernFactory;
    Client client(&modernFactory);
    client.buyFurniture();

    ChineseStyleFactory chineseStyleFactory;
    client.set_factory(&chineseStyleFactory);
    client.buyFurniture();

    return 0;
}