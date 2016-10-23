#include <stdafx.hpp>
#include <ssLib.hpp>
#include <ssImpl/ssConfig.hpp>
#include <ssImpl/ssEchoServerSessionHandler.hpp>



int main(int argc, char* argv[])
{
	ssConfig cnf;
	if (!cnf.init(argc, argv))
		return -1;
/*
	baIoService ioService;
	ssAcceptor<ssEchoServerSessionHandler> acceptor(ioService);
	if (!acceptor.init(1, 1))
	{
		std::cerr << "Fail to acceptor.init()" << std::endl;
		return -1;
	}

	acceptor.accept(baEndpoint(baAddr::from_string("127.0.0.1"), 10000));

	ioService.run();
*/
    return 0;
}
