// implement caching for a multithreaded dictionary
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;

class Server_request {
public:
	Server_request(const string& request) :request_{ request } {}
	const string& get_server_request() {
		return request_;
	}
private:
	string request_;
};

class Server_response {
public:
	Server_response() = default;
	Server_response(const string& request, const vector<string>&strings) :request_{ request }, strings_{ strings } {}
	const string& get_request() {
		return request_;
	}
	const vector<string>& get_strings() {
		return strings_;
	}
private:
	string request_;
	vector<string>strings_;
};

vector<string> closest_words(const string& word) {
	this_thread::sleep_for(chrono::milliseconds{ 200 });
	return{ "result" };
}

class Spell_check_service {
public:
	static void service(Server_request& req, Server_response& res) {
		string request = req.get_server_request();
		vector<string>result;
		bool found = false;
		{
			lock_guard<mutex>lock{ mx_ };
			if (last_response_.get_request() == request) {
				found = true;
				result = last_response_.get_strings();
			}
		}
		if (!found) {
			Server_response new_response{ request,closest_words(request) };
			lock_guard<mutex>lock{ mx_ };
			last_response_ = move(new_response);
			result = last_response_.get_strings();
		}
		res = { request,result };
	}
private:
	static Server_response last_response_;
	static mutex mx_;
};
Server_response Spell_check_service::last_response_;
mutex Spell_check_service::mx_;

void func(const string& data) {
	auto start_time = chrono::system_clock::now();
	Server_request req{ data };
	Server_response resp{};
	Spell_check_service::service(req, resp);
	chrono::duration<float> passed_time = chrono::system_clock::now() - start_time;
	cout << resp.get_request() << resp.get_strings().front() <<" "<<passed_time.count() <<endl;
}

//void main() {
//	int threads = 10;
//	thread{ func, "0_" }.detach();
//	this_thread::sleep_for(chrono::milliseconds{ 250 });
//	for (int i = 1; i < threads; ++i) {
//		thread{ func,to_string(i) + "_" }.detach();
//		thread{ func,to_string(i - 1) + "_" }.detach();
//		this_thread::sleep_for(chrono::milliseconds{ 500 });
//	}
//	system("pause");
//}
