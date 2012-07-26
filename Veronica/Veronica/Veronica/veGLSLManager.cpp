#include "veGLSLManager.h"

namespace vee {

	//---------------------------------------------------------------
	GLSLManager::GLSLManager() {
	}
	//---------------------------------------------------------------
	GLSLManager::~GLSLManager()  {

		map<string, Shader*>::const_iterator shader;
		for (shader = m_Shaders.begin(); shader != m_Shaders.end(); shader++) {

			delete shader->second;
		}

		// Clear shaders
		m_Shaders.clear();


		map<string, ShaderProgram*>::const_iterator program;
		for (program = m_Programs.begin(); program != m_Programs.end(); program++) {

			delete program->second;
		}

		// Clear programs
		m_Programs.clear();
	}


	//---------------------------------------------------------------
	// Initialize the static member.
	template<> GLSLManager* SingletonVee<GLSLManager>::ms_Singleton = 0;
	GLSLManager& GLSLManager::getSingleton(void) {

		return *ms_Singleton;
	}
	//-------------------------------------------------------
	GLSLManager* GLSLManager::getSingletonPtr(void) {

		return ms_Singleton;
	}


	//---------------------------------------------------------------
	/* Create a shader
	 * @param name {string} name of the shader
	 * @param type {GLenum} type of the shader
	 * @param filename {const char*} source file name for the shader
	 */
	void GLSLManager::createShader(string name, GLenum type, const char* filename) {

		Shader* shader = new Shader();

		// Initialize shader
		int r = shader->init(name, type, filename);
		if (!r) {

			m_Shaders[name] = shader;
		} else {

			delete shader;
		}
	}

	//---------------------------------------------------------------
	/* Create a shader program.
	 * @param name {string name} of the shader program
	 */
	void GLSLManager::createShaderProgram(string name) {

		ShaderProgram* program = new ShaderProgram();

		program->init(name);

		m_Programs[name] = program;
	}

	//---------------------------------------------------------------
	// Attach shader to a program
	void GLSLManager::attachShaderToProgram(string sName, string pName) {

		// Try to find the shader and program
		map<string, Shader*>::const_iterator shader = m_Shaders.find(sName);
		map<string, ShaderProgram*>::const_iterator program = m_Programs.find(pName);

		if (shader != m_Shaders.end() && program != m_Programs.end()) {

			// Attach shader to program
			program->second->attachShader(shader->second);
		}
	}

	//---------------------------------------------------------------
	/** Link a shader program
	 * @returns 0 correct result
	 * @returns -1 link failed
	 * @returns -2 can not find program
	 */
	int GLSLManager::linkProgram(string pName) {

		// Find program
		map<string, ShaderProgram*>::const_iterator program = m_Programs.find(pName);

		if (program != m_Programs.end()) {

			// Link program
			int r = program->second->link();
			if (!r) {

				return 0;
			} else {

				return -1;
			}
		}

		return -2;
	}

	//---------------------------------------------------------------
	// Operator []
	ShaderProgram* GLSLManager::operator[](const string &pName) {

		map<string, ShaderProgram*>::const_iterator program = m_Programs.find(pName);

		if (program != m_Programs.end()) {

			return program->second;
		}

		return NULL;
	}
};