#include "ConnectFour.hpp"

AI_Player::AI_Player(ConnectFourBoard *bPtr, bool isFirst) : Player(isFirst)
{
    boardPtr = bPtr;
    this->name = "AI Computer Player";
    std::cout << "My names is " << name << '\n';
    int mid = 3, index = 1;
    arr[0] = mid;
    for (int i = 1; i <= mid; i++)
    {
        arr[index++] = mid + i;
        arr[index++] = mid - i;
    }
}

int AI_Player::minimax(bool player, int alpha, int beta, int depth, int ans[])
{
    ++runs;
    cut = false;
    int value, result;
    if (boardPtr->is_winner())
        return ((player ? -1 : 1) * (5000 - boardPtr->moves()));
    if (boardPtr->is_draw())
        return 0;
    if (boardPtr->game_is_over())
        return ((boardPtr->is_winner() ? 1 : -1) * (5000 - boardPtr->moves()));
    if (depth == 9)
    {
        return (boardPtr->heuristic());
    }
    result = (player ? -5000 : 5000);

    for (int i = 0; i < 7; i++)
    {
        if (boardPtr->update_board(arr[i]))
        {
            std::string state = boardPtr->to_string();
            if (myMap.count(state))
            {
                value = myMap[state];
            }
            else
            {
                value = minimax(!player, alpha, beta, depth + 1, ans);
                if (!cut)
                {
                    myMap[state] = value;
                }
            }
            boardPtr->reset(arr[i]);
            if (player)
            {
                result = std::max(result, value);
                alpha = std::max(alpha, value);
            }
            else
            {
                result = std::min(result, value);
                beta = std::min(beta, value);
            }
            if (depth == 0 && ans[1] != value && ((ans[1] > value) ^ player))
            {
                ans[1] = value;
                ans[0] = arr[i];
            }
            if (beta <= alpha)
            {
                cut = true;
                return (result);
            }
        }
    }

    return (result);
}

int AI_Player::get_move()
{
    int ans[2];
    ans[1] = 5000 - 10000 * (isFirst);
    minimax(isFirst, -5000, 5000, 0, ans);
    return ans[0];
}