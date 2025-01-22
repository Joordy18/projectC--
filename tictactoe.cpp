#include <iostream>
using namespace std;

string grille[3][3] = {{" ", " ", " "},
                        {" ", " ", " "},
                        {" ", " ", " "}};

void grid() {
    cout << grille[0][0] << " | " << grille[0][1] << " | " << grille[0][2] << endl;
    cout << grille[1][0] << " | " << grille[1][1] << " | " << grille[1][2] << endl;
    cout << grille[2][0] << " | " << grille[2][1] << " | " << grille[2][2] << endl;
}

void play(int player) {
    char letters[2] = {'X', 'O'};
    int col, row;
    while (true) {
        cout << "Player " << letters[player] << " enter the column and row you want to play" << endl;
        cin >> col >> row;
        if (col < 0 || col >= 3 || row < 0 || row >= 3) {
            cout << "Invalid input. Please enter a valid column and row." << endl;
        } else if (grille[col][row] != " ") {
            cout << "This grid is already taken. Please choose another one." << endl;
        } else {
            cout << "Player " << letters[player] << " has played" << endl;
            grille[col][row] = letters[player];
            break;
        }
    }
}

bool checkWin() {
    // lignes
    for (int i = 0; i < 3; i++) {
        if (grille[i][0] == grille[i][1] && grille[i][1] == grille[i][2] && grille[i][0] != " ") {
            return true;
        }
    }
    // colonnes
    for (int i = 0; i < 3; i++) {
        if (grille[0][i] == grille[1][i] && grille[1][i] == grille[2][i] && grille[0][i] != " ") {
            return true;
        }
    }
    // diagonales
    if (grille[0][0] == grille[1][1] && grille[1][1] == grille[2][2] && grille[0][0] != " ") {
        return true;
    }
    if (grille[0][2] == grille[1][1] && grille[1][1] == grille[2][0] && grille[0][2] != " ") {
        return true;
    }
    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grille[i][j] == " ") {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int currentPlayer = 0;
    grid();
    while (true) {
        play(currentPlayer);
        grid();
        if (checkWin()) {
            cout << "Player " << (currentPlayer == 0 ? 'X' : 'O') << " wins!" << endl;
            break;
        }
        if (checkDraw()) {
            cout << "It's a draw!" << endl;
            break;
        }
        currentPlayer = 1 - currentPlayer; // changer de joueur
    }
}