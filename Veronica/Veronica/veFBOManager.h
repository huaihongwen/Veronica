#ifndef VEE_FBOMANAGER_H
#define VEE_FBOMANAGER_H

/* Basic FBO manager
 */

#include "vePrerequisites.h"
#include "veSingleton.h"

#include "veFramebufferObject.h"
#include <map>

namespace vee {

	// Frame buffer object map
	typedef map<string, FramebufferObject*> FBOMap;

	// FBO manager
	class FBOManager : public SingletonVee<FBOManager> {

	public:
		FBOManager();
		~FBOManager();

	public:
		// Get singleton
		static FBOManager& getSingleton(void);
		static FBOManager* getSingletonPtr(void);

	public:
		// Create FBO
		FramebufferObject* createFBO(string name);
		// Get FBO
		FramebufferObject* getFBO(string name);

	protected:
		// Frame buffer objects
		FBOMap mFBOs;
	};
};

#endif