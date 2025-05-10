#include "ConnectFour.hpp"
#define BOARD(i, j) board[(i) * 7 + (j)]

static const char fourInRow[69][4] = {
    {0, 1, 2, 3},
    {0, 7, 14, 21},
    {0, 8, 16, 24},
    {1, 2, 3, 4},
    {1, 8, 15, 22},
    {1, 9, 17, 25},
    {2, 3, 4, 5},
    {2, 9, 16, 23},
    {2, 10, 18, 26},
    {3, 4, 5, 6},
    {3, 10, 17, 24},
    {3, 11, 19, 27},
    {3, 9, 15, 21},
    {4, 11, 18, 25},
    {4, 10, 16, 22},
    {5, 12, 19, 26},
    {5, 11, 17, 23},
    {6, 13, 20, 27},
    {6, 12, 18, 24},
    {7, 8, 9, 10},
    {7, 14, 21, 28},
    {7, 15, 23, 31},
    {8, 9, 10, 11},
    {8, 15, 22, 29},
    {8, 16, 24, 32},
    {9, 10, 11, 12},
    {9, 16, 23, 30},
    {9, 17, 25, 33},
    {10, 11, 12, 13},
    {10, 17, 24, 31},
    {10, 18, 26, 34},
    {10, 16, 22, 28},
    {11, 18, 25, 32},
    {11, 17, 23, 29},
    {12, 19, 26, 33},
    {12, 18, 24, 30},
    {13, 20, 27, 34},
    {13, 19, 25, 31},
    {14, 15, 16, 17},
    {14, 21, 28, 35},
    {14, 22, 30, 38},
    {15, 16, 17, 18},
    {15, 22, 29, 36},
    {15, 23, 31, 39},
    {16, 17, 18, 19},
    {16, 23, 30, 37},
    {16, 24, 32, 40},
    {17, 18, 19, 20},
    {17, 24, 31, 38},
    {17, 25, 33, 41},
    {17, 23, 29, 35},
    {18, 25, 32, 39},
    {18, 24, 30, 36},
    {19, 26, 33, 40},
    {19, 25, 31, 37},
    {20, 27, 34, 41},
    {20, 26, 32, 38},
    {21, 22, 23, 24},
    {22, 23, 24, 25},
    {23, 24, 25, 26},
    {24, 25, 26, 27},
    {28, 29, 30, 31},
    {29, 30, 31, 32},
    {30, 31, 32, 33},
    {31, 32, 33, 34},
    {35, 36, 37, 38},
    {36, 37, 38, 39},
    {37, 38, 39, 40},
    {38, 39, 40, 41},
};

void ConnectFourBoard::display_board()
{
    for (int i = 0; i < 6; i++)
    {
        std::cout << "\n|";
        for (int j = 0; j < 7; j++)
        {
            std::cout << ' ';
            if (BOARD(i, j))
                std::cout << BOARD(i, j) << " |";
            else
                std::cout << "  |";
        }
        std::cout << "\n-----------------------------";
    }
    std::cout << "\n ";
    for (int i = 0; i < 7; i++)
        std::cout << " " << i << "  ";
    std::cout << '\n';
}

bool ConnectFourBoard::is_winner()
{
    if (n_moves < 7)
    {
        return false;
    }

    for (int i = 0; i < 69; i++)
    {
        char current = board[fourInRow[i][0]];
        if (current &&
            current == board[fourInRow[i][1]] &&
            current == board[fourInRow[i][2]] &&
            current == board[fourInRow[i][3]])
        {
            return true;
        }
    }
    return false;
}

bool ConnectFourBoard::is_draw()
{
    return (n_moves == 42 && !is_winner());
}

bool ConnectFourBoard::valid_move(int index)
{
    return (index >= 0 && index < 7 && lowest_row[index] != -1);
}

void ConnectFourBoard::update_board(int index)
{
    int x = lowest_row[index]--;
    BOARD(x, index) = (n_moves % 2) ? 'O' : 'X';
    ++n_moves;
}

bool ConnectFourBoard::game_is_over()
{
    return (n_moves >= 42);
}

void ConnectFourBoard::reset(int index)
{
    int x = ++lowest_row[index];
    BOARD(x, index) = '\0';
    --n_moves;
}

void ConnectFourBoard::resetBoard()
{
    n_moves = 0;
    for (int i = 0; i < 7; i++)
    {
        lowest_row[i] = 5;
    }
    board = std::string(42, '\0');
}

int ConnectFourBoard::heuristic()
{
    int scores[2] = {0};
    for (int i = 0; i < 69; ++i)
    {
        int sum = board[fourInRow[i][0]] + board[fourInRow[i][1]] + board[fourInRow[i][2]] + board[fourInRow[i][3]];
        if (sum % 88 == 0)
        {
            sum /= 88;
            scores[0] += sum * sum * sum;
        }
        else if (sum % 79 == 0)
        {
            sum /= 79;
            scores[1] += sum * sum * sum;
        }
    }
    bool player = (n_moves & 1);
    return (scores[player] - scores[!player]);
}

int ConnectFourBoard::moves()
{
    return n_moves;
}

std::string ConnectFourBoard::get_state()
{
    return board;
}