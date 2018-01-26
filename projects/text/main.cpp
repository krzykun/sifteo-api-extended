/* -*- mode: C; c-basic-offset: 4; intent-tab	s-mode: nil -*-
 *
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include "fontdata.h"
#include "assets.gen.h"
using namespace Sifteo;

static Metadata M = Metadata()
    .title("Text SDK Example")
    .package("com.sifteo.sdk.text", "1.0")
    .icon(Icon)
    .cubeRange(1);

static VideoBuffer vid;

struct CubeWrapper
{
	unsigned ID;
	CubeID ID;
	char* Alias;
	//GraphicsEngine graphics;
	void print(char*);
	void println(char*);//? moze
	void setBGColor(RGB565 newBGColor);
	void setBGColor(CubeID cubeNumber, uint16_t newBGColor);
	void setBGColor(CubeSet cubeSet, uint16_t newBGColor);
	void setBGAsset(CubeID cubeNumber, const char* assetName);
	void setBGAsset(CubeSet cubeSet, const char* assetName);
	void moveAsset(CubeID sourceCube, CubeID destCube, const char* assetName);
	void moveAsset(CubeID sourceCube, CubeSet destCubeSet, const char* assetName);
};

enum PrintWindowPosition {
	Top, Center, Bottom
};

struct SimplePrinter {
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
	
    // SimplePrinter(FB128Drawable &fb, unsigned startX, unsigned startY, unsigned sizeX, unsigned sizeY) // deprecated
	// {
		// startPosition.x = startX;
		// startPosition.y = startY;		
		// size.x = sizeX;
		// size.y = sizeY;
		// maxCharInLine = 25;
		// maxLinesInWindow = 6;
	// }
	
	SimplePrinter(VideoBuffer& videoBuffer, PrintWindowPosition windowPosition): localVideoBuffer(videoBuffer)
	{
		currentWindowPosition = windowPosition;
		currentPosition.x = startPosition.x;
		currentPosition.y = startPosition.y;
		localVideoBuffer.colormap[0] = backgroundColor;
		refreshModeAndWindowPosition();
		LOG("SimplePrinter: %d %d %d %d %d %d %d %d\n", startPosition.x, startPosition.y, size.x, size.y, maxCharInLine, maxLinesInWindow, currentPosition.x, currentPosition.y);
	}
	
	void print(const char* str) // TO DO TO BE UPDATED
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
					LOG("SimplePrinter: detected a tabulation %d %d %d\n", currentPosition.x, startPosition.x, size.x);
					if (currentPosition.x >= startPosition.x + size.x - 8)	// safety check against tab count over 6 (more than a single line can handle)
					{
						charInLineCount = 0;
						lineCount++;
						currentPosition.x = startPosition.x;
						currentPosition.y += 8;
					}
					
					for (unsigned nextTabulationAt = 20; nextTabulationAt < startPosition.x + size.x; nextTabulationAt += 20) // loop that checks tabulation slots
					{
						LOG("SimplePrinter: Inside the loop, x: %d, nextTabulationAt value: %d\n", currentPosition.x, nextTabulationAt);
						if (currentPosition.x < nextTabulationAt)	// if we enter this, slot is found
						{
							LOG("SimplePrinter: Setting the x (current %d) to %d pixels\n", currentPosition.x, nextTabulationAt);
							currentPosition.x = nextTabulationAt;
							charInLineCount = nextTabulationAt/5;
							LOG("SimplePrinter: Current x: %d pixels\n", currentPosition.x);
							break;
						}
					}
					continue;
				}
				case '\n':
				{
					LOG("SimplePrinter: detected a newline\n");
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
			LOG("SimplePrinter: index = %d\n", index);
			const uint8_t *data = font_data + (index << 3) + index;
			LOG("SimplePrinter: *data = %d\n", *data);
			uint8_t escapement = *(data++);
			LOG("SimplePrinter: escapement = %d\n", escapement);
			const Int2 size = {8, 8};
			LOG("SimplePrinter: X: %d, Y: %d\n", currentPosition.x, currentPosition.y);
			fb->bitmap(currentPosition, size, data, 1);
			currentPosition.x += escapement;
        }
		vid.colormap[0] = backgroundColor;	//0 is responsible for background, 1 for foreground
	}
	
	void println(const char* str)
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
					LOG("SimplePrinter: detected a tabulation %d %d %d\n", currentPosition.x, startPosition.x, size.x);
					if (currentPosition.x >= startPosition.x + size.x - 8)	// safety check against tab count over 6 (more than a single line can handle)
					{
						charInLineCount = 0;
						lineCount++;
						currentPosition.x = startPosition.x;
						currentPosition.y += 8;
					}
					
					for (unsigned nextTabulationAt = 20; nextTabulationAt < startPosition.x + size.x; nextTabulationAt += 20) // loop that checks tabulation slots
					{
						LOG("SimplePrinter: Inside the loop, x: %d, nextTabulationAt value: %d\n", currentPosition.x, nextTabulationAt);
						if (currentPosition.x < nextTabulationAt)	// if we enter this, slot is found
						{
							LOG("SimplePrinter: Setting the x (current %d) to %d pixels\n", currentPosition.x, nextTabulationAt);
							currentPosition.x = nextTabulationAt;
							charInLineCount = nextTabulationAt/5;
							LOG("SimplePrinter: Current x: %d pixels\n", currentPosition.x);
							break;
						}
					}
					continue;
				}
				case '\n':
				{
					LOG("SimplePrinter: detected a newline\n");
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
			LOG("SimplePrinter: index = %d\n", index);
			const uint8_t *data = font_data + (index << 3) + index;
			LOG("SimplePrinter: *data = %d\n", *data);
			uint8_t escapement = *(data++);
			LOG("SimplePrinter: escapement = %d\n", escapement);
			const Int2 size = {8, 8};
			LOG("SimplePrinter: X: %d, Y: %d\n", currentPosition.x, currentPosition.y);
			fb->bitmap(currentPosition, size, data, 1);
			currentPosition.x += escapement;
        }
		vid.colormap[0] = backgroundColor;
 		currentPosition.x = startPosition.x;
		currentPosition.y += 8;
		lineCount++;
	}
	
	void paintPrintingColor(RGB565 newBGColor)
	{
		vid.colormap[1] = newBGColor;
		System::paint();
	}
	
	void paintPrintingBackColor(RGB565 newBGColor)
	{
		backgroundColor = newBGColor;
		System::paint();
	}
	
	void paintBackgroundColor(RGB565 newBGColor)
	{
		vid.initMode(SOLID_MODE);
		vid.colormap[0] = newBGColor;
		System::paint();
		refreshModeAndWindowPosition();
	}

	void paintBackgroundColor(UByte3 newBGColor)
	{
		vid.initMode(SOLID_MODE);
		vid.colormap[0] = RGB565::fromRGB(newBGColor.x, newBGColor.y, newBGColor.z);
		System::paint();
		refreshModeAndWindowPosition();
	}
	
	struct videoHandler{ //obsolete?
		VideoMode currentVideoMode;
		
		void setVideoMode(VideoMode newVideoMode)
		{
			currentVideoMode = newVideoMode;
		}
		
		VideoMode getVideoMode()
		{
			return currentVideoMode;
		}
	};

private:
	void refreshModeAndWindowPosition()
	{
		switch(currentWindowPosition)
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
};

static RGB565 makeColor(uint8_t alpha)
{
    // Linear interpolation between foreground and background

    const RGB565 bg = RGB565::fromRGB(0x31316f);
    const RGB565 fg = RGB565::fromRGB(0xc7c7fc);

    return bg.lerp(fg, alpha);
}


static void fadeInAndOut(Colormap &cm)
{
    const unsigned speed = 4;
    const unsigned hold = 100;
    
    LOG(("~ FADE ~\n"));
    
    for (unsigned i = 0; i < 0x100; i += speed) {
        cm[1] = makeColor(i);
        System::paint();
    }

    for (unsigned i = 0; i < hold; i++)
        System::paint();

    for (unsigned i = 0; i < 0x100; i += speed) {
        cm[1] = makeColor(255 - i);
        System::paint();
    }
}

void initDrawing()
{
    /*
     * Init framebuffer, paint a solid background.
     */

    vid.initMode(SOLID_MODE);
    vid.colormap[0] = makeColor(0);
    vid.attach(0);

    System::paint();

    /*
     * Now set up a letterboxed 128x48 mode. This uses windowing to
     * start drawing on scanline 40, and draw a total of 48 scanlines.
     *
     * initMode() will automatically wait for the above rendering to finish.    
     */

    vid.initMode(FB128, 0, 48);
    vid.colormap[0] = makeColor(0);
}

