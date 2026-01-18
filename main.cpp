#include <SDL2/SDL.h>

int szybkosc = 5;
int width = 1600;
int height = 900;
int rad = 50;

struct Ball{
	double x, y;
	double vx, vy;
	int radius;
};

int main(){
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Ball", 100, 100, width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Ball* pilka = new Ball;
	pilka -> x = (width /2);
	pilka -> y = (height/2);
	pilka -> radius = rad;
	pilka -> vx = szybkosc;
	pilka -> vy = szybkosc;

	bool czyDziala = true;
	SDL_Event event;
	while(czyDziala){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				czyDziala = false;
			}
		}
		
		//fizyka
		pilka -> x += pilka -> vx;
		pilka -> y += pilka -> vy;

		//odwrocenie kierunku przy spoktaniu ze sciana 
		if(pilka -> x + pilka -> radius >= width || pilka -> x <= 0){
			pilka -> vx *= -1;
		}

		if(pilka -> y + pilka -> radius >= height || pilka -> y <= 0){
			pilka -> vy *= -1;
		}

		//rysowanie

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		
		SDL_Rect pro;
		pro.x = pilka -> x;
		pro.y = pilka -> y;
		pro.w = rad;
		pro.h = rad;

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &pro);

		SDL_RenderPresent(renderer);

		SDL_Delay(10);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	}

	delete pilka;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
