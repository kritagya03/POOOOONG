#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "Dashboard.h"
#include "Constants.h"

class Player{
private:
    AnimationWindow& window;
    bool player1;

    int width;
    int height;
    Point topLeftCorner;
    int dashboard_height;

public:
    Player(AnimationWindow& win, bool player1);
    void DrawPlayer();
    void MovePlayer();
    void run();

    Point getTopLeftCorner();
    int getHeight();
    int getWidth();
};