#include "veShaderProgram.h"

namespace vee {

	//---------------------------------------------------------------
	ShaderProgram::ShaderProgram() {

		// Invalid program id
		mId = 0;
	}
	//---------------------------------------------------------------
	ShaderProgram::~ShaderProgram() {

		if (mId) {
			// Delete program from OpenGL or mark delete dirty
			glDeleteProgram(mId);
		}
	}


	//---------------------------------------------------------------
	// Print program info log
	void ShaderProgram::_printInfoLog() {

		int infoLen;
		int charWritten;
		GLchar* log;

		// Get info log length
		glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 0) {

			log = (GLchar*)malloc(infoLen);
			if (!log) {
				printf("Can not allocate memory for the info log");
			}

			// Get info log content
			glGetProgramInfoLog(mId, infoLen, &charWritten, log);

			printf("Info Log: \n%s\n", log);

			free(log);
		}
	}


	//---------------------------------------------------------------
	/* Link this program
	 * @returns 0 link succeed
	 * @returns -1 link failed
	 */
	int ShaderProgram::link() {

		int link;

		// Link program
		glLinkProgram(mId);

		// Get link status
		glGetProgramiv(mId, GL_LINK_STATUS, &link);

		if (link == GL_FALSE) {

			_printInfoLog();

			return -1;
		}

		mLinked = true;
		return 0;
	}

	//---------------------------------------------------------------
	// Initialize a shader program
	void ShaderProgram::init(string name) {

		mName = name;

		mLinked = false;

		// Create shader program
		mId = glCreateProgram();
	}

	//---------------------------------------------------------------
	/* Attach shader to the program
	 * @params shader {Shader*} shader u wanna attach
	 */
	void ShaderProgram::attachShader(Shader* shader) {

		glAttachShader(mId, shader->getId());
	}

	//---------------------------------------------------------------
	// Get uniform location
	GLuint ShaderProgram::getUniformLocation(const char* uniformName) {

		GLuint loc = glGetUniformLocation(mId, uniformName);

		if (loc == -1) {
			//printf("Can not found uniform.");
		}

		return loc;
	}

	//---------------------------------------------------------------
	// Set uniform 1i
	void ShaderProgram::setUniform1i(const char* uniformName, GLint value) {

		glUniform1i(getUniformLocation(uniformName), value);
	}

	//---------------------------------------------------------------
	void ShaderProgram::setUniform1f(const char* uniformName, GLfloat value) {

		glUniform1f(getUniformLocation(uniformName), value);
	}


	//---------------------------------------------------------------
	void ShaderProgram::setUniformMatrix4fv(const char* uniformName, GLfloat* value) {

		glUniformMatrix4fv(getUniformLocation(uniformName), 1, false, value);
	}
};