#include "LoggingObserver.h"
using namespace std;
//------------------------------------------------
//Class ILoggable (Abstract superclass)
ILoggable :: ILoggable(){

} 
ILoggable :: ~ILoggable(){

} 
//------------------------------------------------
//Class Observer
Observer :: Observer(){
}

Observer :: ~Observer(){
}
//------------------------------------------------
//Class Subject (Superclass)
Subject :: Subject(){
    observers = new list<Observer*>;
}

Subject :: ~Subject(){
    delete observers;
}

void Subject :: Attach(Obcerver* o){
    observers -> push_back(o);
}

void Subject :: Detach(Obcerver* o){
    for (int i = 0; i < observers->size(); i++)
	{
		if (o == observers->at(i)) //They point to the same thing
			observers->erase(observers->begin() + i); //Remove the Observer from the list
	}
}

void Subject :: Notify(ILoggable* log){
    list < Observer* > :: iterator i = observers -> begin();
    for(; i!=observers -> end(); ++i ){
        (*i) -> Update(log);
    }
}
//------------------------------------------------
//Class LogObserver
LogObserver :: LogObserver(){
}

void LogObserver:: Update(ILoggable* log){
    //declare an output stream 
    fstream filestream;
    //if the file does not exit, it will create a new file. Otherwise, append content to the file
    filestream.open("gamelog.txt", ofstream::app);
    //output the the string returned from stringToLog method to the file
    filestream <<log->stringToLog() <<endl;
    //close the file
    outputfilestream.close();
}


