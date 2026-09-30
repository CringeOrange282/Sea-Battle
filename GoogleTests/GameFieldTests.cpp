#include "pch.h"
#include "Ship.h"
#include "GameField.h"
#include "Player.h"

TEST(GameFieldTest, EmptyFieldOnCreation) {
    GameField gf;
    EXPECT_EQ(gf.get(1, 'A'), ' ');
    EXPECT_EQ(gf.get(10, 'J'), ' ');
}

TEST(GameFieldTest, OutOfBoundsShotThrows) {
    GameField gf;
    EXPECT_THROW(gf.set(0, 'A'), std::logic_error);
    EXPECT_THROW(gf.set(11, 'A'), std::logic_error);
    EXPECT_THROW(gf.set(5, '@'), std::logic_error);
    EXPECT_THROW(gf.set(5, 'K'), std::logic_error);
}

TEST(GameFieldTest, MissedShotLogic) {
    GameField gf;
    State result = gf.set(3, 'C');

    EXPECT_EQ(result, Missed);
    EXPECT_EQ(gf.get(3, 'C'), '.');
}

TEST(GameFieldTest, DuplicateShotThrows) {
    GameField gf;
    gf.set(3, 'C');
    EXPECT_THROW(gf.set(3, 'C'), std::logic_error);
}

TEST(GameFieldTest, PlaceShipAndHitLogic) {
    GameField gf;
    Position pos(2, 'B');
    Ship ship(3, pos, Horizontal);
    gf.set(ship);

    EXPECT_EQ(gf.get(2, 'B'), '*');
    EXPECT_EQ(gf.get(2, 'C'), '*');
    EXPECT_EQ(gf.get(2, 'D'), '*');

    State shot1 = gf.set(2, 'B');
    EXPECT_EQ(shot1, Hit);
    EXPECT_EQ(gf.get(2, 'B'), 'X');

    State shot2 = gf.set(2, 'C');
    EXPECT_EQ(shot2, Hit);

    State shot3 = gf.set(2, 'D');
    EXPECT_EQ(shot3, CruisersDestroyed);
}

TEST(GameFieldTest, CollisionPlacementThrows) {
    GameField gf;

    Ship ship1(3, Position(2, 'B'), Horizontal);
    gf.set(ship1);

    Ship ship_overlap(2, Position(2, 'C'), Vertical);
    EXPECT_THROW(gf.set(ship_overlap), std::logic_error);

    Ship ship_touch(1, Position(3, 'C'), Horizontal);
    EXPECT_THROW(gf.set(ship_touch), std::logic_error);
}

