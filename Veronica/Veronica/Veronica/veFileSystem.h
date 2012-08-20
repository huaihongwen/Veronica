#ifndef VEE_FILESYSTEM_H
#define VEE_FILESYSTEM_H

/**
 * veFileSystem.h
 */

#include "vePrerequisites.h"
#include "veSingleton.h"

#include <windows.h>


namespace vee {

	// veFileSystem
	class veFileSystem : public SingletonVee<veFileSystem> {

	public:
		veFileSystem();
		~veFileSystem();


		// Singleton
		static veFileSystem& getSingleton(void);
		static veFileSystem* getSingletonPtr(void);


	public:
		/**
		 * Init
		 */
		void init();

		/**
		 * Destroy
		 */
		void destroy();


		/**
		 * Open file dialog
		 */
		bool openFileDialog(char* buffer);

		/**
		 * Save file dialog
		 */
		bool saveFileDialog(char* buffer);


	public:
		// Window handler
		HWND mHWnd;
	};
};

#endif