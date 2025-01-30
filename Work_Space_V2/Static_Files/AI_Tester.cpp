#include <iostream>
#include <chrono>
#include "../ConnectFourBoard.cpp"
#include "../AI_V1/AI_Player.cpp"
#include "RandomPlayer.cpp"
#include "GameManager.cpp"
#include "Player.cpp"
#include <fstream>
using namespace std;

void test(ConnectFourBoard *board, Player *players[2])
{
    std::ofstream outFile("log.txt", std::ios::app);
    bool finished = false;

    chrono::milliseconds averages[2] = {0ms, 0ms};
    chrono::milliseconds maxes[2] = {0ms, 0ms};
    chrono::milliseconds mins[2] = {chrono::milliseconds::max(), chrono::milliseconds::max()};

    while (!finished)
    {
        for (int i : {0, 1})
        {
            auto start = chrono::high_resolution_clock::now();
            int move = players[i]->get_move();
            while (!board->update_board(move))
            {
                move = players[i]->get_move();
            }
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            averages[i] += duration;
            maxes[i] = max(maxes[i], duration);
            mins[i] = min(mins[i], duration);
            if (board->is_winner())
            {
                board->display_board();
                std::cout << "player " << i + 1 << " wins\n";
                finished = true;
                break;
            }
            if (board->is_draw())
            {
                board->display_board();
                std::cout << "Draw!\n";
                finished = true;
                break;
            }
        }
    }
    averages[0] /= (board->moves() + 1) / 2;
    averages[1] /= board->moves() / 2;

    outFile << "Player 1:\n";
    outFile << "Average: " << averages[0].count() << "ms\n";
    outFile << "Max: " << maxes[0].count() << "ms\n";
    outFile << "Min: " << mins[0].count() << "ms\n";

    outFile << "\nPlayer 2:\n";
    outFile << "Average: " << averages[1].count() << "ms\n";
    outFile << "Max: " << maxes[1].count() << "ms\n";
    outFile << "Min: " << mins[1].count() << "ms\n\n\n";
}

int main()
{
    ConnectFourBoard *board = new ConnectFourBoard();
    Player *players[2];

    players[0] = new AI_Player_V1(board);
    players[1] = new AI_Player_V1(board);
    test(board, players);
    cout << "\n\n\n";

    board = new ConnectFourBoard();
    players[0] = new AI_Player_V1(board);
    players[1] = new AI_Player_V1(board);
    test(board, players);
}