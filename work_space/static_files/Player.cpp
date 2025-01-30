#include "../ConnectFour.hpp"

Player::Player(bool isFirst)
{
    this->isFirst = isFirst;
}

// Give player info as a string
std::string Player::to_string()
{
    return "Player: " + name;
}

ConnectFourPlayer::ConnectFourPlayer(bool isFirst) : Player(isFirst)
{
    std::cout << "Welcome player " << (int)(!isFirst) + 1;
    std::cout << "\nPlease enter your name: ";
    std::cin >> name;
}

int ConnectFourPlayer::get_move()
{
    int move;
    std::cout << "Choose the column (0 to 6): ";
    std::cin >> move;
    return move;
}