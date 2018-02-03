#include <sifteo.h>
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
	//env.getCube(0).getPrinter().
	env.getCube(0).print("1\n2\n3\n90");
	while (true)
	{
		System::paint();
	}
}
