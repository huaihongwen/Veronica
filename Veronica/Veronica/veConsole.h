#ifndef VEE_CONSOLE_H
#define VEE_CONSOLE_H


/* 
 * Basic console
 */


#include "vePrerequisites.h"
#include "veSingleton.h"

#include <Windows.h>

#include <map>
#include <vector>


namespace vee {

	// Command handler base
	class CommandHandlerBase {

	public:
		CommandHandlerBase() {}
		virtual ~CommandHandlerBase() {}


	public:
		// Execute command
		virtual void executeCommand(const vector<string>& v) = 0;
	};


	// Command handler
	template <typename Executor>
	class CommandHandler : public CommandHandlerBase {

		// Executor member function pointer
		typedef void (Executor::*MemFuncPtr) (const vector<string>&);


	public:
		CommandHandler() {}
		CommandHandler(Executor* e, MemFuncPtr ptr) {
		
			// Executor
			mExecutor = e;

			// Executor member function pointer
			mFuncPtr = ptr;
		}
		~CommandHandler() {}


	public:
		// Execute command
		void executeCommand(const vector<string>& v) {

			// Call executor's function
			(mExecutor->*mFuncPtr)(v);
		}


	protected:
		// Executor
		Executor* mExecutor;

		// Executor member function pointer
		MemFuncPtr mFuncPtr;
	};


	// Console
	class Console : public SingletonVee<Console> {

		// Command handler base map
		typedef map<string, CommandHandlerBase*> HandlerMap;


	public:
		Console();
		~Console();

	public:
		// Get singleton
		static Console& Console::getSingleton(void);
		// Get singleton ptr
		static Console* Console::getSingletonPtr(void);


	public:
		// Key pressed
		void keyPressed(char c);

		// Render
		void render();


		// Add handler
		template <typename Executor>
		void addHandler(const string name, Executor* e, void (Executor::*MemFuncPtr) (const vector<string>&));


	protected:
		// Execute command
		void _executeCommand();

		// Parse command line
		void _parseCommandLine();


	protected:
		// Command line string
		string mCommandLine;


		// Command handlers
		HandlerMap mHandlers;
	};

};

#endif