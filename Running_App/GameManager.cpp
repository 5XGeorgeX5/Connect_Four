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

    while (!board->game_is_over())
    {
        for (int i : {0, 1})
        {
            int move = players[i]->get_move();
            while (!board->update_board(move))
            {
                move = players[i]->get_move();
            }
            board->display_board();
            if (board->is_winner())
            {
                std::cout << players[i]->get_name() << " wins\n";
                return;
            }
            if (board->is_draw())
            {
                std::cout << "Draw!\n";
                return;
            }
        }
    }
}
