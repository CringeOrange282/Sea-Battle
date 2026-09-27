#include "pch.h"
#include "Ship.h"
#include "GameField.h"
#include "Player.h"


TEST(PlayerTest, InitialState) {
    Player player;
    EXPECT_FALSE(player.check_ready());
}

TEST(PlayerTest, SetShipValidAndLimits) {
    Player player;

    Ship boat1(1, Position(1, 1), Horizontal);
    Ship boat2(1, Position(1, 3), Horizontal);
    Ship boat3(1, Position(1, 5), Horizontal);
    Ship boat4(1, Position(1, 7), Horizontal);

    player.set_ship(boat1);
    player.set_ship(boat2);
    player.set_ship(boat3);
    player.set_ship(boat4);

    Ship extra_boat(1, Position(1, 9), Horizontal);
    EXPECT_THROW(player.set_ship(extra_boat), std::logic_error);
}

TEST(PlayerTest, CheckReadyWhenAllShipsPlaced) {
    Player player;

    player.set_ship(Ship(4, Position(1, 1), Horizontal));

    player.set_ship(Ship(3, Position(3, 1), Horizontal));
    player.set_ship(Ship(3, Position(5, 1), Horizontal));

    player.set_ship(Ship(2, Position(7, 1), Horizontal));
    player.set_ship(Ship(2, 'H', 9, 'A'));
    player.set_ship(Ship(2, Position(9, 5), Horizontal));

    player.set_ship(Ship(1, Position(1, 7), Horizontal));
    player.set_ship(Ship(1, Position(3, 7), Horizontal));
    player.set_ship(Ship(1, Position(5, 7), Horizontal));
    player.set_ship(Ship(1, Position(7, 7), Horizontal));

    EXPECT_TRUE(player.check_ready());
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTest, SetActionAndLoseLogic) {
    Player player;

    Ship boat(1, Position(2, 2), Horizontal);
    player.set_ship(boat);

    State res1 = player.set_action(1, 'A');
    EXPECT_EQ(res1, Missed);
    EXPECT_FALSE(player.check_lose());

    State res2 = player.set_action(2, 'B');
    EXPECT_EQ(res2, BoatDestroyed);
    EXPECT_TRUE(player.check_lose());
}
