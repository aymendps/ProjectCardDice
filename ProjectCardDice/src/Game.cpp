#include "Game.h"
#include "Gameplay/Scenes/SceneManager.h"
#include "Gameplay/Collections/CardCollection.h"

SDL_Renderer* Game::renderer = nullptr;

Game::Game() : _isRunning {false}, _window {nullptr}
{
}

Game::~Game()
{
}

void Game::Init()
{
	std::cout << "Initializing SDL..." << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0) {
		std::cout << "SDL was initialized!" << std::endl;

		std::cout << "Creating Game Window..." << std::endl;

		_window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			GAME_WIDTH, GAME_HEIGHT, GAME_FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

		if (_window) {
			std::cout << "Game Window was created!" << std::endl;
		}

		std::cout << "Creating Game Renderer..." << std::endl;

		renderer = SDL_CreateRenderer(_window, -1, 0);

		if (renderer) {
			std::cout << "Game Renderer was created!" << std::endl;
			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
		}

		std::cout << "\033[33m" << "Allowing a maximum of " << maxComponentTypes << " component types per entity" << "\033[0m" << std::endl;
		std::cout << "\033[33m" << "Allowing only 1 instance of each component type per entity" << "\033[0m" << std::endl;

		CardCollection::GetInstance().Init();
		SceneManager::GetInstance().Init();

		_isRunning = true;
	}
	else {
		_isRunning = false;
	}
}


void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYDOWN:
		_isRunning = event.key.keysym.sym != SDLK_ESCAPE;
		break;
	default:
		break;
	}
	SceneManager::GetInstance().HandleEvents(event);
}

void Game::Update(const float deltaTime)
{
	SceneManager::GetInstance().Update(deltaTime);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SceneManager::GetInstance().Render();
	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	std::cout << "Destroying Game Window..." << std::endl;
	SDL_DestroyWindow(_window);
	std::cout << "Game Window was destroyed!" << std::endl;

	std::cout << "Destroying Game Renderer..." << std::endl;
	SDL_DestroyRenderer(renderer);
	std::cout << "Game Renderer was destroyed!" << std::endl;

	std::cout << "Destroying SDL_TTF..." << std::endl;
	TTF_Quit();
	std::cout << "SDL_TTF was destroyed!" << std::endl;

	std::cout << "Destroying SDL..." << std::endl;
	SDL_Quit();
	std::cout << "SDL was destroyed!" << std::endl;
}
