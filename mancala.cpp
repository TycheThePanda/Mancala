#include <iostream>
#include <string>
#include <limits>

using namespace std;

void displayBoard(int board[]) {
    cout << "   12 11 10 9  8  7\n";
    cout << "-------------------\n";

    cout << to_string(board[1]) + "  ";

    for (int i = 13; i > 7 ; i--) {
        cout << to_string(board[i]) + "  ";
    }

    cout << "\n";
    cout << " " << string(to_string(board[1]).length() + 1, ' ');

    for (int i = 2; i < 8; i++) {
        cout << to_string(board[i]) + "  ";
    }
    cout << to_string(board[0]) << "  " << endl;

    cout << "-------------------\n";
    cout << "   1  2  3  4  5  6\n";
}

int* updateBoard(int* board, int pit, bool turn) {
    int temp = board[pit];
    int next;
    board[pit] = 0;

    for (int i = 0; i < temp; i++) {
        if ((pit <= 6 && pit >= 1) || (pit <= 12 && pit >= 8)) {
            next = pit + 1;
        }
        else if (pit == 7) {
            if (!turn) {
                next = 0;
            }
            else {
                next = pit + 1;
            }
        }
        else if (pit == 13) {
            if (turn) {
                next = 1;
            }
            else {
                next = 2;
            }
        }
        else if (pit == 0) {
            next = 8;
        }
        board[next]++;
        pit = next;
    }
    return board;
}


int main() {
    int board[] = {0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    bool turn = 0; //0 means player 1's turn
    bool finish = 0;
    int input;
    
    do{
        displayBoard(board);
        cout << (!turn ? "Player 1 ,please choose a pit (1-6)" : "Player 2 ,please choose a pit (7-12)") << endl;
        while(true){
            cin >> input;
            if (cin.fail()) {
                cin.clear();  // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore the invalid input
                cout << "Invalid input. Please enter an integer." << endl;
            }
            else if(((input >= 1 && input <= 6) && !turn) || ((input >= 7 && input <= 12) && turn)){
                if (board[input+1] != 0){
                    updateBoard(board, input + 1, turn);
                    break;
                }
                else{
                    cout << "Please enter a number of a pit with stones in it." << endl;
                }
            }
            else{
                cout << "Please enter a value" << (!turn ? " 1-6\n" : " 7-12\n");
            }
        }

        //iffy about this one.
        for (int i = 1; i < 13; i++) {
            if (board[i] != 0) {
                finish = 0;
                break;
            }
            else{finish = 1;}
        }
        //check if it is possible for the next player to play
        if (!turn){ //player 1
            
        }
        else{//player 2

        }
        turn = !turn;
    }while(!finish);

    displayBoard(board);
    return 0;
}
