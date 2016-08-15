﻿#pragma once



typedef boost::asio::const_buffers_1		baConstBuffer;
typedef boost::asio::mutable_buffers_1		baMutableBuffer;
typedef boost::asio::io_service				baIoService;
typedef boost::asio::ip::address			baAddr;
typedef boost::asio::ip::tcp				baTcp;
typedef boost::asio::ip::tcp::acceptor		baAcceptor;
typedef boost::asio::ip::tcp::endpoint		baEndpoint;
typedef boost::asio::ip::tcp::socket		baSocket;
typedef boost::system::error_code			bsErrorCode;



#include <ssLib/ssINonCopyable.hpp>
#include <ssLib/ssBuffer.hpp>
#include <ssLib/ssSession.hpp>
#include <ssLib/ssAcceptor.hpp>
#include <ssLib/ssService.hpp>