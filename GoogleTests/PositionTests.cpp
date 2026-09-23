#include "pch.h"
#include "Position.h"
#include "Ship.h"


TEST(PositionTest, ValidCoordinates) {
    Position p1(5, 3);
    EXPECT_EQ(p1.row(), 5);
    EXPECT_EQ(p1.col(), 3);
    EXPECT_EQ(p1.char_col(), 'C');

    Position p2(7, 'F');
    EXPECT_EQ(p2.row(), 7);
    EXPECT_EQ(p2.col(), 6);

    Position p3("4 D");
    EXPECT_EQ(p3.row(), 4);
    EXPECT_EQ(p3.col(), 4);
}

TEST(PositionTest, InvalidCoordinates) {
    EXPECT_THROW(Position(0, 5), std::logic_error);
    EXPECT_THROW(Position(11, 5), std::logic_error);
    EXPECT_THROW(Position(5, 0), std::logic_error);
    EXPECT_THROW(Position(5, 11), std::logic_error);
    EXPECT_THROW(Position(5, 'Z'), std::logic_error);
}

TEST(PositionTest, InvalidStrings) {
    EXPECT_THROW(Position("11 A"), std::logic_error);
    EXPECT_THROW(Position("5 Z"), std::logic_error);
    EXPECT_THROW(Position("abc"), std::logic_error);
}

TEST(PositionTest, SettersAndGetters) {
    Position p(5, 5);

    p.row(1);
    EXPECT_EQ(p.row(), 1);

    p.col(10);
    EXPECT_EQ(p.col(), 10);

    p.col('E');
    EXPECT_EQ(p.col(), 5);

    EXPECT_THROW(p.row(15), std::logic_error);
    EXPECT_THROW(p.col(0), std::logic_error);
    EXPECT_THROW(p.col('X'), std::logic_error);
}



#include "pch.h"
#include "Ship.h"
TEST(ShipTest, ValidConstructor) {
    Position pos(1, 1);
    Ship ship(3, pos, Horizontal);

    EXPECT_EQ(ship.size(), 3);
    EXPECT_EQ(ship.row(), 1);
    EXPECT_EQ(ship.col(), 1);
    EXPECT_EQ(ship.direction(), Horizontal);
}

TEST(ShipTest, InvalidConstructorSize) {
    Position pos(1, 1);
    EXPECT_THROW(Ship(0, pos, Horizontal), std::logic_error);
    EXPECT_THROW(Ship(5, pos, Horizontal), std::logic_error);
}

TEST(ShipTest, InvalidConstructorOutOfBounds) {
    Position pos1(1, 10);
    EXPECT_THROW(Ship(2, pos1, Horizontal), std::logic_error);

    Position pos2(9, 1);
    EXPECT_THROW(Ship(3, pos2, Vertical), std::logic_error);
}

TEST(ShipTest, CharConstructorValid) {
    Ship ship(4, 'V', 2, 'C');
    EXPECT_EQ(ship.size(), 4);
    EXPECT_EQ(ship.row(), 2);
    EXPECT_EQ(ship.col(), 3);
    EXPECT_EQ(ship.direction(), Vertical);
}

TEST(ShipTest, StringConstructorValid) {
    Ship ship("3 H 4 B");
    EXPECT_EQ(ship.size(), 3);
    EXPECT_EQ(ship.row(), 4);
    EXPECT_EQ(ship.col(), 2);
    EXPECT_EQ(ship.direction(), Horizontal);
}

TEST(ShipTest, StringConstructorInvalid) {
    EXPECT_THROW(Ship("5 H 1 A"), std::logic_error);
    EXPECT_THROW(Ship("3 X 1 A"), std::logic_error);
    EXPECT_THROW(Ship("4 H 2 J"), std::logic_error);
    EXPECT_THROW(Ship("4 V 9 A"), std::logic_error);
}

TEST(ShipTest, SettersValid) {
    Position pos(1, 1);
    Ship ship(2, pos, Horizontal);

    ship.size(3);
    EXPECT_EQ(ship.size(), 3);

    ship.row(5);
    EXPECT_EQ(ship.row(), 5);

    ship.col(4);
    EXPECT_EQ(ship.col(), 4);

    ship.direction(Vertical);
    EXPECT_EQ(ship.direction(), Vertical);
}

TEST(ShipTest, SettersInvalid) {
    Position pos(1, 1);
    Ship ship(4, pos, Horizontal);

    EXPECT_THROW(ship.size(5), std::logic_error);
    EXPECT_THROW(ship.col(8), std::logic_error);

    Ship ship_bottom(4, Position(9, 1), Horizontal);
    EXPECT_THROW(ship_bottom.direction(Vertical), std::logic_error);
}