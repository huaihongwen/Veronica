#ifndef VEED_UITEXTUREPANEL_H
#define VEED_UITEXTUREPANEL_H

/*
 * veedUITexturePanel.h
 */

#include "veedPrerequisites.h"
#include "veUIComponent.h"
#include "veVoxel.h"

#include <vector>

namespace veed {

	/**
	 * Texture panel
	 */
	class UITexturePanel : public UIComponent {

	public:
		UITexturePanel();
		~UITexturePanel();


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
		 * Render
		 */
		void render();


	public:
		/**
		 * Mouse left button up
		 */
		bool mouseLUp(int x, int y);


	protected:
		/**
		 * Init types
		 */
		void _initTypes();


	protected:
		// Buttons
		vector<UIComponent*> mButtons;

		// Types
		vector<VoxelType> mTypes;


		// Selected index
		int mSelectedIdx;
	};
};

#endif