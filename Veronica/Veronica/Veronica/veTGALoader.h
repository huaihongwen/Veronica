#ifndef VEE_TGALOADER_H
#define VEE_TGALOADER_H


/*
 * veTGALoader.h
 */


#include "vePrerequisites.h"


namespace vee {

	// TGA data
	struct TGAData {

		// Type code
		// 2 for uncompressed RGB, 3 for uncompressed grayscale
		uchar mTypeCode;

		// Width
		short mWidth;
		// Height
		short mHeight;

		// Bits per pixel
		uchar mBitsPP;

		// Data
		uchar* mData;

		//---------------------------------------------------------------
		TGAData() {

			mData = NULL;
		}
		//---------------------------------------------------------------
		~TGAData() {

			if (mData) {

				delete [] mData;
			}
		}
	};


	// Simple .tga image loader
	class TGALoader {

	public:

		// Load .tga image
		static void loadTGAFile(TGAData* pTga, const char* filename);

		// Save .tga image
		static void saveTGAFile(TGAData* pTga, const char* filename);
	};
};

#endif