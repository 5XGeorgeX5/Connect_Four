#include "ConnectFour.hpp"

// Give player info as a string
std::string Player::get_name()
{
    return name;
}

ConnectFourPlayer::ConnectFourPlayer(bool isFirst)
{
    this->isFirst = isFirst;
    std::cout << "Welcome player " << (int)(!isFirst) + 1;
    std::cout << "\nPlease enter your name: ";
    std::cin >> name;
}

int ConnectFourPlayer::get_move()
{
    int move;
    std::cout << name << "'s turn.\n";
    std::cout << "Choose the column (0 to 6): ";
    std::cin >> move;
    return move;
}

// Set player symbol and name as Random Computer Player
RandomPlayer::RandomPlayer() : generator(rd()), distribution(0, 6)
{
    this->name = "Random Computer Player";
    std::cout << "My names is " << name << '\n';
}

// Generate a random move
int RandomPlayer::get_move()
{
    return distribution(generator);
}

Base_AI_Player::Base_AI_Player(ConnectFourBoard *board) : board(board) {}
