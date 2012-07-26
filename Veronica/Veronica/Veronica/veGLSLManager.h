#ifndef VEE_GLSLMANAGER_H
#define VEE_GLSLMANAGER_H

/* Basic glsl manager
 */

#include "vePrerequisites.h"
#include "veSingleton.h"

#include "veShaderProgram.h"
#include <map>

namespace vee {

	// Define ShaderMap and ShaderProgramMap
	typedef map<string, Shader*> ShaderMap;
	typedef map<string, ShaderProgram*> ShaderProgramMap;

	// GLSL manager
	class GLSLManager : public SingletonVee<GLSLManager> {

	public:
		GLSLManager();
		~GLSLManager();

	public:
		// Get singleton
		static GLSLManager& getSingleton(void);
		static GLSLManager* getSingletonPtr(void);

	public:
		// Create a shader
		void createShader(string name, GLenum type, const char* filename);

		// Create a single shader program
		void createShaderProgram(string name);

		// Attach shader to a program
		void attachShaderToProgram(string sName, string pName);

		// Link a shader program
		int linkProgram(string pName);

		// Operator []
		ShaderProgram* operator[](const string &pName);

	protected:
		// Shaders
		ShaderMap m_Shaders;

		// Programs
		ShaderProgramMap m_Programs;
	};

};

#endif