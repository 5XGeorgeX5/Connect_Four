#ifndef CONNECT_FOUR_HPP
#define CONNECT_FOUR_HPP

#include <iostream>
#include <random>
#include <unordered_map>

class ConnectFourBoard
{
private:
    int n_rows, n_cols;
    char board[6][7];
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

    int heuristic2();

    std::string to_string();
};

// Players
//___________________________________

class Player
{
protected:
    std::string name;

public:
    virtual int get_move() = 0;

    std::string get_name();
};

class ConnectFourPlayer : public Player
{
private:
    bool isFirst;

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
    RandomPlayer();
    // Generate a random move
    int get_move();
};

class AI_Player_V1 : public Player
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
    AI_Player_V1(ConnectFourBoard *);
    // Generate best move move
    int get_move();
};

class AI_Player_V2 : public Player
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
    AI_Player_V2(ConnectFourBoard *);
    // Generate best move move
    int get_move();
};

class AI_Player_V3 : public Player
{
private:
    ConnectFourBoard *boardPtr;
    int minimax(int alpha, int beta, int depth, int ans[]);
    std::unordered_map<std::string, int> myMap;
    bool cut;
    unsigned long long runs = 0;
    int searchOrder[7] = {3, 4, 2, 5, 1, 6, 0};

public:
    // Take a symbol and pass it to parent
    AI_Player_V3(ConnectFourBoard *);
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