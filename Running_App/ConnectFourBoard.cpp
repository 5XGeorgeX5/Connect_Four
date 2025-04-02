#include "ConnectFour.hpp"
#define BOARD(i, j) board[(i) * 7 + (j)]

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

    int counter = 0;

    // checking the rows winning
    for (int i = 0; i < 6; i++)
    {
        counter = 0;
        for (int j = 0; j < 6; j++)
        {
            if (BOARD(i, j) && BOARD(i, j) == BOARD(i, j + 1))
            {
                ++counter;
                if (counter == 3)
                    return true;
            }
            else
                counter = 0;
        }
    }

    // checking the columns winning
    for (int j = 0; j < 7; j++)
    {
        counter = 0;
        for (int i = 0; i < 5; i++)
        {
            if (BOARD(i, j) && BOARD(i, j) == BOARD(i + 1, j))
            {
                ++counter;
                if (counter == 3)
                    return true;
            }
            else
                counter = 0;
        }
    }

    // Checking the diagonal winning
    for (int i = 0; i < 3; i++)
    {
        // for negative-sloped diagonal
        for (int j = 0; j < 4; j++)
        {
            if (BOARD(i, j))
            {
                int k;
                for (k = 1; k <= 3; k++)
                    if (BOARD(i, j) != BOARD(i + k, j + k))
                        break;
                if (k == 4)
                    return true;
            }
        }
        // for positive-sloped diagonal
        for (int j = 3; j < 7; j++)
        {
            if (BOARD(i, j))
            {
                int k;
                for (k = 1; k <= 3; k++)
                    if (BOARD(i, j) != BOARD(i + k, j - k))
                        break;
                if (k == 4)
                    return true;
            }
        }
    }
    return false;
}
bool ConnectFourBoard::is_draw()
{
    return (n_moves == 42 && !is_winner());
}

bool ConnectFourBoard::update_board(int index)
{
    if (index < 0 || index > 6 || lowest_row[index] == -1)
        return false;
    int x = lowest_row[index]--;
    BOARD(x, index) = (n_moves % 2) ? 'O' : 'X';
    n_moves++;
    return true;
}

bool ConnectFourBoard::game_is_over()
{
    return (n_moves >= 42);
}

void ConnectFourBoard::reset(int index)
{
    int x = ++lowest_row[index];
    BOARD(x, index) = '\0';
    n_moves--;
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
    int index;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (!BOARD(i, j))
            {
                continue;
            }
            index = BOARD(i, j) / 88;
            auto updateScores = [&](int i1, int j1, int i2, int j2, int i3, int j3)
            {
                int sum = BOARD(i + i1, j + j1) + BOARD(i + i2, j + j2) + BOARD(i + i3, j + j3);
                if (sum % BOARD(i, j) == 0)
                {
                    sum /= BOARD(i, j);
                    sum += 1;
                    scores[index] += (sum * sum);
                }
            };
            if (j < 4)
            {
                updateScores(0, 1, 0, 2, 0, 3);
            }
            if (j > 2)
            {
                updateScores(0, -1, 0, -2, 0, -3);
            }
            if (j > 0 && j < 5)
            {
                updateScores(0, -1, 0, 1, 0, 2);
            }
            if (j > 1 && j < 6)
            {
                updateScores(0, -1, 0, -2, 0, 1);
            }
            if (i < 3)
            {
                updateScores(1, 0, 2, 0, 3, 0);
                updateScores(1, 0, 2, 0, 3, 0);
                updateScores(1, 0, 2, 0, 3, 0);
            }
            if (i < 3 && j < 4)
            {
                updateScores(1, 1, 2, 2, 3, 3);
            }
            if (i > 2 && j > 2)
            {
                updateScores(-1, -1, -2, -2, -3, -3);
            }
            if (i < 3 && j > 2)
            {
                updateScores(1, -1, 2, -2, 3, -3);
            }
            if (i > 2 && j < 4)
            {
                updateScores(-1, 1, -2, 2, -3, 3);
            }
            if (i > 0 && i < 4 && j > 0 && j < 5)
            {
                updateScores(-1, -1, 1, 1, 2, 2);
            }
            if (i > 0 && i < 4 && j > 1 && j < 6)
            {
                updateScores(-1, 1, 1, -1, 2, -2);
            }
            if (i > 1 && i < 5 && j > 1 && j < 6)
            {
                updateScores(-1, -1, -2, -2, 1, 1);
            }
            if (i > 1 && i < 5 && j > 1 && j < 5)
            {
                updateScores(-1, 1, -2, 2, 1, -1);
            }
        }
    }
    if (n_moves & 1)
    {
        return (scores[0] - scores[1]);
    }
    return (scores[1] - scores[0]);
}

int ConnectFourBoard::moves()
{
    return n_moves;
}

std::string ConnectFourBoard::get_state()
{
    return board;
}