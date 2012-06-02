#include "veRenderPass.h"
#include "veFBOManager.h"
#include "veGLSLManager.h"
#include "veTextureManager.h"
#include "veRenderSystem.h"
#include "veRenderer.h"

namespace vee {

	//---------------------------------------------------------------
	RenderPass::RenderPass() {

		// Shader program
		mProgram = NULL;

		// FBO
		mFBO = NULL;

		// Ortho projection?
		mOrtho = false;
	}

	//---------------------------------------------------------------
	RenderPass::RenderPass(RenderPassType type) {

		// Render pass type
		mType = type;

		// Ortho projection?
		mOrtho = false;

		// Setup render pass meta data
		setupMetaData();
	}

	//---------------------------------------------------------------
	RenderPass::~RenderPass() {
	}


	//---------------------------------------------------------------
	void RenderPass::setupMetaData() {

		switch (mType)
		{
		// SSAO_1
		case RPT_SSAO_1:
			{
				// Shader
				// Names
				mVS = "SSAO_1VS";
				mFS = "SSAO_1FS";
				// Files
				mVSFile = "shaders\\SSAO_1VS.txt";
				mFSFile = "shaders\\SSAO_1FS.txt";
				// Program name
				mProgramName = "SSAO_1PROGRAM";

				// FBO
				// Name
				mFBOName = "SSAO_1FBO";
				// Width
				mFBOWidth = 800;
				// Height
				mFBOHeight = 600;


				// Output textures
				// Position
				// Name
				mFBOTexNames.push_back("SSAO1_POS");
				// Internal format
				mFBOTexInternalFormat.push_back(GL_RGB16F);
				// Format
				mFBOTexFormat.push_back(GL_RGB);
				// Type
				mFBOTexType.push_back(GL_HALF_FLOAT);
				// Attack point
				mAttactPoint.push_back(GL_COLOR_ATTACHMENT0_EXT);


				// Normal
				// Name
				mFBOTexNames.push_back("SSAO1_NORMAL");
				// Internal format
				mFBOTexInternalFormat.push_back(GL_RGBA8);
				// Format
				mFBOTexFormat.push_back(GL_RGBA);
				// Type
				mFBOTexType.push_back(GL_UNSIGNED_BYTE);
				// Attack point
				mAttactPoint.push_back(GL_COLOR_ATTACHMENT1_EXT);


				// Color
				// Name
				mFBOTexNames.push_back("SSAO1_COLOR");
				// Internal format
				mFBOTexInternalFormat.push_back(GL_RGBA8);
				// Format
				mFBOTexFormat.push_back(GL_RGBA);
				// Type
				mFBOTexType.push_back(GL_UNSIGNED_BYTE);
				// Attack point
				mAttactPoint.push_back(GL_COLOR_ATTACHMENT2_EXT);


				// Depth
				// Name
				mFBOTexNames.push_back("SSAO1_DEPTH");
				// Internal format
				mFBOTexInternalFormat.push_back(GL_DEPTH_COMPONENT);
				// Format
				mFBOTexFormat.push_back(GL_DEPTH_COMPONENT);
				// Type
				mFBOTexType.push_back(GL_UNSIGNED_BYTE);
				// Attack point
				mAttactPoint.push_back(GL_DEPTH_ATTACHMENT_EXT);


				break;
			}

		// SSAO_2
		case RPT_SSAO_2:
			{
				// Shader
				// Name
				mVS = "SSAO_2VS";
				mFS = "SSAO_2FS";
				// File
				mVSFile = "shaders\\SSAO_2VS.txt";
				mFSFile = "shaders\\SSAO_2FS.txt";

				// Program name
				mProgramName = "SSAO_2PROGRAM";
				// Uniforms
				mUniformiNames.push_back("texNormal");
				mUniformsi.push_back(0);

				mUniformiNames.push_back("texPos");
				mUniformsi.push_back(1);

				mUniformiNames.push_back("texRandom");
				mUniformsi.push_back(2);

				mUniformiNames.push_back("texColor");
				mUniformsi.push_back(3);


				// FBO
				// Name
				mFBOName = "SSAO_1FBO";
				// Width
				mFBOWidth = 800;
				// Height
				mFBOHeight = 600;


				// Output textures
				// SSAO2 result
				// Name
				mFBOTexNames.push_back("SSAO2_RESULT");
				// Internal format
				mFBOTexInternalFormat.push_back(GL_RGB32F);
				// Format
				mFBOTexFormat.push_back(GL_RGB);
				// Type
				mFBOTexType.push_back(GL_FLOAT);
				// Attack point
				mAttactPoint.push_back(GL_COLOR_ATTACHMENT0_EXT);

				// Depth
				// Name
				mFBOTexNames.push_back("SSAO2_DEPTH");
				// Internal format
				mFBOTexInternalFormat.push_back(GL_DEPTH_COMPONENT32F);
				// Format
				mFBOTexFormat.push_back(GL_DEPTH_COMPONENT);
				// Type
				mFBOTexType.push_back(GL_FLOAT);
				// Attack point
				mAttactPoint.push_back(GL_DEPTH_ATTACHMENT_EXT);


				// Input textures
				mInputTexNames.push_back("SSAO1_NORMAL");
				mInputTexFiles.push_back("");

				mInputTexNames.push_back("SSAO1_POS");
				mInputTexFiles.push_back("");

				mInputTexNames.push_back("SSAO2_INPUTRANDOM");
				mInputTexFiles.push_back("textures\\SSAO_RandNormal.tga");

				mInputTexNames.push_back("SSAO1_COLOR");
				mInputTexFiles.push_back("");


				// Ortho projection
				mOrtho = true;

				break;
			}

		default:
			break;
		}
	}

