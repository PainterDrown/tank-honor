#ifndef BASE
#define BASE

#include "Attackable.hpp"

#include <string>
using namespace std;

class Base: public Attackable {
public:
    static Base* create(const bool isR);
    
    void initAttributes();
    
    void playDestroyAnimation();
protected:
    bool isR;
};

#endif
