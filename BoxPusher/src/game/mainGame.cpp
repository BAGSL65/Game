#ifdef _WIN32
    #include <Windows.h>
    #include <imm.h>
#endif
#include "gameProcessor.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({MapLength*BlockSize,MapWidth*BlockSize}),L"推箱子",sf::Style::Default & ~sf::Style::Resize);
    
    #ifdef _WIN32
        // 禁用输入法
        HWND hwnd = window.getNativeHandle();
        if (hwnd) {
            // 禁用 IME
            ImmAssociateContext(hwnd, NULL);
        }
    #endif
    
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
        }else if (gameState == GameState::StartMenu)
        {
            mainMenu(window);
        }else if (gameState == GameState::Config){
            config(window);
        }
    }

    return EXIT_SUCCESS;
}