	//---------------------------------------------------------------
	// Prepare for the render pass
	void RenderPass::prepare() {

		// GLSL manager
		GLSLManager& glslManager = GLSLManager::getSingleton();

		// Create shaders
		glslManager.createShader(mVS, GL_VERTEX_SHADER, mVSFile.c_str());
		glslManager.createShader(mFS, GL_FRAGMENT_SHADER, mFSFile.c_str());
		
		// Create program
		glslManager.createShaderProgram(mProgramName);

		// Attach shader and link program
		glslManager.attachShaderToProgram(mVS, mProgramName);
		glslManager.attachShaderToProgram(mFS, mProgramName);
		glslManager.linkProgram(mProgramName);

		// Set program pointer
		mProgram = glslManager[mProgramName];


		// Prepare FBO
		// FBO manager
		FBOManager& fboManager = FBOManager::getSingleton();
		// Set FBO
		mFBO = fboManager.createFBO(mFBOName);
		

		// Texture manager
		TextureManager& textureManager = TextureManager::getSingleton();
		Texture* texture;


		// Output textures
		for (uint i = 0; i < mFBOTexNames.size(); i++) {

			// Create new texture
			texture = textureManager.createTexture(mFBOTexNames.at(i));

			// Initialize texture
			texture->init(mFBOWidth, mFBOHeight, mFBOTexInternalFormat.at(i), mFBOTexFormat.at(i),
				mFBOTexType.at(i));

			// Attach texture to FBO
			mFBO->attachTexture2D(mAttactPoint.at(i), texture);
		}


		// Draw buffer options
		for (uint j = 0; j < mFBOTexNames.size()-1; j++) {

			mDrawBufferOptions.push_back(mAttactPoint.at(j));
		}


		// Input textures
		for (uint k = 0; k < mInputTexNames.size(); k++) {
			
			// Check whether we have the texture already
			if (!textureManager.getTexture(mInputTexNames.at(k))) {
				
				// Load textures from file
				texture = textureManager.loadTexture(mInputTexNames.at(k), 
					mInputTexFiles.at(k).c_str());
			}
		}
	}

	//---------------------------------------------------------------
	// Get program
	ShaderProgram* RenderPass::getProgram() {
		return mProgram;
	}

	//---------------------------------------------------------------
	// Get FBO
	FramebufferObject* RenderPass::getFBO() {
		return mFBO;
	}
	//---------------------------------------------------------------
	// Get FBO width
	int RenderPass::getFBOWidth() {
		return mFBOWidth;
	}
	//---------------------------------------------------------------
	// Get FBO height
	int RenderPass::getFBOHeight() {
		return mFBOHeight;
	}

	//---------------------------------------------------------------
	// Get draw buffer options
	vector<GLenum>* RenderPass::getDrawBufferOptions() {

		return &mDrawBufferOptions;
	}


	//---------------------------------------------------------------
	// Start render pass
	void RenderPass::start() {

		/*
		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();
		// Render
		Renderer& r = Renderer::getSingleton();

		// Bind FBO
		rs.bindFBO(mFBO);
		// Use program
		rs.useProgram(mProgram);

		// Uniforms
		for (uint ui = 0; ui < mUniformiNames.size(); ui++) {
			mProgram->setUniform1i(mUniformiNames.at(ui).c_str(), mUniformsi.at(ui));
		}
		// Whether we need to do another projection
		if (mOrtho) {
			float pm[16];
			r.getInverseProjection(pm);

			// Pass renderer projection matrix to uniform
			mProgram->setUniformMatrix4fv("gProjectionMatrixInverse", pm);
		}


		// Clear buffers
		rs.clearBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Draw buffers
		rs.drawBuffers(&mDrawBufferOptions);

		// Push current projection matrix
		rs.pushProjection();
		// Whether we need to do another projection
		if (mOrtho) {
			// Do ortho projection
			rs.setOrthoProjection(-(mFBOWidth*0.5f), mFBOWidth*0.5f,
				-(mFBOHeight*0.5f), mFBOHeight*0.5f);
		}

		// Push current viewport
		rs.pushViewport();
		// Do new viewport
		rs.setViewport(0, 0, mFBOWidth, mFBOHeight);
		
		// Push modelview
		rs.pushModelView();
		// Whether we need to do another modelview
		if (mOrtho) {
			// Identity modelview
			rs.identityModelView();
		}


		TextureManager& tm = TextureManager::getSingleton();
		// Input textures
		for (uint i = 0; i < mInputTexNames.size(); i++) {
			rs.bindTexture2D(tm.getTexture(mInputTexNames.at(i))->getId(), i);
		}
		*/
	}

	//---------------------------------------------------------------
	// End render pass
	void RenderPass::end() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		rs.popProjection();
		rs.popViewport();
		rs.popModelView();

		// Input textures
		for (uint i = 0; i < mInputTexNames.size(); i++) {
			rs.bindTexture2D(0, i);
		}

		// Use default program
		rs.useProgram(NULL);
		// Bind default FBO
		rs.bindFBO(NULL);
	}
};