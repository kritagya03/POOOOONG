#include "Player.h"
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

Player::Player(AnimationWindow& win, bool player1) : window{win} , player1{player1} {
    width = int(win.width()/60);
    height = int(win.height()/8);

    if (player1){
        topLeftCorner = {0,int(window.height()/2)};
    } else {
        topLeftCorner = {int(window.width()-width),int(window.height()/2)};
    }

    dashboard_height= DASHBOARD_HEIGHT;
}

void Player::DrawPlayer() {

    random_device rd;    
    default_random_engine engine (rd());
    uniform_int_distribution dist(1,225);

    int red = dist(engine);
    int green = dist(engine);
    int blue = dist(engine);

    Color color{static_cast<unsigned char>(red),
        static_cast<unsigned char>(green),
        static_cast<unsigned char>(blue)};

    if (player1){
        window.draw_rectangle(topLeftCorner, width, height, Color::red, Color::white);
    } else {
        window.draw_rectangle(topLeftCorner, width, height, Color::blue, Color::white);
    }

}

void Player::MovePlayer() {
    if (player1){
        if(window.is_key_down(KeyboardKey::W) && topLeftCorner.y>=dashboard_height){
            topLeftCorner.y-=8;
        } else if (window.is_key_down(KeyboardKey::S) && 
                topLeftCorner.y+height<window.height()){

            topLeftCorner.y+=8;
        }

    } else {
        if(window.is_key_down(KeyboardKey::UP) && topLeftCorner.y>=dashboard_height){
            topLeftCorner.y-=8;
        } else if (window.is_key_down(KeyboardKey::DOWN) && 
                topLeftCorner.y+height<window.height()){

            topLeftCorner.y+=8;
        }
    }
}

Point Player::getTopLeftCorner() {
    return topLeftCorner;
}

int Player::getHeight() {
    return height;
}

int Player::getWidth() {
    return width;
}

void Player::run() {
    DrawPlayer();
    MovePlayer();
}