// Anjali Verma
// October 6, 2016 : 2:13 AM

#include "threadLocal.h"
#include <iostream>
#include <string>

using namespace cop5618;
using namespace std;

threadLocal<int> value;     //Local variable for each thread, EACH THREAD GETS IT'S OWN COPY OF THIS VARIABLE
int err_count=0;


void get_withoutSet(const string& thread_name, int no)
{
try
{
    value.get();
}
    catch(exception& e)
    {
        cout<<"Failed to fetch a value because one doesn't exist"<<endl;
            err_count=err_count+1;
    }
}
void remove_withoutSet(const string& thread_name, int no)
{
    try
    {
        value.remove();
    }
    catch(exception& e)
    {
        cout<<"Failed to remove a value because one doesn't exist"<<endl;
        err_count=err_count+1;
    }
}
void set_remove_remove(const string& thread_name, int no)
{
    try
    {
        value.set(no);
    }
    catch(exception& e)
    {
        cout<<"Failed to set the value"<<endl;
        err_count=err_count+1;
    }

    try
    {
        value.remove();
    }
    catch(exception& f)
    {
        cout<<"Failed to remove the value because one doesn't exist"<<endl;
        err_count=err_count+1;
    }

    try
    {
        value.remove();
    }
    catch(exception& f)
    {
        cout<<"Failed to remove the value because one doesn't exist"<<endl;
        err_count=err_count+1;
    }
}
void *check(void *ID)
{
    cout<<"   From thread   "<<(*(int *)ID)<<std::endl;
    }
void test_concurrent()
{
    try
    {
pthread_t threads[10];
    int id[10];
    int rc,t;
    for(t=1;t<=10;t++)
    {
       cout<<"Created Thread   "<< t <<std::endl;
        id[t]=t;
        rc=pthread_create(&threads[t],NULL,check, &id[t]);
    }
    pthread_exit(NULL);


    }
    catch(exception& e)
    {
     cout<<"Failed to achieve concurrency"<<endl;
        err_count=err_count+1;
    }}


void test_set_get(const string& thread_name, int no)
{
    try
    {
        value.set(no);
    }
    catch(exception& f)
    {
        cout<<"Failed to set the value"<<endl;
        err_count=err_count+1;
    }

    try
    {
        value.get();
    }
    catch(exception& f)
    {
        cout<<"Failed to get the value"<<endl;
        err_count=err_count+1;
    }
}

int test_threadLocal()
{
    // Test Case 1: Trying to get a value when no value exists.
   thread tc1(get_withoutSet,"TestingGetWithoutSet", 257);


    // Test Case 2: Removing a value when there is no value
    thread tc2(remove_withoutSet,"RemoveWithoutSet", 174);


    // Test Case 3: Setting a value and then trying to remove it more than once
    thread tc3(set_remove_remove,"SettingThenRemovingTwice", 107);


    // Test Case 4: Concurrency Test to ensure they are not running concurrently
    thread tc4(test_concurrent);


    // Test Case 5: Setting and reading a value
    thread tc5(remove_withoutSet,"SettingAndReadingAValue", 144);

    tc1.join();
    tc2.join();
    tc3.join();
    tc4.join();
    tc5.join();

    return err_count;
}

int main()
{
int a=test_threadLocal();
    std::cout<<a<<"   ERRORS   "<<"IN 5 TEST CASES"<<endl;
        return a;
}
