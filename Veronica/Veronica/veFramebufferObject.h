#ifndef VEE_FRAMEBUFFEROBJECT_H
#define VEE_FRAMEBUFFEROBJECT_H

/* Frame buffer object
 */

#include "vePrerequisites.h"
#include "veTexture.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	// Frame buffer object
	class FramebufferObject {

	public:
		FramebufferObject() {

			// Not ready
			mReady = false;

			// Generate OpenGL FBO
			glGenFramebuffersEXT(1, &mId);

			// Attack depth render buffer

		}
		~FramebufferObject() {

			// Delete OpenGL FBO
			glDeleteFramebuffersEXT(1, &mId);
		}


	public:
		// Get id
		GLuint getId() {
			return mId;
		}

		// Attach 2d texture to frame buffer object
		void attachTexture2D(GLenum attachPoint, veTexture* texture) {

			// Bind current
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mId);

			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attachPoint, GL_TEXTURE_2D,
				texture->getId(), texture->getMiplevel());
			// Check status
			if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_COMPLETE_EXT) {
				mReady = true;
			}

			// Back to default
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}


	protected:
		bool mReady; // Ready or not
		GLuint mId; // Frame buffer object id
	};
};

#endif