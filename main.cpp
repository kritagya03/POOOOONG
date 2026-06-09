#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "Player.h"
#include "Dashboard.h"
#include "Ball.h"
#include "Constants.h"

int main() {

    // game window
    AnimationWindow window (WINDOW_X, WINDOW_Y , WINDOW_WIDTH , WINDOW_HEIGHT ,"PONG");

    //create objects
    Player player1 (window, true);
    Player player2 (window, false);
    Ball ball(window, player1, player2);
    Dashboard dashboard (window, ball);

    //game
    while(!window.should_close()){
        dashboard.run();
        ball.run();
        player1.run();
        player2.run();

        window.next_frame();
    }

    return 0;
}

/*
int xPosition = 0;
    bool goingRight = true;
    while(!window.should_close()) {

        if (xPosition+100>=window.width() || xPosition<=0){
            if (xPosition<=0){
                xPosition+=5;
                goingRight=true;
            } else {
                xPosition-=5;
                goingRight=false;
            }
        } else if (!goingRight){
            xPosition-=5;
        } else if (goingRight){
            xPosition+=5;
        } else {
            std::cout << "Not entering if statements :(";
        }
        


        Point position {xPosition, 100};
        window.draw_rectangle(position, 100, 100);


        window.next_frame();
    }

*/
