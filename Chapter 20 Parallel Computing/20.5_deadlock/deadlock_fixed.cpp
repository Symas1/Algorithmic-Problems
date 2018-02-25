// deadlock fixed
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
using namespace std;

class Account {
public:
	Account(int balance) :account_id_{ ++id_ }, balance_{ balance } {}
	friend bool transfer(Account& from, Account& to, unsigned amount) {
		cout << from.account_id_ << " transfers " << amount << "$ to " << to.account_id_ << endl;

		recursive_mutex& lock1 = from.account_id_ < to.account_id_ ? from.recursive_mx_ : to.recursive_mx_;
		recursive_mutex& lock2 = from.account_id_ < to.account_id_ ? to.recursive_mx_ : from.recursive_mx_;
		lock_guard<recursive_mutex>from_lock{lock1};
		{
			cout << from.account_id_ << " locked hist first mutex and is going to lock mutex " << to.account_id_ << endl;
			this_thread::sleep_for(chrono::milliseconds{ 500 });
			lock_guard<recursive_mutex>to_lock{ lock2 };
			cout << "Transfering money" << endl;
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
	thread first{ transfer,ref(a),ref(b),100 };
	this_thread::sleep_for(chrono::milliseconds{ 50 });
	thread second{ transfer,ref(b),ref(a),100 };
	first.join();
	second.join();

	first = thread{ transfer,ref(a),ref(a),100 };
	first.join();
	system("pause");
}