#pragma once
class GameLogic
{
private:
	short quantityCellY;
	short quantityCellX;
	bool** TetrisMap;
	short newCubeX, newCubeY;
	short celStep;
	short Score;
public:
	short GetScore();
	void SetNewCubeX(short newc);
	void SetNewCubeY(short newc);
	short GetNewCubeX();
	short GetNewCubeY();
	short GetSavedNewCubeX();
	short GetSavedNewCubeY();
	GameLogic(short CellStep, short pos, short screenWidth, short screenHeight);
	bool CheckIsGameOver();
	bool CheckToEraseDownLine()const;
	void EraseDownLine();
	bool IsCubeInCoord(int x, int y);
	void SetCubeOnMap(int x, int y);
	bool IfCubeDown(int CubeX, int CubeY)const;
	void CubeFall(short fallingOn);
	~GameLogic();
};