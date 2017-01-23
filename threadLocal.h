// Anjali Verma
// October 5, 2016 : 8 AM

/*
 * threadLocal.h
 *  Start with this and add what is necessary
 */

#ifndef THREADLOCAL_H_
#define THREADLOCAL_H_

#include <iostream>
#include <mutex>
#include <thread>
#include <pthread.h>
#include <map>
#include <algorithm>
using namespace std;

namespace cop5618
{
    template <typename T>
    class threadLocal
    {
    public:
        threadLocal()
        {
            threadID = (long)pthread_self();
        }
        ~threadLocal(){};

        //disable copy, assign, move, and move assign constructors
        threadLocal(const threadLocal&)=delete;
        threadLocal& operator=(const threadLocal&)=delete;
        threadLocal(threadLocal&&)=delete;
        threadLocal& operator=(const threadLocal&&)=delete;

        /**
        * Returns the current thread's value.
        * If no value has been previously set by this
        * thread, an out_of_range exception is thrown.
        */
        const T& get() const
        {
            std::lock_guard<std::mutex> guard(threadLock);
            if (threadLocal::IDValueMap.find(threadID) == threadLocal::IDValueMap.end())
                throw std::runtime_error("Out of Range");
            else return threadLocal::IDValueMap.find(threadID) -> second;
        }

        /**
        * Sets the value of the threadLocal for the current thread
        * to val.
        */

        void set(T val)
        {
            std::lock_guard<std::mutex> guard(threadLock);
            threadLocal::IDValueMap[threadID] = val;
        }

        /**
        * Removes the current thread's value for the threadLocal
        */

        void remove()
        {
            std::lock_guard<std::mutex> guard(threadLock);
            if (threadLocal::IDValueMap.find(threadID) == threadLocal::IDValueMap.end())
                throw std::runtime_error("element not found");
            else
                threadLocal::IDValueMap.erase(threadID); // deleting from the map
        }

        /**
        * Friend function.  Useful for debugging only
        */

        template <typename U>
        friend std::ostream& operator<< (std::ostream& os, const threadLocal<U>& obj)
        {
            std::lock_guard<std::mutex> guard(obj.threadLock);
            for (auto i = obj.IDValueMap.begin(); i != obj.IDValueMap.end(); ++i)
            {
                os << i -> first << " - " << i -> second;
            }
            return os;
        }

    private:
        mutable mutex threadLock;
        typedef map<long,T> MapDef;
        MapDef IDValueMap;
        long threadID;


    };
} /* namespace cop5618 */

#endif /* THREADLOCAL_H_ */
