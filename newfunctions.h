//
// Created by Gabriel on 5/18/2024.
//

#ifndef BALLS_NEWFUNCTIONS_H
#define BALLS_NEWFUNCTIONS_H

#endif //BALLS_NEWFUNCTIONS_H

#include <iostream>
#include <SFML/Graphics.hpp> // Include directive for SFML graphics library
#include <cmath>
#include <iomanip>
#include <vector>
#include <sstream>



class Ball {
public:
    float x, y; // Position
    float vx, vy; // Velocity
    float radius;
    sf::Color color;
    float circle_radius;

    Ball(float x, float y, float vx, float vy, float radius, sf::Color color, float cr)
            : x(x), y(y), vx(vx), vy(vy), radius(radius), color(color), circle_radius(cr) {}

    void update(double gravity) {
        // Update position
        x += vx;
        y += vy;
        //gravity
        vy += gravity;

        // Bounce off walls (circle boundary)
        float distance = std::sqrt(x * x + y * y);
        if (distance + radius >= circle_radius) {
            float angle = std::atan2(y, x);
            x = (circle_radius - radius) * std::cos(angle);
            y = (circle_radius - radius) * std::sin(angle);
            // Reflect velocity
            float dot = vx * std::cos(angle) + vy * std::sin(angle);
            vx -= 2 * dot * std::cos(angle);
            vy -= 2 * dot * std::sin(angle);
            //energy loss
            vx = vx * 0.9;
            vy = vy * 0.9;
        }

    }
    bool isColliding(const Ball& b) {
        float dx = b.x - x;
        float dy = b.y - y;
        float distance = std::sqrt(dx * dx + dy * dy);
        return distance < (radius + b.radius);
    }

    void resolveCollision(Ball& b) {
        // std::cout << "Collison" << std::endl;
    }

};

void initialize_balls(int num_balls, float circle_radius, float ball_radius, std::vector<Ball> &balls){
    balls.clear();
    for (int i = 0; i < num_balls; ++i) {
        float angle = i * (2 * 3.14159f / num_balls);
        float x = circle_radius * std::cos(angle);
        float y = circle_radius * std::sin(angle);
        float vx = 1.10f; // initial velocity
        float vy = 1.10f;
        sf::Color color(100,100,100); // or any other color
        balls.emplace_back(x, y, vx, vy, ball_radius , color,circle_radius); // Adjust radius as needed
    }
};
std::string formatFloat(float value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << value;  // Adjust precision as needed
    std::string str = out.str();

    // Remove trailing zeros and potential remaining decimal point
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') str.pop_back();

    return str;
}