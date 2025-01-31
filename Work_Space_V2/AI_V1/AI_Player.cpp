#include "../ConnectFour.hpp"

AI_Player_V1::AI_Player_V1(ConnectFourBoard *board) : Base_AI_Player(board)
{
    this->name = "AI Computer Player V1";
    std::cout << "My names is " << name << '\n';
}

int AI_Player_V1::minimax(int alpha, int beta, int depth, int ans[])
{
    ++runs;
    cut = false;

    if (board->is_winner())
        return board->moves() - 5000;
    if (board->moves() == 42)
        return 0;
    if (depth == 11)
    {
        return (board->heuristic());
    }

    int value;
    int result = -5000;

    for (int i = 0; i < 7; i++)
    {
        if (board->update_board(searchOrder[i]))
        {
            std::string state = board->to_string();
            if (myMap.count(state))
            {
                value = myMap[state];
            }
            else
            {
                value = -minimax(-beta, -alpha, depth + 1, ans);
                if (!cut)
                {
                    myMap[state] = value;
                }
            }
            board->reset(searchOrder[i]);
            result = std::max(result, value);
            alpha = std::max(alpha, result);
            if (depth == 0 && ans[1] < result)
            {
                ans[1] = result;
                ans[0] = searchOrder[i];
            }
            if (beta <= alpha)
            {
                cut = true;
                return (alpha);
            }
        }
    }

    return (result);
}

int AI_Player_V1::get_move()
{
    myMap.clear();
    int ans[2];
    ans[1] = -5000;
    minimax(-5000, 5000, 0, ans);
    return ans[0];
}