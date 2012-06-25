#ifndef VEE_UITEXTUREPANEL_H
#define VEE_UITEXTUREPANEL_H

/*
 * veUITexturePanel.h
 */

// Engine
#include "vePrerequisites.h"

#include "veUIComponent.h"
#include "veVoxel.h"
#include "veEvent.h"

#include <vector>

namespace vee {

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


	public:
		// Event
		Event1<bool, VoxelType> mEvent;
	};
};

#endif