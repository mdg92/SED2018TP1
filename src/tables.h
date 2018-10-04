#ifndef _TABLE_H_
#define _TABLE_H_

#include "atomic.h"
#include "VTime.h"
#include "real.h"
#include "tuple_value.h"


#define TABLE_NAME "Table"


class Table : public Atomic {
  public:
    
    Table(const string &name = TABLE_NAME );
    virtual string className() const {  return TABLE_NAME ;}
  
  protected:
    Model &initFunction();
    Model &internalFunction( const InternalMessage & );
    Model &externalFunction( const ExternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    
    Port &field;
    Port &best_neighbour;
    Port &wgc;
    Port &external_change;
    
    const Port &r_amb;
    const Port &r_usd;
    const Port &cost;

    const Real emergy [3][5] = {
      {35.551, 38.433,  45.582,  49.711,  51.865},
      {27.380, 29.067,  31.974,  31.507,  34.459},
      {58.337, 50.499, 44.978, 46.401, 45.882}
    };
    const Real price [3] = {141, 277, 153};
    const Real costs [3][5] = {
      {618, 768, 832, 906, 965},
      {329, 374, 401, 435, 460},
      {5618, 656, 675, 690, 738}
    };
    const Real yield [3][5] = {
      {4.877, 7.782, 9.018, 10.450, 11.586},
      {2.130, 3.002, 3.525, 4.184, 4.669},
      {3.52950732625353, 4.8915812474795, 6.00734561096922, 6.5482087646189, 8.15745796478021}
    };
    Real multiplier [3] = {1, 1, 1};
    Tuple<Real> field_saved;
    Tuple<Real> neighbour;
    Real wgc_status = 5;
    
    bool received [3]= {false, false, false};
};

#endif