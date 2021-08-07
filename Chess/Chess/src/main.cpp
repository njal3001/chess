#include <iostream> 
#include "chess/graphics/window.h"
#include "chess/utils/file.h"
#include "chess/graphics/shader.h"
#include "chess/maths/maths.h"
#include "chess/graphics/buffers/buffer.h"
#include "chess/graphics/buffers/vertexarray.h"
#include "chess/graphics/buffers/indexbuffer.h"
#include "chess/graphics/renderable2d.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/graphics/sprite.h"
#include "chess/utils/timer.h"
#include "chess/graphics/uilayer.h"
#include "chess/graphics/group.h"
#include "FreeImage.h"

#if 0
int main()
{
	using namespace Chess;
	using namespace Graphics;
	using namespace Maths;

	Window window("Chess", 960, 540);
	glClearColor(0, 0, 0, 1);

	Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader* shader2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");

	UILayer layer1(shader, 0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	UILayer layer2(shader2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.13f)
	{
		for (float x = 0; x < 16.0f; x += 0.13f)
		{
			layer1.add(new Sprite(Maths::Vec2(x, y), Maths::Vec2(0.08f, 0.08f), Maths::Vec4((float)rand() / RAND_MAX, 0, 1, 1)));
		}
	}

	Mat4x4 mat = Mat4x4::create_translation(Vec3(0.25f, 0.25f, 0.0f));
		
	Group* group = new Group(mat);
	group->add(new Sprite(Vec2(0.0f, 0.0f), Vec2(0.5f, 0.5f), Vec4(0.8f, 0.7f, 0.2f, 1.0f)));
	group->add(new Sprite(Vec2(0.125f, 0.125f), Vec2(0.25f, 0.25f), Vec4(0.4f, 1.0f, 0.7f, 1.0f)));

	layer2.add(group);

	Utils::Timer timer;
	float secs = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.clear();

		Vec2 mouse_pos = window.get_mouse_pos();
		Vec2 light_pos = Vec2(mouse_pos.x * (16.0f / 960.0f), 9.0f - mouse_pos.y * (9.0f / 540.0f));
		shader->enable();
		shader->set_uniform_2f("light_pos", light_pos);
		layer1.render();

		mat *= Mat4x4::create_translation(Vec3(0.25f, 0.25f, 0.0f));
		mat *= Mat4x4::create_rotation(0.1f, Vec3(0, 0, 1));
		mat *= Mat4x4::create_translation(Vec3(-0.25f, -0.25f, 0.0f));
		layer2.render();

		window.update();

		frames++;
		if (timer.elapsed() > secs + 1.0f)
		{
			secs++;
			std::cout << frames << " fps" << std::endl;
			frames = 0;
		}
	}
}
#endif

int main()
{

  const char* filename = "test.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	
	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if(!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
  unsigned int pitch = FreeImage_GetPitch(dib);

	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if((bits == 0) || (width == 0) || (height == 0))
		return false;

  // Reading image values from bottom left to top right
  for (int y = 0; y < height; y++)
  {
    BYTE* pixel = (BYTE*)bits; // Copying pointer?
    for (int x = 0; x < width; x++)
    {
      std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << std::endl;
      pixel += 3;
    }
    bits += pitch;
  }

  FreeImage_Unload(dib);
}
