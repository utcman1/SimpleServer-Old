#include <stdafx.hpp>
#include <ssLib/ssLib.hpp>



int main()
{
	ssCService server;
	server.accept(9999);
	server.run();

    return 0;
}
