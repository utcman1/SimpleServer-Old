#include <stdafx.hpp>
#include <ssImpl/ssConfig.hpp>



///////////////////////////////////////////////////////////////////////////////
// Base
std::string ssConfig::Base::toString(const Type& _type)
{
	switch (_type)
	{
	default:			return "";
	case Base::SERVER:	return "SERVER";
	case Base::CLIENT:	return "CLIENT";
	}
}

std::string ssConfig::Base::toString() const
{
	return Base::toString(this->type) + "_" + std::to_string(id);
}



///////////////////////////////////////////////////////////////////////////////
// Server
void ssConfig::Server::readFrom(const bpTree& _pTree, const std::string& _pathPrefix)
{
	this->poolSize		 = _pTree.get<size_t>		(_pathPrefix + "POOL_SIZE",			this->poolSize);
	this->backlogMaxSize = _pTree.get<size_t>		(_pathPrefix + "BACKLOG_MAX_SIZE",	this->backlogMaxSize);
	this->serverIp		 = _pTree.get<std::string>	(_pathPrefix + "SERVER_IP",			this->serverIp);
	this->serverPort	 = _pTree.get<uint16_t>		(_pathPrefix + "SERVER_PORT",		this->serverPort);
}



///////////////////////////////////////////////////////////////////////////////
// Client
void ssConfig::Client::readFrom(const bpTree& _pTree, const std::string& _pathPrefix)
{
	Server::readFrom(_pTree, _pathPrefix);

	this->localIp		 = _pTree.get<std::string>	(_pathPrefix + "LOCAL_IP",			this->localIp);
	this->localPortBegin = _pTree.get<uint16_t>		(_pathPrefix + "LOCAL_PORT_BEGIN",	this->localPortBegin);
	this->localPortEnd	 = _pTree.get<uint16_t>		(_pathPrefix + "LOCAL_PORT_END",	this->localPortEnd);
}



///////////////////////////////////////////////////////////////////////////////
// ssConfig
void ssConfig::readVector(
	std::vector<int>& _outVec,
	const bpTree& _pTree, const std::string& _path)
{
	const std::string strValue = _pTree.get<std::string>(_path, "");
	_outVec.assign(
		std::istream_iterator<int>(std::istringstream(strValue)),
		std::istream_iterator<int>());
}

void ssConfig::readServerMap(
	std::unordered_map<int, Server>& _serverMap,
	const std::vector<int> _serverList, const Server& _serverDefault,
	const bpTree& _pTree)
{
	for (int serverId : _serverList)
	{
		const std::string pathPrefix = "SERVER_" + std::to_string(serverId) + ".";

		Server server = _serverDefault;
		server.type = Base::SERVER;
		server.id = serverId;

		server.readFrom(_pTree, pathPrefix);

		_serverMap[serverId] = server;
	}
}

void ssConfig::readClientMap(
	std::unordered_map<int, Client>& _clientMap,
	const std::vector<int> _clientList, const Client& _clientDefault,
	const bpTree& _pTree)
{
	for (int clientId : _clientList)
	{
		const std::string pathPrefix = "CLIENT_" + std::to_string(clientId) + ".";

		Client client = _clientDefault;
		client.type = Base::CLIENT;
		client.id = clientId;

		client.readFrom(_pTree, pathPrefix);

		_clientMap[clientId] = client;
	}
}

void ssConfig::readFrom(const bpTree& _pTree)
{
	ssConfig::readVector(this->serverList, _pTree, "MAIN.SERVER_LIST");
	ssConfig::readVector(this->clientList, _pTree, "MAIN.CLIENT_LIST");
	serverDefault.readFrom(_pTree, "SERVER_DEFAULT.");
	clientDefault.readFrom(_pTree, "CLIENT_DEFAULT.");

	ssConfig::readServerMap(this->serverMap, this->serverList, this->serverDefault, _pTree);
	ssConfig::readClientMap(this->clientMap, this->clientList, this->clientDefault, _pTree);
}



bool ssConfig::init(const std::string& _configFileName)
{
	bpTree pTree;
	boost::property_tree::ini_parser::read_ini(_configFileName, pTree);

	readFrom(pTree);

	return true;
}