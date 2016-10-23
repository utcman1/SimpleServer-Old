class ssConfig
{
	typedef std::string string;
	template<typename K, typename V> using map = std::unordered_map<K, V>;
	template<typename T> using vector = std::vector<T>;

public:

	///////////////////////////////////////////////////////////////////////////
	// Base
	struct Base
	{
		enum Type
		{
			UNKNOWN,
			SERVER,
			CLIENT
		};

		Type		type;
		int			nodeId;

		static string toString(const Type& _type);
		string toString() const;
	};



	///////////////////////////////////////////////////////////////////////////
	// Server
	struct Server
		: public Base
	{
		// SessionPool
		size_t		poolSize		= 1;
		size_t		backlogMaxSize	= 1;

		// Acceptor
		string		serverIp		= "0.0.0.0";
		uint16_t	serverPort		= 10000;

		void parseFrom(const string& _conf, const string& _keyPrefix);
	};



	///////////////////////////////////////////////////////////////////////////
	// Client
	struct Client
		: public Server
	{
		// Connector
		// 여러개의 ip가 있는 서버에서 테스트 client를 돌리는 경우에만 의미가 있음.
		string		localIp			= "0.0.0.0";
		uint16_t	localPortBegin	= 0;
		uint16_t	localPortEnd	= 0;

		void parseFrom(const string& _conf, const string& _keyPrefix);
	};



	///////////////////////////////////////////////////////////////////////////
	// ssConfig
	string configFileName;
	int nodeId;

	vector<int> serverList;
	vector<int> clientList;
	Server serverDefault;
	Client clientDefault;
	map<int, Server> serverMap;
	map<int, Client> clientMap;



private:
	static void parseVector(
		vector<int>& _outVec,
		const string& _conf, const string& _key);

	static void parseServerMap(
		map<int, Server>& _serverMap,
		const string& _conf, const vector<int>& _serverList,
		const Server& _serverDefault);

	static void parseClientMap(
		map<int, Client>& _clientMap,
		const string& _conf, const vector<int>& _clientList,
		const Client& _clientDefault);

	bool parseCnfFile();
	bool parseCmdArg(const int _ac, char* const _av[]);



public:
	bool init(const int _ac, char* const _av[]);
	const Base& getConf() const;
};
