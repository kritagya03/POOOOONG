#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "Ball.h"

Ball::Ball (AnimationWindow& win, Player& player1, Player& player2): 
window{win}, player1{player1}, player2{player2} {
    
    position = {int(win.width()/2), int(win.height()/2)};

    topLeftCornerPlayer1 = player1.getTopLeftCorner();
    topLeftCornerPlayer2 = player2.getTopLeftCorner();

    dashboard_height = DASHBOARD_HEIGHT;


    random_device rd;    
    default_random_engine engine (rd());
    uniform_int_distribution dist(-5,5);

    right_speed = dist(engine);
    bottom_speed = dist(engine);

    while (right_speed == 0 || bottom_speed == 0) {
        right_speed = dist(engine);
        bottom_speed = dist(engine);
    }

    cout << right_speed << bottom_speed;
}

void Ball::DrawBall (){
    
    random_device rd;    
    default_random_engine engine (rd());
    uniform_int_distribution dist(0,255);

    int red = dist(engine);
    int green = dist(engine);
    int blue = dist(engine);

    Color color{static_cast<unsigned char>(red),
        static_cast<unsigned char>(green),
        static_cast<unsigned char>(blue)};

    window.draw_circle(position, radius, color, Color::white);
}

void Ball::MoveBall(){

    topLeftCornerPlayer1 = player1.getTopLeftCorner();
    topLeftCornerPlayer2 = player2.getTopLeftCorner();

    if (BallCollisionHorizontal()) {
        right_speed = - right_speed - speed_increase*(right_speed/abs(right_speed));
        bottom_speed += speed_increase*(bottom_speed/abs(bottom_speed));
    } 
    
    if (BallCollisionVertical()) {
        bottom_speed = - bottom_speed;
    }

    if (position.x < window.width() && position.x > 0 && gameStart) {
        position.x += right_speed;
        position.y += bottom_speed;
    
    } else if (position.x >= window.width()){
        player1win = true;
        gameOver = true; 
    
    } else if (position.x <= 0) {
        player1win = false;
        gameOver = true;
    }

}

bool Ball::BallCollisionHorizontal() {
    Point ball_right = {position.x + radius, position.y};
    Point ball_left = {position.x - radius, position.y};

    Point bottomLeftCornerPlayer1 = {topLeftCornerPlayer1.x, topLeftCornerPlayer1.y+player1.getHeight()};
    Point bottomLeftCornerPlayer2 = {topLeftCornerPlayer2.x, topLeftCornerPlayer2.y+player1.getHeight()};

    //check right
    if (ball_right.x >= topLeftCornerPlayer2.x &&
        (ball_right.y >= topLeftCornerPlayer2.y &&
        ball_right.y <= bottomLeftCornerPlayer2.y)) {
            
        return true;
    
    //check left
    } else if (ball_left.x <= topLeftCornerPlayer1.x + player1.getWidth() &&
            (ball_left.y >= topLeftCornerPlayer1.y &&
            ball_left.y <= bottomLeftCornerPlayer1.y)){

        return true;

    //no instances
    } else {

        return false;
    }
}

bool Ball::BallCollisionVertical() {
    Point ball_top = {position.x, position.y-radius};
    Point ball_bottom = {position.x, position.y+radius};

    //check top
    if(ball_top.y <= dashboard_height) {
        
        return true;

    //check bottom
    } else if (ball_bottom.y >= window.height()) {
        
        return true;
    
    //no instance
    } else {
        return false;
    }
}

bool Ball::GetGameOver() {
    return gameOver;
}

void Ball::SetGameStart(bool state) {
    gameStart = state;
}

void Ball::SetGameOver(bool state) {
    gameOver = state;
}

void Ball::SetPosition(Point pos) {
    position = pos;
}

void Ball::SetRightSpeed(int speed) {
    right_speed = speed;
}

void Ball::SetBottomSpeed(int speed) {
    bottom_speed = speed;
}

void Ball::run() {
    DrawBall();
    MoveBall();
}

