#pragma once
//#include "sifteo.h"
//#include "GraphicsEngine.h"
#include "SimplePrinter.h"
//#include "Common.h"

using namespace Sifteo;

struct CubeWrapper
{
	unsigned ID;
	char Alias; //char [20]?
	VideoBuffer* videoBuffer;
	// GraphicsEngine graphics;
	SimplePrinter printer;

	void init(VideoBuffer* newVidBuf, unsigned id)
	{
		ID = id;
		videoBuffer = newVidBuf;
		//cubeID = newCubeID;
		PrintWindowPosition pwp = Center;
		setPrinterTo(newVidBuf, pwp);
		printer.backgroundColor = RGB565::fromRGB(0xC7C7FC);
	}

	//void setAlias(const char* newAlias, unsigned length)
	//{
	//	this->Alias = new char[length];
	//	memcpy8((uint8_t*) this->Alias, (const uint8_t*)newAlias, length);
	//}

	//const char* getAlias()
	//{
	//	return this->Alias;
	//}

	void print(const char * string)
	{
		videoBuffer->attach(ID);
		printer.print(string);
		System::paint();
		System::finish();
	}

	void print(const char * string, PrintWindowPosition winPos)
	{
		videoBuffer->attach(ID);
		setPrinterTo(videoBuffer, winPos);
		printer.print(string);
		System::paint();
		System::finish();
	}

	void println(const char* string)
	{
		videoBuffer->attach(ID);
		printer.println(string);
		System::paint();
		System::finish();
	}

	void println(const char * string, PrintWindowPosition winPos)
	{
		videoBuffer->attach(ID);
		setPrinterTo(videoBuffer, winPos);
		printer.println(string);
		System::paint();
		System::finish();
	}

	//void moveAssetTo()
	//{
	//	return;
	//}

	SimplePrinter& getPrinter()
	{
		return printer;
	}

	// void setLoadingScreen(LoadingScreen screenData);
	void showColor(RGB565 newBGColor)
	{
		videoBuffer->initMode(SOLID_MODE);
		videoBuffer->attach(ID);
		videoBuffer->colormap[0] = newBGColor;
		System::paint();
		System::finish();
	}
	void showColor(UByte3 newBGColor)
	{
		videoBuffer->initMode(SOLID_MODE);
		videoBuffer->attach(ID);
		videoBuffer->colormap[0] = RGB565::fromRGB(newBGColor.x, newBGColor.y, newBGColor.z);
		System::paint();
		System::finish();
	}
	void showAsset(AssetImage image)
	{
		videoBuffer->initMode(BG0);
		videoBuffer->attach(ID);
		videoBuffer->bg0.image(vec(0, 0), image);
		System::paint();
		System::finish();
	}

	//this is private
	void setPrinterTo(VideoBuffer* vidBufParam, PrintWindowPosition winPos)
	{
		//SimplePrinter newPrinter;
		//printer = newPrinter;
		printer.init(vidBufParam, winPos);
	}
};