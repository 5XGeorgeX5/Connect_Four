#include "ConnectFour.hpp"

AI_Player::AI_Player(ConnectFourBoard *board) : Base_AI_Player(board)
{
    this->name = "AI Computer Player";
    std::cout << "My names is " << name << '\n';
}

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> AI_Player::valideMoves()
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> moves;
    for (int i = 0; i < 7; i++)
    {
        if (board->valid_move(i))
        {
            board->update_board(i);
            moves.push(std::make_pair(board->heuristic(), i));
            board->reset(i);
        }
    }
    return moves;
}

int AI_Player::minimax(int alpha, int beta, int depth)
{
    ++runs;
    cut = false;

    if (board->is_winner())
        return board->moves() - 5000;
    if (board->moves() == 42)
        return 0;
    if (depth == 10)
    {
        return (board->heuristic());
    }

    int value;
    int result = -5000;
    auto moves = valideMoves();

    while (!moves.empty())
    {
        std::pair<int, int> movePair = moves.top();
        moves.pop();
        board->update_board(movePair.second);

        std::string state = board->get_state();
        auto it = myMap.find(state);
        if (it != myMap.end())
        {
            value = it->second;
        }
        else
        {
            value = -minimax(-beta, -alpha, depth + 1);
            if (!cut)
            {
                myMap[state] = value;
            }
        }
        board->reset(movePair.second);
        result = std::max(result, value);
        alpha = std::max(alpha, result);
        if (beta <= alpha)
        {
            cut = true;
            return (alpha);
        }
    }

    return (result);
}

int AI_Player::get_move()
{
    runs = 0;
    myMap.clear();
    int move = -1;
    int opponentScore = 5000;
    auto moves = valideMoves();
    while (!moves.empty())
    {
        std::pair<int, int> movePair = moves.top();
        moves.pop();
        board->update_board(movePair.second);
        int value = minimax(-5000, opponentScore, 0);
        board->reset(movePair.second);
        if (value < opponentScore)
        {
            opponentScore = value;
            move = movePair.second;
        }
    }
    return move;
}