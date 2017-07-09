#ifndef DRAGON
#define DRAGON

#include "Attackable.hpp"

#include <string>
using namespace std;

class Dragon: public Attackable {
public:
    static Dragon* create(const bool isBig);
    
    void initAttributes();
    
    void playDestroyAnimation();
    
protected:
    bool isBig;
};

#endif /* Dragon_hpp */
