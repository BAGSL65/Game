#include "gameSystem.h"
Logger logger(log_path);
GameState gameState = GameState::StartMenu;

std::vector<std::vector<sf::Sprite>> sBlockList2d;
std::vector<sf::FloatRect> sBlockBoundsList;
// Using autoptr for safety
std::vector<std::shared_ptr<Water>> waterList;
std::vector<std::shared_ptr<Box>> boxList;
std::unordered_map<float, std::shared_ptr<Water>> waterMap;
std::unordered_map<float, std::shared_ptr<Box>> boxMap;

std::vector<std::vector<int>> mapData;
std::unordered_map<TextureName, sf::Texture> texture_map;

sf::Texture playerTex;
std::unique_ptr<sf::Sprite> p_sprite;
std::unique_ptr<Player> p_player;
bool hitboxDirty = true;

sf::Font font;
sf::Font title_font;

sf::Music music;
sf::SoundBuffer buffer;
std::unordered_map<SoundName,sf::SoundBuffer> soundBufferMap;
std::unordered_map<SoundName,std::shared_ptr<sf::Sound>> soundMap;

sf::FloatRect exit_hitbox;

//load hitbox
std::vector<sf::FloatRect> hitBoxList;
int init_texture()
{
    try
    {
        load_texture(texture_map);
    }
    catch(LoadException& e)
    {
        logger.log(e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int init_font()
{
    // 加载字体
    if(!font.openFromFile(font_path)){
        logger.log("font.openFromFile() failed");
        return EXIT_FAILURE;
    }
    if(!title_font.openFromFile(title_font_path)){
        logger.log("title_font.openFromFile() failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int load_map()
{
    // Load mapData
    try
    {
        mapData = loadFromCSV(mapdata_path);
    }
    catch (const MapLoadException& e)
    {
        logger.log(e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int init_map()
{
    // Init Map
    int x=0,y=0;
    bool has_exit = false;
    for (auto& row : mapData){
        std::vector<sf::Sprite> sBlockRow;
        x=0;
        for (auto t : row){
            sf::Sprite sprite(texture_map[TextureName(t)]);
            sf::Vector2f posVec = conv2uTo2f({BlockSize*x,BlockSize*y});

            sprite.setScale({block_scale, block_scale});
            sprite.setPosition(posVec);
            if(TextureName(t) >= TextureName::Wall_Corner_Top_Left &&
                TextureName(t) <= TextureName::Wall_Block) // if it is a wall
            {
                sBlockBoundsList.push_back(sprite.getGlobalBounds());
            }
            else if(TextureName(t) == TextureName::Water) // if it is water
            {
                auto water = std::make_shared<Water>(sprite,posVec,BlockSize);
                waterMap[vecToFloat(posVec)] = water;
                waterList.push_back(water);
            }
            else if(TextureName(t) == TextureName::Box) // if it is a box
            {
                sprite.setTexture(texture_map[TextureName::Grass]);

                sf::Sprite box_sprite(texture_map[TextureName::Box]);
                float origin_x = texture_map[TextureName::Box].getSize().x / 2.f;
                float origin_y = texture_map[TextureName::Box].getSize().y / 2.f;
                
                // set origin center, box scale, set position in the block center
                box_sprite.setOrigin({origin_x,origin_y});
                box_sprite.setScale({box_scale,box_scale});
                box_sprite.setPosition({posVec.x+origin_x*block_scale,posVec.y+origin_y*block_scale}); 
                
                auto box = std::make_shared<Box>(box_sprite,BlockSize);  
                boxMap[vecToFloat(posVec)] = box;
                boxList.push_back(box);
            }
            if(TextureName(t) == TextureName::Exit)
            {   
                if(has_exit) throw MapLoadException("Multiple exit");
                exit_hitbox = sprite.getGlobalBounds();
                has_exit = true;
            }
            sBlockRow.push_back(sprite);
            x++;
        }
        sBlockList2d.push_back(sBlockRow);
        y++;
    }
    // reset hitbox
    hitboxDirty = true;
    return EXIT_SUCCESS;
}
void init_player_sprite()
{
    float origin_x = playerTex.getSize().x / 2.f;
    float origin_y = playerTex.getSize().y / 2.f;
    p_sprite->setOrigin({origin_x,origin_y}); // 设置中心为原点
    p_sprite->setScale({p_scale,p_scale}); 
}

void init_player_loc()
{
    float origin_x = playerTex.getSize().x / 2.f;
    float origin_y = playerTex.getSize().y / 2.f;
    sf::Vector2u pos = {player_ini_pos_x,player_ini_pos_y};
    sf::Vector2f p_block_pos = conv2uTo2f({pos.x*BlockSize,pos.y*BlockSize});
    p_player->sprite.setPosition({p_block_pos.x+origin_x*block_scale,p_block_pos.y+origin_y*block_scale});  
}
int init_player()
{
    playerTex = texture_map[TextureName::Pupu];
    p_sprite = std::make_unique<sf::Sprite>(playerTex);
    init_player_sprite(); 
    p_player = std::make_unique<Player>(*p_sprite);
    init_player_loc(); 
    return EXIT_SUCCESS;
}

int initAudio()
{
    if (!music.openFromFile(music_path)) {
        return EXIT_FAILURE;
    }
    music.setVolume(100);        // Volume (0-100)
    music.setLooping(true);        // set looping
    music.setPitch(1.0f); 

    load_sound_map(soundBufferMap,soundMap);
    return EXIT_SUCCESS;
}
int initLevel(){
    try{
        if (init_texture()==EXIT_FAILURE) return EXIT_FAILURE;
        if (init_font()==EXIT_FAILURE) return EXIT_FAILURE;
        if (load_map()==EXIT_FAILURE) return EXIT_FAILURE;
        if (init_map()==EXIT_FAILURE) return EXIT_FAILURE;
        if (init_player()==EXIT_FAILURE) return EXIT_FAILURE;
    } 
    catch(const MapLoadException& e){
        logger.log(e.what());
    }
    catch(...)
    {
        throw;
    }
    return EXIT_SUCCESS;
}
int resetLevel(){
    boxList.clear();
    boxMap.clear();
    waterList.clear();
    waterMap.clear();
    sBlockList2d.clear();
    sBlockBoundsList.clear();
    if (init_map()==EXIT_FAILURE) return EXIT_FAILURE;
    init_player_loc();
    return EXIT_SUCCESS;
}

int levelPass()
{
    gameState = GameState::Loading;
    return resetLevel();
}
