#include <iostream>
#include "../ConnectFourBoard.cpp"
#include "../AI_V1/AI_Player.cpp"
#include "RandomPlayer.cpp"
#include "GameManager.cpp"
#include "Player.cpp"
using namespace std;

int main()
{
    int choice = 1, mode;
    Player *players[2];
    ConnectFourBoard *board;

    cout << "Welcome to Connect Four. :)\n";
    while (choice)
    {
        board = new ConnectFourBoard();
        cout << "Press 1 if you want to play with computer: ";
        cin >> choice;
        if (choice != 1)
        {
            players[0] = new ConnectFourPlayer(true);
            players[1] = new ConnectFourPlayer(false);
        }
        else
        {
            cout << "choose the mode, 1 for easy and 2 for hard: ";
            cin >> mode;
            cout << "Press 1 if you want to play first: ";
            cin >> choice;
            choice = (choice == 1);

            players[!choice] = new ConnectFourPlayer(choice);
            if (mode == 1)
                players[choice] = new RandomPlayer();
            else
                players[choice] = new AI_Player_V1(board);
        }
        GameManager game_manager(board, players);
        game_manager.run();
        system("pause");
        cout << "enter 0 if you want to exit: ";
        cin >> choice;
    }
}
