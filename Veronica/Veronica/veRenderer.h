#ifndef VEE_RENDERER_H
#define VEE_RENDERER_H

/* 
 * Renderer
 */

#include "vePrerequisites.h"
// Singleton
#include "veSingleton.h"
// Camera
#include "veSphericalCamera.h"
// Transform
#include "veTransform.h"


// Chunk serializer
#include "veChunkSerializer.h"
// Texture
#include "veTexture.h"


namespace vee {

	// Renderer
	class Renderer : public SingletonVee<Renderer> {

	public:
		Renderer();
		~Renderer();


	public:
		static Renderer& getSingleton(void);
		static Renderer* getSingletonPtr(void);


	public:
		// Get viewport
		void getViewport(int* data);

		// Set viewport
		void setViewport(int x, int y, int width, int height);


		// Get view matrix
		void getView(float* data);


		// Get projection matrix
		void getProjection(float* data);

		// Set projection matrix
		void setProjection(Transform& t);


		// Get camera
		SphericalCamera& getCamera();


	public:
		// Init
		void init();

		// Destroy
		void destroy();
		
		// Render
		void render();


	protected:
		// Render background stage
		void _renderStage();

		// Render indicator
		void _renderIndicator();


	protected:
		// Viewport
		int mViewport[4];

		// Projection matrix
		Transform mProjection;


		// Camera
		SphericalCamera mCamera;


	public:
		// Texture
		veTexture mTestTexture;

		// Test mesh
		Mesh* mTestMesh;


		// Indicator visible flag
		bool mIndicatorVisible;

		// Indicator position
		int mIndicatorPos[4];
	};
};

#endif