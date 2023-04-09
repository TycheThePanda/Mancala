#include "utils.h"

int main(){
    char gamemode;
    while(true){
        cout << endl << "Which gamemode would you like to play?" << endl;
        cout << "Vanilla (a)" << endl << "Vanilla+ (b)" << endl << "ChooseAny (c)" << endl << "ChooseAny+ (d)" << endl << "Exit(e)" << endl;
        cin >> gamemode;
        for (int i=0; i<25;i++){
            cout << endl;
        }

        switch (gamemode){
        case 'a':
            playMancala(NOT_CHOOSE, NOT_PLUS);
            break;

        case 'b':
            playMancala(NOT_CHOOSE, PLUS);
            break;

        case 'c':
            playMancala(CHOOSE, NOT_PLUS);
            break;

        case 'd':
            playMancala(CHOOSE, PLUS);
            break;
        
        case 'e':
            exit(0);
            break;

        default:
            cout << endl << "Please enter a valid letter." << endl;
            break;
        }
    }
    return 0;
}