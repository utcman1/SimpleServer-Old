#include <stdafx.hpp>
#include <ssLib.hpp>
#include <ssImpl/ssEchoServerSessionHandler.hpp>



int main()
{
	baIoService service;
	ssAcceptor<ssEchoServerSessionHandler> acceptor(service);
	if (!acceptor.init(service, 1, 1))
	{
		std::cerr << "Fail to acceptor.init()" << std::endl;
		return -1;
	}

	acceptor.accept(baEndpoint(baAddr::from_string("127.0.0.1"), 9999));

	service.run();

    return 0;
}
