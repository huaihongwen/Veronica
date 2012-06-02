#include "veTGALoader.h"
#include <fstream>


namespace vee {
	
	//---------------------------------------------------------------
	// Load .tga image
	void TGALoader::loadTGAFile(TGAData* pTga, const char* filename) {

		// Open file
		FILE* pFile;
		fopen_s(&pFile, filename, "rb");

		if (!pFile) {
			return;
		}


		// Ignore
		uchar ucIgnore;
		short siIgnore;


		// Ignore
		fread(&siIgnore, sizeof(uchar), 2, pFile);


		// Type code
		fread(&pTga->mTypeCode, sizeof(uchar), 1, pFile);


		// Invalid image
		if (pTga->mTypeCode != 2 && pTga->mTypeCode != 3) {
			
			fclose(pFile);
			return;
		}


		// Ignored stuffs
		fread(&siIgnore, sizeof(short), 1, pFile);
		fread(&siIgnore, sizeof(short), 1, pFile);
		fread(&ucIgnore, sizeof(uchar), 1, pFile);
		fread(&siIgnore, sizeof(short), 1, pFile);
		fread(&siIgnore, sizeof(short), 1, pFile);


		// Width
		fread(&pTga->mWidth, sizeof(short), 1, pFile);
		// Height
		fread(&pTga->mHeight, sizeof(short), 1, pFile);
		

		// Color bits
		fread(&pTga->mBitsPP, sizeof(uchar), 1, pFile);


		// Ignore
		fread(&ucIgnore, sizeof(uchar), 1, pFile);


		// Color component
		int colorcmp = pTga->mBitsPP / 8;

		// Total length
		int length = pTga->mWidth * pTga->mHeight * colorcmp;


		// Allocate memory
		pTga->mData = (uchar*)malloc(length);

		if (!pTga->mData) {

			fclose(pFile);
			return;
		}


		// Read image data
		fread(pTga->mData, sizeof(uchar), length, pFile);


		if (colorcmp != 1) {

			// Swap r and b
			uchar swapColor;

			for (int i = 0; i < length; i += colorcmp) {

				swapColor = pTga->mData[i];

				pTga->mData[i] = pTga->mData[i + 2];

				pTga->mData[i + 2] = swapColor;


				swapColor = pTga->mData[i+3];
			}
		}


		fclose(pFile);

		return;
	};


	//---------------------------------------------------------------
	// Save .tga image
	void TGALoader::saveTGAFile(TGAData* pTga, const char* filename) {

		// Create or open file
		FILE* pFile;
		fopen_s(&pFile, filename, "wb");

		if (!pFile){
			return;
		}


		// Ignore
		uchar ucIgnore = 0;
		short siIgonre = 0;


		// Ignore
		fwrite(&siIgonre, sizeof(uchar), 2, pFile);


		// Type code
		fwrite(&pTga->mTypeCode, sizeof(uchar), 1, pFile);


		// Ignored
		fwrite(&siIgonre, sizeof(short), 1, pFile);
		fwrite(&siIgonre, sizeof(short), 1, pFile);
		fwrite(&ucIgnore, sizeof(uchar), 1, pFile);
		fwrite(&siIgonre, sizeof(short), 1, pFile);
		fwrite(&siIgonre, sizeof(short), 1, pFile);


		// Width
		fwrite(&pTga->mWidth, sizeof(short), 1, pFile);
		// Height
		fwrite(&pTga->mHeight, sizeof(short), 1, pFile);


		// Color bits
		fwrite(&pTga->mBitsPP, sizeof(uchar), 1, pFile);


		// Ignore
		fwrite(&ucIgnore, sizeof(uchar), 1, pFile);


		// Color component num
		int colorcmp = pTga->mBitsPP / 8;

		// Total length
		int length = pTga->mWidth * pTga->mHeight * colorcmp;


		if (colorcmp != 1) {

			// Swap r and b
			uchar swapColor;
			for (int i = 0; i < length; i+=colorcmp) {

				swapColor = pTga->mData[i];

				pTga->mData[i] = pTga->mData[i + 2];

				pTga->mData[i + 2] = swapColor;
			}
		}


		// Write color
		fwrite(pTga->mData, sizeof(uchar), length, pFile);


		fclose(pFile);
	}
};