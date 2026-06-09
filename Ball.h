#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "Player.h"
#include "Dashboard.h"
#include "Constants.h"

class Player;
class Dashboard;

class Ball{
private:
    AnimationWindow& window;
    Player& player1;
    Player& player2;
    Point topLeftCornerPlayer1;
    Point topLeftCornerPlayer2;
    int dashboard_height;

    Point position;
    const int radius = 6;
    int right_speed;
    int bottom_speed;
    const int speed_increase = 1;

    bool gameStart = false;
    bool gameOver = false;
   
public:
    Ball(AnimationWindow& win, Player& player1, Player& player2);
    void DrawBall();
    void MoveBall();
    bool BallCollisionHorizontal();
    bool BallCollisionVertical();
    void run();

    bool GetGameOver();
    void SetGameStart(bool state);
    void SetGameOver(bool state);
    void SetPosition(Point pos);
    void SetRightSpeed(int speed);
    void SetBottomSpeed(int speed);
    bool player1win;
};