#include "Console.h"

#include <Arduino.h>

namespace TwinSystem {

	String Console::endl = String("\n");
	ConsoleLevel Console::_level = ConsoleLevel::_INFO;

	ConsoleStream Console::trace(String origin) {
		return ConsoleStream(ConsoleLevel::_TRACE, origin);
	}

	ConsoleStream Console::info(String origin) {
		return ConsoleStream(ConsoleLevel::_INFO, origin);
	}

	ConsoleStream Console::warn(String origin) {
		return ConsoleStream(ConsoleLevel::_WARNING, origin);
	}

	ConsoleStream Console::error(String origin) {
		return ConsoleStream(ConsoleLevel::_ERROR, origin);
	}

	ConsoleStream Console::success(String origin) {
		return ConsoleStream(ConsoleLevel::_SUCCESS, origin);
	}

	ConsoleStream Console::critical(String origin) {
		return ConsoleStream(ConsoleLevel::_CRITICAL, origin);
	}


	void Console::Initialize(){
		Serial.begin(115200);
		Serial.println("");
		Serial.println("   _______       _       _      _     _            ");
		Serial.println("  |__   __|     (_)     | |    (_)   | |           ");
		Serial.println("     | |_      ___ _ __ | |     _  __| | __ _ _ __ ");
		Serial.println("     | \\ \\ /\\ / / | '_ \\| |    | |/ _` |/ _` | '__|");
		Serial.println("     | |\\ V  V /| | | | | |____| | (_| | (_| | |   ");
		Serial.println("     |_| \\_/\\_/ |_|_| |_|______|_|\\__,_|\\__,_|_|   ");                                           
		Serial.println("");                                           
	}

	void Console::write(const char* str) {
		Serial.write(str);
	}

	void Console::print(String s){
		Serial.print(s);
	}

	void Console::println(String s){
		Serial.println(s);
	}


}