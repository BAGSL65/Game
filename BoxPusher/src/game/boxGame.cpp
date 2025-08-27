#include <SFML/Graphics.hpp>
#include "textureLoader.h"
#include "mapLoader.h"
#include "player.h"
#include "water.h"
#include "box.h"
#include "logger.h"
#include <unordered_map>

// 在这里定义地图长宽和贴图大小
const int BlockSize = 64;
const int MapLength = 8;
const int MapWidth = 6;
float vecToFloat(sf::Vector2f vec);
sf::Vector2f conv2iTo2f(sf::Vector2i vec);
int main()
{
    const char* path = "../../log/log.txt";
    Logger logger(path);

    sf::RenderWindow window(sf::VideoMode({MapLength*BlockSize,MapWidth*BlockSize}),L"推箱子");

    std::unordered_map<TextureName, sf::Texture> texture_map;
    try
    {
        load_texture(texture_map);
    }
    catch(LoadException& e)
    {
        logger.log(e.what());
        return EXIT_FAILURE;
    }
    std::vector<std::vector<int>> mapData;
    try
    {
        mapData = loadFromCSV("../../resources/maps/level001.csv");
    }
    catch (const MapLoadException& e)
    {
        logger.log(e.what());
        return EXIT_FAILURE;
    }
    std::vector<std::vector<sf::Sprite>> sBlockList2d;
    std::vector<sf::FloatRect> sBlockBoundsList;
    // 使用智能指针（更安全）
    std::vector<std::shared_ptr<Water>> waterList;
    std::vector<std::shared_ptr<Box>> boxList;
    std::unordered_map<float, std::shared_ptr<Water>> waterMap;
    std::unordered_map<float, std::shared_ptr<Box>> boxMap;
    
    sf::Texture playerTex=texture_map[TextureName::Wall_Block];
    sf::Sprite p_sprite(playerTex);
    float block_scale = 0.25f;
    sf::Vector2f p_block_pos;
    {
        sf::Vector2i pos = {1,2};
        p_block_pos = conv2iTo2f({pos.x*BlockSize,pos.y*BlockSize});
        float scale = 0.2f;
        float origin_x = playerTex.getSize().x / 2.f;
        float origin_y = playerTex.getSize().y / 2.f;
        p_sprite.setOrigin({origin_x,origin_y}); // 设置中心为原点
        p_sprite.setScale({scale,scale}); 
        p_sprite.setPosition({p_block_pos.x+origin_x*block_scale,p_block_pos.y+origin_y*block_scale});  
    }
    Player player(p_sprite,p_block_pos);

    int x=0,y=0;

    // Init Map
    for (auto& row : mapData){
        std::vector<sf::Sprite> sBlockRow;
        x=0;
        for (auto t : row){
            sf::Sprite sprite(texture_map[TextureName(t)]);
            sf::Vector2f posVec = conv2iTo2f({BlockSize*x,BlockSize*y});

            sprite.setScale({block_scale, block_scale});
            sprite.setPosition(posVec);
            if(t >= 10)
            {
                sBlockBoundsList.push_back(sprite.getGlobalBounds());
            }
            else if(t == 1)
            {
                auto water = std::make_shared<Water>(sprite,posVec,BlockSize);
                waterMap[vecToFloat(posVec)] = water;
                waterList.push_back(water);
            }
            else if(t == 2)
            {
                sprite.setTexture(texture_map[TextureName::Grass]);

                sf::Sprite box_sprite(texture_map[TextureName::Box]);
                float scale = 0.20f;
                float origin_x = texture_map[TextureName::Box].getSize().x / 2.f;
                float origin_y = texture_map[TextureName::Box].getSize().y / 2.f;
                
                // set origin center, box scale, set position in the block center
                box_sprite.setOrigin({origin_x,origin_y});
                box_sprite.setScale({scale,scale});
                box_sprite.setPosition({posVec.x+origin_x*block_scale,posVec.y+origin_y*block_scale}); 
                
                auto box = std::make_shared<Box>(box_sprite,posVec,BlockSize);  
                boxMap[vecToFloat(posVec)] = box;
                boxList.push_back(box);
            }
            sBlockRow.push_back(sprite);
            x++;
        }
        sBlockList2d.push_back(sBlockRow);
        y++;
    }
    //load hitbox
    std::vector<sf::FloatRect> hitBoxList;
    bool hitboxDirty = true;
    // Render the window
    while (window.isOpen())
    {   
        if(hitboxDirty){
            hitBoxList = sBlockBoundsList;
            for(const auto& water: waterList){
                if(!water->boxed)
                    hitBoxList.push_back(water->getFloatRect());
            }
            for(const auto& box: boxList){
                if(!box->sinked)
                    hitBoxList.push_back(box->getFloatRect());
            }
            hitboxDirty = false;
        }
        
        while (auto event = window.pollEvent())
        {
            // 使用 event->type 来访问事件类型
            if (event->is<sf::Event::Closed>())
                window.close();
            // press esc key to exit game
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
                window.close();
            // press w a s d to move the player
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W) 
                player.move({0,1}, hitBoxList);
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S) 
                player.move({0,-1}, hitBoxList);
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A) 
                player.move({-1,0}, hitBoxList);
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) 
                player.move({1,0}, hitBoxList);
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::E) {
                sf::Vector2f targetLoc=player.getBoxAt(BlockSize);
                auto it = boxMap.find(vecToFloat(targetLoc)); // 查找键
                if (it != boxMap.end()) { // 如果找到了
                    it->second->getPushed(player.direction, BlockSize/*, hitBoxList*/); // 建议将hitBoxList也传入，用于推动时的碰撞检测
                    hitboxDirty = true;
                }
            }          
        }
        // Flush the window
        window.clear();

        // Draw Map
        for(const auto& row : sBlockList2d)
        {
            for(auto& obj : row)
            {
                window.draw(obj);
            }
        }
        for(const auto& water: waterList)
        {
            //if(water->boxed) {};
        }
        for(const auto& box : boxList)
        {
            if(!box->sinked)
            {
                window.draw(box->sprite);
            }
        }
        // Draw Player
        window.draw(player.sprite);
        
        window.display();
    }

    return 0;
}

float vecToFloat(sf::Vector2f vec)
{
    return (int)vec.x/BlockSize*BlockSize + (int)vec.y/BlockSize*MapLength*BlockSize;
}

sf::Vector2f conv2iTo2f(sf::Vector2i vec){
    return sf::Vector2f((float)vec.x,(float)vec.y);
}