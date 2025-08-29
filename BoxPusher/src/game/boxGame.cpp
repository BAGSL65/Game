#include "gameSystem.h"

int playingLevel(sf::RenderWindow& window){
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
            if(resetLevel() == -1){
                logger.log("resetLevel() failed");
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

    return EXIT_SUCCESS;
}

int loadingLevel(sf::RenderWindow& window){
    // Flush the window
    window.clear();
    while(auto event = window.pollEvent())
    {
        // can close the window to exit game
        if (event->is<sf::Event::Closed>())
            window.close();
        // debug press enter as load finished
        if (event->is<sf::Event::KeyPressed>()&&event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) 
            gameState = GameState::Playing;
    }
    // 创建"Loading"文本
    static sf::Text loadingText(font);
    loadingText.setFont(font);
    loadingText.setCharacterSize(24);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setStyle(sf::Text::Bold | sf::Text::Italic);
    // 设置文本位置到屏幕右下角
    sf::FloatRect textBounds = loadingText.getLocalBounds();
    loadingText.setPosition({static_cast<float>(window.getSize().x) - textBounds.size.x - 20, 
                           static_cast<float>(window.getSize().y) - textBounds.size.y - 20});
    
    // 动态加载效果
    static int LoadingTick = -1;
    static sf::Clock clock;
    if (clock.getElapsedTime().asMilliseconds() > 500) { // 每300ms更新一次
        LoadingTick = (LoadingTick+1) % 7; // 0, 1, 2, 3, 4, 5, 6循环
        clock.restart();
    }
    
    static std::string loadingString;
    for (int i = 0; i <= LoadingTick; i++) {
        if (i == 0) loadingString.clear();
        else if (i == 1) loadingString = "Lo";
        else if (i == 2) loadingString += "ad";
        else if (i == 3) loadingString += "ing";
        else loadingString += ".";
    }
    
    loadingText.setString(loadingString);
    // 重新计算位置以保持右下角对齐
    textBounds = loadingText.getLocalBounds();
    loadingText.setPosition({static_cast<float>(window.getSize().x) - textBounds.size.x - 20, 
                           static_cast<float>(window.getSize().y) - textBounds.size.y - 20});
    
    window.draw(loadingText);
    window.display();
    
    return EXIT_SUCCESS;
}
int main()
{
    sf::RenderWindow window(sf::VideoMode({MapLength*BlockSize,MapWidth*BlockSize}),L"推箱子");
    if(initLevel()==-1){
        logger.log("initLevel() failed");
        return EXIT_FAILURE;
    }
    // Render the window
    while (window.isOpen())
    {   
        if(gameState == GameState::Playing)
        {
            playingLevel(window);
        }
        else if (gameState == GameState::Loading)
        {
            loadingLevel(window);
        }
        
    }

    return EXIT_SUCCESS;
}