#include "veRenderer.h"
#include "veRenderSystem.h"
#include "veGLSLManager.h"
#include "veTGALoader.h"


namespace vee {

	//---------------------------------------------------------------
	Renderer::Renderer() {

		// Texture
		TGAData tgaData;
		TGALoader::loadTGAFile(&tgaData, "textures//terrain.tga");

		mTestTexture.init(tgaData.mWidth, tgaData.mHeight,
			GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, tgaData.mData);


		// Indicator visible flag
		mIndicatorVisible = false;
	}
	//---------------------------------------------------------------
	Renderer::~Renderer() {

		destroy();
	}


	//---------------------------------------------------------------
	// Initialize the static member
	template<> Renderer* SingletonVee<Renderer>::ms_Singleton = 0;
	Renderer& Renderer::getSingleton(void) {

		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	Renderer* Renderer::getSingletonPtr(void) {

		return ms_Singleton;
	}


	//---------------------------------------------------------------
	/* Get viewport
	 * @param data {int*} result data
	 */
	void Renderer::getViewport(int* data) {
		
		data[0] = mViewport[0];
		data[1] = mViewport[1];
		data[2] = mViewport[2];
		data[3] = mViewport[3];
	}

	//---------------------------------------------------------------
	/* Set viewport
	 * @param x {int} viewport x
	 * @param y {int} viewport y
	 * @param width {int} viewport width
	 * @param height {int} viewport height
	 */
	void Renderer::setViewport(int x, int y, int width, int height) {

		mViewport[0] = x;
		mViewport[1] = y;
		mViewport[2] = width;
		mViewport[3] = height;
	}


	//---------------------------------------------------------------
	// Get view matrix
	void Renderer::getView(float* data) {

		// Get view matrix from camera
		mCamera.getViewMatrix().toArray(data);
	}


	//---------------------------------------------------------------
	/* Get projection matrix
	 * @param data {float*} result data
	 */
	void Renderer::getProjection(float* data) {

		mProjection.toArray(data);
	}

	//---------------------------------------------------------------
	// Set projection matrix
	void Renderer::setProjection(Transform& t) {

		mProjection = t;
	}


	//---------------------------------------------------------------
	// Get camera
	SphericalCamera& Renderer::getCamera() {

		return mCamera;
	}


	//---------------------------------------------------------------
	void Renderer::init() {
	
		// Testing
		// GLSL manager
		GLSLManager& glslManager = GLSLManager::getSingleton();

		// Create shaders
		glslManager.createShader("TestVS", GL_VERTEX_SHADER, "shaders//DirectionalLightingVS.txt");
		glslManager.createShader("TestFS", GL_FRAGMENT_SHADER, "shaders//DirectionalLightingFS.txt");

		// Create program
		glslManager.createShaderProgram("Test");

		// Attach shader and link program
		glslManager.attachShaderToProgram("TestVS", "Test");
		glslManager.attachShaderToProgram("TestFS", "Test");
		glslManager.linkProgram("Test");
	}

	//---------------------------------------------------------------
	void Renderer::destroy() {
	}


	//---------------------------------------------------------------
	// Render
	void Renderer::render() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();


		// Set projection matrix
		rs.setPerspectiveProjection(mProjection);

		// Set viewport
		rs.setViewport(mViewport[0], mViewport[1], mViewport[2], mViewport[3]);


		// Render background stage
		_renderStage();


		// View matrix
		Transform vMat = mCamera.getViewMatrix();
		// Model matrix
		Transform mMat;


		// GLSL manager
		GLSLManager& glslManager = GLSLManager::getSingleton();

		// Shader program
		ShaderProgram* p = glslManager["Test"];
		rs.useProgram(p);


		// Vertex attribute
		GLint aoPos = glGetAttribLocation(p->getId(), "ao");


		// Texture
		rs.bindTexture2D(mTestTexture.getId(), 0);

		// Unifrom
		p->setUniform1i("tex", 0);



		rs.setModelView(vMat * mTestMesh->getTransform());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glEnableVertexAttribArray(aoPos);


		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), mTestMesh->getData());
		glNormalPointer(GL_FLOAT, sizeof(Vertex), mTestMesh->getData()+12);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), mTestMesh->getData()+24);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), mTestMesh->getData()+32);

		// Ambient occlusion
		glVertexAttribPointer(aoPos, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), mTestMesh->getData()+36);


		glDrawArrays(GL_TRIANGLES, 0, mTestMesh->getVertNum());


		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		glDisableVertexAttribArray(aoPos);


		rs.useProgram(NULL);

		rs.bindTexture2D(0, 0);


		// Render indicator
		_renderIndicator();
	}


	//---------------------------------------------------------------
	// Render background stage
	void Renderer::_renderStage() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();


		// Setup model view matrix
		rs.setModelView(mCamera.getViewMatrix());


		glBegin(GL_LINES);


		// Render grid
		glColor3ub(64, 64, 64);

		for (int i = -25; i <= 25; i++) {

			// X-Z
			glVertex3f(1.0f*i, 0.0f, -25.0f);
			glVertex3f(1.0f*i, 0.0f, 25.0f);
			glVertex3f(-25.0f, 0.0f, 1.0f*i);
			glVertex3f(25.0f, 0.0f, 1.0f*i);
		}

		
		// Render world x, y, z axes
		glColor3ub(0, 0, 0);
		
		// X
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(25.0f, 0.0f, 0.0f);
		
		// Y
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 25.0f, 0.0f);
		
		// Z
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 25.0f);


		glEnd();
	}

	//---------------------------------------------------------------
	/**
	 * Render indicator
	 */
	void Renderer::_renderIndicator() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();


		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);


		// Voxel size
		float vs = 1.0f;

		// Base position
		float bp[3];
		bp[0] = mIndicatorPos[0] * vs;
		bp[1] = mIndicatorPos[1] * vs;
		bp[2] = mIndicatorPos[2] * vs;



		if (mIndicatorVisible) {

			glColor3ub(255, 0, 0);
			glBegin(GL_QUADS);

			switch (mIndicatorPos[3]) {

			case 0:
				{
					glVertex3f(bp[0], bp[1]+vs, bp[2]);
					glVertex3f(bp[0], bp[1], bp[2]);
					glVertex3f(bp[0], bp[1], bp[2]+vs);
					glVertex3f(bp[0], bp[1]+vs, bp[2]+vs);

					break;
				}

			case 1:
				{
					glVertex3f(bp[0]+vs, bp[1]+vs, bp[2]+vs);
					glVertex3f(bp[0]+vs, bp[1], bp[2]+vs);
					glVertex3f(bp[0]+vs, bp[1], bp[2]);
					glVertex3f(bp[0]+vs, bp[1]+vs, bp[2]);

					break;
				}

			case 2:
				{
					glVertex3f(bp[0], bp[1], bp[2]+vs);
					glVertex3f(bp[0], bp[1], bp[2]);
					glVertex3f(bp[0]+vs, bp[1], bp[2]);
					glVertex3f(bp[0]+vs, bp[1], bp[2]+vs);

					break;
				}

			case 3:
				{
					glVertex3f(bp[0], bp[1]+vs, bp[2]);
					glVertex3f(bp[0], bp[1]+vs, bp[2]+vs);
					glVertex3f(bp[0]+vs, bp[1]+vs, bp[2]+vs);
					glVertex3f(bp[0]+vs, bp[1]+vs, bp[2]);

					break;
				}

			case 4:
				{
					glVertex3f(bp[0]+vs, bp[1]+vs, bp[2]);
					glVertex3f(bp[0]+vs, bp[1], bp[2]);
					glVertex3f(bp[0], bp[1], bp[2]);
					glVertex3f(bp[0], bp[1]+vs, bp[2]);

					break;
				}

			case 5:
				{
					glVertex3f(bp[0], bp[1]+vs, bp[2]+vs);
					glVertex3f(bp[0], bp[1], bp[2]+vs);
					glVertex3f(bp[0]+vs, bp[1], bp[2]+vs);
					glVertex3f(bp[0]+vs, bp[1]+vs, bp[2]+vs);

					break;
				}

			default:
				break;
			}

			glEnd();
		}
	}
};