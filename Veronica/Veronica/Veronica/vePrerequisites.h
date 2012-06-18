#ifndef VEE_PREREQUISITES_H
#define VEE_PREREQUISITES_H

/*
 * vePrerequisites.h
 * This file should be included by each engine header file
 */

#include <string> // String
#include <iostream> // Debug io
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
	// GUI manager
	class GUIManager;


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


	// Input
	class Input;
};

#endif