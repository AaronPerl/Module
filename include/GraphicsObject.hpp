#ifndef __MODULE__GRAPHICSOBJECT_HPP__
#define __MODULE__GRAPHICSOBJECT_HPP__

#include "Mesh.hpp"
#include "TextureData.hpp"
#include "Texture.hpp"
#include "GraphicsInterface.hpp"

namespace Module
{
	class GraphicsObject
	{
		friend class GraphicsInterface;
		
		protected:
			Mesh* m;
			TextureData* textures;
			GraphicsObject(Mesh* m, TextureData* t): mesh(m), textures(t) {}
			
		public:
			const Mesh* getMesh()				{	return m;	}
			const TextureData* getTextures()	{	return t;	}
	};
}
#endif