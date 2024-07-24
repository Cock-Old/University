#include <array>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <iomanip>
#include <string_view>

using namespace std;

const int no_of_philosophers = 5;
const int set_dinner_time = 3;
const int eat_koeff = 1;
const int eat_range[2] = { {1}, {100} };
const int think_koeff = 1;
const int think_range[2] = { {1}, {20} };

struct fork
{
	mutex mutex;
	int number;
};

struct table
{
	atomic<bool> ready = false;
	array<fork, no_of_philosophers> forks;
};

mutex lockprint;

class philosopher
{
private:
	string const name;
	table const& dinnertable;
	fork& left_fork;
	fork& right_fork;
	thread lifethread;
	mt19937 rng{ random_device{}() };
	void eat();
	void print(string_view text);
	void print(int value, string_view text1, string_view text2);
	void dinner();
	void hunger();
	void think();
public:
	philosopher(string_view n, table const& t, fork& l, fork& r) : name(n), dinnertable(t), left_fork(l), right_fork(r), lifethread(&philosopher::dinner, this) {}
	~philosopher();
};

void philosopher::eat() {
	static thread_local uniform_int_distribution<> dist(eat_range[0], eat_range[1]);
	this_thread::sleep_for(chrono::milliseconds(dist(rng) * eat_koeff));
	print(18, " started eating ", "with forks: ");
	this_thread::sleep_for(chrono::milliseconds(dist(rng) * eat_koeff));
	left_fork.mutex.unlock();
	right_fork.mutex.unlock();
	print(18, " finishes eating ", "and returns forks: ");
}

void philosopher::print(string_view text)
{
	lock_guard<mutex> cout_lock(lockprint);
	cout << left << setw(10) << setfill(' ') << name << text << endl;
}

void philosopher::print(int value, string_view text1, string_view text2)
{
	lock_guard<mutex> cout_lock(lockprint);
	cout << left << setw(10) << setfill(' ') << name << left << setw(value) << setfill(' ') << text1 << text2 << left_fork.number << ", " << right_fork.number << endl;
}

void philosopher::dinner()
{
	do
	{
		hunger();
		think();
	} while (dinnertable.ready);
}

void philosopher::hunger()
{
	if (try_lock(left_fork.mutex, right_fork.mutex) == -1) {
		print(18, " ", "takes the forkes: ");
		eat();
	}
	else {
		print(18, " is starving ", "and waiting for forks: ");
		lock(left_fork.mutex, right_fork.mutex);
		print(18, " ", "takes the forkes: ");
		eat();
	}
}

void philosopher::think()
	{
	static thread_local uniform_int_distribution<> wait(think_range[0], think_range[1]);
	print(" is thinking ");
	this_thread::sleep_for(chrono::milliseconds(wait(rng) * think_koeff));
}

philosopher::~philosopher()
{
	lifethread.join();
}

int main()
{
	cout << "Dinner started!" << endl;
	{
		table table;
		for (int i = 0; i < no_of_philosophers; i++) { table.forks[i].number = i + 1; }
		array<philosopher, no_of_philosophers> philosophers
		{ { { "Aristotle", table, table.forks[0], table.forks[1] },
			{ "Platon", table, table.forks[1], table.forks[2] },
			{ "Descartes", table, table.forks[2], table.forks[3] },
			{ "Kant", table, table.forks[3], table.forks[4] },
			{ "Nietzsche", table, table.forks[4], table.forks[0] }, } };
		table.ready = true;
		this_thread::sleep_for(chrono::seconds(set_dinner_time));
		table.ready = false;
	}
	cout << "Dinner done!" << endl;
	return 0;
}