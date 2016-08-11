#include <stdafx.hpp>
#include <ssLib/ssLib.hpp>



int main()
{
	ssCService client;
	client.connect(BAEndpoint(BAAddr::from_string("127.0.0.1"), 9999));
	client.run();

    return 0;
}
