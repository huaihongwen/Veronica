#ifndef VEE_RENDERPASS_H
#define VEE_RENDERPASS_H

/* Render pass
 */

#include "vePrerequisites.h"
#include <vector>

// OpenGL stuffs
#include <windows.h>
#include <GL\glew.h>

namespace vee {

	// Render pass type
	enum RenderPassType {

		// Unknown
		RPT_UNKNOWN,

		// SSAO_1
		RPT_SSAO_1,

		// SSAO_2
		RPT_SSAO_2
	};


	 // Render pass
	class RenderPass {

	public:
		RenderPass();
		RenderPass(RenderPassType mType);
		~RenderPass();

	public:
		// Setup render pass meta data
		void setupMetaData();

		// Prepare for the render pass
		void prepare();
	

		// Start render pass
		void start();

		// End render pass
		void end();

	public:
		// Get program
		ShaderProgram* getProgram();

		// Get FBO
		FramebufferObject* getFBO();

		// Get FBO width
		int getFBOWidth();
		// Get FBO height
		int getFBOHeight();

		// Get draw buffer options
		vector<GLenum>* getDrawBufferOptions();

	protected:
		// Shader type
		RenderPassType mType;

		// Meta data
		// Vertex shader name
		string mVS;
		// Fragment shader name
		string mFS;
		// Vertex shader file
		string mVSFile;
		// Fragment shader file
		string mFSFile;

		// Program name
		string mProgramName;
		// Uniform name
		vector<string> mUniformiNames;
		// Uniformi value
		vector<uint> mUniformsi;

		// FBO name
		string mFBOName;
		// FBO width
		int mFBOWidth;
		// FBO height
		int mFBOHeight;


		// Output textures
		vector<string> mFBOTexNames;
		vector<GLenum> mFBOTexInternalFormat;
		vector<GLenum> mFBOTexFormat;
		vector<GLenum> mFBOTexType;
		vector<GLenum> mAttactPoint;

		// Input textures
		// Input texture name
		vector<string> mInputTexNames;
		// Input texture file
		vector<string> mInputTexFiles;



		// Shader program
		ShaderProgram* mProgram;

		// FBO
		FramebufferObject* mFBO;

		// Ortho projection?
		bool mOrtho;

		// Draw buffer options
		vector<GLenum> mDrawBufferOptions;
	};
};

#endif