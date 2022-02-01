#define TX_COMPILED
#include "TXLib.h"

const int SizeX = 1900;
const int SizeY = 850;
const int GroundY = 580;
const COLORREF SkyColor = RGB (0, 0, 255); //0xFB945D;
const COLORREF DeathColor = RGB (255, 255, 255);

void DrawCircle (double posX, double posY);

void Move (double *posX, double *posY, double *speedX, double *speedY, double *axeX, double *axeY);

int Control (double *speedX, double *speedY, COLORREF LegColor);

int main()
{
    txCreateWindow (SizeX, SizeY);

	HDC back  = txLoadImage ("back.bmp");
	HDC mario = txLoadImage ("mario.bmp");
	HDC map   = txLoadImage ("map.bmp");

	int marioSizeX = txGetExtentX (mario);
	int marioSizeY = txGetExtentY (mario);

	double posX = 100, posY = 100;
	double speedX = 5, speedY = 3;
	double axeX = 0, axeY = 1;

	while (true)
	{
		txBitBlt (txDC (), 0, 0, 0, 0, back);

		COLORREF LegColor = txGetPixel (posX, posY + marioSizeY, map);

		//printf ("color = %06X \n", color);

		double oldX = posX;
		double oldY = posY;

		int ret = Control (&speedX, &speedY, LegColor);										//																					static double i = 1; if (i++ % 100 == 0) prdoublef ("Grishka is the zhopa %d times\n", i);
		
		if (ret == 0)
		{
			break;
		}

		Move (&posX, &posY, &speedX, &speedY, &axeX, &axeY);

		LegColor = txGetPixel (posX, posY + marioSizeY - 10, map);

		if (LegColor != SkyColor)
		{
			posX = oldX;
			posY = oldY;
		}

		if (LegColor == DeathColor)
		{
			txMessageBox ( "НАЖМИТЕ ЛЮБУЮ КНОПКУ", "GAME OVER EPTA" );

			break;
		}

		DrawCircle (posX, posY);

		int rot = 0;
		
		if (speedX < 0)
		{
			rot = marioSizeX / 2;
		}

		txTransparentBlt (txDC (), posX, posY, marioSizeX / 2, 0, mario, rot, 0, RGB (255, 0, 255));

		txSleep (0);
	}

	txDeleteDC (back);
	txDeleteDC (mario);
	txDeleteDC (map);
}

void DrawCircle (double posX, double posY)
	{
	//double v = sqrt (speedX * speedX + speedY * speedY) * 5;

	txSetColor     (TX_LIGHTRED);
	txSetFillColor (TX_RED);

	txCircle (posX, posY, 20);
	}


void Move (double *posX, double *posY, double *speedX, double *speedY, double *axeX, double *axeY)
{
	*speedX += *axeX,
	*speedY += *axeY;
	*speedX *= 0.9;
	*speedY *= 0.9;
	*posX = *posX + *speedX,
	*posY = *posY + *speedY;
	
	if (*posX > SizeX)
	{
		*speedX = -*speedX;
		*posX = *posX - 2 * (*posX - SizeX);
	}

	if (*posX < 0)
	{
		*speedX = -*speedX;
		*posX = -*posX * 2;
	}
		
	if (*posY > GroundY)
	{
		*speedY = -*speedY;
		*posY = *posY - 2 * (*posY - GroundY);
	}

	if (*posY < 0)
	{
		*speedY = -*speedY;
		*posY = -*posY * 2;
	}
}

int Control (double *speedX, double *speedY, COLORREF LegColor)
{
	if (GetAsyncKeyState (VK_ESCAPE))
	{
		return 0;
	}

	if (GetAsyncKeyState (VK_RIGHT))
	{
		(*speedX)++;
	}

	if (GetAsyncKeyState (VK_LEFT))
	{
		(*speedX)--;
	}

	if (GetAsyncKeyState (VK_DOWN))
	{
		(*speedY)++;
	}

	if (GetAsyncKeyState (VK_UP) && LegColor != SkyColor)
	{
		if (GetAsyncKeyState (VK_SHIFT))
		{
			*speedY -= 50;
		}
		(*speedY) -= 25;
	}

	if (GetAsyncKeyState (VK_SPACE))
	{
		*speedX = 0, *speedY = 0;
	}

	return 1;
}

//	void DrawMario (*posX, *posY)
//	{
//	
//	}



		//	txCreateWindow (800, 600);

		//	txSelectFont ("Arial", 20, 0, FW_BOLD);
			//txDrawText   (100, 250, 700, 350, "GAME OVER, EPTA");