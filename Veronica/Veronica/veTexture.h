/**
 * veTexture.h
 */

#ifndef VEE_TEXTURE_H
#define VEE_TEXTURE_H

#include "vePrerequisites.h"
#include "veTGALoader.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	// Basic texture
	class veTexture {

	public:
		veTexture() {

			mWidth = 0;
			mHeight = 0;

			mMiplevel = 0;

			mId = 0;
		}
		~veTexture() {

			// Destroy
			destroy();
		}

	public:
		// Initializes texture
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
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			// Data, in our engine empty data is enough
			glTexImage2D(GL_TEXTURE_2D, mMiplevel, internalFormat, mWidth, mHeight, 0,
				format, pixelType, data);

			// Bind to default
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Reloads sub-image of the texture data for the current texture
		// @params
		// xOffset, yOffset (int)			x and y offset of the subimage
		// width, height (int)				Width and height of the new texture data
		// format (GLenum)					Pixel data format
		// pixelType (GLenum)				Data type of the pixel data
		// data (uchar*)					Pointer to the data
		// @return
		void reUpload(int xOffset, int yOffset, int width, int height, GLenum format, GLenum pixelType, uchar* data=NULL) {

			// Bind it again before upload new texture data
			glBindTexture(GL_TEXTURE_2D, mId);

			// Re-upload texture data
			//glTexImage2D(GL_TEXTURE_2D, mMiplevel, internalFormat, mWidth, mHeight, 0,
			//	format, pixelType, data);

			glTexSubImage2D(GL_TEXTURE_2D, mMiplevel, xOffset, yOffset, mWidth, mHeight,
				format, pixelType, data);

			// Bind to default
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Load texture data from TGA img
		// @params
		// filename (const char*)			The name of the TGA file
		// @return
		void loadDataFromTGA(const char* filename) {

			// TGA data
			TGAData tgaData;
			// Load tgaData from file
			TGALoader::loadTGAFile(&tgaData, filename);

			GLenum format, internalFormat;
			// Texture format
			switch (tgaData.mBitsPP / 8)
			{
				case 3:
					format = GL_RGB;
					internalFormat = GL_RGB8;
					break;
				case 4:
					format = GL_RGBA;
					internalFormat = GL_RGBA8;
					break;
				default:
					break;
			}

			// Initialize the texture
			this->init(tgaData.mWidth, tgaData.mHeight,
				internalFormat, format, GL_UNSIGNED_BYTE, tgaData.mData);
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
		int mMiplevel;

		// Texture id
		GLuint mId;
	};
};

#endif