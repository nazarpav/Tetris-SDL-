#include"TetrisLogic.h"

short GameLogic::GetScore()
{
	return Score;
}
void GameLogic::SetNewCubeX(short newc)
{
	this->newCubeX = newc;
}
void GameLogic::SetNewCubeY(short newc)
{
	this->newCubeY = newc;
}
short GameLogic::GetNewCubeX()
{
	return this->newCubeX;
}
short GameLogic::GetNewCubeY()
{
	return this->newCubeY;
}
short GameLogic::GetSavedNewCubeX()
{
	return this->quantityCellX;
}
short GameLogic::GetSavedNewCubeY()
{
	return this->quantityCellY;
}
GameLogic::GameLogic(short CellStep, short pos, short screenWidth, short screenHeight)
{
	newCubeX = pos;
	newCubeY = 0;
	celStep = CellStep;
	this->quantityCellY = screenHeight / CellStep;
	this->quantityCellX = screenWidth / 2 / CellStep;
	TetrisMap = new bool* [quantityCellY];
	for (short i = 0; i < quantityCellY; i++)
	{
		TetrisMap[i] = new bool[quantityCellX];
	}
	for (short i = 0; i < quantityCellY; i++)
	{
		for (short j = 0; j < quantityCellX; j++)
		{
			TetrisMap[i][j] = false;
		}
	}
}
bool GameLogic::CheckIsGameOver()
{
	for (short i = 0; i < quantityCellX; i++)
	{
		if (TetrisMap[1][i] == true)
			return true;
	}
	return false;
}
bool GameLogic::CheckToEraseDownLine()const
{
	for (short i = 0; i < quantityCellX; i++)
	{
		if (TetrisMap[quantityCellY - 1][i] == false)
			return false;
	}
	return true;
}
void GameLogic::EraseDownLine()
{
	Score += 100;
	for (short i = 0; i < quantityCellX; i++)
	{
		TetrisMap[quantityCellY - 1][i] = false;
	}
	bool* tmpPointer = TetrisMap[quantityCellY - 1];
	for (short i = quantityCellY - 1; i > 0; i--)
	{
		TetrisMap[i] = TetrisMap[i - 1];
	}
	TetrisMap[0] = tmpPointer;
	tmpPointer = nullptr;
}
bool GameLogic::IsCubeInCoord(int x, int y)
{
	if (y == 0)
		return  false;
	return TetrisMap[y][x];
}
void GameLogic::SetCubeOnMap(int x, int y)
{
	if (x >= 0 && y > 0 && x <= quantityCellX && y <= quantityCellY)
		TetrisMap[y - 1][x] = true;
}
bool GameLogic::IfCubeDown(int CubeX, int CubeY)const
{
	return CubeY == quantityCellY || TetrisMap[CubeY][CubeX] == true ? true : false;
}
void GameLogic::CubeFall(short fallingOn)
{
	if (newCubeY / celStep != quantityCellY)
		newCubeY += fallingOn;
}
GameLogic::~GameLogic()
{
	for (short i = 0; i < quantityCellY; i++)
	{
		delete[] TetrisMap[i];
	}
	delete[] TetrisMap;
}