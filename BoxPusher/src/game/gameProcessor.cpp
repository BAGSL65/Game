#include "gameProcessor.h"

int playingLevel(sf::RenderWindow& window){
    if(music.getStatus() == sf::SoundSource::Status::Stopped ||
        music.getStatus() == sf::SoundSource::Status::Paused) music.play();
    // Flush the window
    window.clear();
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
        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
            window.close();
        // press w a s d to move the player
        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W) 
            (*p_player).move({0,1}, hitBoxList);
        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S) 
            (*p_player).move({0,-1}, hitBoxList);
        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A) 
            (*p_player).move({-1,0}, hitBoxList);
        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) 
            (*p_player).move({1,0}, hitBoxList);
        // press r to reset game
        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R) {
            if(resetLevel() == -1){
                logger.log("resetLevel() failed");
                return EXIT_FAILURE;
            }
        }
        // press e to push the box
        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::E) {
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
    if(music.getStatus() == sf::SoundSource::Status::Playing) music.pause();
    // Flush the window
    window.clear();

    static sf::Clock big_clock;
    if (big_clock.getElapsedTime() > sf::seconds(4.5)) { // 每500ms更新一次
        gameState = GameState::Playing;
        return EXIT_SUCCESS;
    }

    while(auto event = window.pollEvent())
    {
        // can close the window to exit game
        if (event->is<sf::Event::Closed>())
            window.close();
        // debug press enter as load finished
        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) 
            gameState = GameState::Playing;
    }
    // 创建"Loading"文本
    static sf::Text loadingText(font);
    loadingText.setFont(font);
    loadingText.setCharacterSize(30);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setStyle(sf::Text::Bold | sf::Text::Italic);

    // 动态加载效果
    static int LoadingTick = 0;
    static sf::Clock clock;
    if (clock.getElapsedTime().asMilliseconds() > 250) { // 每500ms更新一次
        LoadingTick = (LoadingTick+1) % 9; // 0, 1, 2, 3, 4, 5...循环
        clock.restart();
    }

    static std::string loadingString;
    // Avoiding text shake, calculate and set the height in advance
    loadingString.clear();
    loadingString = "Loading...";
    loadingText.setString(loadingString);
    sf::FloatRect textBounds = loadingText.getLocalBounds();
    int weight = window.getSize().x;
    int height = window.getSize().y;
    float fixedX = static_cast<float>(weight) - 20 - textBounds.size.x;
    float fixedY = static_cast<float>(height) - 20 - textBounds.size.y;
    loadingText.setPosition({fixedX, fixedY});

    for (int i = 0; i <= LoadingTick; i++) {
        if (i == 0) loadingString.clear();
        else if (i == 1) loadingString = "Lo";
        else if (i == 2) loadingString += "ad";
        else if (i == 3) loadingString += "i";
        else if (i == 4) loadingString += "n";
        else if (i == 5) loadingString += "g";
        else loadingString += ".";
    }

    loadingText.setString(loadingString);
    textBounds = loadingText.getLocalBounds();
    // recalculate the x position
    fixedX = static_cast<float>(weight) - 20 - textBounds.size.x;
    loadingText.setPosition({fixedX, fixedY});
    window.draw(loadingText);
    window.display();
    
    return EXIT_SUCCESS;
}

