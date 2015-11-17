#ifndef __SDLOPENGLTEXTURE_HPP__
#define __SDLOPENGLTEXTURE_HPP__

#include "SDLOpenGLInterface.hpp"
#include <ModuleDefines.hpp>
#include <Texture.hpp>
#include <stdexcept>

namespace Module
{
	class SDLOpenGLInterface;
	
	/**
	 * A Texture implementation for the SDLOpenGLInterface
	 */
	class SDLOpenGLTexture : public Texture
	{
		protected:
			GLuint textureID;
		public:
			Color getPixel(uint16_t x, uint16_t y) { throw std::runtime_error("getPixelColor not implemented!"); }
			Color getPixel(float x, float y) { throw std::runtime_error("getPixelColor not implemented!"); }
			friend class SDLOpenGLInterface;
	};
}

#endif
