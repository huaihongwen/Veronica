#ifndef VEE_VOXELMODEL_H
#define VEE_VOXELMODEL_H


/*
 * veVoxelModel.h
 */


#include "vePrerequisites.h"

// Voxel table
#include "veVoxel.h"

// Transform
#include "veTransform.h"


// Map
#include <map>


namespace vee {

	// Voxel group
	class VoxelGroup {

	public:
		VoxelGroup();
		VoxelGroup(const string& name, int sx, int sy, int sz,
			float px=0.0f, float py=0.0f, float pz=0.0f);
		~VoxelGroup();


	public:
		// Serialize
		void serialize(VoxelTableSerializer* serializer);


	public:
		// Get name
		string getName();

		// Set name
		void setName(const string& name);


		// Get position
		Vector3 getPosition();

		// Set position
		void setPosition(const Vector3& p);


		// Get tranform
		Transform getTransform();


		// Get mesh
		Mesh* getMesh();
		

		// Get model space BB
		BBox getModelSpaceBB();

		// Get model space voxel BB
		BBox getModelSpaceVoxelBB(int i, int j, int k);


	protected:
		// Name
		string mName;


		// Voxel table
		//VoxelTable* mVoxelTable;


		// Model space position in world unit
		Vector3 mPos;

		// Transform matrix from group space to model space
		Transform mTransform;


		// Voxel size in world unit
		float mVoxelSize;

		// Mesh in group space (table space)
		Mesh* mMesh;
	};




	// Voxel group map
	typedef map<string, VoxelGroup*> VoxelGroupMap;

	// Voxel model
	class VoxelModel {

	public:
		VoxelModel();
		VoxelModel(const string& name);
		~VoxelModel();


	public:
		// Get groups
		VoxelGroupMap& getGroups();

		// Get group
		VoxelGroup* getGroup(const string& name);


	public:
		// Add group
		void addGroup(const string& groupName, VoxelGroup* group);

		// Remove group
		void removeGroup(const string& groupName);


		// Save to file
		void saveToFile();

		// Load from file
		void loadFromFile(const char* name);


		// Serialize
		void serialize(VoxelTableSerializer* serializer);

		// Serialize group
		void serializeGroup(VoxelTableSerializer* serializer, const string& name);


	protected:
		// Name
		string mName;

		// Voxel groups
		VoxelGroupMap mGroups;
	};
};

#endif