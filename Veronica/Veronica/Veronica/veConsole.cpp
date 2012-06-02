#include "veConsole.h"
// Font system
#include "veFontSystem.h"


namespace vee {

	//---------------------------------------------------------------
	Console::Console() {
	}

	//---------------------------------------------------------------
	Console::~Console() {

		map<string, CommandHandlerBase*>::const_iterator handler;

		for (handler = mHandlers.begin(); handler != mHandlers.end(); handler++) {

			// Delete command handler
			delete handler->second;
		}

		mHandlers.clear();
	}

	//---------------------------------------------------------------
	// Initialize the static member.
	template<> Console* SingletonVee<Console>::ms_Singleton = 0;
	Console& Console::getSingleton(void) {

		return *ms_Singleton;
	}

	//---------------------------------------------------------------
	Console* Console::getSingletonPtr(void) {

		return ms_Singleton;
	}


	//---------------------------------------------------------------
	// Key pressed
	void Console::keyPressed(char c) {

		// Handle key pressed
		switch (c)
		{

		// Backspace
		case 8:
			{
				if (!mCommandLine.empty()) {
					// Delete last char from command line
					mCommandLine.erase(mCommandLine.length()-1, 1);
				}
				break;
			}

		// Enter
		case 13:
			{
				// Parse command line
				_parseCommandLine();

				break;
			}


		// Default
		default:
			{
				mCommandLine += c;

				break;
			}
		}
	}


	//---------------------------------------------------------------
	// Render
	void Console::render() {

		// Font system
		FontSystem& fs = FontSystem::getSingleton();

		fs.render("<<: " + mCommandLine);
	}


	//---------------------------------------------------------------
	// Add handler
	template <typename Executor>
	void Console::addHandler(const string name, Executor* e, void (Executor::*MemFuncPtr) (const vector<string>&)) {

		map<string, CommandHandlerBase*>::const_iterator handler = mHandlers.find(name);

		if (handler == mHandlers.end()) {

			mHandlers[name] = new CommandHandler<Executor>(e, MemFuncPtr);
		}
	}


	//---------------------------------------------------------------
	// Execute command
	void Console::_executeCommand() {
	}


	//---------------------------------------------------------------
	// Parse command line
	void Console::_parseCommandLine() {

		// Arguments
		vector<string> args;


		// Temp string
		string temp = "";


		// Loop command line
		for (uint i = 0; i < mCommandLine.length(); i++) {

			// Meet an empty space
			if (mCommandLine.at(i) == ' ') {

				if (!temp.empty()) {

					// Push temp
					args.push_back(temp);

					// Reset temp
					temp.clear();
				}
			} else {

				temp += mCommandLine.at(i);
			}
		}

		if (!temp.empty()) {
			// Push temp
			args.push_back(temp);
		}


		// Reset command line
 		mCommandLine.clear();


		if (!args.empty()) {

			// Find command handler
			map<string, CommandHandlerBase*>::const_iterator handler = mHandlers.find(args[0]);

			if (handler != mHandlers.end()) {

				// Execute command
				handler->second->executeCommand(args);
			} else {

				// Invalid command
				cout<<"Invalid command."<<endl;
			}
		}
	}
};