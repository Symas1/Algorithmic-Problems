// web server with thread pool
#include <boost\asio.hpp>
#include <boost\thread\sync_bounded_queue.hpp>
#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <atomic>
namespace asio = boost::asio;
using asio::ip::tcp;
using  queue_type = boost::sync_bounded_queue<std::unique_ptr<tcp::socket>>;

class Server {
public:
	Server() :work_{ true },queue_(max_threads_),
		acceptor_{ io_service_,tcp::endpoint{ tcp::v4(),8080 } } {
		try {
			for (int i = 0; i < max_threads_; ++i) {
				threads_.emplace_back(std::thread{ &Server::pool,this });
			}
		}
		catch (...) {
			work_ = false;
			throw;
		}
		accept_sockets();
	}
	~Server() {
		work_ = false;
		for (auto& t : threads_) {
			if (t.joinable()) {
				t.join();
			}
		}
	}

private:
	void accept_sockets() {
		while (work_) {
			std::unique_ptr<tcp::socket>sock = std::make_unique<tcp::socket>(io_service_);
			acceptor_.accept(*sock);
			queue_ << std::move(sock);
		}
	}
	void process_request(const std::unique_ptr<tcp::socket>&socket) {
		asio::streambuf sb;
		while (true) {
			boost::system::error_code e;
			size_t n = asio::read_until(*socket, sb, '\n', e);
			if (e == asio::error::eof) {
				break;
			}
		}
		asio::write(*socket, sb.data());
	}

	void pool() {
		while (work_) {
			std::unique_ptr<tcp::socket>socket;
			if (queue_.try_pull(socket)) {
				process_request(socket);
			}
			else {
				std::this_thread::yield;
			}
		}
	}
	tcp::acceptor acceptor_;
	asio::io_service io_service_;
	const int max_threads_ = 2;
	std::atomic_bool work_;
	queue_type queue_;
	std::vector<std::thread>threads_;

};


void main() {
	Server{};
}