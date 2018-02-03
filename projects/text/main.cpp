/* -*- mode: C; c-basic-offset: 4; intent-tab	s-mode: nil -*-
 *
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include "fontdata.h"
#include "assets.gen.h"
#include "Environment.h"

using namespace Sifteo;


static Metadata M = Metadata()
    .title("Text SDK Example")
    .package("com.sifteo.sdk.text", "1.0")
    .icon(Icon)
    .cubeRange(3);

//static VideoBuffer vid[3];

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

    // vid.initMode(SOLID_MODE);
    // vid.colormap[0] = makeColor(0);
    // vid.attach(0);

    // System::paint();

    /*
     * Now set up a letterboxed 128x48 mode. This uses windowing to
     * start drawing on scanline 40, and draw a total of 48 scanlines.
     *
     * initMode() will automatically wait for the above rendering to finish.    
     */

    // vid.initMode(FB128, 0, 48);
    // vid.colormap[0] = makeColor(0);
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

// static const CubeSet allCubes(0, 1);
static const CubeSet cubes(0, 3);
static AssetSlot MainSlot = AssetSlot::allocate();
// .bootstrap(CustomGroup);
// static MyLoader loader(allCubes, MainSlot, &vid);

void printOnManyCubes()
{
		//AssetConfiguration<1> config;
		//config.append(MainSlot, CustomGroup);
		//ScopedAssetLoader loader;
		//loader.start(config, cubes);
		//loader.finish();
		//
		//vid[0].initMode(BG0);
  //      vid[0].attach(0);
		//vid[1].initMode(BG0);
  //      vid[1].attach(1);
		//vid[2].initMode(BG0);
  //      vid[2].attach(2);
		//vid[0].bg0.image(vec(0,0), CustomImage);
		//
		//vid[1].bg0.image(vec(0,0), CustomImage);

		//vid[2].bg0.image(vec(0,0), CustomImage);
		//
		//System::paint();
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
    // initDrawing();

	
	// text.println("aaaa");
	// text.println("\t\tabc");
	// text.println("\t\t\tabc");
	// text.println("12345678901234567890123456");
	// text.println("\t\t\t\t\tabc");
	// text.println("\t\t\t\t\t\t\t\t\t\tkk");
    // loader.load(WhiteImage.assetGroup(), MainSlot);
	
	Environment env;
	env.init(3,3);
	CubeWrapper cw = env.getCube(0);
	env.getVideoBuffer(0);
	//env.setMetadata("title", "package", "version", Icon);

	PrintWindowPosition pwp = Center;
	//CubeWrapper cw;
	//cw.defaultInit();
	cw.showAsset(WhiteImage);
	//cw.setPrinterTo(pwp);
	RGB565 color = RGB565::fromRGB(0xFF0000);
	//cw.showColor(color);
	for (unsigned i = 0; i < 0x100; i += 4) { System::paint(); }
	//PrintWindowPosition pwp = Center;
	//SimplePrinter sp(vid[0], pwp);
	//sp.print("razdwatrzy");

	cw.showColor(color);
	for (unsigned i = 0; i < 0x100; i += 4) { System::paint(); }
	env.loadAssetToCube(0, 0, CustomGroup, WhiteImage);
	for (unsigned i = 0; i < 0x100; i += 4) { System::paint(); }
	//RGB565 color = RGB565::fromRGB(0xFF0000);
	//cw.showAsset(WhiteImage);
	//cw.videoBuffer->attach(0);
	cw.getPrinter().paintPrintingBackColor(RGB565::fromRGB(0x00FF00));
	cw.getPrinter().paintPrintingColor(RGB565::fromRGB(0xFF0000));
	//SimplePrinter sp;
	//sp.init(env.getVideoBuffer(0), pwp);
	//sp.print("abc");
	//printOnManyCubes();
		while (1) {
			//cw.getPrinter().init(env.getVideoBuffer(0), pwp);
			cw.println("cokol\twiek\n");
		for (unsigned i=0; i < 0x200; i += 4)
		{
			//env.getVideoBuffer(0).bg0.image(vec(0, 0), WhiteImage);
		
		// PrintWindowPosition winpos = Top;
		// SimplePrinter topPrinter(vid, winpos);
		// RGB565 topbgcolor = RGB565::fromRGB(0xFF0000);
		// topPrinter.paintPrintingBackColor(topbgcolor);
		// topPrinter.print("1234567890123456789+_+-012345435345634");
		// for (unsigned i=0; i < 0x200; i += 4)
		// {
			// System::paint();
		// }
		// winpos = Center;
		// SimplePrinter centerPrinter(vid, winpos);
		// UByte3 newcolor = { 0xFF, 0x00, 0x00};
		// centerPrinter.paintBackgroundColor(newcolor);
		// centerPrinter.print("12345\n\n67890123456789012345566565");
		// for (unsigned i=0; i < 0x200; i += 4)
		// {
			// System::paint();
		// }
		// winpos = Bottom;
		// SimplePrinter bottomPrinter(vid, winpos);
		// RGB565 textcolor = RGB565::fromRGB(0x00FF00);
		// bottomPrinter.paintPrintingColor(textcolor);
		// bottomPrinter.print("1234567890123456789012345");

			//vid[0].bg0.image(vec(0,0), WhiteImage);
			// vid[1].bg0.image(vec(0,0), WhiteImage);
			// vid[2].bg0.image(vec(0,0), WhiteImage);
			// LOG("Connected: %d\n", CubeSet::connected());
			
			System::paint();
			//System::finish();
		}
    }
}

