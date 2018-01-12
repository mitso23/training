#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class Turtle
{
public:
    virtual ~Turtle()
    {
    }

    virtual void PenUp() = 0;

    virtual void PenDown() = 0;

    virtual void Forward(int distance) = 0;

    virtual void Turn(int degrees) = 0;

    virtual void GoTo(int x, int y) = 0;

    virtual int GetX() const = 0;

    virtual int GetY() const = 0;
};

class MockTurtle : public Turtle
{
public:
    MOCK_METHOD0(PenUp, void());
    MOCK_METHOD0(PenDown, void());
    MOCK_METHOD1(Forward, void(int distance));
    MOCK_METHOD1(Turn, void(int degrees));
    MOCK_METHOD2(GoTo, void(int x, int y));
    MOCK_CONST_METHOD0(GetX, int());
    MOCK_CONST_METHOD0(GetY, int());
};

class Painter
{
public:
    Painter(Turtle& turtle) : m_turtle(turtle)
    {

    }

    bool Draw(int x, int y)
    {
        int res = m_turtle.GetX();

        if (res == 100)
        {
            std::cout << "100" << std::endl;
            m_turtle.GoTo(x, y);
        }

        res = m_turtle.GetX();

        if (res == 101)
        {
            std::cout << "101" << std::endl;
            m_turtle.GoTo(x, y);
        }

        return true;
    }

private:
    Turtle& m_turtle;
};

TEST(PainterTest, CanDrawSomething)
{
    MockTurtle turtle;
    Painter paint(turtle);

    EXPECT_CALL(turtle, GetX())
         .Times(2)
         .WillOnce(Return(100))
         .WillOnce(Return(101));

    EXPECT_CALL(turtle, GoTo(_,_))
    .Times(2);

    paint.Draw(1,2);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
