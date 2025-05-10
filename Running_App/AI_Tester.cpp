#include <iostream>
#include <chrono>
#include <fstream>
#include "Player.cpp"
#include "ConnectFourBoard.cpp"
#include "AI_Player.cpp"
using namespace std;

void test(ConnectFourBoard *board, Base_AI_Player *players[2])
{
    std::ofstream outFile("log.txt", std::ios::app);
    bool finished = false;

    chrono::milliseconds averages[2] = {0ms, 0ms};
    chrono::milliseconds maxes[2] = {0ms, 0ms};
    chrono::milliseconds mins[2] = {chrono::milliseconds::max(), chrono::milliseconds::max()};
    unsigned long long runs[2] = {0, 0};

    while (!finished)
    {
        for (int i : {0, 1})
        {
            auto start = chrono::high_resolution_clock::now();
            int move = players[i]->get_move();
            while (!board->valid_move(move))
            {
                move = players[i]->get_move();
            }
            board->update_board(move);
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            averages[i] += duration;
            maxes[i] = max(maxes[i], duration);
            mins[i] = min(mins[i], duration);
            runs[i] += players[i]->get_runs();
            if (board->is_winner())
            {
                board->display_board();
                std::cout << "player " << i + 1 << " wins\n";
                outFile << players[i]->get_name() << " wins\n";
                finished = true;
                break;
            }
            if (board->is_draw())
            {
                board->display_board();
                std::cout << "Draw!\n";
                outFile << "Draw!\n";
                finished = true;
                break;
            }
        }
    }
    averages[0] /= (board->moves() + 1) / 2;
    averages[1] /= board->moves() / 2;

    outFile << players[0]->get_name() << ":\n";
    outFile << "Average: " << averages[0].count() << "ms\n";
    outFile << "Max: " << maxes[0].count() << "ms\n";
    outFile << "Min: " << mins[0].count() << "ms\n";
    outFile << "Runs: " << runs[0] << "\n\n";

    outFile << players[1]->get_name() << ":\n";
    outFile << "Average: " << averages[1].count() << "ms\n";
    outFile << "Max: " << maxes[1].count() << "ms\n";
    outFile << "Min: " << mins[1].count() << "ms\n";
    outFile << "Runs: " << runs[1];
    outFile << "\n\n========================\n\n";
    outFile.close();
}

int main()
{
    ConnectFourBoard *board = new ConnectFourBoard();
    Base_AI_Player *players[2];

    players[0] = new AI_Player(board);
    players[1] = new AI_Player(board);
    test(board, players);
    cout << "\n\n\n";

    board = new ConnectFourBoard();
    players[0] = new AI_Player(board);
    players[1] = new AI_Player(board);
    test(board, players);
}