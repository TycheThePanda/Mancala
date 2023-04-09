#include "utils.h"

//displays the board in a way that ensures everything stays perfectly spaced
void displayBoard(int board[]) {

    cout << "   ";
    for(int i = SIDE_LENGTH * 2 ; i > SIDE_LENGTH; i--){
        cout << i;
        for(int j = 0; j < (3 - to_string(i).length());j++){
            cout <<" ";
        }
    }
    cout << endl;
    for(int i = 0; i < SIDE_LENGTH; i++){
        cout <<"---";
    }
    cout << endl;

    cout << board[P2_WELL];
    //adds a number of spaces to keep characters before final pit even(3 characters)
    for(int i = 0; i < (3 - to_string(board[P2_WELL]).length()); i++){
        cout << " ";
    }

    for (int i = P2_END; i >= P2_START ; i--) {
        cout << board[i];
        for(int j = 0; j < (3 - to_string(board[i]).length()); j++){
            cout << " ";
        }
    }

    cout << endl << "   ";

    for (int i = P1_START; i <= P1_END; i++) {
        cout << board[i];
        for(int j = 0; j < (3 - to_string(board[i]).length()); j++){
            cout << " ";
        }
    }
    cout << board[P1_WELL] << endl;

    for(int i = 0; i < SIDE_LENGTH; i++){
        cout <<"---";
    }
    
    cout << endl << "   ";
    
    for(int i = 1; i <= SIDE_LENGTH; i++){
        cout << i;
        for(int j = 0; j<(3 - to_string(i).length());j++){
            cout <<" ";
        }
    }

    cout << endl;
}

void populateBoard(int * board){
    board[P1_WELL] = 0;
    board[P2_WELL] = 0;

    for(int i = P1_START; i <= P2_END; i++){
        board[i] = INIT_STONES;
    }
}

bool updateBoard(int* board, int pit, bool turn) {
    //in the board array,

    int temp = board[pit];
    int next = pit;
    board[pit] = 0;

    //this loop moves the stones previously stored at the chosen pit around the board.
    for (int i = 0; i < temp; i++) {
        //pit = next;
        if ((pit < P1_END && pit >= P2_WELL) || (pit < P2_END && pit > P1_END)) {
            next = pit + 1; 
        }
        else if (pit == P1_END) {
            if (!turn) {
                next = P1_WELL;
            }
            else {//continue placing stones on the following pits
                next = pit + 1;
            }
        }
        else if (pit == P2_END) {
            if (turn) {
                next = P2_WELL;
            }
            else {//continue placing stones on the following pits
                next = P1_START;
            }
        }
        else if (pit == P1_WELL) {
            next = P2_START;
        }
        board[next]++;
        pit = next;
    }
    if ((pit == P1_WELL) || (pit == P2_WELL)){
        return true;
    }
    else{
        return false;
    }
}

void displayWinner(int* board){
    if (board[P1_WELL]>board[P2_WELL]){
        cout << "\n\n\nPlayer 1 won the game!\n\n\n";
    }
    else if (board[P1_WELL] == board[P2_WELL]){
        cout << "\n\n\nPlayer 1 and Player 2 tied!\n\n\n";
    }
    else{
        cout << "\n\n\nPlayer 2 won the game!\n\n\n";
    }
}

void vanilla(bool plus) {
    int board[P2_END + 1]; 
    bool turn = 0; //0 means player 1's turn
    bool finish = false;
    bool canPlay = false;
    bool anotherTurn = false;
    int input;
    int index;

    populateBoard(board);
    
    do{
        displayBoard(board);
        if(!turn){//player1
            cout << "Player 1, please choose a pit (1-" << SIDE_LENGTH << ")" << endl;
        }
        else{
            cout << "Player 2, please choose a pit (" << SIDE_LENGTH + 1 << "-" << SIDE_LENGTH*2 << ")" << endl;
        }
        while(true){
            cin >> input;
            index = input + 1;
            if (cin.fail()) {
                cin.clear();  // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore the invalid input
                cout << "Invalid input. Please enter an integer." << endl;
            }
            else if(((index >= P1_START && index <= P1_END) && !turn) || ((index >= P2_START && index <= P2_END) && turn)){
                if (board[index] != 0){
                    anotherTurn = updateBoard(board, index, turn);
                    break;
                }
                else{
                    cout << "Please enter a number of a pit with stones in it." << endl;
                }
            }
            else{
                cout << "Please enter a value ";
                if(!turn){//player1
                    cout << "(1-" << SIDE_LENGTH << ")" << endl;
                }
                else{
                    cout << "(" << SIDE_LENGTH + 1 << "-" << SIDE_LENGTH*2 << ")" << endl;
                }
            }
        }

        //checks if the board is completely empty
        for (int i = P1_START; i <= P2_END; i++) {
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
                for (int i = P1_START; i <= P1_END; i++) {
                    if (board[i] != 0) {
                        canPlay = true; //means the game continues
                        break;
                    }
                }
            }
            else{//if it is currently P1's turn, make sure P2 can play
                for (int i = P2_START; i <= P2_END; i++) {
                    if (board[i] != 0) {
                        canPlay = true; //means the game continues
                        break;
                    }
                }
            }
            //if the next player can play, alternate the turn. Otherwise, it will stay on the same turn.
            if(plus && canPlay && anotherTurn){
                cout << (!turn ? "Player 1 gets another turn!" : "Player 2 gets another turn!") << endl;
            }
            else if (canPlay)
            {
                turn = !turn;
                canPlay = false;//resets this value for next loop
            }
            else{
                cout << endl << (!turn ? "Player 2 can not play, Player 1 plays again": "Player 1 can not play, Player 2 plays again") << endl;
            }
        }
    }while(!finish);
    displayBoard(board);
    //display who won the game
    displayWinner(board);
}

void chooseAny(bool plus) {
    int board[P2_END + 1]; 
    bool turn = 0; //0 means player 1's turn
    bool finish = false;
    bool anotherTurn = false;
    int input;
    int index;

    populateBoard(board);
    
    do{
        displayBoard(board);
        cout << endl << (!turn ? "Player1's turn" : "Player 2's turn") << endl;
        while(true){
            cin >> input;
            index = input + 1;
            if (cin.fail()) {
                cin.clear();  // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore the invalid input
                cout << "Invalid input. Please enter an integer." << endl;
            }
            else if((index >= P1_START && index <= P2_END)){
                if (board[index] != 0){
                    anotherTurn = updateBoard(board, index, turn);
                    break;
                }
                else{
                    cout << "Please enter a number of a pit with stones in it." << endl;
                }
            }
            else{
                cout << "Please enter a number (" << 1 << "-" << SIDE_LENGTH*2 << ")" << endl;
            }
        }

        //checks if the board is completely empty
        for (int i = P1_START; i <= P2_END; i++) {
            if (board[i] != 0) {
                finish = false;
                break;
            }
            else{finish = true;}
        }
        if(plus && anotherTurn){
        cout << (!turn ? "Player 1 gets another turn!" : "Player 2 gets another turn!") << endl;
        }
        else{
            turn = !turn;
        }
    }while(!finish);

    displayBoard(board);

    //display who won the game
    displayWinner(board);

}
