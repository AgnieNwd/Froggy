//
// Created by dy on 19/02/2020.
//

#ifndef FROGGER_IOBSERVER_HH
#define FROGGER_IOBSERVER_HH

class IObservable;
class IObserver {
public:
    virtual ~IObserver() {};
    virtual void Notify(IObservable*) = 0;
};


#endif //FROGGER_IOBSERVER_HH
