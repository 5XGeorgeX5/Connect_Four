#include "../ConnectFour.hpp"

AI_Player_V1::AI_Player_V1(ConnectFourBoard *bPtr)
{
    boardPtr = bPtr;
    this->name = "AI Computer Player";
    std::cout << "My names is " << name << '\n';
}

int AI_Player_V1::minimax(int alpha, int beta, int depth, int ans[])
{
    ++runs;
    cut = false;
    int value, result;
    if (boardPtr->is_winner())
        return boardPtr->moves() - 5000;
    if (boardPtr->moves() == 42)
        return 0;
    if (depth == 10)
    {
        return (boardPtr->heuristic());
    }
    result = -5000;

    for (int i = 0; i < 7; i++)
    {
        if (boardPtr->update_board(searchOrder[i]))
        {
            std::string state = boardPtr->to_string();
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
            boardPtr->reset(searchOrder[i]);
            result = std::max(result, value);
            alpha = std::max(alpha, value);
            if (depth == 0 && ans[1] < value)
            {
                ans[1] = value;
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