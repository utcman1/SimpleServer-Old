#include <stdafx.hpp>
#include <ssLib.hpp>
#include <ssImpl/ssEchoClientSessionHandler.hpp>



int main()
{
	baIoService ioService;
	ssConnector<ssEchoClientSessionHandler> connector(ioService);
	if (!connector.init(1, 1))
	{
		std::cerr << "Fail to connector.init()" << std::endl;
		return -1;
	}

	connector.connect(baEndpoint(baAddr::from_string("127.0.0.1"), 10000));

	ioService.run();

    return 0;
}
