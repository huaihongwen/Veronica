#ifndef VEE_TIMER_H
#define VEE_TIMER_H

/*
 * Basic timer
 */

#include "vePrerequisites.h"
#include <Windows.h>


namespace vee {

	// Timer
	class Timer {

	public:
		Timer() {}
		~Timer() {}

	public:

		// Init
		void init() {

			// Query the performance timer ticks per second(frequency)
			QueryPerformanceFrequency((LARGE_INTEGER*)&mTicksPerSecond);

			// Calculate the start time
			mStartTime = 0;
			mStartTime = getCurremtTime();

			// FPS
			mLastUpdate = 0;
			mFPSUpdateInterval = 0.5f; // Update fps every 0.5 second
			mNumFrames = 0;
			mFPS = 0;
		}

		// Get current time
		float getCurremtTime() {
			UINT64 ticks;
			// Query the performance timer ticks
			QueryPerformanceCounter((LARGE_INTEGER*)&ticks);

			float time = (float)(__int64)ticks/(float)(__int64)mTicksPerSecond;
			time -= mStartTime;
			return time;
		}

		// Update fps
		void updateFPS() {

			mNumFrames++;
			float currentUpdate = getCurremtTime();
			if (currentUpdate - mLastUpdate > mFPSUpdateInterval) {

				mFPS = mNumFrames / (currentUpdate - mLastUpdate);
				mLastUpdate = currentUpdate;
				mNumFrames = 0;
			}
		}

		// Get FPS
		float getFPS() {

			return mFPS;
		}

	protected:
		float mStartTime; // Timer at game start
		UINT64 mTicksPerSecond; // Ticks per second

		// FPS
		float mLastUpdate;
		float mFPSUpdateInterval;
		uint mNumFrames;
		float mFPS;
	};
};

#endif