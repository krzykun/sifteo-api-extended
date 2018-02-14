#include <sifteo.h>
#include "assets.gen.h"

#include "Environment.h"

using namespace Sifteo;

static Metadata M = Metadata()
    .title("Printing example project")
    .package("com.sifteo.eapi.printing", "1.0")
    .cubeRange(3);

void main()
{
	Environment env;
	env.init(3, 1);
	env.loadAssetToCube(0, 0, CustomGroup, gateImage);
	System::finish();
	while (true)
	{
		for (unsigned i = 0; i < 0x200; i += 4)
		{
			System::paint();
		}
	}
}
