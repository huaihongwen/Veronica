#ifndef VEE_UICOMPONENT_H
#define VEE_UICOMPONENT_H

/* Basic UI component
 */

#include "vePrerequisites.h"

namespace vee {

	// Rect
	class Rect {

	public:
		Rect();
		Rect(int x, int y, int width, int height);
		~Rect();

	public:
		// Contain test with point
		bool containPoint(int px, int py);

		// =
		void operator = (const Rect& r);

	public:
		int x; // Upper left corner x relative to parent
		int y; // Upper left corner y relative to parent
		int w; // Width
		int h; // Height
	};


	// UI component
	class UIComponent {

	public:
		UIComponent();
		UIComponent(string name, Rect& rect);
		~UIComponent();

	public:
		// Set background color
		void setBackgroundColor(float r, float g, float b);

		// Render
		void render();

		// Render with texture
		void render(Texture* t);


		// Hit test
		bool hitTest(int px, int py);

		// Handle move
		virtual void handleMove(int dx, int dy) {
		}

	protected:
		// Prepare render
		void _prepare();
		// End
		void _end();

		// Render background
		void _renderBackground();

		// Render background with texture
		void _renderBackground(Texture* t);


		// Handle hit
		virtual void _handleHit(int px, int py) {
		}

	protected:
		// Name
		string mName;
		
		// Rect
		Rect mRect;

		// background color
		float mBackground[3];
	};
};

#endif