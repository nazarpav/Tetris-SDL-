#pragma once
#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_timer.h> 
#include <SDL_mixer.h> 
#include<string>
#include<iostream>
#include"TetrisLogic.h"
#include<Windows.h>
class Tetris
{
private:
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;
	
	SDL_Event event;
	SDL_Rect Background;
	SDL_Window* win;
	GameLogic* gameLogic;
	SDL_Renderer* rend;
	SDL_Texture* background;
	SDL_Texture* background2;
	SDL_Texture* cubeTexture;
	SDL_Texture* gameOver;
	SDL_Texture* destroyCube;
	Mix_Chunk* SoundFall;
	Mix_Chunk* soundGameOver;
	Mix_Chunk* soundDestroyCube;
	Mix_Chunk* SoundKeyDown;
	int close = 0;
	short Speed = 0;
	int xTiles;
	int yTiles;


	int CubeW;
	unsigned int render_flags = SDL_RENDERER_ACCELERATED;
	SDL_Texture* LoadTexture(const std::string& file, SDL_Renderer* ren);
	void RenderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h);
	void RenderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y);
	void RenderBackground();
	void RenderCubes();

public:
	void StartGame();
	Tetris(short quantityCellY, short quantityCellX);
	~Tetris();
};