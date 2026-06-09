#include "Dashboard.h"

Dashboard::Dashboard(AnimationWindow& win, Ball& ball) : window{win}, ball{ball},
height{DASHBOARD_HEIGHT}, width{WINDOW_WIDTH} {

    //add GUI elements
    window.add(message);
    window.add(startButton);
    startButton.setCallback(std::bind(&Dashboard::callbackStartButton, this));
    window.add(restart);
    restart.setCallback(std::bind(&Dashboard::callbackRestart, this));
}

void Dashboard::DrawBoard(){
    window.draw_rectangle({0,0}, WINDOW_WIDTH, WINDOW_HEIGHT, Color::black);
    window.draw_rectangle({0,0}, width, height, Color::dark_red);

    random_device rd;    
    default_random_engine engine (rd());
    uniform_int_distribution dist1(0,WINDOW_WIDTH);
    uniform_int_distribution dist2(0,WINDOW_HEIGHT);

    window.draw_line({dist1(engine),dist2(engine)}, {dist1(engine),dist2(engine)},
    Color::white);
    window.draw_line({dist1(engine),dist2(engine)}, {dist1(engine),dist2(engine)},
    Color::white);
}

void Dashboard::callbackStartButton() {
    ball.SetGameStart(true);
}

void Dashboard::callbackRestart() {
    ball.SetPosition({int(window.width()/2),int(window.height()/2)});
    ball.SetGameOver(false);
    ball.SetGameStart(false);

    player1_points = 0;
    player2_points = 0;

    message.setText(text_message_front + to_string(player1_points) + 
    text_message_middle + to_string(player2_points) + text_message_end);

    random_device rd;    
    default_random_engine engine (rd());
    uniform_int_distribution dist(-5,5);

    int right_speed = dist(engine);
    int bottom_speed = dist (engine);

    while (right_speed == 0 || bottom_speed == 0) {
        right_speed = dist(engine);
        bottom_speed = dist (engine);
    }

    ball.SetRightSpeed(right_speed);
    ball.SetBottomSpeed(bottom_speed);
}

void Dashboard::UpdateWin() {
    if (ball.GetGameOver()) {
        if (ball.player1win) {
            player1_points++;
        } else {
            player2_points++;
        }

        message.setText(text_message_front + to_string(player1_points) + 
        text_message_middle + to_string(player2_points) + text_message_end);

        ball.SetPosition({int(window.width()/2),int(window.height()/2)});
        ball.SetGameOver(false);
        ball.SetGameStart(false);

        random_device rd;    
        default_random_engine engine (rd());
        uniform_int_distribution dist(-5,5);

        int right_speed = dist(engine);
        int bottom_speed = dist (engine);

        while (right_speed == 0 || bottom_speed == 0) {
            right_speed = dist(engine);
            bottom_speed = dist (engine);
        }

        ball.SetRightSpeed(right_speed);
        ball.SetBottomSpeed(bottom_speed);
        }
}

void Dashboard::run() {
    DrawBoard();
    UpdateWin();
}