#ifndef __MODULE__TEXTURE_HPP__
#define __MODULE__TEXTURE_HPP__

#include <stdint.h>
#include "ModuleDefines.hpp"
namespace Module {

	/**
	 * A pure virtual class meant to be subclassed for interface implementation.
	 * Subclasses store an implentation-specific representation of a texture.
	 */
	class Texture {
	protected:
	public:
		/**
		 * Returns the color of a pixel at a given integer position
		 */
		virtual Color getPixel(uint16_t x, uint16_t y) = 0;
		/**
		 * Returns the color of a pixel at a given floating-point position
		 */
		virtual Color getPixel(float x, float y) = 0;
	};
}

#endif