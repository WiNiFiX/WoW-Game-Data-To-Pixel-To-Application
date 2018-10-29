#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

struct RGBCOLOR {
	double r;
	double g;
	double b;

	RGBCOLOR(double red, double green, double blue)
	{
		r = red;
		g = green;
		b = blue;
	}
};

RGBCOLOR getNextSpell(HDC desktopHdc, HWND desktop)
{
	COLORREF color = GetPixel(desktopHdc, 0, 0);

	double red, green, blue;
	red = green = blue = 0;

	blue = GetBValue(color);
	green = GetGValue(color);
	red = GetRValue(color);

	red = ceil((red / 255) * 100) / 100;
	green = ceil((green / 255) * 100) / 100;
	blue = ceil((blue / 255) * 100) / 100;

	RGBCOLOR rgb = RGBCOLOR(red, green, blue);

	return rgb;
}

void sendKey(int key)
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; 
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key; 
	ip.ki.dwFlags = 0; 
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

}

int main(int argc, char** argv)
{
	while (true) 
	{
		HWND desktop = GetDesktopWindow();
		HDC desktopHdc = GetDC(desktop);

		RGBCOLOR nextSpell = getNextSpell(desktopHdc, desktop);

		ReleaseDC(desktop, desktopHdc);

		//Bug or a feature, .5 in wow turns into .51 here, my guess is COLORREF is using ints instead of decimals. 
		RGBCOLOR spiritBomb = RGBCOLOR(.51, 0, 0);
		RGBCOLOR fracture = RGBCOLOR(0, .51, 0);
		RGBCOLOR immolationAura = RGBCOLOR(0, 0, .51);
		RGBCOLOR soulCleave = RGBCOLOR(1, 1, 0);

		if (nextSpell.r == spiritBomb.r && nextSpell.g == spiritBomb.g && nextSpell.b == spiritBomb.b)
		{
			std::cout << "Spirit Bomb" << std::endl;
			sendKey(0x36);
		}
		else if (nextSpell.r == fracture.r && nextSpell.g == fracture.g && nextSpell.b == fracture.b)
		{
			std::cout << "fracture" << std::endl;
			sendKey(0x32);
		}
		else if (nextSpell.r == immolationAura.r && nextSpell.g == immolationAura.g && nextSpell.b == immolationAura.b)
		{
			std::cout << "immolationAura" << std::endl;
			sendKey(0x37);
		}
		else if (nextSpell.r == soulCleave.r && nextSpell.g == soulCleave.g && nextSpell.b == soulCleave.b)
		{
			std::cout << "soulCleave" << std::endl;
			sendKey(0x34);
		}
	}
	return 0;
}