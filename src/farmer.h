#ifndef _Farmer_H_
#define _Farmer_H_

#include "atomic.h"
#include "VTime.h"
#include "real.h"
#include "tuple_value.h"


#define FARMER_NAME "Farmer"


class Farmer : public Atomic {
  public:
    
    Farmer(const string &name = FARMER_NAME );
    virtual string className() const {  return FARMER_NAME ;}
  
  protected:
    Model &initFunction();
    Model &internalFunction( const InternalMessage & );
    Model &externalFunction( const ExternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    
    Port &r_usd;
    Port &r_amb;
    Port &cost;
    Port &wgc;
    Port &neighbour;
    
    const Port &u_amb;
    const Port &u_usd;
    const Port &field;
    const Port &satisfaction;



    Real s_usd;
    Real s_amb;
    Tuple<Real> field_saved = {33,33,33};
    Tuple<Real> field_neighbour;
    Tuple<Real> past_r_usd;
    Tuple<Real> past_r_amb;
    Tuple<Real> past_cost;
    Real wgc_status;

    bool first_run = true;
    
    bool received [5]= {false, false, false, false, false};
};

#endif