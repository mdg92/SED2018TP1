#ifndef _Neighbour_H_
#define _Neighbour_H_

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "Neighbour"


class Neighbour : public Atomic {
  public:
    
    Neighbour(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}
  
  protected:
    Model &initFunction();
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    /*Port &corn;
    Port &soy;
    Port &wheat;
    */
    Port &out;
    VTime frequency_time;
};

#endif
