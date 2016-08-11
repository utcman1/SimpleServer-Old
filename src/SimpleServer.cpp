#include <stdafx.hpp>
#include <ssLib/ssLib.hpp>



int main()
{
	ssCService server;
	server.accept(BAEndpoint(BAAddr::from_string("127.0.0.1"), 9999));
	server.run();

    return 0;
}
