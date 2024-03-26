#include "ThreadedGrid.h"
#include <thread>
#include <vector>
#include <mutex>

ThreadedGrid::ThreadedGrid()
    : NumberGrid(), mTasks() {}
ThreadedGrid::ThreadedGrid(const int& height, const int& width)
    : NumberGrid(height, width), mTasks() {}
ThreadedGrid::~ThreadedGrid() {}
void ThreadedGrid::calculateAllNumbers() {
    //make tasks
    for(int row=0; row < mHeight; row++) {
		mTasks.push_back(row);
    }
    //get thread_count
    unsigned int thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    unsigned int i;
    for(i = 0; i < thread_count; i++) {
        threads.push_back(std::thread(&ThreadedGrid::worker, this));
        // this->worker()
    }
    for(i = 0; i < thread_count; i++) {
        threads[i].join();
    }
}
void ThreadedGrid::worker() {
    while(true) {
        mLock.lock();
        if(mTasks.size() == 0) {
            mLock.unlock();
            break;
        }
        int row = mTasks.back();
        mTasks.pop_back();
        mLock.unlock();
		for(int column = 0; column < mWidth; column++) {
			int number = calculateNumber(row, column);
			setNumber(row, column, number);
		}
    }
}
