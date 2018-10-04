#ifndef _Field_H_
#define _Field_H_

#include "atomic.h"
#include "VTime.h"
#include "real.h"
#include "tuple_value.h"


#define FIELD_NAME "Field"


class Field : public Atomic {
  public:
    
    Field(const string &name = FIELD_NAME );
    virtual string className() const {  return FIELD_NAME ;}
  
  protected:
    Model &initFunction();
    Model &internalFunction( const InternalMessage & );
    Model &externalFunction( const ExternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    Tuple<Real> content;
    Port &seed;
    const Port &reaped;
      // [(!) declare common variables]
    // Lifetime programmed since the last state transition to the next planned internal transition.
    VTime sigma;

    // Time elapsed since the last state transition until now
    VTime elapsed;

    // Time remaining to complete the last programmed Lifetime
    VTime timeLeft;  
};

#endif