int mainMenu(sf::RenderWindow &window)
{
    // Flush the window
    window.clear();

    enum class MenuState
    {
        START=0,
        OPTIONS=1,
        QUIT=2
    };
    float weight = window.getSize().x;
    float height = window.getSize().y;
    static MenuState menuState = MenuState::START;
    
    while(auto event = window.pollEvent())
    {
        // can close the window to exit game
        if (event->is<sf::Event::Closed>())
            window.close();
        // can close the window to exit game
        if (event->is<sf::Event::KeyPressed>() && 
        (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W ||
        event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up))
        {
            auto& sound = soundMap[SoundName::SwitchMenu];
            if(sound->getStatus() == sf::Sound::Status::Stopped){
                sound->stop();
            }
            sound->play();
            // avoid -1 % 3 calculate
            menuState = MenuState((static_cast<int>(menuState) + 3 - 1) % 3);
        }
        if (event->is<sf::Event::KeyPressed>() && 
        (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S ||
        event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down))
        {
            auto& sound = soundMap[SoundName::SwitchMenu];
            if(sound->getStatus() == sf::Sound::Status::Stopped){
                sound->stop();
            }
            sound->play();
            menuState = MenuState((static_cast<int>(menuState) + 1) % 3);
        }
        if (event->is<sf::Event::KeyPressed>() &&
        event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter)
        {
            auto& sound = soundMap[SoundName::EnterMenu];
            if(sound->getStatus() == sf::Sound::Status::Stopped){
                sound->stop();
            }
            sound->play();
            if(menuState == MenuState::START)
            {
                gameState = GameState::Loading;
                return EXIT_SUCCESS;
            }
            else if(menuState == MenuState::OPTIONS) 
            {
                gameState = GameState::Config;
                return EXIT_SUCCESS;
            }
            else if(menuState == MenuState::QUIT) window.close();
        }
    }

    static bool initialized = false;
    static sf::Text titleText(title_font);
    if(!initialized)
    {
        titleText.setCharacterSize(60);
        titleText.setFillColor(sf::Color::Yellow);
        titleText.setStyle(sf::Text::Bold | sf::Text::Italic);
        titleText.setOutlineColor(sf::Color::Black);
        titleText.setOutlineThickness(5);
        titleText.setString("BoxPusher");
        titleText.setOrigin(titleText.getLocalBounds().getCenter());
        titleText.setPosition({static_cast<float>(weight)/2.f,static_cast<float>(height)/2.f - 100});
    }
    static sf::Text titleOutline(title_font);
    if(!initialized)
    {
        titleOutline.setCharacterSize(60);
        titleOutline.setStyle(sf::Text::Bold | sf::Text::Italic);
        titleOutline.setOutlineColor(sf::Color::White);
        titleOutline.setOutlineThickness(10);
        titleOutline.setString("BoxPusher");
        titleOutline.setOrigin(titleOutline.getLocalBounds().getCenter());
        titleOutline.setPosition({static_cast<float>(weight)/2.f,static_cast<float>(height)/2.f - 100});
    }
    static sf::Text startText(font);
    if(!initialized)
    {
        startText.setCharacterSize(35);
        startText.setFillColor(sf::Color::Yellow);
        startText.setStyle(sf::Text::Bold);
        startText.setString("Start Game");
        startText.setOrigin(startText.getLocalBounds().getCenter());
        startText.setPosition({static_cast<float>(weight)/2.f,static_cast<float>(height)/2.f});
    }
    static sf::Text configText(font);
    if(!initialized)
    {
        configText.setCharacterSize(35);
        configText.setFillColor(sf::Color::Yellow);
        configText.setStyle(sf::Text::Bold);
        configText.setString("Options");
        configText.setOrigin(configText.getLocalBounds().getCenter());
        configText.setPosition({static_cast<float>(weight)/2.f,static_cast<float>(height)/2.f + 50});
    }
    static sf::Text quitText(font);
    if(!initialized)
    {
        quitText.setCharacterSize(35);
        quitText.setFillColor(sf::Color::Yellow);
        quitText.setStyle(sf::Text::Bold);
        quitText.setString("Quit Game");
        quitText.setOrigin(quitText.getLocalBounds().getCenter());
        quitText.setPosition({static_cast<float>(weight)/2.f,static_cast<float>(height)/2.f + 100});
    }
    static sf::Clock clock;
    static sf::Color tipcolor(255,255,255,75);
    static sf::Text tipText(font);
    if(!initialized)
    {
        tipText.setCharacterSize(15);
        tipText.setFillColor(tipcolor);
        tipText.setString("Up or Down to choose");
        tipText.setOrigin({tipText.getLocalBounds().size.x,tipText.getLocalBounds().size.y});
        tipText.setPosition({weight-10,height-10});
    }
    static sf::Text tipText2(font);
    if(!initialized)
    {
        tipText2.setCharacterSize(15);
        tipText2.setFillColor(tipcolor);
        tipText2.setString("Enter to select");
        tipText2.setOrigin({tipText2.getLocalBounds().size.x,tipText2.getLocalBounds().size.y});
        tipText2.setPosition({weight-35,height-30});
    }
    // Make the selectBox
    static sf::RectangleShape selectBox;
    if(!initialized)
    {
        selectBox.setFillColor(sf::Color(0,83,102)); 
        selectBox.setOutlineThickness(5);
        selectBox.setOutlineColor(sf::Color::Yellow); 
    }

    switch (menuState)
    {
    case MenuState::START:
        selectBox.setPosition(startText.getPosition());
        selectBox.setSize({startText.getLocalBounds().size.x + 30,startText.getLocalBounds().size.y + 5});
        selectBox.setOrigin(selectBox.getLocalBounds().getCenter());
        break;
    case MenuState::OPTIONS:
        selectBox.setPosition(configText.getPosition());
        selectBox.setSize({configText.getLocalBounds().size.x + 30,configText.getLocalBounds().size.y + 5});
        selectBox.setOrigin(selectBox.getLocalBounds().getCenter());
        break;
    case MenuState::QUIT:
        selectBox.setPosition(quitText.getPosition());
        selectBox.setSize({quitText.getLocalBounds().size.x + 30,quitText.getLocalBounds().size.y + 5});
        selectBox.setOrigin(selectBox.getLocalBounds().getCenter());
        break;
    }
    initialized = true;
    window.draw(titleOutline);
    window.draw(titleText);

    window.draw(selectBox);
    window.draw(startText);
    window.draw(configText);
    window.draw(quitText);

    
    static bool increase = true;
    if (clock.getElapsedTime() > sf::milliseconds(50))
    {
        clock.restart();

        int next_a = tipcolor.a;
        next_a += increase ? 5 : -5;
        if(next_a > 255){
            increase = !increase;
            next_a = 255;
        }
        if(next_a < 75){
            increase = !increase;
            next_a = 75;
        }
        tipcolor.a = next_a;
        tipText.setFillColor(tipcolor);
        tipText2.setFillColor(tipcolor);
    }
    window.draw(tipText);
    window.draw(tipText2);
    window.display();
    
    return EXIT_SUCCESS;
}

int config(sf::RenderWindow &window)
{
    // Flush the window
    window.clear();
    while(auto event = window.pollEvent())
    {
        if (event->is<sf::Event::KeyPressed>() && 
        event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
        {
            gameState = GameState::StartMenu;
        }
    }
    static bool initialized = false;
    static sf::Text configText(title_font);
    float weight = window.getSize().x;
    float height = window.getSize().y;
    if(!initialized)
    {
        configText.setCharacterSize(60);
        configText.setFillColor(sf::Color::Yellow);
        configText.setStyle(sf::Text::Bold | sf::Text::Italic);
        configText.setOutlineColor(sf::Color::Black);
        configText.setOutlineThickness(5);
        configText.setString("Config");
        // configText.setOrigin(configText.getLocalBounds().getCenter());
        configText.setPosition({20,20});
    }
    window.draw(configText);
    window.display();
    return EXIT_SUCCESS;
}
