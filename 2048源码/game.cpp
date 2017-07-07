#include "game.h"
#include "ui_game.h"
#include <QPixmap>
#include <QPalette>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
#include <QKeyEvent>
#include <string.h>
#include <QTime>
#include <Windows.h>
using namespace std;
int fen = 0;
int mmap[4][4];
Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    this->setFixedSize(722, 537);
    QPixmap pix(":/tupian/backimg.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(pix));
    this->setPalette(palette);
    memset(mmap, 0, sizeof(mmap));
    srand(time(0));
    sui();
    sui();
}

Game::~Game()
{
    delete ui;
}
void Game::paintEvent(QPaintEvent *event){
    Sleep(30);
    QImage img;
    img.load(":/tupian/" + QString::number(mmap[0][0]) + ".png");
    ui->show1->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[0][1]) + ".png");
    ui->show2->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[0][2]) + ".png");
    ui->show3->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[0][3]) + ".png");
    ui->show4->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[1][0]) + ".png");
    ui->show5->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[1][1]) + ".png");
    ui->show6->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[1][2]) + ".png");
    ui->show7->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[1][3]) + ".png");
    ui->show8->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[2][0]) + ".png");
    ui->show9->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[2][1]) + ".png");
    ui->show10->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[2][2]) + ".png");
    ui->show11->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[2][3]) + ".png");
    ui->show12->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[3][0]) + ".png");
    ui->show13->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[3][1]) + ".png");
    ui->show14->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[3][2]) + ".png");
    ui->show15->setPixmap(QPixmap::fromImage(img));
    img.load(":/tupian/" + QString::number(mmap[3][3]) + ".png");
    ui->show16->setPixmap(QPixmap::fromImage(img));
    ui->score->setText(QString::number(fen));

}
void Game::reset(){
    memset(mmap, 0, sizeof(mmap));
    fen = 0;
    sui();
    sui();
}

bool Game::go(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(mmap[i][j] == 0)return true;
        }
    }
    return false;
}
bool Game::isOver(){
    int k[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int ni, nj;
    for(int i = 0; i < 4; i++){
        for(int j = 0; i < 4; j++){
            if(mmap[i][j] == 0)return false;
            for(int s = 0; s < 4; s++){
                ni = i + k[s][0];
                nj = j + k[s][1];
                if(ni < 0 || ni > 3 || nj < 0 || nj > 3)continue;
                if(mmap[ni][nj] == 0)return false;
                if(mmap[i][j] == mmap[ni][nj])return false;
            }
        }
    }
    return true;
}

void Game::sui(){
    if(go() == false)return;
    int x, y;
    do{
        x = rand() % 4;
        y = rand() % 4;
        if(mmap[x][y] == 0){
            mmap[x][y] = (rand() % 20 == 4) ? 4 : 2;
            return;
        }
    }while(1);
}
void Game::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_W:
        up();
        break;
    case Qt::Key_S:
        down();
        break;
    case Qt::Key_D:
        right();
        break;
    case Qt::Key_A:
        left();
        break;
    }
    if(go() == false){
        if(QMessageBox::warning(this, "重来", "再试一次？", QMessageBox::Yes | QMessageBox::No) ==  QMessageBox::Yes){
            reset();
        }else this->close();
    }else sui();
}
void Game::up(){
    for(int k = 0; k < 3; k++){
        for(int x = 1; x < 4; x++){
          for(int y = 0; y < 4; y++){
            if(mmap[x - 1][y] == 0){
              mmap[x - 1][y] = mmap[x][y];
              mmap[x][y] = 0;
            }else {
              if(mmap[x - 1][y] == mmap[x][y]){
                mmap[x - 1][y] *= 2;
                mmap[x][y] = 0;
                fen += mmap[x - 1][y] * 4;
              }
            }
          }
        }
      }
}
void Game::down(){
    for(int k = 0; k < 3; k++){
        for(int x = 2; x >= 0; x--){
          for(int y = 0; y < 4; y++){
            if(mmap[x + 1][y] == 0){
              mmap[x + 1][y] = mmap[x][y];
              mmap[x][y] = 0;
            }else {
              if(mmap[x + 1][y] == mmap[x][y]){
                mmap[x + 1][y] *= 2;
                mmap[x][y] = 0;
                fen += mmap[x + 1][y] * 4;
              }
            }
          }
        }
      }
}
void Game::right(){
    for(int k = 0; k < 3; k++){
        for(int y = 2; y >= 0; y--){
          for(int x = 0; x < 4; x++){
            if(mmap[x][y + 1] == 0){
              mmap[x][y + 1] = mmap[x][y];
              mmap[x][y] = 0;
            }else {
              if(mmap[x][y + 1] == mmap[x][y]){
                mmap[x][y + 1] *= 2;
                mmap[x][y] = 0;
                fen += mmap[x][y + 1] * 4;
              }
            }
          }
        }
      }
}
void Game::left(){
    for(int k = 0; k < 3; k++){
        for(int x = 0; x < 4; x++){
          for(int y = 1; y < 4; y++){
            if(mmap[x][y - 1] == 0){
              mmap[x][y - 1] = mmap[x][y];
              mmap[x][y] = 0;
            }else {
              if(mmap[x][y - 1] == mmap[x][y]){
                mmap[x][y - 1] *= 2;
                mmap[x][y] = 0;
                fen += mmap[x][y - 1] * 4;
              }
            }
          }
        }
      }
}
void Game::on_reset_button_clicked()
{
    reset();
}

