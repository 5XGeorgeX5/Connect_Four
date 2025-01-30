#include "../ConnectFour.hpp"

// Set player symbol and name as Random Computer Player
RandomPlayer::RandomPlayer(bool isFirst) : Player(isFirst), generator(rd()), distribution(0, 6)
{
    this->name = "Random Computer Player";
    std::cout << "My names is " << name << '\n';
}

// Generate a random move
int RandomPlayer::get_move()
{
    return distribution(generator);
}