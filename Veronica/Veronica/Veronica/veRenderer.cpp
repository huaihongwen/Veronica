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
		
	}
	//---------------------------------------------------------------
	Renderer::~Renderer() {
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


		// Loop each mesh
		for (uint i = 0; i < mTestMeshes->size(); i++) {

			rs.setModelView(vMat * mTestMeshes->at(i)->getTransform());


			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			//glEnableClientState(GL_COLOR_ARRAY);

			glEnableVertexAttribArray(aoPos);


			glVertexPointer(3, GL_FLOAT, sizeof(Vertex), mTestMeshes->at(i)->getData());
			glNormalPointer(GL_FLOAT, sizeof(Vertex), mTestMeshes->at(i)->getData()+12);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), mTestMeshes->at(i)->getData()+24);
			//glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(Vertex), mTestMesh->getData()+32);

			// Ambient occlusion
			glVertexAttribPointer(aoPos, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), mTestMeshes->at(i)->getData()+36);
			
			glDrawArrays(GL_TRIANGLES, 0, mTestMeshes->at(i)->getVertNum());


			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			//glDisableClientState(GL_COLOR_ARRAY);

			glDisableVertexAttribArray(aoPos);
		}
		rs.useProgram(NULL);

		rs.bindTexture2D(0, 0);
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
};