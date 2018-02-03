/*=======================================================

	bareMinimum
This project does literally nothing.

This project presents the critical pieces to a Sifteo app.
Every project is obliged to have a main.cpp file and a
makefile.

In makefile, you can change the name of the project.
With the wrong name in the makefile, Sifteo linker (Slinky)
will raise an exception.
=======================================================*/
//	sifteo.h contains all standard Sifteo API parts.
#include <sifteo.h>
using namespace Sifteo;

//	Although not critical for application launch, without Metadata
//	cubes will never display anything. Defining cubeRange parameter
//	is often the first thing you should do.

static Metadata M = Metadata()
    .cubeRange(1);

void main()
{
	//	Without main application loop of some sort, your application will be
	//	terminated by the Siftulator.
	while (true)
	{
		//	If you delete this instruction, and will not provide another,
		//	the Siftulator will raise an exception due to infinite loop
		//	with no operations.
		System::paint();
	}
}
