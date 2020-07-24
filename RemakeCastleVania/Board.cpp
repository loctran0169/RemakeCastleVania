#include "Board.h"


CBoard* CBoard::_instance = NULL;

CBoard* CBoard::GetInstance()
{
	if (_instance == NULL) _instance = new CBoard();
	return _instance;
}

CBoard::CBoard()
{
}

void CBoard::Render()
{
}


CBoard::~CBoard()
{
}
