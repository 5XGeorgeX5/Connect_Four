#ifndef CONNECT_FOUR_HPP
#define CONNECT_FOUR_HPP

#include <iostream>
#include <random>
#include <unordered_map>

class ConnectFourBoard
{
private:
    int n_rows, n_cols;
    char **board;
    int n_moves = 0;
    int lowest_row[7];

public:
    ConnectFourBoard();

    bool update_board(int index);

    bool is_winner();

    bool is_draw();

    bool game_is_over();

    int moves();

    void display_board();

    void reset(int index);

    int heuristic();

    std::string to_string();

    ~ConnectFourBoard();
};

// Players
//___________________________________

class Player
{
protected:
    std::string name;
    bool isFirst;

public:
    Player(bool isFirst);

    virtual int get_move() = 0;

    std::string to_string();

    char get_symbol();
};

class ConnectFourPlayer : public Player
{
public:
    ConnectFourPlayer(bool isFirst);

    int get_move();
};

class RandomPlayer : public Player
{
private:
    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;

public:
    // Take a symbol and pass it to parent
    RandomPlayer(bool isFirst);
    // Generate a random move
    int get_move();
};

class AI_Player : public Player
{
private:
    ConnectFourBoard *boardPtr;
    int minimax(bool player, int alpha, int beta, int depth, int ans[]);
    std::unordered_map<std::string, int> myMap;
    bool cut;
    unsigned long long runs = 0;
    int arr[7];

public:
    // Take a symbol and pass it to parent
    AI_Player(ConnectFourBoard *, bool isFirst);
    // Generate best move move
    int get_move();
};
///////////////////////////////////////////
class GameManager
{
private:
    ConnectFourBoard *boardPtr;
    Player *players[2];

public:
    GameManager(ConnectFourBoard *, Player *playerPtr[2]);
    void run();
};

#endif