void onRefresh(void*, unsigned cube)
{
    /*
     * This is an event handler for cases where the system needs
     * us to fully repaint a cube. Normally this can happen automatically,
     * but if we're doing any fancy windowing effects (like we do in this
     * example) the system can't do the repaint all on its own.
     */

    LOG("Refresh event on cube %d\n", cube);
    if (cube == 0)
        initDrawing();
}

void main()
{
    /*
     * Draw some text!
     *
     * We do the drawing while the text is invisible (same fg and bg
     * colors), then fade it in and out using palette animation.
     */

    // SimplePrinter text(vid.fb128, 0, 0, 128, 48);
	// vid.setWindow(80, 48);
    //Events::cubeRefresh.set(onRefresh);
    initDrawing();

	
	// text.println("aaaa");
	// text.println("\t\tabc");
	// text.println("\t\t\tabc");
	// text.println("12345678901234567890123456");
	// text.println("\t\t\t\t\tabc");
	// text.println("\t\t\t\t\t\t\t\t\t\tkk");

    while (1) {
		PrintWindowPosition winpos = Top;
		SimplePrinter topPrinter(vid, winpos);
		RGB565 topbgcolor = RGB565::fromRGB(0xFF0000);
		topPrinter.paintPrintingBackColor(topbgcolor);
		topPrinter.print("1234567890123456789+_+-012345435345634");
		for (unsigned i=0; i < 0x200; i += 4)
		{
			System::paint();
		}
		winpos = Center;
		SimplePrinter centerPrinter(vid, winpos);
		UByte3 newcolor = { 0xFF, 0x00, 0x00};
		//centerPrinter.paintBackgroundColor(newcolor);
		centerPrinter.print("12345\n\n67890123456789012345566565");
		for (unsigned i=0; i < 0x200; i += 4)
		{
			System::paint();
		}
		winpos = Bottom;
		SimplePrinter bottomPrinter(vid, winpos);
		RGB565 textcolor = RGB565::fromRGB(0x00FF00);
		bottomPrinter.paintPrintingColor(textcolor);
		bottomPrinter.print("1234567890123456789012345");
		for (unsigned i=0; i < 0x200; i += 4)
		{
			System::paint();
		}
    }
}

