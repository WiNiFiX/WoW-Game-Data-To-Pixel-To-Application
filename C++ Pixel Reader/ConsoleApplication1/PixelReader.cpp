#include <stdio.h>
#include <iostream>
#include <math.h>
#include "RGBCOLOR.h"
#include "SpellList.h"
#include "InputFaker.h"

RGBCOLOR getNextSpell()
{
	HWND desktop = GetDesktopWindow();
	HDC desktopHdc = GetDC(desktop);

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
	
	ReleaseDC(desktop, desktopHdc);
	return rgb;
}

int main(int argc, char** argv)
{
	InputFaker ip;
	std::cout << "Pixel Reader Ready. Ensure wow is in windowed fullscreen on monitor 1. " << std::endl;
	while (true) 
	{
		Sleep(150);

		RGBCOLOR nextSpell = getNextSpell();
		
		SpellList dhv;
		dhv.registerSpell("demonSpikes", RGBCOLOR(1,.51,1), { 0x12 , 0x31 });
		dhv.registerSpell("spiritBomb", RGBCOLOR(.51, 0, 0), { 0x36 });
		dhv.registerSpell("fracture", RGBCOLOR(0, .51, 0), { 0x32 });
		dhv.registerSpell("immolationAura", RGBCOLOR(0, 0, .51), { 0x37 });
		dhv.registerSpell("soulCleave", RGBCOLOR(1, 1, 0), { 0x34 });
		dhv.registerSpell("throwGlaive", RGBCOLOR(0, 1, 1), { 0x33 });
		dhv.registerSpell("disrupt", RGBCOLOR(0, .51, 1), { 0x38 });

		SpellList dhh;
		dhh.registerSpell("immolationAura", RGBCOLOR(0, 0, .51), { 0x39 });
		dhh.registerSpell("bladeDance", RGBCOLOR(0, 1, 1), { 0x33 });
		dhh.registerSpell("eyeBeam", RGBCOLOR(1, 1, 0), { 0x36 });
		dhh.registerSpell("felBlade", RGBCOLOR(.51, 0, 0), { 0x32 });
		dhh.registerSpell("chaosStrike", RGBCOLOR(0, .51, 0), { 0x35 });
		dhh.registerSpell("demonsBite", RGBCOLOR(0, .51, 1), { 0x34 });

		SpellList disp;
		disp.registerSpell("shadowWordPain", RGBCOLOR(0, .51, 0), { 0x31 });
		disp.registerSpell("powerWordSolace", RGBCOLOR(.51, 0, 0), { 0x32 });
		disp.registerSpell("penance", RGBCOLOR(0, 0, .51), { 0x33 });
		disp.registerSpell("smite", RGBCOLOR(1, .51, 0), { 0x34 });


		auto key = dhv.getSpellBinding(nextSpell);

		if (key.size() > 0) 
		{
			ip.sendKey(key);
		}

	}
	return 0;
}