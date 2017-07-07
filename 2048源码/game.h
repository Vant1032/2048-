#ifndef GAME_H
#define GAME_H

#include <QWidget>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    void paintEvent(QPaintEvent *event);
    void sui();
    bool go();
    void keyPressEvent(QKeyEvent *event);
    void up();
    void down();
    void left();
    void right();
    bool isOver();
    void reset();
private slots:
    void on_reset_button_clicked();


private:
    Ui::Game *ui;

};

#endif // GAME_H
