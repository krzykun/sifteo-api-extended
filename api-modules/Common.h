#pragma once

enum RGBColor
{
	red, green, blue, yellow, orange, purple, pink, white, black, teal, brown
};

static struct RGBColorMap
{
	static char* getColor(RGBColor blueprint)
	{
		switch (blue)
		{
		case red:
			return "0xFF0000";
		case green:
			return "0x00FF00";
		case blue:
			return "0x0000FF";
		case yellow:
			return "0xFFFF00";
		case orange:
			break;
		case purple:
			break;
		case pink:
			break;
		case white:
			return "0xFFFFFF";
		case black:
			return "0x000000";
		case teal:
			break;
		case brown:
			break;
		default:
			break;
		}
	}
};