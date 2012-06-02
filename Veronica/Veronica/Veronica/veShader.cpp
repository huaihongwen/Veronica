#include "veShaderProgram.h"

namespace vee {

	//---------------------------------------------------------------
	Shader::Shader() {

		// Invalid shader id
		mId = 0;
	}
	//---------------------------------------------------------------
	Shader::~Shader() {

		if (mId) {
			// Delete shader from OpenGL or mark delete dirty
			glDeleteShader(mId);
		}
	}


	//---------------------------------------------------------------
	// Print shader info log
	void Shader::_printInfoLog() {

		int infoLen, charWritten;
		GLchar* log;

		// Get shader info log length
		glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 0) {

			// Allocate log
			log = (GLchar*)malloc(infoLen);
			if (!log) {

				printf("Can not allocate memory for the info log");
			}

			// Get info log
			glGetShaderInfoLog(mId, infoLen, &charWritten, log);

			printf("Info Log: \n%s\n", log);

			free(log);
		}
	}

	//---------------------------------------------------------------
	/* Load shader source from file
	 * @params filename {const char*} shader source file name
	 * @returns 0 no error
	 * @returns -1 file open failed 
	 * @returns -2 can not allocate enough memory for string
	 */
	int Shader::_loadShaderSource(const char* filename) {

		ifstream fin;

		int length;
		char* buffer = NULL;

		// Open file
		fin.open(filename, ifstream::in);
		if (!fin.good()) {

			return -1;
		}

		// Get file length
		length = FileUtil::getFileLength(fin);

		// Create content buffer
		buffer = new char[length + 1];
		if (!buffer) {

			fin.close();
			return -2;
		}
		buffer[length] = 0;

		// Get file content
		int i = 0;
		while (fin.good()) {

			buffer[i++] = fin.get();
		}
		buffer[i - 1] = 0;

		fin.close();

		// Pass shader source to OpenGL
		glShaderSource(mId, 1, (const GLchar**)&buffer, NULL);

		// Clear content buffer
		delete [] buffer;

		return 0;
	}


	//---------------------------------------------------------------
	/* Initialize a shader
	 * @params name {string} name of the shader
	 * @params type {GLenum} GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
	 * @params filename {const char*} shader source file name
	 * @returns 0 correct result
	 * @returns -1 invalid file name
	 * @returns -2 can't get shader's source from file
	 * @returns -3 shader compile error
	 */
	int Shader::init(string name, GLenum type, const char* filename) {
			
		if (!filename) {

			return -1;
		}

		mName = name;
		mType = type;
		mCompiled = false;

		// Create OpenGL shader
		mId = glCreateShader(type);

		int source, compile;

		// Load shader source
		source = _loadShaderSource(filename);
		
		// Compile shader
		if (!source) {

			// Compile shader
			glCompileShader(mId);

			// Get compile state
			glGetShaderiv(mId, GL_COMPILE_STATUS, &compile);

			if (compile == GL_FALSE) {

				_printInfoLog();
				return -3;
			} else {

				return 0;
			}
		}
		else 
			// Cant not get shader source
			return -2;
	}

};