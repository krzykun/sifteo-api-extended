#pragma once

#include "Cubewrapper.h"
#include "SimplePrinter.h"
#include "..\..\include\sifteo\array.h"
#include "..\..\include\sifteo\video.h"
#include "..\..\include\sifteo\cube.h"
#include "..\..\include\sifteo\asset.h"
#include "..\..\include\sifteo\asset\group.h"
#include "..\..\include\sifteo\abi\types.h"
#include "..\..\include\sifteo\asset\loader.h"

using namespace Sifteo;

struct Environment
{
	static const unsigned gNumCubes = 3;
	Environment(){}
	~Environment(){}

	CubeWrapper Cube0, Cube1, Cube2;
	VideoBuffer videoBufferArray[gNumCubes];
	Metadata meta;
	AssetSlot assetSlot0 = AssetSlot::allocate();
	AssetSlot assetSlot1 = AssetSlot::allocate();
	AssetSlot assetSlot2 = AssetSlot::allocate();
	AssetConfiguration<3> assetConfiguration;

	void init(unsigned cubeCount, unsigned slotCount)
	{
		//meta.cubeRange(cubeCount);
		for (unsigned i = 0; i < cubeCount; i++)
		{

		}
		//CubeSet::iterator iter;
		Cube0.init(&videoBufferArray[0], 0);
		Cube1.init(&videoBufferArray[1], 1);
		Cube2.init(&videoBufferArray[2], 2);
		//cubes = new CubeSet(0, 3);
		//Events::cubeConnect.set(&activeCubesListener, this);
	}

	int loadAssetToCube(unsigned CubeID, unsigned assetSlotNumber, AssetGroup assetgroup, AssetImage image)
	{
		if (CubeID > 2) return 1;		//at this moment, we have only 3 cubes active: 0, 1 and 2
		CubeSet cubes(CubeID);
		switch (assetSlotNumber)
		{
		case 0:
			assetConfiguration.append(assetSlot0, assetgroup);
			break;
		case 1:
			assetConfiguration.append(assetSlot1, assetgroup);
			break;
		case 2:
			assetConfiguration.append(assetSlot2, assetgroup);
			break;
		default:
			return -1;	//error code
		}
		ScopedAssetLoader loader;
		loader.start(assetConfiguration, cubes);
		loader.finish();
		videoBufferArray[CubeID].initMode(BG0);
		videoBufferArray[CubeID].attach(CubeID);
		videoBufferArray[CubeID].bg0.image(vec(0, 0), image);
		System::paint();
		System::finish();
		return 1;
	}

	CubeWrapper& getCube(unsigned index)
	{
		switch (index)
		{
		case 0:
			return Cube0;
		case 1:
			return Cube1;
		case 2:
			return Cube2;
		default:
			return Cube0;
		}
	}

	VideoBuffer& getVideoBuffer(unsigned index)
	{
		return videoBufferArray[index];
	}

	void setMetadata(const char* newTitle, const char* newPackage, const char* version, AssetImage newIcon)
	{
		return;
	}

	//out of scope
	//void setBGColor(UByte3 newBGColor, CubeSet cubeSet)
	//{
	//	for (CubeSet::iterator iter = cubeSet.begin; iter < cubeSet.end; iter++)
	//	{
	//		switch (iter.index)
	//		{
	//		case 0:
	//			Cube0.showColor(newBGColor);
	//			break;
	//		case 1:
	//			Cube1.showColor(newBGColor);
	//			break;
	//		case 2:
	//			Cube2.showColor(newBGColor);
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}
	//void setBGAsset(const char* assetName, CubeSet cubeSet) {}
	};

//Sifteo::Array<CubeWrapper, 3> availableCubes;
//Sifteo::Array<CubeSet, 3> cubeSetVector;
//static CubeWrapper *ActiveCubes;
/*
Out of scope
*/
//CubeWrapper& getCube(const char* aliasParameter)
//{
//	return cubeWrapperArray[0]; //todo
//}

/*
Out of scope, ambiguous call to function (first param ambiguous)
*/
//static void loadAssetToCube(const char* CubeAlias, unsigned assetSlotNumber, AssetGroup assetgroup, AssetImage image)
//{
//	return;
//}

/*
Out of scope
*/
//void sendImageFromCubeToCube(unsigned fromIndex, unsigned toIndex)
//{
//	return;
//}


	//void moveAsset(const char* assetName, CubeID destCube) {}
	//void moveAsset(const char* assetName, CubeSet destCubeSet) {}
	//void activeCubesListener(void*, unsigned)
	//{
	//	
	//}
	//int activateCube(unsigned ID, const char* alias) { return 0; }
	//int deactivateCube(unsigned ID) { return 0; }
//static void setProjectProperties(char* newTitle, char* const newPackage, static const unsigned cubeCountNeeded, Icon icon);
//static void setLoadingPhaseFor(LoadingScreen screenData, const unsigned CubeID);
//static void setLoadingPhaseFor(LoadingScreen screenData, char* const CubeAlias);
//static void setLoadingPhaseFor(LoadingScreen screenData, unsigned* const CubeIDs, unsigned count);
//static void setLoadingPhaseFor(LoadingScreen screenData, char** const CubeAliases, unsigned count);
//init videobuffer
//int activateCube(unsigned ID)
//{
//	System::yield();	// lets trigger the events and let cubes be discovered
//	return 0;
//}