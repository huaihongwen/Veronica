#ifndef VEE_PREREQUISITES_H
#define VEE_PREREQUISITES_H

/*
 * vePrerequisites.h
 * This file should be included by each engine header file
 */

// String
#include <string>
// Debug io
#include <iostream>

using namespace std;

namespace vee {

	// Debug
	#define DEBUGMODE 1


	// Re-define data types
	typedef float real;
	typedef unsigned char uchar;
	typedef unsigned int uint;
	typedef unsigned short ushort;
	typedef unsigned long ulong;


	// Pre-declare classes
	// Allows use of pointers in header files without including individual .h


	//---------------------------------------------------------------
	// Engine
	// Math
	class Vector3;
	class Vector4;
	class Matrix3x3;
	class Transform;


	// Console
	class Console;

	// Font system
	class FontSystem;


	// Voxel
	class VoxelGroup;
	class VoxModel;
	class VoxelTableSerializer;


	// GUI
	// GUI element
	class GUIElement;
	// GUI
	class GUI;
	// GUI utility
	class GUIUtility;


	// Rendering
	// Mesh
	class Mesh;
	// Texture
	class Texture;
	// Texture manager
	class TextureManager;

	// Frame buffer object
	class FramebufferObject;
	// Render pass
	class RenderPass;


	class FileUtil;
	// Shader
	class Shader;
	// Shader program
	class ShaderProgram;
	// GLSL manager
	class GLSLManager;

	class RenderSystem;
	class Renderer;

	class Utils;


	// Others
	// Octree
	struct OctreeNode;
	// Bounding box
	class BBox;
	// Ray
	class Ray;
	// TGA loader
	class TGALoader;
	// Timer
	class Timer;



	//---------------------------------------------------------------
	// Editor
	// Screen width
	#define EDITWINDOWWIDTH 1024
	// Screen height
	#define EDITWINDOTHEIGHT 768


	// Edit view port x
	#define EDITVIEWPORTX 0
	// Edit view port y
	#define EDITVIEWPORTY 0

	// Edit viewport width
	#define EDITVIEWPORTWIDTH 800
	// Edit viewport height
	#define EDITVIEWPORTHEIGHT 600


	// Factory history
	class FactoryHistory;

	// Model factory
	class ModelFactory;

	// Color panel
	class UIColorPanel;

	// Editor
	class Editor;
};

#endif