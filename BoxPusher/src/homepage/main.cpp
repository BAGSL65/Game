#include <SFML/Graphics.hpp>
#include "textureLoader.h"
int main()
{
    // SFML 3.x 语法：使用 {} 初始化或 Vector2u
    sf::RenderWindow window(sf::VideoMode({800, 600}), "我的推箱子游戏!");
    // Create a circle shape
    sf::CircleShape s_circle(100.f,10);
    s_circle.setPosition({300, 250}); // SFML 3.x 语法
    // Set the circle color
    s_circle.setFillColor(sf::Color::Black);
    // Create a triangle shape
    sf::ConvexShape s_triangle(3);
    s_triangle.setPoint(0, sf::Vector2f(400, 100));  // 顶点
    s_triangle.setPoint(1, sf::Vector2f(200, 446.4));  // 左下角
    s_triangle.setPoint(2, sf::Vector2f(600, 446.4));  // 右下角
    // Set the triangle color and outline
    s_triangle.setFillColor(sf::Color::Yellow);
    s_triangle.setOutlineThickness(10);
    s_triangle.setOutlineColor(sf::Color(224, 40, 216));
    s_triangle.setPosition(sf::Vector2f(400, 331));
    s_triangle.setOrigin(sf::Vector2f(400, 331));
    // Set some properties about rotation
    float angle = 0;
    sf::Clock clock;
    // Render the window
    while (window.isOpen())
    {
        // SFML 3.x 事件处理方式
        while (auto event = window.pollEvent())
        {
            // 使用 event->type 来访问事件类型
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        s_triangle.rotate(sf::degrees(360.f * clock.restart().asSeconds())); // 每秒90度

        // Flush the window
        window.clear();
        window.draw(s_triangle);
        window.draw(s_circle);
        window.display();
    }

    return 0;
}