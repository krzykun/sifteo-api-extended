#pragma once
#include <string.h>
#include "Common.h"

class SimplePrinter
{
	FB128Drawable* fb;
	VideoBuffer& localVideoBuffer;
	UByte2 startPosition;
	UByte2 size;
	UByte2 currentPosition;
	int lineCount = 1;
	int charInLineCount = 0;
	unsigned maxCharInLine;
	unsigned maxLinesInWindow;
	PrintWindowPosition currentWindowPosition;
	RGB565 backgroundColor = RGB565::fromRGB(0xc7c7fc);
public:
	SimplePrinter(VideoBuffer& videoBuffer, PrintWindowPosition windowPosition);
	void print(const char* str);
	void println(const char* str);
	void paintPrintingColor(RGB565 newBGColor);
	void paintPrintingBackColor(RGB565 newBGColor);

private:

	void refreshModeAndWindowPosition();
};

