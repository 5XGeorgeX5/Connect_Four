#include <iostream>
#include "ConnectFourBoard.cpp"
#include "AI_Player.cpp"
#include "GameManager.cpp"
#include "Player.cpp"
using namespace std;

void setGame(ConnectFourBoard *board, Player *players[])
{
    int choice;
    cout << "Press 1 if you want to play with computer: ";
    cin >> choice;
    if (choice != 1)
    {
        players[0] = new ConnectFourPlayer(true);
        players[1] = new ConnectFourPlayer(false);
    }
    else
    {
        int mode;
        cout << "choose the mode, 1 for easy and 2 for hard: ";
        cin >> mode;
        cout << "Press 1 if you want to play first: ";
        cin >> choice;
        choice = (choice == 1);

        players[!choice] = new ConnectFourPlayer(choice);
        if (mode == 1)
            players[choice] = new RandomPlayer();
        else
            players[choice] = new AI_Player(board);
    }
}

int main()
{
    int choice;
    Player *players[2];
    ConnectFourBoard *board = new ConnectFourBoard();

    cout << "Welcome to Connect Four. :)\n";
    setGame(board, players);
    while (true)
    {
        GameManager game_manager(board, players);
        game_manager.run();
        system("pause");
        cout << "Please select an option:\n1. Play again\n2. New Game\n0. Exit\n";
        cin >> choice;
        while (choice < 0 || choice > 2)
        {
            cout << "Invalid choice. Please select again:\n1. Play again\n2. New Game\n0. Exit\n";
            cin >> choice;
        }
        if (choice == 0)
            return 0;

        board->resetBoard();
        if (choice == 1)
        {
            swap(players[0], players[1]);
        }
        else if (choice == 2)
        {
            delete players[0];
            delete players[1];
            setGame(board, players);
        }
    }
}
