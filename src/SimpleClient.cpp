#include <stdafx.hpp>
#include <ssLib.hpp>



int main()
{
	ssService client;
	client.connect(baEndpoint(baAddr::from_string("127.0.0.1"), 9999));
	client.run();

    return 0;
}
