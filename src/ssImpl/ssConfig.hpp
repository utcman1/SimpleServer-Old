class ssConfig
{
public:
	typedef boost::property_tree::ptree bpTree;



	///////////////////////////////////////////////////////////////////////////
	// Base
	struct Base
	{
		enum Type
		{
			SERVER,
			CLIENT
		};

		Type		type;
		int			id;

	private:
		friend ssConfig;
		static std::string toString(const Type& _type);
		std::string toString() const;
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
		std::string	serverIp		= "0.0.0.0";
		uint16_t	serverPort		= 10000;

	private:
		friend ssConfig;
		void readFrom(const bpTree& _pTree, const std::string& _pathPrefix);
	};



	///////////////////////////////////////////////////////////////////////////
	// Client
	struct Client
		: public Server
	{
		// Connector
		// 여러개의 ip가 있는 서버에서 테스트 client를 돌리는 경우에만 의미가 있음.
		std::string	localIp			= "0.0.0.0";
		uint16_t	localPortBegin	= 0;
		uint16_t	localPortEnd	= 0;

	private:
		friend ssConfig;
		void readFrom(const bpTree& _pTree, const std::string& _pathPrefix);
	};



	///////////////////////////////////////////////////////////////////////////
	// ssConfig
	std::vector<int> serverList;
	std::vector<int> clientList;
	Server serverDefault;
	Client clientDefault;
	std::unordered_map<int, Server> serverMap;
	std::unordered_map<int, Client> clientMap;



private:
	static void readVector(
		std::vector<int>& _outVec,
		const bpTree& _pTree, const std::string& _path);

	static void readServerMap(
		std::unordered_map<int, Server>& _serverMap,
		const std::vector<int> _serverList, const Server& _serverDefault,
		const bpTree& _pTree);

	static void readClientMap(
		std::unordered_map<int, Client>& _clientMap,
		const std::vector<int> _clientList, const Client& _clientDefault,
		const bpTree& _pTree);

	void readFrom(const bpTree& _pTree);



public:
	bool init(const std::string& _configFileName);
};
