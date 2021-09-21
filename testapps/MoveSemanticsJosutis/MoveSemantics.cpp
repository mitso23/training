#include "PowerOfMoveSemantics.h"
#include "utils/counted.h"
#include <iostream>


void TestConstRef(const Counted<std::string>& v)
{
    std::cout << "Counted<std::string> : " << v << std::endl;
}

void TestValue(Counted<std::string>&& v)
{
    std::cout << "TestValue2 : " << v << std::endl;
}

void TestValue(Counted<std::string> v)
{
    std::cout << "Counted<std::string> : " << v << std::endl;
}

void RvalueRef(Counted<std::string>&& v)
{
    TestValue(v);
}


struct Employee
{
    Employee(std::string name, std::string surname, unsigned transactionId) : m_name(std::move(name)), m_surname(surname), m_transactionId(transactionId)
    {

    }

    Employee(Employee&& rhs)
    {
        rhs.m_name = std::move(m_name);
        rhs.m_surname = std::move(m_surname);

        m_transactionId = 0xFFFFFFFFF;
    }

    ~Employee() = default;

    std::string m_name;
    std::string m_surname;
    uint64_t m_transactionId;
};

int main(int argc, char* argv[])
{
    Employee e1("Dimitrios", "Symonidis", 2);
    Employee e2 = std::move(e1);

    std::cout << "name: " << e1.m_name << " transactionId: " << e1.m_transactionId <<  std::endl;
}

