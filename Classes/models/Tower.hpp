#ifndef TOWER
#define TOWER

#include "Attackable.hpp"

#include <string>
using namespace std;

class Tower: public Attackable {
public:
    static Tower* create(const bool isR);
    
    void initAttributes();
    
    void playDestroyAnimation();
    
protected:
    
    bool isR;
};

#endif
