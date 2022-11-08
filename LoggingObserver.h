#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

//Super class, all loggable object that inherit ILoggable class must implement stringToLog method
class ILoggable{
    public:
    ILoggable();
    //pure virtual method stringToLog() that write updated state to output file
    virtual string stringToLog() = 0;
    ~ILoggable();
};

class Observer{
    public:
    ~Observer();
    //update() method that will call string to lod to update new states into logfile
    //Be define by subclass LogObserver
    virtual void Update(ILoggable* log) = 0;
    protected:
    Observer();  
};

class Subject{
    public:
    //attach this class to observer object (add o to mumber of Subject class: list of observers)
    virtual void Attach(Obcerver* o);
    //detach this class to observer object 
    virtual void Detach(Obcerver* o);
    //once the notify is called on a loggable object, the update method will be called on every
    //observer objects in observer class, and then invoke stringToLod to write update state into files
    virtual void Notify(ILoggable* log);
    Subject();
    ~Subject();
    private:
    list<Observer*> *observers;
};

class LogObserver: public Observer{
    public:
    LogObserver();
    //will call stringToLog to output the implementation state code into output file
    void Update(ILoggable* log);
    ~LogObserver();
    
    private:
    


};