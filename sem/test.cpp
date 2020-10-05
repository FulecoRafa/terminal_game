#include <iostream>
#include <thread>
#include <chrono>
// #include <mutex>
#include "fulecoSimpleSemaphore.h"

std::chrono::seconds times[3] = {std::chrono::seconds(3), std::chrono::seconds(2), std::chrono::seconds(2)};

void print_after_time(std::chrono::seconds time, int thread_num){
	fulss::wait("thread_count");
	std::cout<<thread_num+1<<" started\n";
	std::this_thread::sleep_for(time);
	// mtx.lock();
	fulss::lock("stdout_lock");
	std::cout<<thread_num+1<<" finished\n";
	// mtx.unlock();
	fulss::unlock("stdout_lock");
  
	fulss::uncommit("thread_count");

	return;
}

int main(void){
	int n_threads = 3;
	int thread_limit = 2;
	fulss::create_mutex("stdout_lock");
	fulss::create_semaphore("thread_count", thread_limit);
	std::thread threads[3];
	// std::mutex mtx;
	for(int i = 0 ; i < n_threads ; i++){
		threads[i] = std::thread(print_after_time, times[i%3], i);
	}
	for(int i = 0 ; i < 3 ; i++){
		threads[i].join();
	}

	std::cout<< "Main thread finshed\n";

	return 0;
}