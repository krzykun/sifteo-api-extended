/*=======================================================

	template

Project template.

By:
Version:
=======================================================*/
#include <sifteo.h>
#include "Environment.h"
using namespace Sifteo;

static Metadata M = Metadata()
	.title("New project")
	.package("TBD", "1.0");
    .cubeRange(1);

	Environment env;	// global environment object, for accessing the EAPI
	
void main()
{
	while (true)
	{
		for (unsigned i = 0; i < 0x200; i += 4)	//waiting loop, does nothing but paints for a second
		{
			System::paint();
		}
	}
}
