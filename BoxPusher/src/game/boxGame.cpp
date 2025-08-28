#include "gameSystem.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({MapLength*BlockSize,MapWidth*BlockSize}),L"推箱子");
    if(initGame()==-1){
        logger.log("initGame() failed");
        return EXIT_FAILURE;
    }
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
                if(!box->sunk)
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
                (*p_player).move({0,1}, hitBoxList);
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S) 
                (*p_player).move({0,-1}, hitBoxList);
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A) 
                (*p_player).move({-1,0}, hitBoxList);
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) 
                (*p_player).move({1,0}, hitBoxList);
            // press r to reset game
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R) {
                if(resetGame()==-1){
                    logger.log("resetGame() failed");
                    return EXIT_FAILURE;
                }
            }
            // press e to push the box
            if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::E) {
                sf::Vector2f targetLoc=(*p_player).getBoxAt();
                if (boxMap.find(vecToFloat(targetLoc)) != boxMap.end()) { // 如果找到了
                    sf::Vector2f pushed_pos;
                    std::shared_ptr<Box> box = boxMap[vecToFloat(targetLoc)];
                    if(box->getPushed((*p_player).direction, waterMap,hitBoxList,pushed_pos)){
                        boxMap.insert({vecToFloat(pushed_pos),box});
                        boxMap.erase(vecToFloat(targetLoc));
                        hitboxDirty = true;
                    }
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
            window.draw(box->sprite);
        }
        // Draw Player
        window.draw((*p_player).sprite);
        
        window.display();
    }

    return EXIT_SUCCESS;
}