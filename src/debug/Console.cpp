#include "Console.h"

#include <Arduino.h>

namespace TwinSystem {


	std::string Console::endl = "\n";
	ConsoleLevel Console::_level = ConsoleLevel::_INFO;

	ConsoleStream Console::trace(std::string origin) {
		return ConsoleStream(ConsoleLevel::_TRACE, origin);
	}

	ConsoleStream Console::info(std::string origin) {
		return ConsoleStream(ConsoleLevel::_INFO, origin);
	}

	ConsoleStream Console::warn(std::string origin) {
		return ConsoleStream(ConsoleLevel::_WARNING, origin);
	}

	ConsoleStream Console::error(std::string origin) {
		return ConsoleStream(ConsoleLevel::_ERROR, origin);
	}

	ConsoleStream Console::success(std::string origin) {
		return ConsoleStream(ConsoleLevel::_SUCCESS, origin);
	}

	ConsoleStream Console::critical(std::string origin) {
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

	void Console::write(std::string str) {
		Serial.write(str.c_str());
	}

	void Console::print(char c){
		Serial.print(c);
	}

	void Console::print(const char s[]){
		Serial.print(s);
	}
	
	void Console::print(unsigned char n, int base){
		Serial.print(n, base);
	}
	
	void Console::print(int n, int base){
		Serial.print(n, base);
	}
	
	void Console::print(unsigned int n, int base){
		Serial.print(n, base);
	}
	
	void Console::print(long n, int base){
		Serial.print(n, base);
	}
	
	void Console::print(unsigned long n, int base){
		Serial.print(n, base);
	}
	
	void Console::print(int64_t n, int base){
		Serial.print(n, base);
	}
	
	void Console::print(uint64_t n, int base){
		Serial.print(n, base);
	}
	
	void Console::print(double n, int digits = 4){
		Serial.print(n, digits);
	}

	void Console::print(std::string s){
		Serial.print(s.c_str());
	}



	void Console::println(char c){
		Serial.println(c);
	}

	void Console::println(const char s[]){
		Serial.println(s);
	}

	
	void Console::println(unsigned char n, int base){
		Serial.println(n, base);
	}
	
	void Console::println(int n, int base){
		Serial.println(n, base);
	}
	
	void Console::println(unsigned int n, int base){
		Serial.println(n, base);
	}
	
	void Console::println(long n, int base){
		Serial.println(n, base);
	}
	
	void Console::println(unsigned long n, int base){
		Serial.println(n, base);
	}
	
	void Console::println(int64_t n, int base){
		Serial.println(n, base);
	}
	
	void Console::println(uint64_t n, int base){
		Serial.println(n, base);
	}
	
	void Console::println(double n, int digits = 4){
		Serial.println(n, digits);
	}

	void Console::println(std::string s){
		Serial.println(s.c_str());
	}
	

}