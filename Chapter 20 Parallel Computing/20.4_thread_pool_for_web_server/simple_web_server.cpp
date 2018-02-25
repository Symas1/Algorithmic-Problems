// simple web server
#include <boost\asio.hpp>
#include <iostream>
namespace asio = boost::asio;
using asio::ip::tcp;

const unsigned short port = 8080;

void process_request(tcp::socket& sock) {
	asio::streambuf sb;
	while (true) {
		boost::system::error_code e;
		size_t n = asio::read_until(sock, sb, '\n', e);
		if (e == asio::error::eof) {
			std::cout << "connection closed\n";
			break;
		}
	}
	asio::write(sock, sb.data());
}

void main() {
	asio::io_service io_service;
	tcp::acceptor acceptor{ io_service,tcp::endpoint{tcp::v4(),port} };
	while (true) {
		tcp::socket socket{ io_service };
		acceptor.accept(socket);
		process_request(socket);
	}
}