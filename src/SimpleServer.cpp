#include <stdafx.hpp>
#include <ssLib.hpp>
#include <ssImpl/ssConfig.hpp>
#include <ssImpl/ssEchoServerSessionHandler.hpp>
#include <ssImpl/ssEchoClientSessionHandler.hpp>



int serverMain(const ssConfig::Server& _server)
{
	baIoService ioService;
	ssAcceptor<ssEchoServerSessionHandler> acceptor(ioService);
	if (!acceptor.init(_server.poolSize, _server.backlogMaxSize))
	{
		std::cerr << "Fail to acceptor.init()" << std::endl;
		return -1;
	}

	acceptor.accept(baEndpoint(baAddr::from_string(_server.serverIp), _server.serverPort));

	ioService.run();
	return 0;
}

int clientMain(const ssConfig::Client& _client)
{
	baIoService ioService;
	ssConnector<ssEchoClientSessionHandler> connector(ioService);
	if (!connector.init(_client.poolSize, _client.backlogMaxSize))
	{
		std::cerr << "Fail to connector.init()" << std::endl;
		return -1;
	}

	connector.connect(baEndpoint(baAddr::from_string(_client.serverIp), _client.serverPort));

	ioService.run();

	return 0;
}

int main(int argc, char* argv[])
{
	ssConfig cnf;
	if (!cnf.init(argc, argv))
		return -1;

	const ssConfig::Base& base = cnf.getConf();
	switch (base.type)
	{
	default:
	case ssConfig::Base::INVALID: return -1;
	case ssConfig::Base::SERVER: return serverMain(static_cast<const ssConfig::Server&>(base));
	case ssConfig::Base::CLIENT: return clientMain(static_cast<const ssConfig::Client&>(base));
	}
}
