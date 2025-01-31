#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

class TicTacToe : public QWidget {
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr) : QWidget(parent) {
        // Create buttons for the game board
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                buttons[i][j] = new QPushButton("", this);
                buttons[i][j]->setFixedSize(100, 100);
                connect(buttons[i][j], &QPushButton::clicked, this, &TicTacToe::buttonClicked);
            }
        }

        // Create labels for player turns
        playerLabel = new QLabel("Player X's Turn", this);

        // Create game board layout
        QGridLayout *boardLayout = new QGridLayout;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                boardLayout->addWidget(buttons[i][j], i, j);
            }
        }

        // Create main layout
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(playerLabel);
        mainLayout->addLayout(boardLayout);

        // Initialize game variables
        currentPlayer = 'X';
        gameWon = false;
    }

private slots:
    void buttonClicked() {
        QPushButton *button = qobject_cast<QPushButton*>(sender());
        if (button->text() == "" && !gameWon) {
            button->setText(QString(currentPlayer));
            checkWin();
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            playerLabel->setText(QString("Player ") + QString(currentPlayer) + "'s Turn");
        }
    }

    void checkWin() {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (buttons[i][0]->text() == currentPlayer &&
                buttons[i][1]->text() == currentPlayer &&
                buttons[i][2]->text() == currentPlayer) {
                gameWon = true;
                QMessageBox::information(this, "Game Over", "Player " + QString(currentPlayer) + " wins!");
                return;
            }
        }

        // Check columns
        for (int j = 0; j < 3; ++j) {
            if (buttons[0][j]->text() == currentPlayer &&
                buttons[1][j]->text() == currentPlayer &&
                buttons[2][j]->text() == currentPlayer) {
                gameWon = true;
                QMessageBox::information(this, "Game Over", "Player " + QString(currentPlayer) + " wins!");
                return;
            }
        }

        // Check diagonals
        if ((buttons[0][0]->text() == currentPlayer &&
             buttons[1][1]->text() == currentPlayer &&
             buttons[2][2]->text() == currentPlayer) ||
            (buttons[0][2]->text() == currentPlayer &&
             buttons[1][1]->text() == currentPlayer &&
             buttons[2][0]->text() == currentPlayer)) {
            gameWon = true;
            QMessageBox::information(this, "Game Over", "Player " + QString(currentPlayer) + " wins!");
            return;
        }

        // Check for draw
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
            QMessageBox::information(this, "Game Over", "It's a draw!");
        }
    }

private:
    QPushButton *buttons[3][3];
    QLabel *playerLabel;
    char currentPlayer;
    bool gameWon;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TicTacToe game;
    game.setGeometry(100, 100, 330, 330);
    game.setWindowTitle("Tic-Tac-Toe");
    game.show();
    return app.exec();
}

#include "moc_tictactoe.cpp"
