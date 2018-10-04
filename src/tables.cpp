#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "tables.h"

using namespace std;


Table::Table(const string &name) :
	Atomic(name),
	r_amb(addOutputPort("r_amb")),
	r_usd(addOutputPort("r_usd")),
	cost(addOutputPort("cost")),
	field(addInputPort("field")),
	best_neighbour(addInputPort("best_neighbour")),
	wgc(addInputPort("wgc")),
	external_change(addInputPort("external_change"))
{
}


Model &Table::initFunction()
{
	this->wgc_status = 5;
	this->multiplier[0] = 1; 
	passivate();
	return *this;
}

Model &Table::internalFunction(const InternalMessage &)
{
	this->wgc_status = 5;
	this->multiplier[0] = 1; 
	passivate();
	return *this;
}

Model &Table::externalFunction(const ExternalMessage &msg)
{
	if (msg.port() == wgc && this->wgc_status == 5 ){
		this->received[0] = true;
		this->wgc_status = Tuple<Real>::from_value(msg.value())[0];
	}
	if (msg.port() == field  ){
		this->received[1] = true;
		this->field_saved = Tuple<Real>::from_value(msg.value());
		
	}
	if (msg.port() == best_neighbour  ){
		this->received[2] = true;
		this->neighbour = Tuple<Real>::from_value(msg.value());
	}
	if (msg.port() == external_change){
		//for(int i = 0; i<3; i++){
			this->multiplier[0] =  Tuple<Real>::from_value(msg.value())[0];
			this->multiplier[1] =  Tuple<Real>::from_value(msg.value())[1];
			this->multiplier[2] =  Tuple<Real>::from_value(msg.value())[2];
		//}
		passivate();
	}

	if(this->received[0] && this->received[1] && this->received[2]){
		this->received[0] = this->received[1] = this->received[2] = false;
		holdIn(AtomicState::active, VTime(0,0,0,0));
	}else{
		passivate();
	}
	
	return *this;
}

Model &Table::outputFunction(const CollectMessage &msg)
{
	int __wgc;
	if(this->wgc_status ==1) __wgc=1;
	if(this->wgc_status ==2) __wgc=2;
	if(this->wgc_status ==3) __wgc=3;
	if(this->wgc_status ==4) __wgc=4;
	if(this->wgc_status ==0) __wgc=0;

	Real field_cost = (this->field_saved[1]*((costs[1])[__wgc])+this->field_saved[2]*costs[2][__wgc]+this->field_saved[0]*costs[0][__wgc]) * multiplier[1] / 100;
	Real neighbour_cost = (this->neighbour[1]*costs[1][__wgc]+this->neighbour[2]*costs[2][__wgc]+this->neighbour[0]*costs[0][__wgc])*multiplier[1] / 100;
	Tuple<Real> _cost = {field_cost, neighbour_cost};

	Real field_usd = (this->field_saved[1]*(price[1]*multiplier[2]*yield[1][__wgc]*multiplier[0])+this->field_saved[2]*(price[2]*multiplier[2]*yield[2][__wgc]*multiplier[0])+this->field_saved[0]*(price[0]*multiplier[2]*yield[0][__wgc]*multiplier[0])) / 100;
	Real neighbour_usd = (this->neighbour[1]*(price[1]*multiplier[2]*yield[1][__wgc]*multiplier[0])+this->neighbour[2]*(price[2]*multiplier[2]*yield[2][__wgc]*multiplier[0])+this->neighbour[0]*(price[0]*multiplier[2]*yield[0][__wgc]*multiplier[0])) / 100;
	Tuple<Real> _r_usd = {field_usd, neighbour_usd};

	Real field_amb = (this->field_saved[1]*emergy[1][__wgc]+this->field_saved[2]*emergy[2][__wgc]+this->field_saved[0]*emergy[0][__wgc]) / 100;
	Real neighbour_amb = (this->neighbour[1]*emergy[1][__wgc]+this->neighbour[2]*emergy[2][__wgc]+this->neighbour[0]*emergy[0][__wgc]) / 100;
	Tuple<Real> _r_amb = {field_amb, neighbour_amb};

	this->sendOutput(msg.time(), r_amb, _r_amb);
	this->sendOutput(msg.time(), r_usd, _r_usd);
	this->sendOutput(msg.time(), cost, _cost);
	return *this;
}