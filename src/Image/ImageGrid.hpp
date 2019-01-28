#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <../Window/Window.hpp>


class ImageGrid : Image
{
	public:
		ImageGrid();
		ImageGrid(std::string path);
		~ImageGrid();
	private:
		int px;
		int py;
}
