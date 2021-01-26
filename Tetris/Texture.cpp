#include "Texture.h"

Texture::Texture(string path)
{
	loadFromBMP(path);
	if (texture == nullptr) return;

	//获取大小
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void Texture::loadFromBMP(string path)
{
	static std::string path_base = string(SDL_GetBasePath()) + "res\\";		//目录
	static Uint32 transparency = 0x000001;						//透明色

	SDL_Surface* loadedImage = SDL_LoadBMP((path_base + path).c_str());
	cout << "Texture::loadFromBMP: Load " << path_base + path<<endl;

	if (loadedImage == nullptr) {
		logError(path + "can't be loaded.");
		return;
	}
	

	//设置透明
	SDL_SetColorKey(loadedImage, SDL_TRUE, transparency);
	//创建纹理
	texture =  SDL_CreateTextureFromSurface(ren, loadedImage);
	SDL_FreeSurface(loadedImage);
	if (texture == nullptr) {
		logError("Can't create texture from surface.");
		return;
	}
}

void Texture::render(int x, int y, int h, int w)
{
	static SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.h = h;
	dst.w = w;

	SDL_RenderCopy(ren, texture, nullptr, &dst);
}

void Texture::render(int x, int y)
{
	static SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.h = height;
	dst.w = width;

	SDL_RenderCopy(ren, texture, nullptr, &dst);
}
