#include <stdafx.hpp>
#include <ssImpl/ssConfig.hpp>



using namespace std;
using namespace boost::program_options;

///////////////////////////////////////////////////////////////////////////////
// Base
const char* const ssConfig::Base::TypeStr[] = {"INVALID", "SERVER", "CLIENT"};

ssConfig::Base::Type ssConfig::Base::fromString(const string& _str) noexcept
{
	for (int i = 0; MAX >= i; ++i)
	{
		if (0 == _str.compare(TypeStr[i]))
			return static_cast<Type>(i);
	}

	return INVALID;
}

void ssConfig::Base::parseFrom(const string& _conf, const string& _keyPrefix) noexcept(false)
{
	string strValue;
	options_description desc;
	variables_map vm;
	desc.add_options()
		((_keyPrefix + "TYPE").c_str(), value(&strValue)->required(), "");
	store(parse_config_file<char>(_conf.c_str(), desc, true), vm);
	notify(vm);

	type = Base::fromString(strValue);
}



#define OPTION_ENTRY(k, v) ((_keyPrefix + k).c_str(), value(&(v)), "")
///////////////////////////////////////////////////////////////////////////////
// Server
void ssConfig::Server::parseFrom(const string& _conf, const string& _keyPrefix) noexcept(false)
{
	Base::parseFrom(_conf, _keyPrefix);

	options_description desc;
	variables_map vm;
	desc.add_options()
		OPTION_ENTRY("POOL_SIZE",		poolSize)
		OPTION_ENTRY("BACKLOG_MAX_SIZE",backlogMaxSize)
		OPTION_ENTRY("SERVER_IP",		serverIp)
		OPTION_ENTRY("SERVER_PORT",		serverPort);
	store(parse_config_file<char>(_conf.c_str(), desc, true), vm);
	notify(vm);
}



///////////////////////////////////////////////////////////////////////////////
// Client
void ssConfig::Client::parseFrom(const string& _conf, const string& _keyPrefix) noexcept(false)
{
	Server::parseFrom(_conf, _keyPrefix);

	options_description desc;
	variables_map vm;
	desc.add_options()
		OPTION_ENTRY("LOCAL_IP",		localIp)
		OPTION_ENTRY("LOCAL_PORT_BEGIN",localPortBegin)
		OPTION_ENTRY("LOCAL_PORT_END",	localPortEnd);
	store(parse_config_file<char>(_conf.c_str(), desc, true), vm);
	notify(vm);
}
#undef OPTION_ENTRY



///////////////////////////////////////////////////////////////////////////////
// ssConfig
bool ssConfig::parseCmdArg(const int _ac, char* const _av[]) noexcept
{
	options_description desc("Allowed options");
	auto printUsage = [&desc]()
	{
		cout << "Usage: SimpleServer {node-id} [options]" << endl;
		cout << desc;
	};

	try
	{
		desc.add_options()
			("help,h",
				"produce help message")
			("config-file,f",
				value(&m_configFileName)->default_value("SimpleServer.ini"),
				"{string} config file path")
			("node-id",
				value(&m_nodeId)->required(),
				"{number} node id");

		positional_options_description positional;
		positional.add("node-id", 1);

		variables_map vm;
		store(command_line_parser(_ac, _av).options(desc).positional(positional).run(), vm);

		if (vm.count("help"))
		{
			printUsage();
			return false;

		}

		notify(vm);
		cerr << "config-file:" << m_configFileName << endl;
		cerr << "node-id:" << m_nodeId << endl;
		return true;
	}
	catch (exception& e)
	{
		printUsage();
		cerr << endl << endl << "[ERROR]: " << e.what() << endl;
		return false;
	}
}

void ssConfig::parseNodeList() noexcept(false) // throw parse exception
{
	string strValue;
	options_description desc;
	variables_map vm;
	desc.add_options()
		("NODE.LIST", value(&strValue), "");
	store(parse_config_file<char>(m_configFileName.c_str(), desc, true), vm);
	notify(vm);

	istringstream is(strValue);
	m_nodeList.assign(
		istream_iterator<int>(is),
		istream_iterator<int>());
}

void ssConfig::parseNodeMap() noexcept(false) // throw parse exception
{
	for (const int nodeId : m_nodeList)
	{
		const string keyPrefix = "NODE." + to_string(nodeId) + ".";
		Base base;
		base.parseFrom(m_configFileName, keyPrefix);

		switch (base.type)
		{
		default:
		case Base::INVALID:
			assert(false); break;

		case Base::SERVER:
			{
				Server* pServer = new Server(m_defaultServer);
				pServer->nodeId = nodeId;
				pServer->parseFrom(m_configFileName, keyPrefix);
				m_nodeMap[nodeId] = pServer;
				break;
			}

		case Base::CLIENT:
			{
				Client* pClient = new Client(m_defaultClient);
				pClient->nodeId = nodeId;
				pClient->parseFrom(m_configFileName, keyPrefix);
				m_nodeMap[nodeId] = pClient;
				break;
			}
		}
	}
}

bool ssConfig::parseCnfFile() noexcept
{
	try
	{
		m_defaultServer.parseFrom(m_configFileName, "DEFAULT_SERVER.");
		m_defaultClient.parseFrom(m_configFileName, "DEFAULT_CLIENT.");
		ssConfig::parseNodeList();
		ssConfig::parseNodeMap();

		return true;
	}
	catch (exception& e)
	{
		cerr << "[ERROR]: " << e.what() << endl;
		return false;
	}
}



bool ssConfig::init(const int _ac, char* const _av[]) noexcept
{
	if (!ssConfig::parseCmdArg(_ac, _av))
		return false;

	if (!ssConfig::parseCnfFile())
		return false;

	// node id가 잘못된 경우
	if (m_nodeMap.end() == m_nodeMap.find(m_nodeId))
	{
		cerr << "[ERROR]: " << "unknown node-id" << endl;
		return false;
	}

	return true;
}

const ssConfig::Base& ssConfig::getConf() const noexcept
{
	return *(m_nodeMap.at(m_nodeId));
}
