#ifndef VEE_SHADER_H
#define VEE_SHADER_H

/* Basic shader
 */

#include "vePrerequisites.h"

#include <fstream>
#include <windows.h>
#include <GL\glew.h>

namespace vee {

	// File utilities
	class FileUtil {

	public:
		FileUtil() {}
		~FileUtil() {}

	public:
		// Get file lenght
		static int getFileLength(ifstream& fin) {

			if (!fin.good()) {

				return 0;
			} else {

				// Get length
				fin.seekg(0, ios_base::end);
				int length = (int)fin.tellg();
				fin.seekg(0, ios_base::beg);

				return length;
			}
		}
	};


	// Basic shader
	class Shader {

	public:
		Shader();
		~Shader();

	protected:
		// Print shader info log
		void _printInfoLog();

		// Load shader source from file
		int _loadShaderSource(const char* filename);

	public:
		// Initialize a shader
		int init(string name, GLenum type, const char* filename);

	public:
		// Get shader id
		GLuint getId() { return mId; }
		// Get shader type
		GLenum getType() { return mType; }

	protected:
		// Shader name
		string mName;

		// Shader type
		GLenum mType;

		// Whether this shader is been compiled
		bool mCompiled;

		// Shader id
		GLuint mId;
	};
};

#endif