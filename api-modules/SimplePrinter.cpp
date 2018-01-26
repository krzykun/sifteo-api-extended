#include "SimplePrinter.h"


SimplePrinter::SimplePrinter(VideoBuffer & videoBuffer, PrintWindowPosition windowPosition)
{
	currentWindowPosition = windowPosition;
	currentPosition.x = startPosition.x;
	currentPosition.y = startPosition.y;
	localVideoBuffer.colormap[0] = backgroundColor;
	refreshModeAndWindowPosition();
	// LOG("SimplePrinter: %d %d %d %d %d %d %d %d\n", startPosition.x, startPosition.y, size.x, size.y, maxCharInLine, maxLinesInWindow, currentPosition.x, currentPosition.y);
}

void SimplePrinter::print(const char * str)
{
	LOG("SimplePrinter: drawing text \"%s\" at (%d, %d)\n", str, currentPosition.x, currentPosition.y);
	char ch;
	while ((ch = *str))
	{
		str++;
		charInLineCount++;
		switch (ch)
		{
		case '\t':
		{
			// LOG("SimplePrinter: detected a tabulation %d %d %d\n", currentPosition.x, startPosition.x, size.x);
			if (currentPosition.x >= startPosition.x + size.x - 8)	// safety check against tab count over 6 (more than a single line can handle)
			{
				charInLineCount = 0;
				lineCount++;
				currentPosition.x = startPosition.x;
				currentPosition.y += 8;
			}

			for (unsigned nextTabulationAt = 20; nextTabulationAt < startPosition.x + size.x; nextTabulationAt += 20) // loop that checks tabulation slots
			{
				// LOG("SimplePrinter: Inside the loop, x: %d, nextTabulationAt value: %d\n", currentPosition.x, nextTabulationAt);
				if (currentPosition.x < nextTabulationAt)	// if we enter this, slot is found
				{
					// LOG("SimplePrinter: Setting the x (current %d) to %d pixels\n", currentPosition.x, nextTabulationAt);
					currentPosition.x = nextTabulationAt;
					charInLineCount = nextTabulationAt / 5;
					// LOG("SimplePrinter: Current x: %d pixels\n", currentPosition.x);
					break;
				}
			}
			continue;
		}
		case '\n':
		{
			// LOG("SimplePrinter: detected a newline\n");
			charInLineCount = 0;
			lineCount++;
			currentPosition.x = 0;
			currentPosition.y += 8;
			continue;
		}
		}

		if (charInLineCount > maxCharInLine)	// safety check against too many characters in a single line
		{
			charInLineCount = 1;
			lineCount++;
			currentPosition.x = startPosition.x;
			currentPosition.y += 8;
		}

		if (lineCount > maxLinesInWindow)		// safety check against too many lines to draw
		{
			currentPosition.y = startPosition.y;
			lineCount = 1;
			charInLineCount = 1;
		}

		// Specifics of our font format
		uint8_t index = ch - 32;
		// LOG("SimplePrinter: index = %d\n", index);
		const uint8_t *data = font_data + (index << 3) + index;
		// LOG("SimplePrinter: *data = %d\n", *data);
		uint8_t escapement = *(data++);
		// LOG("SimplePrinter: escapement = %d\n", escapement);
		const Int2 size = { 8, 8 };
		// LOG("SimplePrinter: X: %d, Y: %d\n", currentPosition.x, currentPosition.y);
		fb->bitmap(currentPosition, size, data, 1);
		currentPosition.x += escapement;
	}
	vid.colormap[0] = backgroundColor;	//0 is responsible for background, 1 for foreground
}

