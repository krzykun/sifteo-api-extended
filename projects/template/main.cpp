/*=======================================================

	template

Project template.

By:
Version:
=======================================================*/
#include <sifteo.h>
using namespace Sifteo;

static Metadata M = Metadata()
	.title("New project")
	.package("TBD", "1.0");
    .cubeRange(1);

void main()
{
	while (true)
	{
		System::paint();
	}
}
