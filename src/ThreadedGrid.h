#ifndef _THREADED_GRID_H_
#define _THREADED_GRID_H_
#include "NumberGrid.h"
#include <vector>
#include <mutex>
#include <thread>

class ThreadedGrid: public NumberGrid {
public:
    ThreadedGrid();
    ThreadedGrid(const int& height, const int& width);
    virtual ~ThreadedGrid();
    virtual void calculateAllNumbers();
    virtual void worker();

protected:
    std::vector<int> mTasks;
    std::mutex mLock;
};

#endif /* _THREADED_GRID_H_ */