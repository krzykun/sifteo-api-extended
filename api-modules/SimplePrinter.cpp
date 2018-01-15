#include "SimplePrinter.h"


void SimplePrinter::print(char* toPrint)
{
	FB128Drawable &fb;
	UByte2 position;
	while (toPrint != 0)
	{
		uint8_t index = *toPrint - ' ';
		const uint8_t *data = font_data + (index << 3) + index;
		uint8_t escapement = *(data++);
		const Int2 size = { 8, 8 };

		fb.bitmap(position, size, data, 1);
		position.x += escapement;
		toPrint++;
	}
}