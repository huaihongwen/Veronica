#include "veVoxelModel.h"
// Bounding box
#include "veBoundingBox.h"

// File
#include <stdio.h>


namespace vee {

	/*
	//---------------------------------------------------------------
	VoxelGroup::VoxelGroup() {

		// Name
		mName = "";


		// Voxel table
		mVoxelTable = NULL;


		// Model space position in world unit
		mPos.setValue(0.0f, 0.0f, 0.0f);


		// Voxel size in world unit
		mVoxelSize = 0.0f;

		// Mesh
		mMesh = NULL;
	}

	//---------------------------------------------------------------
	VoxelGroup::VoxelGroup(const string& name, int sx, int sy, int sz,
		float px, float py, float pz) {

		// Name
		mName = name;


		// Voxel table
		mVoxelTable = new VoxelTable(sx, sy, sz);

		// Fill voxel table
		//mVoxelTable->fill();


		// Model space position in world unit
		mPos.setValue(px, py, pz);

		// Transform matrix
		mTransform = Transform::getTranslationMatrix(mPos);


		// Voxel size in world unit
		mVoxelSize = 0.0f;

		// Mesh
		mMesh = NULL;
	}

	//---------------------------------------------------------------
	VoxelGroup::~VoxelGroup() {

		// Delete voxel table
		if (mVoxelTable) {
			delete mVoxelTable;
		}

		// Delete mesh
		if (mMesh) {
			delete mMesh;
		}
	}


	//---------------------------------------------------------------
	// Serialize voxel group
	void VoxelGroup::serialize(VoxelTableSerializer* serializer) {

		// Delete old mesh
		if (mMesh) {
			delete mMesh;
		}

		// Serialize voxel table into mesh in group space
		mMesh = serializer->serialize(mVoxelTable);


		// Set voxel size in world unit
		//mVoxelSize = serializer->getVoxelSize();
	}


	//---------------------------------------------------------------
	// Get name
	string VoxelGroup::getName() {
		return mName;
	}

	//---------------------------------------------------------------
	// Set name
	void VoxelGroup::setName(const string& name) {
		mName = name;
	}


	//---------------------------------------------------------------
	// Get voxel table
	VoxelTable* VoxelGroup::getVoxelTable() {
		return mVoxelTable;
	}

	//---------------------------------------------------------------
	// Set voxel table
	void VoxelGroup::setVoxelTable(VoxelTable* vt) {

		// Delete old voxel table
		if (mVoxelTable) {

			delete mVoxelTable;
		}

		// Set voxel table
		mVoxelTable = vt;
	}



	//---------------------------------------------------------------
	// Get position
	Vector3 VoxelGroup::getPosition() {
		return mPos;
	}

	//---------------------------------------------------------------
	// Set position
	void VoxelGroup::setPosition(const Vector3& p) {

		mPos = p;

		// Transform matrix
		mTransform = Transform::getTranslationMatrix(mPos);
	}


	//---------------------------------------------------------------
	// Get tranform
	Transform VoxelGroup::getTransform() {
		return mTransform;
	}

	//---------------------------------------------------------------
	// Get mesh
	Mesh* VoxelGroup::getMesh() {
		return mMesh;
	}

	//---------------------------------------------------------------
	// Get model space BB
	BBox VoxelGroup::getModelSpaceBB() {

		BBox bb;

		// Origin
		bb.setOrigin(mPos[0], mPos[1], mPos[2]);

		
		// Voxel table size in voxel unit
		int x = 0; //mVoxelTable->getSizeX();
		int y = 0; //mVoxelTable->getSizeY();
		int z = 0; //mVoxelTable->getSizeZ();

		bb.setSize(x*mVoxelSize, y*mVoxelSize, z*mVoxelSize);

		return bb;
	}


	//---------------------------------------------------------------
	// Get model space voxel BB
	BBox VoxelGroup::getModelSpaceVoxelBB(int i, int j, int k) {

		BBox bb;

		// Voxel table size in voxel unit
		int x = 0; //mVoxelTable->getSizeX();
		int y = 0; //mVoxelTable->getSizeY();
		int z = 0; //mVoxelTable->getSizeZ();

		// Origin
		bb.setOrigin(mPos[0]+i*mVoxelSize, mPos[1]+j*mVoxelSize, mPos[2]+k*mVoxelSize);

		// Size
		bb.setSize(mVoxelSize, mVoxelSize, mVoxelSize);

		return bb;
	}




	//---------------------------------------------------------------
	VoxelModel::VoxelModel() {
	}

	//---------------------------------------------------------------
	VoxelModel::VoxelModel(const string& name) {

		mName = name;
	}

	//---------------------------------------------------------------
	VoxelModel::~VoxelModel() {

		map<string, VoxelGroup*>::const_iterator group;

		for (group = mGroups.begin(); group != mGroups.end(); group++) {

			// Delete voxel group
			delete group->second;
		}

		mGroups.clear();
	}


	//---------------------------------------------------------------
	// Get groups
	VoxelGroupMap& VoxelModel::getGroups() {
		return mGroups;
	}


	//---------------------------------------------------------------
	// Get group
	VoxelGroup* VoxelModel::getGroup(const string& name) {

		map<string, VoxelGroup*>::const_iterator group = mGroups.find(name);

		if (group != mGroups.end()) {

			return group->second;
		}

		return NULL;
	}


	//---------------------------------------------------------------
	// Add group
	void VoxelModel::addGroup(const string& groupName, VoxelGroup* g) {

		map<string, VoxelGroup*>::const_iterator group = mGroups.find(groupName);

		// We already have voxel group
		if (group != mGroups.end()) {

			return;
		}

		// Add to map
		mGroups[groupName] = g;
	}

	//---------------------------------------------------------------
	// Remove group
	void VoxelModel::removeGroup(const string& groupName) {

		map<string, VoxelGroup*>::const_iterator group = mGroups.find(groupName);

		if (group != mGroups.end()) {

			// Delete group
			delete group->second;

			// Remove it from list
			mGroups.erase(group);
		}
	}


	//---------------------------------------------------------------
	// Save to file
	void VoxelModel::saveToFile() {

		// Path
		string path = "voxelModels\\" + mName + ".vxm";


		// File
		FILE* fp;

		// Open or create file
		fopen_s(&fp, path.c_str(), "wb");


		// Group number
		int groupNum = mGroups.size();

		// Write group number
		fwrite(&groupNum, sizeof(int), 1, fp);


		// Group
		VoxelGroup* g;


		// Group name
		string name;
		// Group name length
		int nameLen;


		// Voxel table
		VoxelTable* vt;

		// Voxel table size
		int size[3];

		// Voxel number
		int voxelNum;

		// Voxel
		Voxel* v;


		// Group position
		float pos[3];


		map<string, VoxelGroup*>::const_iterator group;

		// Loop each group
		for (group = mGroups.begin(); group != mGroups.end(); group++) {
		
			// Group
			g = group->second;


			// Group name
			name = g->getName();
			// Group name length
			nameLen = name.size() + 1;

			// Write name length
			fwrite(&nameLen, sizeof(int), 1, fp);
			// Write name
			fwrite(name.c_str(), sizeof(uchar), nameLen, fp);


			// Voxel table
			vt = g->getVoxelTable();


			// Voxel table size
			size[0] = 0; //vt->getSizeX();
			size[1] = 0; //vt->getSizeY();
			size[2] = 0; //vt->getSizeZ();

			// Write size
			fwrite(size, sizeof(int), 3, fp);


			// Voxel number
			//voxelNum = vt->getVoxelNum();

			// Write voxel number
			fwrite(&voxelNum, sizeof(int), 1, fp);


			// Loop each voxel
			for (int i = 0; i < size[0]; i++) {

				for (int j = 0; j < size[1]; j++) {

					for (int k = 0; k < size[2]; k++) {

						// Voxel
						v = vt->getVoxel(i, j, k);

						if (v) {

							// Write voxel position
							//fwrite(v->getPos(), sizeof(int), 3, fp);

							// Write voxel color
							//fwrite(v->getColor(), sizeof(uchar), 3, fp);
						}
					}
				}
			}


			// Position
			pos[0] = g->getPosition()[0];
			pos[1] = g->getPosition()[1];
			pos[2] = g->getPosition()[2];

			// Write position
			fwrite(pos, sizeof(float), 3, fp);
		}


		// Close file
		fclose(fp);
	}

	//---------------------------------------------------------------
	// Load from file
	void VoxelModel::loadFromFile(const char* modelname) {

		// Model name
		mName = modelname;


		// Path
		string path = "voxelModels\\" + mName + ".vxm";


		// File
		FILE* fp;

		// Open file
		fopen_s(&fp, path.c_str(), "rb");

		if (!fp) {

			// Reset model name
			mName = "";

			return;
		}


		// Group number
		int groupNum;

		// Read group number
		fread(&groupNum, sizeof(int), 1, fp);


		// Voxel group
		VoxelGroup* g;


		// Group name
		char* name;
		// Group name length
		int nameLength;


		// Voxel table
		VoxelTable* vt;

		// Voxel table size
		int size[3];

		// Voxel number
		int voxelNum;


		// Voxel position
		int voxelPos[3];
		// Voxel color
		uchar voxelColor[3];


		// Group position
		float pos[3];


		// Loop each group
		for (int i = 0; i < groupNum; i++) {

			// Create voxel group
			g = new VoxelGroup();


			// Read group name length
			fread(&nameLength, sizeof(int), 1, fp);

			// Create group name buffer
			name = new char[nameLength];

			// Read group name
			fread(name, sizeof(char), nameLength, fp);

			// Set group name
			g->setName(name);

			// Delete group name buffer
			delete [] name;


			// Read voxel size
			fread(size, sizeof(int), 3, fp);

			// Create voxel table
			vt = new VoxelTable(size[0], size[1], size[2]);


			// Read voxel number
			fread(&voxelNum, sizeof(int), 1, fp);

			// Loop each voxel
			for (int j = 0; j < voxelNum; j++) {

				// Read voxel position
				fread(voxelPos, sizeof(int), 3, fp);

				// Read voxel color
				fread(voxelColor, sizeof(uchar), 3, fp);


				// Create voxel and put it into voxel table
				//vt->setVoxel(voxelPos[0], voxelPos[1], voxelPos[2], new Voxel(voxelPos[0], voxelPos[1], voxelPos[2],
				//	voxelColor[0], voxelColor[1], voxelColor[2]));
			}


			// Set group voxel table
			g->setVoxelTable(vt);


			// Read group position
			fread(pos, sizeof(float), 3, fp);

			// Set group position
			g->setPosition(Vector3(pos[0], pos[1], pos[2]));


			// Add group to model
			addGroup(g->getName(), g);
		}

		fclose(fp);
	}


	//---------------------------------------------------------------
	// Serialize
	void VoxelModel::serialize(VoxelTableSerializer* serializer) {

		map<string, VoxelGroup*>::const_iterator group;

		// Loop each group
		for (group = mGroups.begin(); group != mGroups.end(); group++) {

			group->second->serialize(serializer);
		}
	}

	//---------------------------------------------------------------
	// Serialize group
	void VoxelModel::serializeGroup(VoxelTableSerializer* serializer, const string& name) {

		VoxelGroup* g = getGroup(name);

		if (g) {
			g->serialize(serializer);
		}
	}
	*/
};