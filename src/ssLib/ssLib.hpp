#pragma once



typedef boost::asio::const_buffers_1		BAConstBuffer;
typedef boost::asio::mutable_buffers_1		BAMutableBuffer;
typedef boost::asio::io_service				BAIoService;
typedef boost::asio::ip::tcp				BATcp;
typedef boost::asio::ip::tcp::acceptor		BAAcceptor;
typedef boost::asio::ip::tcp::endpoint		BAEndpoint;
typedef boost::asio::ip::tcp::socket		BASocket;
typedef boost::system::error_code			BErrorCode;



#include <ssLib/ssINonCopyable.hpp>
#include <ssLib/ssCBuffer.hpp>
#include <ssLib/ssCSession.hpp>
#include <ssLib/ssCAcceptor.hpp>
#include <ssLib/ssCService.hpp>
