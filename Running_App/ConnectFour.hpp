#ifndef CONNECT_FOUR_HPP
#define CONNECT_FOUR_HPP

#include <iostream>
#include <random>
#include <unordered_map>

class ConnectFourBoard
{
private:
    std::string board = std::string(42, '\0');
    int n_moves = 0;
    int lowest_row[7] = {5, 5, 5, 5, 5, 5, 5};

public:
    ConnectFourBoard() {};

    bool update_board(int index);

    bool is_winner();

    bool is_draw();

    bool game_is_over();

    int moves();

    void display_board();

    void reset(int index);

    int heuristic();

    std::string get_state();
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

class Base_AI_Player : public Player
{
protected:
    ConnectFourBoard *board;
    unsigned long long runs = 0;

public:
    Base_AI_Player(ConnectFourBoard *board);
    virtual int get_move() = 0;
    unsigned long long get_runs() { return runs; }
};

class AI_Player : public Base_AI_Player
{
private:
    std::unordered_map<std::string, int> myMap;
    int searchOrder[7] = {3, 4, 2, 5, 1, 6, 0};
    bool cut;

    int minimax(int alpha, int beta, int depth, int ans[]);

public:
    // Take a symbol and pass it to parent
    AI_Player(ConnectFourBoard *);
    // Generate best move move
    int get_move();
};

///////////////////////////////////////////
class GameManager
{
private:
    ConnectFourBoard *board;
    Player *players[2];

public:
    GameManager(ConnectFourBoard *, Player *playerPtr[2]);
    void run();
};

#endif