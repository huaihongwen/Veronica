#ifndef VEE_TEXTURE_H
#define VEE_TEXTURE_H

/* Basic texture
 */

#include "vePrerequisites.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	// Basic texture
	class Texture {

	public:
		Texture() {

			mWidth = 0;
			mHeight = 0;

			mMiplevel = 0;

			mId = 0;
		}
		~Texture() {

			// Destroy
			destroy();
		}

	public:
		// Initialize texture
		/* @param width {uint} width of the texture
		 * @param height {uint} height of the texture
		 * @param internalFormat {GLint} internal format of the texture
		 * @param format {GLenum} format of the texture
		 * @param pixelType {GLenum} pixel type of the texture
		 * @param data {uchar*} data pointer
		 */
		void init(uint width, uint height,
			GLint internalFormat, GLenum format, GLenum pixelType, uchar* data=NULL) {

			mWidth = width;
			mHeight = height;

			// Generate texture
			glGenTextures(1, &mId);

			// Bind it to be the current texture
			glBindTexture(GL_TEXTURE_2D, mId);

			// Setup texture parameters
			// Anti-aliasing
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			// Texture coordinates
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// Data, in our engine empty data is enough
			glTexImage2D(GL_TEXTURE_2D, mMiplevel, internalFormat, mWidth, mHeight, 0,
				format, pixelType, data);

			// Bind to default
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Destroy
		void destroy() {

			// Delete it from OpenGL
			glDeleteTextures(1, &mId);
		}

	public:
		// Get miplevel
		uint getMiplevel() { 
			return mMiplevel; 
		}

		// Get id
		GLuint getId() { 
			return mId; 
		}

		// Get width
		uint getWidth() {
			return mWidth;
		}

		// Get height
		uint getHeight() {
			return mHeight;
		}

	protected:
		// Texture width
		uint mWidth;
		// Texture height
		uint mHeight;

		// Texture miplevel
		uint mMiplevel;

		// Texture id
		GLuint mId;
	};
};

#endif