void SimplePrinter::println(const char * str)
{
	LOG("SimplePrinter: drawing text \"%s\" at (%d, %d)\n", str, currentPosition.x, currentPosition.y);
	char ch;
	int charInLineCount = 0;
	while ((ch = *str)) {
		str++;
		charInLineCount++;
		switch (ch)
		{
		case '\t':
		{
			// LOG("SimplePrinter: detected a tabulation %d %d %d\n", currentPosition.x, startPosition.x, size.x);
			if (currentPosition.x >= startPosition.x + size.x - 8)	// safety check against tab count over 6 (more than a single line can handle)
			{
				charInLineCount = 0;
				lineCount++;
				currentPosition.x = startPosition.x;
				currentPosition.y += 8;
			}

			for (unsigned nextTabulationAt = 20; nextTabulationAt < startPosition.x + size.x; nextTabulationAt += 20) // loop that checks tabulation slots
			{
				// LOG("SimplePrinter: Inside the loop, x: %d, nextTabulationAt value: %d\n", currentPosition.x, nextTabulationAt);
				if (currentPosition.x < nextTabulationAt)	// if we enter this, slot is found
				{
					// LOG("SimplePrinter: Setting the x (current %d) to %d pixels\n", currentPosition.x, nextTabulationAt);
					currentPosition.x = nextTabulationAt;
					charInLineCount = nextTabulationAt / 5;
					// LOG("SimplePrinter: Current x: %d pixels\n", currentPosition.x);
					break;
				}
			}
			continue;
		}
		case '\n':
		{
			// LOG("SimplePrinter: detected a newline\n");
			charInLineCount = 0;
			lineCount++;
			currentPosition.x = 0;
			currentPosition.y += 8;
			continue;
		}
		}

		if (charInLineCount > maxCharInLine)	// safety check against too many characters in a single line
		{
			charInLineCount = 1;
			lineCount++;
			currentPosition.x = startPosition.x;
			currentPosition.y += 8;
		}

		if (lineCount > maxLinesInWindow)		// safety check against too many lines to draw
		{
			currentPosition.y = startPosition.y;
			lineCount = 1;
			charInLineCount = 1;
		}

		// Specifics of our font format
		uint8_t index = ch - 32;
		//LOG("SimplePrinter: index = %d\n", index);
		const uint8_t *data = font_data + (index << 3) + index;
		// LOG("SimplePrinter: *data = %d\n", *data);
		uint8_t escapement = *(data++);
		// LOG("SimplePrinter: escapement = %d\n", escapement);
		const Int2 size = { 8, 8 };
		// LOG("SimplePrinter: X: %d, Y: %d\n", currentPosition.x, currentPosition.y);
		fb->bitmap(currentPosition, size, data, 1);
		currentPosition.x += escapement;
	}
	vid.colormap[0] = backgroundColor;
	currentPosition.x = startPosition.x;
	currentPosition.y += 8;
	lineCount++;
}

void SimplePrinter::paintPrintingColor(RGB565 newBGColor)
{
	vid.colormap[1] = newBGColor;
	System::paint();
}
void SimplePrinter::paintPrintingBackColor(RGB565 newBGColor)
{
	backgroundColor = newBGColor;
	System::paint();
}

void SimplePrinter::refreshModeAndWindowPosition()
{
	switch (currentWindowPosition)
	{
	case Top:
	{
		localVideoBuffer.initMode(FB128, 0, 48);
		fb = &localVideoBuffer.fb128;
		// localVideoBuffer.colormap[0] = RGB565::fromRGB(0xc7c7fc);
		startPosition.x = 0;
		startPosition.y = 0;
		size.x = 128;
		size.y = 48;
		maxCharInLine = 25;
		maxLinesInWindow = 6;
		break;
	}
	case Center:
	{
		localVideoBuffer.initMode(FB128, 40, 48);
		fb = &localVideoBuffer.fb128;
		// localVideoBuffer.colormap[0] = RGB565::fromRGB(0xc7c7fc);
		startPosition.x = 0;
		startPosition.y = 0;
		size.x = 128;
		size.y = 48;
		maxCharInLine = 25;
		maxLinesInWindow = 6;
		break;
	}
	case Bottom:
	{
		localVideoBuffer.initMode(FB128, 80, 48);
		fb = &localVideoBuffer.fb128;
		// localVideoBuffer.colormap[0] = RGB565::fromRGB(0xc7c7fc);
		startPosition.x = 0;
		startPosition.y = 0;
		size.x = 128;
		size.y = 48;
		maxCharInLine = 25;
		maxLinesInWindow = 6;
		break;
	}
	default:
		break;
	}
}
