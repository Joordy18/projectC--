#include <QApplication>
#include <iostream>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
class TicTacToe : public QWidget {

public:
    TicTacToe(QWidget *parent = nullptr) : QWidget(parent) {
        // Création des buton jeu
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                buttons[i][j] = new QPushButton("", this);
                buttons[i][j]->setFixedSize(100, 100);
                connect(buttons[i][j], &QPushButton::clicked, this, &TicTacToe::buttonClicked);
            }
        }


        // Affiche qui est en trains de jouer
        playerLabel = new QLabel("Tour du Joueur X", this);


        // Création de la disposition du plateau (Grille - Tableau)
        QGridLayout *boardLayout = new QGridLayout;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                boardLayout->addWidget(buttons[i][j], i, j);
            }
        }

        // Création de la disposition (affichage joueur et grille jeux)
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(playerLabel);
        mainLayout->addLayout(boardLayout);

        currentPlayer = 'X';
        gameWon = false;
    }
// Fonction ButtonClicked réceptione l'information en un bouteau et cliquer,
    // Il vérifie si la case est déjà jouer ou si la partie est gagner en appelant CheckWin
private slots:
    void buttonClicked() {
        QPushButton *button = qobject_cast<QPushButton*>(sender());
        if (button->text() == "" && !gameWon) {
            button->setText(QString(currentPlayer));
            checkWin(); // Exécution de CheckWin
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            playerLabel->setText(QString("Tour du Joueur ") + QString(currentPlayer));
        }
    }

    void checkWin() {
        // Vérification des lignes
        for (int i = 0; i < 3; ++i) {
            if (buttons[i][0]->text() == currentPlayer &&
                buttons[i][1]->text() == currentPlayer &&
                buttons[i][2]->text() == currentPlayer) {
                gameWon = true;
                if(buttons[i][0]->text() == currentPlayer) {
                    QMessageBox::information(this, "Partie terminée", "Le Joueur " + QString(currentPlayer) + " a gagné !");
                    replay();
                    return;
            }

            }
        }

        // Vérification des victoire par colonnes
        for (int j = 0; j < 3; ++j) {
            if (buttons[0][j]->text() == currentPlayer &&
                buttons[1][j]->text() == currentPlayer &&
                buttons[2][j]->text() == currentPlayer) {
                gameWon = true;
                QMessageBox::information(this, "Partie terminée", "Le Joueur " + QString(currentPlayer) + " a gagné !");
                replay();
                return;
            }
        }

        // Vérification des victoire par  diagonales
        if ((buttons[0][0]->text() == currentPlayer &&
             buttons[1][1]->text() == currentPlayer &&
             buttons[2][2]->text() == currentPlayer) ||
            (buttons[0][2]->text() == currentPlayer &&
             buttons[1][1]->text() == currentPlayer &&
             buttons[2][0]->text() == currentPlayer)) {
            gameWon = true;
            QMessageBox::information(this, "Partie terminée", "Le Joueur " + QString(currentPlayer) + " a gagné !");
            replay();
            return;
        }

        //   match nul
        bool draw = true;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (buttons[i][j]->text() == "") {
                    draw = false;
                    break;
                }
            }
            if (!draw) {
                break;
            }
        }
        if (draw) {
            QMessageBox::information(this, "Partie terminée", "Match nul !");
            replay();
        }
    }

private:
    QPushButton *buttons[3][3];
    QLabel *playerLabel;
    char currentPlayer;
    bool gameWon;

    void replay() {
        // Réinitialisation des boutons et des variables
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                buttons[i][j]->setText("");
            }
        }
        currentPlayer = 'X';
        gameWon = false;
        playerLabel->setText("Tour du Joueur X");
    }

};



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TicTacToe game;
    game.setGeometry(100, 100, 330, 330);
    game.setWindowTitle("Morpion");
    game.show();


    return app.exec();}
