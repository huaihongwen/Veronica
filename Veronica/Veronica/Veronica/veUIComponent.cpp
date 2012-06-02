#include "veUIComponent.h"
#include "veRenderSystem.h"
#include "veTexture.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	//---------------------------------------------------------------
	Rect::Rect() {

		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
	//---------------------------------------------------------------
	Rect::Rect(int xPos, int yPos, int width, int height) {

		x = xPos;
		y = yPos;
		w = width;
		h = height;
	}
	//---------------------------------------------------------------
	Rect::~Rect() {
	}


	// Contain test with point
	bool Rect::containPoint(int px, int py) {

		// Out side of range
		if (px < x || px > x+w || py < y || py > y+h) {
			return false;
		}

		return true;
	}

	//---------------------------------------------------------------
	// =
	void Rect::operator = (const Rect& r) {

		x = r.x;
		y = r.y;
		w = r.w;
		h = r.h;
	}


	//---------------------------------------------------------------
	UIComponent::UIComponent() {
	}
	//---------------------------------------------------------------
	UIComponent::UIComponent(string name, Rect& rect) {

		mName = name;
		mRect = rect;

		// Background color
		mBackground[0] = 0.0f; mBackground[1] = 0.0f; mBackground[2] = 0.0f;
	}
	//---------------------------------------------------------------
	UIComponent::~UIComponent() {
	}


	//---------------------------------------------------------------
	// Set color
	void UIComponent::setBackgroundColor(float r, float g, float b) {

		mBackground[0] = r; mBackground[1] = g; mBackground[2] = b;
	}

	//---------------------------------------------------------------
	// Render with background color
	void UIComponent::render() {

		// Prepare
		_prepare();
		
		// Simple background
		_renderBackground();

		// End
		_end();
	}


	// Hit test
	bool UIComponent::hitTest(int px, int py) {

		// Test whether rect contains the hit point
		bool result = mRect.containPoint(px, py);

		// Handle hit
		if (result) {
			_handleHit(px, py);
		}

		return result;
	}

	//---------------------------------------------------------------
	// Prepare
	void UIComponent::_prepare() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();
		// Get window size
		int width = rs.getWindowWidth();
		int height = rs.getWindowHeight();

		// Ortho projection
		rs.setOrthoProjection(0.0f, (float)width, 0.0f, (float)height);
		// Viewport
		rs.setViewport(0, 0, width, height);
		// Model view identity
		rs.identityModelView();

		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);
	}

	//---------------------------------------------------------------
	// End
	void UIComponent::_end() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();
		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);
	}

	//---------------------------------------------------------------
	// Render background
	void UIComponent::_renderBackground() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();
		// Get window size
		int width = rs.getWindowWidth();
		int height = rs.getWindowHeight();

		// Render a single quad
		glColor3f(mBackground[0], mBackground[1], mBackground[2]);
		glBegin(GL_QUADS);
			glVertex3f((float)(mRect.x+mRect.w), (float)(height-mRect.y), -1.0f);
			glVertex3f((float)(mRect.x+mRect.w), (float)(height-mRect.y-mRect.h), -1.0f);
			glVertex3f((float)(mRect.x), (float)(height-mRect.y-mRect.h), -1.0f);
			glVertex3f((float)(mRect.x), (float)(height-mRect.y), -1.0f);
		glEnd();
	}

	//---------------------------------------------------------------
	// Render with texture
	void UIComponent::render(Texture* t) {

		// Prepare
		_prepare();

		_renderBackground(t);
	}

	//---------------------------------------------------------------
	// Render background with texture
	void UIComponent::_renderBackground(Texture* t) {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();
		// Get window size
		int width = rs.getWindowWidth();
		int height = rs.getWindowHeight();


		rs.bindTexture2D(t->getId(), 0);

		// Render a single quad
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f((float)(mRect.x+mRect.w), (float)(height-mRect.y), -1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f((float)(mRect.x+mRect.w), (float)(height-mRect.y-mRect.h), -1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f((float)(mRect.x), (float)(height-mRect.y-mRect.h), -1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f((float)(mRect.x), (float)(height-mRect.y), -1.0f);
		glEnd();

		rs.bindTexture2D(0, 0);
	}

};