#ifndef VEE_EVENT_H
#define VEE_EVENT_H

/**
 * Basic event
 */

#include "vePrerequisites.h"

#include <map>

namespace vee {

	/**
	 * EventHandlerBase1
	 * Event handler base with 1 param.
	 */
	template<typename ReturnT, typename Param1T>
	class EventHandlerBase1 {

	public:
		EventHandlerBase1() {}
		virtual ~EventHandlerBase1() {}

	public:
		/**
		 * Notify listener
		 */
		virtual ReturnT notify(Param1T p1) = 0;
	};



	/**
	 * EventHandler1
	 * Event handler with 1 param.
	 */
	template<typename ListenerT, typename ReturnT, typename Param1T>
	class EventHandler1 : public EventHandlerBase1<ReturnT, Param1T> {

		// Listener member function pointer
		typedef ReturnT (ListenerT::*memberFuncPtr) (Param1T);


	protected:
		// Listener pointer
		ListenerT* mListener;

		// Listener member function pointer
		memberFuncPtr mMemberFuncPtr;


	public:
		EventHandler1() {}
		EventHandler1(ListenerT* listener, memberFuncPtr funcPtr) {

			// Listener pointer
			mListener = listener;

			// Listener member function pointer
			mMemberFuncPtr = funcPtr;
		}
		~EventHandler1() {}


	public:
		/**
		 * Notify listener
		 */
		ReturnT notify(Param1T p1) {
			return (mListener->*mMemberFuncPtr)(p1);
		}
	};



	/**
	 * Event1
	 * Event with 1 param.
	 */
	template<typename ReturnT, typename Param1T>
	class Event1 {

		// Event handler map
		typedef std::map<int, EventHandlerBase1<ReturnT, Param1T>*> HandlerMap;


	public:
		Event1() {

			// Handler number
			mHandlerNum = 0;
		};
		~Event1() {


			HandlerMap::const_iterator h = mHandlers.begin();

			// Loop each event handler
			for (; h != mHandlers.end(); h++) {

				// Delete event handler
				delete h->second;
			}

			mHandlers.clear();
		};


	public:
		/**
		 * Attach event handler
		 */
		template<typename ListenerT>
		int attach(ListenerT* listener, ReturnT (ListenerT::*mFuncPtr) (Param1T)) {

			// Create event handler
			mHandlers[mHandlerNum++] = new EventHandler1<ListenerT, ReturnT, Param1T>(listener, mFuncPtr);

			return mHandlerNum - 1;
		}

		/**
		 * Detach event handler
		 */
		bool detach(int id) {

			// Try to find event handler
			HandlerMap::const_iterator h = mHandlers.find(id);

			// Can not find event handler
			if (h == mHandlers.end()) {
				return false;
			}


			// Delete event handler
			delete h->second;

			// Remove it from map
			mHandlers.erase(h);

			return true;
		}

		/**
		 * Notify event handlers
		 */
		ReturnT notify(Param1T p1) {

			HandlerMap::const_iterator h = mHandlers.begin();

			// Loop each event handler
			for (; h != mHandlers.end(); h++) {

				h->second->notify(p1);
			}

			/**
			 * Normally return type for notify function
			 * is bool.
			 */
			return true;
		}


	protected:
		// Event handler map
		HandlerMap mHandlers;

		// Handler number
		int mHandlerNum;
	};
};

#endif