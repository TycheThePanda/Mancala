#include <iostream>
#include <string>
#include <limits>

using namespace std;

//displays the board in a way that ensures everything stays perfectly spaced
void displayBoard(int board[]) {
    cout << "   12 11 10 9  8  7\n";
    cout << "-------------------------\n";

    cout << board[1];
    for(int i = 0; i < (3 - to_string(board[1]).length()); i++){
        cout << " ";
    }

    for (int i = 13; i > 7 ; i--) {
        cout << board[i];
        for(int j = 0; j < (3 - to_string(board[i]).length()); j++){
            cout << " ";
        }
    }

    cout << "\n   ";

    for (int i = 2; i < 8; i++) {
        cout << board[i];
        for(int j = 0; j < (3 - to_string(board[i]).length()); j++){
            cout << " ";
        }
    }

    cout << board[0] << endl;

    cout << "-------------------------\n";
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
    bool finish = false;
    bool canPlay = false;
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

        //checks if the board is completely empty
        for (int i = 2; i < 14; i++) {
            if (board[i] != 0) {
                finish = false;
                break;
            }
            else{finish = true;}
        }
        
        
        //check if it is possible for the next player to play, 
        //this operation should only continue if finish is false, to prevent double-checking
        if(!finish){
            if (turn){ //if it is currently P2's turn, make sure P1 can play
                for (int i = 2; i <= 7; i++) {
                    if (board[i] != 0) {
                        canPlay = true; //means the game continues
                        break;
                    }
                }
            }
            else{//if it is currently P1's turn, make sure P2 can play
                for (int i = 8; i <= 13; i++) {
                    if (board[i] != 0) {
                        canPlay = true; //means the game continues
                        break;
                    }
                }
            }
            //if the next player can play, alternate the turn. Otherwise, it will stay on the same turn.
            if(canPlay){
                turn = !turn;
                canPlay = false; //resets this value for next loop
            }
            else{
                cout << (!turn ? "\nPlayer 2 can not play, Player 1 plays again": "\nPlayer 1 can not play, Player 2 plays again") << endl;
            }
        }
    }while(!finish);

    displayBoard(board);

    //display who won the game
    if (board[0]>board[1]){
        cout << "\n\n\nPlayer 1 won the game!\n\n\n";
    }
    else if (board[0] == board[1]){
        cout << "\n\n\nPlayer 1 and Player 2 tied!\n\n\n";
    }
    else{
        cout << "\n\n\nPlayer 1 won the game!\n\n\n";
    }

    return 0;
}
