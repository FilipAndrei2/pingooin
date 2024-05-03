#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <wtypes.h>


#define WINDOW_WIDTH 938
#define WINDOW_HEIGHT  526
bool isRunning = true;
bool isMoving = false;
SDL_Rect r1 = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 420, 69};

int x, y;
int x2, y2;

void move(void){

}

void input(void){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            isRunning = false;
        }
        SDL_GetMouseState(&x, &y);
        if ((event.type == SDL_MOUSEBUTTONUP)){
            isMoving = false;
        }
        if ((event.type == SDL_MOUSEBUTTONDOWN) && (x > r1.x) && (x < (r1.x + r1.w) && (y > r1.y) && (y < (r1.y + r1.h)))){
            isMoving = true;
        }
    }
}

void process(void){
    if(isMoving){
        SDL_GetMouseState(&x2, &y2);
        r1.x =x2 - (r1.w/2);
        r1.y =y2 - (r1.h/2);
        //r1.x = x2 - (r1.w / x2 );
        //r1.y = y2 - (r1.h / y2 );
        //std::cout << "Mouse:" << x2 << ", " << y2 << "\nRect: " << r1.x - (r1.w/2) << ", " << r1.y - (r1.h/2) << std::endl;
    }
}
void render(SDL_Renderer * renderer, SDL_Texture * texture){
    SDL_SetRenderDrawColor(renderer, 108, 122, 137,255);
    if(isMoving){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0,255);
    }
    SDL_RenderClear(renderer);


    SDL_RenderCopy(renderer, texture, NULL, &r1);

    SDL_RenderPresent(renderer);
}

int main(int, char **){

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Eroare init sdl!\n";
        return -1;
    }

    if(IMG_INIT_PNG != IMG_Init(IMG_INIT_PNG)){
        std::cout << "Eroare init sdl_img!\n";
        return -1;
    }

    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;

    window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window){
        std::cout << "Eroare init window!\n";
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        std::cout << "Eroare init renderer!\n";
        return -1;
    }

    SDL_Surface * temp = IMG_Load("linux.png");
    if(!temp){
        std::cout << "Eroare deschidere png!\n";
        return -1;
    }

    SDL_Texture * png = SDL_CreateTextureFromSurface(renderer, temp);
    if(!png){
    std::cout << "Eroare creare texture!\n";
    return -1;
    }

    SDL_FreeSurface(temp);
    while(isRunning){
        input();
        process();
        render(renderer, png);
        SDL_Delay(20);
    }

    
    return 0;
}