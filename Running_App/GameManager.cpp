#include "ConnectFour.hpp"

GameManager::GameManager(ConnectFourBoard *board, Player *playerPtr[2])
{
    this->board = board;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run()
{
    board->display_board();
    bool turn = false;

    while (!board->game_is_over())
    {
        int move = players[turn]->get_move();
        while (!board->update_board(move))
        {
            move = players[turn]->get_move();
        }
        board->display_board();
        if (board->is_winner())
        {
            std::cout << players[turn]->get_name() << " wins\n";
            return;
        }
        if (board->is_draw())
        {
            std::cout << "Draw!\n";
            return;
        }
        turn = !turn;
    }
}
