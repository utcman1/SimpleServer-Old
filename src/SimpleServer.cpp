#include <stdafx.hpp>
#include <ssLib.hpp>



int main()
{
	ssService server;
	server.accept(baEndpoint(baAddr::from_string("127.0.0.1"), 9999));
	server.run();

    return 0;
}
