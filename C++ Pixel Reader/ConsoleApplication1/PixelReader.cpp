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
		dhv.registerSpell("Demon Spikes", RGBCOLOR(1, .51, 1), { 0x12 , 0x31 });
		dhv.registerSpell("Fiery Brand", RGBCOLOR(.51, .51, 1), { 0x12 , 0x32 });
		dhv.registerSpell("Metamorphosis", RGBCOLOR(.51, .51, 0), { 0x12 , 0x33 });
		dhv.registerSpell("Spirit Bomb", RGBCOLOR(.51, 0, 0), { 0x36 });
		dhv.registerSpell("Fracture", RGBCOLOR(0, .51, 0), { 0x32 });
		dhv.registerSpell("Immolation Aura", RGBCOLOR(0, 0, .51), { 0x37 });
		dhv.registerSpell("Soul Cleave", RGBCOLOR(1, 1, 0), { 0x34 });
		dhv.registerSpell("Throw Glaive", RGBCOLOR(0, 1, 1), { 0x33 });
		dhv.registerSpell("Disrupt", RGBCOLOR(0, .51, 1), { 0x38 });

		SpellList dhh;
		dhh.registerSpell("Immolation Aura", RGBCOLOR(0, 0, .51), { 0x39 });
		dhh.registerSpell("Blade Dance", RGBCOLOR(0, 1, 1), { 0x33 });
		dhh.registerSpell("Eye Beam", RGBCOLOR(1, 1, 0), { 0x36 });
		dhh.registerSpell("Disrupt", RGBCOLOR(.51, .51, 1), { 0x38 });
		dhh.registerSpell("Throw Glaive", RGBCOLOR(0.51, 0.51, 0.51), { 0x32 });
		dhh.registerSpell("Chaos Strike", RGBCOLOR(0, .51, 0), { 0x35 });
		dhh.registerSpell("Demons Bite", RGBCOLOR(1, .51, 1), { 0x34 });

		SpellList disp;
		disp.registerSpell("Shadow Word Pain", RGBCOLOR(0, .51, 0), { 0x31 });
		disp.registerSpell("Power Word Solace", RGBCOLOR(.51, 0, 0), { 0x32 });
		disp.registerSpell("Penance", RGBCOLOR(0, 0, .51), { 0x33 });
		disp.registerSpell("Smite", RGBCOLOR(1, .51, 0), { 0x34 });

		SpellList holyp;
		holyp.registerSpell("Holy Shock", RGBCOLOR(.51, 0, 0), {0x32});
		holyp.registerSpell("Bestow Faith", RGBCOLOR(0, .51, 0), {0x33});
		holyp.registerSpell("Holy Light", RGBCOLOR(0, 0, .51), {0x35});
		holyp.registerSpell("Flash of Light", RGBCOLOR(.51, 1, 1), {0x36});
		//holyp.registerSpell("Beacon of Light", RGBCOLOR(0, 0, 0), {0x31});
		//holyp.registerSpell("Beacon of Faith", RGBCOLOR(0, 0, 0), { 0x12, 0x31 });
		holyp.registerSpell("Target Player", RGBCOLOR(1, 0, 0), { 0x70 });
		holyp.registerSpell("Target Party 1", RGBCOLOR(0, 1, 0), { 0x71 });
		holyp.registerSpell("Target Party 2", RGBCOLOR(0, 0, 1), { 0x72 });
		holyp.registerSpell("Target Party 3", RGBCOLOR(0, 1, 1), { 0x73 });
		holyp.registerSpell("Target Party 4", RGBCOLOR(1, 0, 1), { 0x74 });

		auto key = holyp.getSpellBinding(nextSpell);
		auto currentSpell = holyp.getSpellName(nextSpell);

		if (key.size() > 0) 
		{
			ip.sendKey(key);
			std::cout << "Action: " << currentSpell << std::endl;
		}

	}
	return 0;
}