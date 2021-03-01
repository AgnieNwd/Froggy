//
// Created by dy on 19/02/2020.
//

#ifndef FROGGER_IOBSERVABLE_HH
#define FROGGER_IOBSERVABLE_HH

#include "IObserver.hh"
#include <list>

class IObservable {
protected:
    std::list<IObserver*> _listObserver;

public:
    virtual ~IObservable() {};
    virtual void AddObserver(IObserver*) = 0;
    virtual void RemoveObserver(IObserver*) = 0;
};


#endif //FROGGER_IOBSERVABLE_HH
