#ifndef __MODULE__INPUTCALLBACK_HPP__
#define __MODULE__INPUTCALLBACK_HPP__

namespace Module {

/* An abstract class to hook into events triggered by user input, such as mouse and key presses.
 * Extend this class if you need to process these events.
 */
class InputCallback {
private:
public:

	/**
	 * Called when a mouse button is pressed down.
	 * @param x The x position of the mouse on screen.
	 * @param y The y position of the mouse on screen.
	 */
	virtual void onMouseDown(uint16_t x, uint16_t y) {}
	
	/**
	 * Called when a mouse button is released.
	 * @param x The x position of the mouse on screen.
	 * @param y The y position of the mouse on screen.
	 */
	virtual void onMouseUp(uint16_t x, uint16_t y) {}
	
	/**
	 * Called when the mouse position changes.
	 * @param x The final x position of the mouse on screen.
	 * @param y The final y position of the mouse on screen.
	 * @param dx The change in the x position of the mouse.
	 * @param dy The change in the y position of the mouse.
	 */
	virtual void onMouseMove(uint16_t x, uint16_t y, int16_t dx, int16_t dy) {}
	
	/**
	 * Called when a key is pressed.
	 * @param key The key that was pressed.
	 */
	virtual void onKeyDown(uint8_t key) {}
	
	/**
	 * Called when a key is released.
	 * @param key The key that was released.
	 */
	virtual void onKeyUp(uint8_t key) {}
};

}

#endif