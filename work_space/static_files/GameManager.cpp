#include "../ConnectFour.hpp"

GameManager::GameManager(ConnectFourBoard *bPtr, Player *playerPtr[2])
{
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run()
{
    boardPtr->display_board();

    while (!boardPtr->game_is_over())
    {
        for (int i : {0, 1})
        {
            int move = players[i]->get_move();
            while (!boardPtr->update_board(move))
            {
                move = players[i]->get_move();
            }
            boardPtr->display_board();
            if (boardPtr->is_winner())
            {
                std::cout << players[i]->get_name() << " wins\n";
                return;
            }
            if (boardPtr->is_draw())
            {
                std::cout << "Draw!\n";
                return;
            }
        }
    }
}
