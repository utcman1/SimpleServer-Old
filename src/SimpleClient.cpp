#include <stdafx.hpp>
#include <ssLib.hpp>
#include <ssImpl/ssEchoClientSessionHandler.hpp>



int main()
{
	baIoService service;
	ssConnector<ssEchoClientSessionHandler> connector;
	if (!connector.init(service, 1))
	{
		std::cerr << "Fail to connector.init()" << std::endl;
		return -1;
	}

	connector.connect(baEndpoint(baAddr::from_string("127.0.0.1"), 9999));

	service.run();

    return 0;
}
