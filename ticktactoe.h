#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>

class TicTacToe : public QWidget {
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr);

    private slots:
        void buttonClicked();
    void checkWin();

private:
    QPushButton *buttons[3][3];
    QLabel *playerLabel;
    char currentPlayer;
    bool gameWon;
};

#endif // TICTACTOE_H