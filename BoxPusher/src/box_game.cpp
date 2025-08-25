#include <SFML/Graphics.hpp>
#include "textureLoader.h"
#include "mapLoader.h"
#include "player.h"
int main()
{
    // SFML 3.x 语法：使用 {} 初始化或 Vector2u
    sf::RenderWindow window(sf::VideoMode({512, 384}), "我的推箱子游戏!");
    std::unordered_map<TextureName, sf::Texture> texture_map;
    if(load_texture(texture_map)){
        return EXIT_FAILURE;
    }
    std::vector<std::vector<int>> texCategoryMap = loadFromCSV("./resources/maps/level001.csv");
    std::vector<std::vector<sf::Sprite>> spriteMap;
    std::vector<sf::FloatRect> wallBoundsMap;
    sf::Texture playerTex=texture_map[TextureName::Wall_Block];
    Player player(playerTex);
    player.sprite.setPosition({100, 100});  
    player.sprite.setScale({0.5f, 0.5f});  
    player.sprite.setOrigin({playerTex.getSize().x / 2.f, playerTex.getSize().y / 2.f}); // 设置中心为原点
    int x=0,y=0;
    for (auto& row : texCategoryMap){
        std::vector<sf::Sprite> spriteRow;
        x=0;
        for (auto t : row){     
            sf::Sprite sprite(texture_map[TextureName(t)]);
            sprite.setScale({0.25f, 0.25f});
            sprite.setPosition({64.f*x,64.f*y});
            spriteRow.push_back(sprite);
            if(t >= 10){
                wallBoundsMap.push_back(sprite.getGlobalBounds());
            }
            x++;
        }
        spriteMap.push_back(spriteRow);
        y++;
    }
    sf::Clock clock;
    // Render the window
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        // SFML 3.x 事件处理方式
        while (auto event = window.pollEvent())
        {
            // 使用 event->type 来访问事件类型
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
                window.close();
        }
        // Flush the window
        window.clear();
         // 绘制地图底层
        for(auto& row : spriteMap){
            for(auto& sprite : row){
                window.draw(sprite);
            }
        }
        player.update(deltaTime, wallBoundsMap);
        window.draw(player.sprite);
    
        window.display();
    }

    return 0;
}