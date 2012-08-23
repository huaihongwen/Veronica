#include "veRenderSystem.h"
#include "veShaderProgram.h"
#include "veFramebufferObject.h"

// OpenGL stuffs
#include <windows.h>
#include <GL\glew.h>

namespace vee {

	//---------------------------------------------------------------
	RenderSystem::RenderSystem() {

		mCurProgram = NULL;
		mCurFBO = NULL;
	}
	//---------------------------------------------------------------
	RenderSystem::~RenderSystem() {
	}


	//---------------------------------------------------------------
	// Initialize the static member
	template<> RenderSystem* SingletonVee<RenderSystem>::ms_Singleton = 0;
	RenderSystem& RenderSystem::getSingleton(void) {

		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	RenderSystem* RenderSystem::getSingletonPtr(void) {

		return ms_Singleton;
	}


	//---------------------------------------------------------------
	// Set window size
	void RenderSystem::setWindowSize(int width, int height) {

		mWindowWidth = width;
		mWindowHeight = height;
	}
	//---------------------------------------------------------------
	// Get window width
	int RenderSystem::getWindowWidth() {

		return mWindowWidth;
	}
	//---------------------------------------------------------------
	// Get window height
	int RenderSystem::getWindowHeight() {

		return mWindowHeight;
	}


	//---------------------------------------------------------------
	// Set viewport for current FBO
	void RenderSystem::setViewport(int x, int y, int width, int height) {

		// View port
		glViewport(x, y, (GLsizei)width, (GLsizei)height);
	}
	//---------------------------------------------------------------
	// Push viewport
	void RenderSystem::pushViewport() {
		glPushAttrib(GL_VIEWPORT_BIT);
	}
	//---------------------------------------------------------------
	// Pop viewport
	void RenderSystem::popViewport() {
		glPopAttrib();
	}


	//---------------------------------------------------------------
	// Set ortho projection
	void RenderSystem::setOrthoProjection(float l, float r, float b, float t) {

		// Clear projection matrix
		glMatrixMode(GL_PROJECTION);	
		glLoadIdentity();

		glOrtho(l, r, b, t, -0.1f, 100.0f);
	}

	//---------------------------------------------------------------
	// Set perspective projection
	void RenderSystem::setPerspectiveProjection(Transform perspective) {

		// Clear projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float pArray[16];
		perspective.toArray(pArray);
		glLoadMatrixf(pArray);
	}

	//---------------------------------------------------------------
	// Push projection
	void RenderSystem::pushProjection() {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
	}
	//---------------------------------------------------------------
	// Pop projection
	void RenderSystem::popProjection() {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	}


	//---------------------------------------------------------------
	// Set modelview
	void RenderSystem::setModelView(Transform modelview) {

		// Clear modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		float mvArray[16];
		modelview.toArray(mvArray);
		glLoadMatrixf(mvArray);
	}

	//---------------------------------------------------------------
	// Identity model view
	void RenderSystem::identityModelView() {

		// Clear modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}


	//---------------------------------------------------------------
	// Push modelview
	void RenderSystem::pushModelView() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
	}
	//---------------------------------------------------------------
	// Pop modelview
	void RenderSystem::popModelView() {
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}


	//---------------------------------------------------------------
	// Clear buffers for current FBO
	void RenderSystem::clearBuffers(GLbitfield mask) {

		glClear(mask);
	}

	//---------------------------------------------------------------
	// Draw buffers for current FBO
	void RenderSystem::drawBuffers(vector<GLenum>* buffers) {

		uint size = buffers->size();

		GLenum* arr = new GLenum[size];
		for (uint i = 0; i < size; i++) {
			arr[i] = buffers->at(i);
		}

		glDrawBuffers(size, arr);

		delete [] arr;
	}


	//---------------------------------------------------------------
	// Enable texture 2d
	void RenderSystem::enableTexture2D() {

		// Enable texture
		glEnable(GL_TEXTURE_2D);
	}
	//---------------------------------------------------------------
	// Diable texture 2d
	void RenderSystem::disableTexture2D() {

		// Enable texture
		glDisable(GL_TEXTURE_2D);
	}

	//---------------------------------------------------------------
	// Bind texture 2d to current texture unit
	void RenderSystem::bindTexture2D(GLuint tex, uint unit) {

		// Active texture unit
		glActiveTexture(GL_TEXTURE0+unit);

		// Unbind texture 2d
		if (tex == 0) {

			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);

			return;
		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);
	}


	//---------------------------------------------------------------
	// Use FBO
	void RenderSystem::bindFBO(FramebufferObject* fbo) {

		GLuint id = fbo ? fbo->getId() : 0;

		// Bind default fbo
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id);
		mCurFBO = fbo;
	}

	//---------------------------------------------------------------
	// Use shader program
	void RenderSystem::useProgram(ShaderProgram* program) {

		GLuint id = program ? program->getId() : 0;

		// Use default program
		glUseProgram(id);
		mCurProgram = program;
	}
};