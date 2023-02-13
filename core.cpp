#include <windows.h>

#include <iostream>

#include <ranges>
#include <string>
#include <vector>

#include <thread>

int main( )
{
	/*
	* Black Nigga Balls HD
	*/

	return 0;
}

bool __stdcall DllMain( HMODULE h_module, std::uint32_t call_type, void* )
{
	if ( call_type == DLL_PROCESS_ATTACH )
		std::thread( main ).detach( );

	return true;
}