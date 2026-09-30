#include "pch.h"
#include "Position.h"



TEST(PositionTest, ValidCoordinates) {
    Position p1(5, 3);
    EXPECT_EQ(p1.get_row(), 5);
    EXPECT_EQ(p1.get_col(), 3);
    EXPECT_EQ(p1.get_char_col(), 'C');

    Position p2(7, 'F');
    EXPECT_EQ(p2.get_row(), 7);
    EXPECT_EQ(p2.get_col(), 6);

    Position p3("4 D");
    EXPECT_EQ(p3.get_row(), 4);
    EXPECT_EQ(p3.get_col(), 4);
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

    p.set_row(1);
    EXPECT_EQ(p.get_row(), 1);

    p.set_col(10);
    EXPECT_EQ(p.get_col(), 10);

    p.set_col('E');
    EXPECT_EQ(p.get_col(), 5);

    EXPECT_THROW(p.set_row(15), std::logic_error);
    EXPECT_THROW(p.set_col(0), std::logic_error);
    EXPECT_THROW(p.set_col('X'), std::logic_error);
}




