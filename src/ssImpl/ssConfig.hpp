class ssConfig
{
	typedef std::size_t size_t;
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
			INVALID,
			SERVER,
			CLIENT,
			MAX = CLIENT
		};

		static const char* const TypeStr[];

		int			nodeId			= -1;
		Type		type			= INVALID;

		static string toString(const Type& _type) noexcept { return TypeStr[_type]; }
		static Type fromString(const string& _str) noexcept;
		Base() = default;
		Base(const Base& _default) = default;
		void parseFrom(const string& _conf, const string& _keyPrefix) noexcept(false);
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

		Server() = default;
		Server(const Server& _default) = default;
		void parseFrom(const string& _conf, const string& _keyPrefix) noexcept(false);
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

		Client() = default;
		Client(const Client& _default) = default;
		void parseFrom(const string& _conf, const string& _keyPrefix) noexcept(false);
	};



	///////////////////////////////////////////////////////////////////////////
	// ssConfig
	string m_configFileName;
	int m_nodeId;

	Server m_defaultServer;
	Client m_defaultClient;
	vector<int> m_nodeList;
	map<int, Base*> m_nodeMap;



private:
	bool parseCmdArg(const int _ac, char* const _av[]) noexcept;
	void parseNodeList() noexcept(false);						// throw parse exception
	void parseNodeMap() noexcept(false);						// throw parse exception
	bool parseCnfFile() noexcept;



public:
	bool init(const int _ac, char* const _av[]) noexcept;
	const Base& getConf() const noexcept;
};
