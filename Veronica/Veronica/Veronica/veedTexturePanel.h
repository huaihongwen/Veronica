#ifndef VEED_UITEXTUREPANEL_H
#define VEED_UITEXTUREPANEL_H

/*
 * veedUITexturePanel.h
 */

#include "veedPrerequisites.h"

#include "veUIComponent.h"

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
	};
};

#endif