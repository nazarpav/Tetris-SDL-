#include"Tetris.h"

void Tetris::RenderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
void Tetris::RenderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	RenderTexture(tex, ren, x, y, w, h);
}
SDL_Texture* Tetris::LoadTexture(const std::string& file, SDL_Renderer* ren)
{
	SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
	if (!texture)
	{
		std::cout << IMG_GetError();
	}
	return texture;
}
void Tetris::RenderBackground()
{
	for (int i = 0; i < xTiles * yTiles; ++i)
	{
		int x = i % xTiles;
		int y = i / xTiles;
		RenderTexture(background, rend, x * Background.w, y * Background.h);
	}
}
void Tetris::RenderCubes()
{

	for (int i = 0; i < SCREEN_HEIGHT / CubeW; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH / 2 / CubeW; j++)
		{
			if (gameLogic->IsCubeInCoord(j, i))
			{
				RenderTexture(cubeTexture, rend, j * CubeW + 256, i * CubeW);
			}
		}
	}
}
Tetris::~Tetris()
{
	delete gameLogic;
	SDL_DestroyTexture(cubeTexture);
	SDL_DestroyTexture(gameOver);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(background2);
	Mix_FreeChunk(SoundFall);
	Mix_FreeChunk(SoundKeyDown);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
}
Tetris::Tetris(short quantityCellY, short quantityCellX)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "error initializing SDL: \n" << SDL_GetError();
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		std::cout << "Mix_OpenAudio: \n" << Mix_GetError();
	}

	win = SDL_CreateWindow("GAME",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	rend = SDL_CreateRenderer(win, -1, render_flags);

	SoundFall = Mix_LoadWAV("SoundFall.wav");
	SoundKeyDown = Mix_LoadWAV("SoundKeyDown.wav");
	soundGameOver = Mix_LoadWAV("SoundGameOver.wav");
	soundDestroyCube = Mix_LoadWAV("SoundDesroyCubes.wav");
	background = LoadTexture("background.png", rend);
	background2 = LoadTexture("background2.png", rend);
	cubeTexture = LoadTexture("Cube.png", rend);
	gameOver = LoadTexture("gameOver.png", rend);
	destroyCube = LoadTexture("destroyCube.png", rend);
	SDL_QueryTexture(cubeTexture, NULL, NULL, &CubeW, &CubeW);
	SDL_QueryTexture(background, NULL, NULL, &Background.w, &Background.h);


	if (!background || !cubeTexture)
	{
		SDL_DestroyTexture(gameOver);
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(background2);
		SDL_DestroyTexture(cubeTexture);
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		IMG_Quit();
		SDL_Quit();
		this->~Tetris();
	}

	xTiles = SCREEN_WIDTH / Background.w;
	yTiles = SCREEN_HEIGHT / Background.h;

	gameLogic = new GameLogic(CubeW, (SCREEN_WIDTH / 2) - CubeW, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void Tetris::StartGame()
{
	int i = 0;
	while (!close)
	{
		/*std::clog << "COORDINATION: = x > " << (gameLogic->GetNewCubeX()-256) / CubeW << "||| = y > " << gameLogic->GetNewCubeY() / CubeW << std::endl;
		for (short i = 0; i < SCREEN_HEIGHT / CubeW; i++)
		{
			for (short j = 0; j < SCREEN_WIDTH /2 / CubeW; j++)
			{
				if (gameLogic->IsCubeInCoord(j, i))
					std::clog << "#";
				else
					std::clog << "_";
			}
			std::clog << "\n";
		}*/
		if (gameLogic->IfCubeDown((gameLogic->GetNewCubeX() - 256) / CubeW, gameLogic->GetNewCubeY() / CubeW))
		{
			gameLogic->SetCubeOnMap((gameLogic->GetNewCubeX() - 256) / CubeW, gameLogic->GetNewCubeY() / CubeW);
			gameLogic->SetNewCubeY(0);
			gameLogic->SetNewCubeX((SCREEN_WIDTH / 2) - CubeW);
		}
		SDL_Delay(110 - Speed);
		while (SDL_PollEvent(&event))
		{
			Speed = 0;
			switch (event.type)
			{
			case SDL_SCANCODE_ESCAPE:
			case SDL_QUIT:
				close = 1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					if ((gameLogic->GetNewCubeX() - CubeW) >= (0 + SCREEN_WIDTH / 4) && gameLogic->IsCubeInCoord((gameLogic->GetNewCubeX() - 256) / CubeW - 1, gameLogic->GetNewCubeY() / CubeW) != true)
					{
						Mix_PlayChannel(-1, SoundKeyDown, 0);
						gameLogic->SetNewCubeX(gameLogic->GetNewCubeX() - CubeW);
					}
					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					if ((gameLogic->GetNewCubeX() + CubeW) < (SCREEN_WIDTH - SCREEN_WIDTH / 4) && gameLogic->IsCubeInCoord((gameLogic->GetNewCubeX() - 256) / CubeW + 1, gameLogic->GetNewCubeY() / CubeW) != true)
					{
						Mix_PlayChannel(-1, SoundKeyDown, 0);
						gameLogic->SetNewCubeX(gameLogic->GetNewCubeX() + CubeW);
					}
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					if (gameLogic->GetNewCubeY() / CubeW != 2)
						Speed += 105;
					break;
				}
			}
		}
		Mix_PlayChannel(-1, SoundFall, 0);
		if (gameLogic->CheckToEraseDownLine())
		{
			Mix_HaltChannel(-1);
			Mix_PlayChannel(-1, soundDestroyCube, 0);
			RenderTexture(destroyCube, rend, 256, 786 - 48);
			SDL_RenderPresent(rend);
			SDL_Delay(1000);
			gameLogic->EraseDownLine();

		}
		if (gameLogic->CheckIsGameOver())
		{
			Mix_HaltChannel(-1);
			RenderTexture(gameOver, rend, 128, 256);
			Mix_PlayChannel(-1, soundGameOver, 0);
			SDL_RenderPresent(rend);
			SDL_Delay(3000);
			return;
		}
		SDL_RenderClear(rend);
		RenderBackground();
		RenderTexture(background2, rend, 256, 0);
		RenderTexture(cubeTexture, rend, gameLogic->GetNewCubeX(), gameLogic->GetNewCubeY(), CubeW, CubeW);
		RenderCubes();
		SDL_RenderPresent(rend);

		gameLogic->CubeFall(CubeW);
	}
}