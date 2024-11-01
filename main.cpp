#include <iostream> // Include directive for input/output stream
#include <SFML/Graphics.hpp> // Include directive for SFML graphics library
#include "functions.cpp"
#include "newfunctions.h"
#include <iomanip>
#include <cmath>


int main() {
    const int window_width = 700;
    const int window_height = 400;
    const float circle_radius = 150.0f;
    int num_balls = 18;
    float ball_radius = 7.0f;
    double gravity = 0.0001;
    bool done = false;

    sf::Sprite reload;
    sf::Texture reloadtext;
    reloadtext.loadFromFile("reload.png");
    reload.setTexture(reloadtext);
    reload.scale(0.1,0.1);
    reload.setPosition(window_width / 4 + 130, window_height / 2 - 170);

    sf::Sprite upbut;
    sf::Texture upbuttext;
    upbuttext.loadFromFile("up.png");
    upbut.setTexture(upbuttext);
    upbut.scale(0.3,0.3);
    upbut.setPosition(window_width / 4 - 190, window_height / 2 - 190);

    sf::Sprite downbut;
    sf::Texture downbuttext;
    downbuttext.loadFromFile("down.png");
    downbut.setTexture(downbuttext);
    downbut.scale(0.318,0.318);
    downbut.setPosition(window_width / 4 - 192, window_height / 2 - 140);

    sf::Sprite upgrav;
    upgrav.setTexture(upbuttext);
    upgrav.setScale(0.3,0.3);
    upgrav.setPosition(window_width - 70, window_height / 2 - 190);

    sf::Sprite dgrav;
    dgrav.setTexture(downbuttext);
    dgrav.setScale(0.318,0.318);
    dgrav.setPosition(window_width - 70, window_height / 2 - 140);




    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Gabriel\\CLionProjects\\Balls\\Roboto-Medium.ttf")){
        std::cout << "error" << std::endl;
    }
    sf::Text BallCount;
    BallCount.setFont(font);
    BallCount.setString("Balls:");
    BallCount.setCharacterSize(40);
    BallCount.setFillColor(sf::Color::Black);
    BallCount.setPosition(window_width / 4 - 192, window_height / 2 + 140);

    sf::Text Num;
    Num.setFont(font);
    Num.setString(std::to_string(num_balls));
    Num.setCharacterSize(40);
    Num.setFillColor(sf::Color::Black);
    Num.setPosition(window_width / 4 - 90, window_height / 2 + 142);

    sf::Text GravityText;
    GravityText.setFont(font);
    GravityText.setString("Gravity: ");
    GravityText.setCharacterSize(40);
    GravityText.setFillColor(sf::Color::Black);
    GravityText.setPosition(window_width /2 + 30 , window_height / 2 - 160);
    sf::Text GravityNum;
    GravityNum.setFont(font);
    float res_grap = gravity * 10000;
    GravityNum.setString(std::to_string(res_grap));
    std::cout << res_grap << std::endl;
    GravityNum.setCharacterSize(40);
    GravityNum.setFillColor(sf::Color::Black);
    GravityNum.setPosition(window_width /2 + 190 , window_height / 2 - 160);


//graph for the balls, timexcollions



    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Bouncing Balls");

    std::vector<Ball> balls;
    sf::CircleShape boundry(circle_radius);
    boundry.setFillColor(sf::Color::Transparent);
    boundry.setPosition(window_width / 4 - boundry.getRadius(), window_height / 2 - boundry.getRadius());
    boundry.setOutlineThickness(2);
    boundry.setOutlineColor(sf::Color::Black);
    // Initialize balls
    initialize_balls(num_balls, circle_radius, ball_radius, balls);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if(reload.getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                        initialize_balls(num_balls, circle_radius, ball_radius, balls);
                    }
                    if(upbut.getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                        num_balls += 1;
                    }
                    if(downbut.getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                        num_balls -= 1;
                    }
                    if(upgrav.getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                        gravity += .0001;
                    }
                    if(dgrav.getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                        gravity -= .0001;
                    }
                }
            }
        }

        // Update balls
        for (auto& ball : balls) {
            ball.update(gravity);
        }
        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                if ((balls[i].isColliding(balls[j]))) {
                    balls[i].resolveCollision(balls[j]);
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(boundry);
        window.draw(reload);
        window.draw(upbut);
        window.draw(downbut);
        window.draw(BallCount);
        //chnage to a system where  u add  tehse to a list and then draw like rthat
        window.draw(upgrav);
        window.draw(dgrav);
        window.draw(GravityText);
        float display_gravity =  (gravity*500);
        GravityNum.setString((formatFloat(display_gravity)));

        //std::cout << gravity;
        //make it anotehr variable taht is tied to grav mby???
        window.draw(GravityNum);
        Num.setString(std::to_string(num_balls));
        window.draw(Num);
        // Draw balls
        for (const auto& ball : balls) {
            sf::CircleShape shape(ball.radius);
            shape.setPosition(ball.x +(window_width / 4) - ball.radius, ball.y + (window_height / 2) - ball.radius);
            shape.setFillColor(ball.color);
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}
