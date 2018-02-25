// deadlock is real
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
using namespace std;

class Account {
public:
	Account(int balance) :account_id_{ ++id_ }, balance_{ balance } {}
	friend bool transfer(Account& from, Account& to,unsigned amount) {
		 //thread 1 (5 transfers to 6)
		 //thread 2 (6 transfers to 5)
		 //in thread #1 5 locks and sheduler switches to #2
		 //in thread #2 6 locks here too
		cout << from.account_id_ << " transfers " << amount<<"$ to" << to.account_id_ << endl;
		lock_guard<recursive_mutex>from_lock{ from.recursive_mx_ }; 
		{
			cout << from.account_id_ << " locked hist first mutex and is going to lock mutex " <<to.account_id_<<endl;
			this_thread::sleep_for(chrono::milliseconds{ 500 }); // for deadlock imitation
			 //neither of #1 or #2 can pass as both mutexes are locked
			lock_guard<recursive_mutex>to_lock{ to.recursive_mx_ };
			cout << "We will never see this message" << endl;
			if (amount > from.balance_) {
				return false;
			}
			from.balance_ -= amount;
			to.balance_ += amount;
			return true;
		}
	}
private:
	recursive_mutex recursive_mx_;
	static unsigned id_;
	unsigned account_id_;
	int balance_;
};
unsigned Account::id_ = 0;

void main() {
	Account a{ 5000 };
	Account b{ 3000 };
	thread first{	transfer,ref(a),ref(b),100 };
	this_thread::sleep_for(chrono::milliseconds{ 50 });
	thread second{ transfer,ref(b),ref(a),100 };
	first.join();
	second.join();
	system("pause");
}