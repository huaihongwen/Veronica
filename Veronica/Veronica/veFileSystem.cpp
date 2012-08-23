#include "veFileSystem.h"


namespace vee {

	//---------------------------------------------------------------
	veFileSystem::veFileSystem() {

		// Window handler
		mHWnd = NULL;
	}

	//---------------------------------------------------------------
	veFileSystem::~veFileSystem() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	// Initialize the static member
	template<> veFileSystem* SingletonVee<veFileSystem>::ms_Singleton = 0;
	veFileSystem& veFileSystem::getSingleton(void) {

		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	veFileSystem* veFileSystem::getSingletonPtr(void) {

		return ms_Singleton;
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void veFileSystem::init() {
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void veFileSystem::destroy() {
	}


	//---------------------------------------------------------------
	/**
	 * Open file dialog
	 * @buffer {char*} file name buffer, must be a char array.
	 * @return {bool} file valid or not.
	 */
	bool veFileSystem::openFileDialog(char* buffer) {

		// Common dialog box struct
		OPENFILENAME ofn;

		// Empty struct
		ZeroMemory(&ofn, sizeof(ofn));


		// Setup params
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = mHWnd;

		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;

		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		ofn.lpstrFile = buffer;

		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;


		// Open file dialog
		if (GetOpenFileName(&ofn)) {

			return true;
		} else {

			return false;
		}
	}
	
	
	//---------------------------------------------------------------
	/**
	 * Save file dialog
	 * @buffer {char*} file name buffer, must be a char array.
	 * @return {bool} file valid or not.
	 */
	bool veFileSystem::saveFileDialog(char* buffer) {

		// Common dialog box struct
		OPENFILENAME ofn;

		// Empty struct
		ZeroMemory(&ofn, sizeof(ofn));


		// Setup params
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = mHWnd;

		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;

		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		ofn.lpstrFile = buffer;

		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;


		// Save file dialog
		if (GetSaveFileName(&ofn)) {

			return true;
		} else {

			return false;
		}
	}
};