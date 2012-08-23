#ifndef VEE_SHADERPROGRAM_H
#define VEE_SHADERPROGRAM_H

/* Basic shader program
 */

#include "vePrerequisites.h"
#include "veShader.h"

// For uniforms and attributes
#include <map>

namespace vee {

	// Uniform variables
	typedef map<string, GLuint> UniformMap;

	class ShaderProgram {

	public:
		ShaderProgram();
		~ShaderProgram();

	protected:
		// Print program info log
		void _printInfoLog();

	public:
		// Get id
		GLuint getId() {
			return mId;
		}

		// Link this program
		int link();

		// Initialize a shader program
		void init(string name);

		// Attach shader to the program
		void attachShader(Shader* shader);

	public:
		// Get uniform location
		GLuint getUniformLocation(const char* uniformName);

		// Set uniform 1i
		void setUniform1i(const char* uniformName, GLint value);
		// Set uniform 1f
		void setUniform1f(const char* uniformName, GLfloat value);
		// Set uniform matrix 4fv
		void setUniformMatrix4fv(const char* uniformName, GLfloat* value);

	protected:
		// Name of the program
		string mName;
		
		// Whether this program is linked
		bool mLinked;

		// Id of the program
		GLuint mId;
	};

};

#endif