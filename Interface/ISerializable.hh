//
// Created by dy on 19/02/2020.
//

#ifndef FROGGER_ISERIALIZABLE_HH
#define FROGGER_ISERIALIZABLE_HH

class ISerializable {
public:
    virtual ~ISerializable() {};
    virtual std::string Serialize() = 0;

};

#endif //FROGGER_ISERIALIZABLE_HH
