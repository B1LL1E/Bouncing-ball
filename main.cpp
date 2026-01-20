#include <SDL2/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>

int szybkosc = 5;
int width = 1600;
int height = 900;
int rad = 50;
int iloscPilek = 20;

struct Ball{
	double x, y;
	double vx, vy;
	int radius = 50;
	int R = 0;
	int G = 0;
	int B = 255;
};



bool collision(Ball &a, Ball &b){
	if(
		a.x < b.x + b.radius &&
		a.x + a.radius > b.x &&
		a.y < b.y + b.radius &&
		a.y + a.radius > b.y
	)
	{
		return true;
	}

	return false;
}


int main(){
	
	//reset losowosci
	srand(time(NULL));

	//inicjacja okna
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Ball", 100, 100, width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	//vector dla pilek

	std::vector<Ball> pilki;

	for(size_t i = 0; i < iloscPilek + 1; i++){
		Ball b;
		//ustalanie predkosci -5;5 i losowego polozenie
		b.x = (rand() % (width - 100)) + 50;
		b.y = (rand() % (height - 100)) + 50;
		b.vx = (rand() % 10) - 5;
		b.vy = (rand() % 10) - 5;

		//losowanie koloru
		b.R = (rand() % 155) + 100;
		b.G = (rand() % 155) + 100;
		b.B = (rand() % 155) + 100;
		

		//jesli predkosc jest 0 to daj 1;
		if(b.vx == 0) b.vx = 1;
		if(b.vy == 0) b.vy = 1;
		pilki.push_back(b);
	}
	
	//pierwsza pilka, wylaczona
	Ball* pilka = new Ball;
	pilka -> x = (width /2);
	pilka -> y = (height/2);
	pilka -> radius = rad;
	pilka -> vx = szybkosc;
	pilka -> vy = szybkosc;


//okienko 
	bool czyDziala = true;
	SDL_Event event;
	while(czyDziala){

	//sprawdzanie czy chcemy zamknac okno
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				czyDziala = false;
			}
		}
	
		

		//sprawdzanie kolizzji
		for(size_t i = 0; i < pilki.size(); ++i){
			for(size_t j = i + 1; j < pilki.size(); ++j){
				if(collision(pilki[i], pilki[j])){
					std::swap(pilki[i].vx, pilki[j].vx);
					std::swap(pilki[i].vy, pilki[j].vy);

					pilki[i].x += pilki[i].vx;
				}
			}
		}






		//fizyka pierwszej wylacznoej pilki
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





		//dodanie losowych pilek
		for(auto& p : pilki){
			p.x += p.vx;
			p.y += p.vy;


			if(p.x + p.radius >= width){
				p.vx *= -1;
			}
			if(p.y + p.radius >= height){
				p.vy *= -1;
			}

			if(p.x <= 0){
				p.vx *= -1;
			}
			if(p.y <= 0){
				p.vy *= -1;
			}

			SDL_Rect rect;
			rect.x = (int)p.x;
			rect.y = (int)p.y;
			rect.w = p.radius;
			rect.h = p.radius;
			
			SDL_SetRenderDrawColor(renderer, p.R, p.G, p.B, 255);
			SDL_RenderFillRect(renderer, &rect);
			
		}
		
		SDL_RenderPresent(renderer);
		SDL_Delay(10);



		//rysowanie
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		/*
		
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
		*/
	}

	delete pilka;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
