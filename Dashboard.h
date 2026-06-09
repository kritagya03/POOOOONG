#pragma once
#include "std_lib_facilities.h"
#include "Constants.h"
#include "Player.h"
#include "Ball.h"
#include "AnimationWindow.h"
#include "widgets\Button.h"
#include "widgets\DropdownList.h"
#include "widgets\TextInput.h"

class Ball;

class Dashboard {
private:
    AnimationWindow& window;
    Ball& ball;

    int player1_points = 0;
    int player2_points = 0;
    const int height;
    const int width;
    string text_message_front = "Welcome to Pong!      Player 1: ";
    string text_message_middle = " points       Player 2: ";
    string text_message_end = " points";

    //GUI
    TDT4102::TextInput message 
    {{0,0}, static_cast<unsigned int>(width/2.3), static_cast<unsigned int>(height), text_message_front +
    to_string(player1_points) + text_message_middle + to_string(player2_points) + text_message_end};

    TDT4102::Button startButton
    {{int(width/2.3)+2,0}, static_cast<unsigned int>(width/10), static_cast<unsigned int>(height), "Start Game"};

    void callbackStartButton();

    TDT4102::Button restart 
    {{int(width/2.3 + width/10)+2,0},static_cast<unsigned int>(width/10), static_cast<unsigned int>(height), "Restart"};

    void callbackRestart();

public:
    Dashboard(AnimationWindow& win, Ball& ball);
    
    void DrawBoard();
    void UpdateWin();
    void run();
};