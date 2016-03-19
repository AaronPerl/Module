#ifndef __MODULE__MODULEGAME_HPP__
#define __MODULE__MODULEGAME_HPP__

#include "ModuleDefines.hpp"
#include "GameObject.hpp"
#include "Book.hpp"
#include "GraphicsInterface.hpp"
#include "ThreadingInterface.hpp"
#include "AudioInterface.hpp"

namespace Module
{

/** The main class of Module. The ModuleGame class represents the core of Module. Its functionality ties together
 * that of the different interfaces. End users of Module (game developers) control Module through this class and not
 * by accessing interfaces, as those are meant to be abstracted away from users. Setting up a ModuleGame instance should
 * be the first thing done in a game that uses Module.
 */
class ModuleGame
{

	private:
		GraphicsInterface* graphics;	/**< The GraphicsInterface attached to this game */
		AudioInterface* audio;			/**< The AudioInterface attached to this game */
		ThreadingInterface* threading;	/**< The ThreadingInterface attached to this game */
		
		Book<GameObject> objects;		/**< The book of all GameObjects */
	public:
		ModuleGame();
		
		void attachGraphicsInterface(GraphicsInterface* newGraphics);
		void attachAudioInterface(AudioInterface* newAudio);
		void attachThreadingInterface(ThreadingInterface* newThreading);
		
		void startThread(ThreadObject* obj);
		
		void start();
		bool isRunning();
		
		// Game Objects
		GameObject* createGameObject();
		Book<GameObject>::size_type numObjects() const;
		GameObject* getGameObject(Book<GameObject>::size_type index);
		const GameObject* getGameObject(Book<GameObject>::size_type index) const;
		
		// Threading
		Mutex* createMutex();
		
		// Graphics
		Texture* loadTexture(const eastl::string&);
		void setMesh(GameObject* obj, Mesh* mesh);
		void setTexture(GameObject* obj, Texture* tex);
		unsigned long getMilliseconds();
		
		// Audio
		Sound* playSound(SoundClip*,GameObject*);                            	// Plays a Sound
		SoundClip* loadSoundClip(const eastl::string&, const eastl::string&);	// Loads SoundClip
		void unloadSoundClip(SoundClip*);                                    	// Unloads SoundClip
		void debugAudio();
};

/**
 * @return The current number of GameObject instances in this game.
 */
inline Book<GameObject>::size_type ModuleGame::numObjects() const
{
	return objects.size();
}

/**
 * @return A reference to the index'th GameObject in this game.
 */
inline GameObject* ModuleGame::getGameObject(Book<GameObject>::size_type index)
{
	return &objects[index];
}

/**
 * @return A const reference to the index'th GameObject in this game.
 */
inline const GameObject* ModuleGame::getGameObject(Book<GameObject>::size_type index) const
{
	return &objects[index];
}

/**
 * Creates a Mutex.
 * @return A pointer to the newly created Mutex
 */
inline Mutex* ModuleGame::createMutex()
{
	return threading->createMutex();
}

/**
 * Loads a given texture file
 * @param filename The name of the texture file to load
 * @return A pointer to the newly loaded Texture
 */
inline Texture* ModuleGame::loadTexture(const eastl::string& filename)
{
	return graphics->loadTexture(filename);
}

/**
 * Sets the Mesh component of a GameObject
 * @param obj The GameObject to set the Mesh component of
 * @param mesh The corresponding Mesh
 */
inline void ModuleGame::setMesh(GameObject* obj, Mesh* mesh)
{
	obj->mesh = mesh;
}

/**
 * Sets the Texture component of a GameObject
 * @param obj The GameObject to set the Texture component of
 * @param tex The corresponding Texture
 */
inline void ModuleGame::setTexture(GameObject* obj, Texture* tex)
{
	obj->texture = tex;
}

/**
 * @return The number of milliseconds that have elapsed since the start of the current game.
 */
inline unsigned long ModuleGame::getMilliseconds()
{
	return graphics->getMilliseconds();
}

/** Plays a Sound.
 * @param clip A pointer to the SoundClip that the Sound will be of.
 * @return A pointer to the Sound, which is currently playing.
*/
inline Sound* ModuleGame::playSound(SoundClip* clip, GameObject* gameObj = NULL)
{
	return audio->playSound(clip,gameObj);
}

/** Loads a SoundClip into memory.
 * @param name The name of the SoundClip, ie: "explosion."
 * @param fileName The name of the file to be loaded from.
 * @return A pointer to the loaded SoundClip.
*/
inline SoundClip* ModuleGame::loadSoundClip(const eastl::string& name, const eastl::string& fileName)
{
	return audio->loadSoundClip(name,fileName);
}

/** Prints out some useful Audio debugging information.
 */
inline void ModuleGame::debugAudio()
{
	audio->debugAudio();
}
 
}
#endif