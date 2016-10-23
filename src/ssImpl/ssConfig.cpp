#include <stdafx.hpp>
#include <ssImpl/ssConfig.hpp>



using namespace std;
using namespace boost::program_options;

///////////////////////////////////////////////////////////////////////////////
// Base
string ssConfig::Base::toString(const Type& _type)
{
	switch (_type)
	{
	default:
	case Base::UNKNOWN:	return "UNKNOWN";
	case Base::SERVER:	return "SERVER";
	case Base::CLIENT:	return "CLIENT";
	}
}

string ssConfig::Base::toString() const
{
	return Base::toString(this->type) + "_" + to_string(nodeId);
}



#define OPTION_ENTRY(k, v) ((_keyPrefix + k).c_str(), value(&(v)), "")
///////////////////////////////////////////////////////////////////////////////
// Server
void ssConfig::Server::parseFrom(const string& _conf, const string& _keyPrefix)
{
	options_description desc;
	variables_map vm;
	desc.add_options()
		OPTION_ENTRY("POOL_SIZE",		this->poolSize)
		OPTION_ENTRY("BACKLOG_MAX_SIZE",this->backlogMaxSize)
		OPTION_ENTRY("SERVER_IP",		this->serverIp)
		OPTION_ENTRY("SERVER_PORT",		this->serverPort);
	store(parse_config_file<char>(_conf.c_str(), desc, true), vm);
	notify(vm);
}



///////////////////////////////////////////////////////////////////////////////
// Client
void ssConfig::Client::parseFrom(const string& _conf, const string& _keyPrefix)
{
	Server::parseFrom(_conf, _keyPrefix);

	options_description desc;
	variables_map vm;
	desc.add_options()
		OPTION_ENTRY("LOCAL_IP",		this->localIp)
		OPTION_ENTRY("LOCAL_PORT_BEGIN",this->localPortBegin)
		OPTION_ENTRY("LOCAL_PORT_END",	this->localPortEnd);
	store(parse_config_file<char>(_conf.c_str(), desc, true), vm);
	notify(vm);
}
#undef OPTION_ENTRY



///////////////////////////////////////////////////////////////////////////////
// ssConfig

// throw exception on fail
void ssConfig::parseVector(
	vector<int>& _outVec,
	const string& _conf, const string& _key)
{
	string strValue;
	options_description desc;
	variables_map vm;
	desc.add_options()
		(_key.c_str(), value(&strValue), "");
	store(parse_config_file<char>(_conf.c_str(), desc, true), vm);
	notify(vm);

	istringstream is(strValue);
	_outVec.assign(
		istream_iterator<int>(is),
		istream_iterator<int>());
}

// throw exception on fail
void ssConfig::parseServerMap(
	map<int, Server>& _serverMap,
	const string& _conf, const vector<int>& _serverList,
	const Server& _serverDefault)
{
	for (int nodeId : _serverList)
	{
		const string keyPrefix = "SERVER_" + to_string(nodeId) + ".";

		Server server = _serverDefault;
		server.type = Base::SERVER;
		server.nodeId = nodeId;

		server.parseFrom(_conf, keyPrefix);

		_serverMap[nodeId] = server;
	}
}

// throw exception on fail
void ssConfig::parseClientMap(
	map<int, Client>& _clientMap,
	const string& _conf, const vector<int>& _clientList,
	const Client& _clientDefault)
{
	for (int nodeId : _clientList)
	{
		const string keyPrefix = "CLIENT_" + to_string(nodeId) + ".";
	
		Client client = _clientDefault;
		client.type = Base::CLIENT;
		client.nodeId = nodeId;
	
		client.parseFrom(_conf, keyPrefix);
	
		_clientMap[nodeId] = client;
	}
}

bool ssConfig::parseCnfFile()
{
	try
	{
		ssConfig::parseVector(this->serverList, this->configFileName, "MAIN.SERVER_LIST");
		ssConfig::parseVector(this->clientList, this->configFileName, "MAIN.CLIENT_LIST");
		serverDefault.parseFrom(this->configFileName, "SERVER_DEFAULT.");
		clientDefault.parseFrom(this->configFileName, "CLIENT_DEFAULT.");
		ssConfig::parseServerMap(this->serverMap, this->configFileName, this->serverList, this->serverDefault);
		ssConfig::parseClientMap(this->clientMap, this->configFileName, this->clientList, this->clientDefault);

		return true;
	}
	catch (exception& e)
	{
		cerr << "  ERROR: " << e.what() << endl;
		return false;
	}
}

bool ssConfig::parseCmdArg(const int _ac, char* const _av[])
{
	try
	{
		options_description desc("Allowed options");
		desc.add_options()
			("help,h",
				"produce help message")
			("config-file,f",
				value(&(this->configFileName))->default_value("SimpleServer.ini"),
				"{string} config file path")
			("node-id",
				value(&(this->nodeId))->required(),
				"{number} node id");

		positional_options_description positional;
		positional.add("node-id", 1);

		variables_map vm;
		store(command_line_parser(_ac, _av).options(desc).positional(positional).run(), vm);
		notify(vm);

		if (vm.count("help"))
		{
			cout << "Usage: SimpleServer {node-id} [options]" << endl;
			cout << desc;
			return false;
		}

		cerr << "config-file:" << this->configFileName << endl;
		cerr << "node-id:" << this->nodeId << endl;

		return true;
	}
	catch (exception& e)
	{
		cerr << "  ERROR: " << e.what() << endl;
		return false;
	}
}



bool ssConfig::init(const int _ac, char* const _av[])
{
	if (!ssConfig::parseCmdArg(_ac, _av))
		return false;

	if (!ssConfig::parseCnfFile())
		return false;

	if ((this->serverMap.end() == this->serverMap.find(this->nodeId)) &&
		(this->clientMap.end() == this->clientMap.find(this->nodeId)))
	{
		cerr << "  ERROR: cannot match node-id[" << this->nodeId << "] from config file" << endl;
		return false;
	}

	return true;
}

const ssConfig::Base& ssConfig::getConf() const
{
	return (this->serverMap.end() != this->serverMap.find(this->nodeId)) ?
		this->serverMap.at(this->nodeId):
		this->clientMap.at(this->nodeId);
}
