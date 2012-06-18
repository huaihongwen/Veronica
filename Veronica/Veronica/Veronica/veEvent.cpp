#include "veEvent.h"

namespace vee {

	//---------------------------------------------------------------
	template<typename ReturnT, typename Param1T>
	EventHandlerBase1<ReturnT, Param1T>::EventHandlerBase1() {
	}

	//---------------------------------------------------------------
	template<typename ReturnT, typename Param1T>
	EventHandlerBase1<ReturnT, Param1T>::~EventHandlerBase1() {
	}



	//---------------------------------------------------------------
	template<typename ListenerT, typename ReturnT, typename Param1T>
	EventHandler1<ListenerT, ReturnT, Param1T>::EventHandler1() {
	}

	//---------------------------------------------------------------
	template<typename ListenerT, typename ReturnT, typename Param1T>
	EventHandler1<ListenerT, ReturnT, Param1T>::EventHandler1(
		ListenerT* listener, memberFuncPtr funcPtr) {

		// Listener pointer
		mListener = listener;

		// Listener member function pointer
		mMemberFuncPtr = funcPtr;
	}

	//---------------------------------------------------------------
	template<typename ListenerT, typename ReturnT, typename Param1T>
	EventHandler1<ListenerT, ReturnT, Param1T>::~EventHandler1() {
	}


	//---------------------------------------------------------------
	/**
	 * Notify listener
	 */
	template<typename ListenerT, typename ReturnT, typename Param1T>
	ReturnT EventHandler1<ListenerT, ReturnT, Param1T>::notify(Param1T p1) {

		return mListener->(*mMemberFuncPtr)(p1);
	}



	//---------------------------------------------------------------
	template<typename ReturnT, typename Param1T>
	Event1<ReturnT, Param1T>::Event1() {

		// Handler number
		mHandlerNum = 0;
	}

	//---------------------------------------------------------------
	template<typename ReturnT, typename Param1T>
	Event1<ReturnT, Param1T>::~Event1() {

		HandlerMap::const_iterator h = mHandlers.begin();

		// Loop each event handler
		for (; h != mHandlers.end(); h++) {

			// Delete event handler
			delete h->second;
		}

		mHandlers.clear();
	}


	//---------------------------------------------------------------
	/**
	 * Attach event handler
	 */
	template<typename ReturnT, typename Param1T>
	template<typename ListenerT>
	int Event1<ReturnT, Param1T>::attach(ListenerT* listener, 
		ReturnT (ListenerT::*mFuncPtr) (Param1T)) {

		// Create event handler
		mHandlers[mHandlerNum++] = new EventHandler1<ListenerT, ReturnT, Param1T>(listener, mFuncPtr);

		return mHandlerNum - 1;
	}

	//---------------------------------------------------------------
	/**
	 * Detach event handler
	 */
	template<typename ReturnT, typename Param1T>
	bool Event1<ReturnT, Param1T>::detach(int id) {

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

	//---------------------------------------------------------------
	/**
	 * Notify event handlers
	 */
	template<typename ReturnT, typename Param1T>
	ReturnT Event1<ReturnT, Param1T>::notify(Param1T p1) {

		HandlerMap::const_iterator h = mHandlers.begin();

		// Loop each event handler
		for (; h != mHandlers.end(); i++) {

			h->second->notify(p1);
		}

		/**
		 * Normally return type for notify function
		 * is bool.
		 */
		return true;
	}
};