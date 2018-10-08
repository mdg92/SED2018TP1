#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "farmer.h"

using namespace std;

Real fuzzy(Real usd, Real amb);

Farmer::Farmer(const string &name) :
	Atomic(name),
	r_amb(addInputPort("r_amb")),
	r_usd(addInputPort("r_usd")),
	neighbour(addInputPort("neighbour")),
	wgc(addInputPort("wgc")),
	cost(addInputPort("cost")),
	u_amb(addOutputPort("u_amb")),
	u_usd(addOutputPort("u_usd")),
	field(addOutputPort("field")),
	satisfaction(addOutputPort("satisfaction"))
{
}


Model &Farmer::initFunction()
{
	srand(time(nullptr)); 
	this->wgc_status = 5; 
	holdIn(AtomicState::active, VTime(0,0,0,0));
	return *this;
}

Model &Farmer::internalFunction(const InternalMessage &)
{
	this->wgc_status = 5; 
	passivate();
	return *this;
}

Model &Farmer::externalFunction(const ExternalMessage &msg)
{
	if (msg.port() == wgc && this->wgc_status == 5 ){
		this->received[0] = true;
		this->wgc_status = Tuple<Real>::from_value(msg.value())[0];
	}
	if (msg.port() == r_amb  ){
		this->received[1] = true;
		this->past_r_amb = Tuple<Real>::from_value(msg.value());
	}
	if (msg.port() == r_usd  ){
		this->received[2] = true;
		this->past_r_usd = Tuple<Real>::from_value(msg.value());
	}
	if (msg.port() == neighbour  ){
		this->received[3] = true;
		this->field_neighbour = Tuple<Real>::from_value(msg.value());
	}
	if (msg.port() == cost  ){
		this->received[4] = true;
		this->past_cost = Tuple<Real>::from_value(msg.value());
	}
	if(this->received[0] && this->received[1] && this->received[2] && this->received[3] && this->received[4]){
		this->received[0] = this->received[1] = this->received[2] = this->received[3] = this->received[4] = false;
		
		Real  _r_usd[2];
		
		_r_usd[0] =this->past_r_usd[0]<this->past_cost[0];
		if(_r_usd[0]<0)																								this->s_usd =0;
		if(this->past_r_usd[0]>=0 && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.1*954 ) )							this->s_usd =0.1;
		if( (( (this->wgc_status*0.2)+0.6)*0.1*954 )<=this->past_r_usd[0] && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.2*954 ) )  	this->s_usd =0.2;
		if( (( (this->wgc_status*0.2)+0.6)*0.2*954 )<=this->past_r_usd[0] && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.3*954 ) )  	this->s_usd =0.3;
		if( (( (this->wgc_status*0.2)+0.6)*0.3*954 )<=this->past_r_usd[0] && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.4*954 ) )  	this->s_usd =0.4;
		if( (( (this->wgc_status*0.2)+0.6)*0.4*954 )<=this->past_r_usd[0] && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.5*954 ) )  	this->s_usd =0.5;
		if( (( (this->wgc_status*0.2)+0.6)*0.5*954 )<=this->past_r_usd[0] && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.6*954 ) )  	this->s_usd =0.6;
		if( (( (this->wgc_status*0.2)+0.6)*0.6*954 )<=this->past_r_usd[0] && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.7*954 ) )  	this->s_usd =0.7;
		if( (( (this->wgc_status*0.2)+0.6)*0.7*954 )<=this->past_r_usd[0] && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.8*954 ) )  	this->s_usd =0.8;
		if( (( (this->wgc_status*0.2)+0.6)*0.8*954 )<=this->past_r_usd[0] && this->past_r_usd[0] < ( ((this->wgc_status*0.2)+0.6)*0.9*954 ) )  	this->s_usd =0.9;
		if( (( (this->wgc_status*0.2)+0.6)*0.9*954 )<=this->past_r_usd[0] ) 										 							this->s_usd =1;

		if(this->past_r_amb[0]<5) 								this->s_amb = 0.0;
		if(this->past_r_amb[0]>=5 && this->past_r_amb[0]<10) 	this->s_amb = 0.1;
		if(this->past_r_amb[0]>=10 && this->past_r_amb[0]<15) 	this->s_amb = 0.2;
		if(this->past_r_amb[0]>=15 && this->past_r_amb[0]<20) 	this->s_amb = 0.3;
		if(this->past_r_amb[0]>=20 && this->past_r_amb[0]<25) 	this->s_amb = 0.4;
		if(this->past_r_amb[0]>=25 && this->past_r_amb[0]<30) 	this->s_amb = 0.5;
		if(this->past_r_amb[0]>=30 && this->past_r_amb[0]<35) 	this->s_amb = 0.6;
		if(this->past_r_amb[0]>=35 && this->past_r_amb[0]<40) 	this->s_amb = 0.7;
		if(this->past_r_amb[0]>=40 && this->past_r_amb[0]<45) 	this->s_amb = 0.8;
		if(this->past_r_amb[0]>=45 && this->past_r_amb[0]<50) 	this->s_amb = 0.9;
		if(this->past_r_amb[0]>=50) 							this->s_amb =   1;
		
		_r_usd[1] =this->past_r_usd[1]<this->past_cost[1];
		Real n_s_usd;
		Real n_s_amb;
		if(_r_usd[1]<0)																n_s_usd =0;
		if(this->past_r_usd[1]>=0 && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.1*954 ) )						n_s_usd =0.1;
		if( (( (this->wgc_status*0.2)+0.6)*0.1*954 )<=this->past_r_usd[1] && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.2*954 ) )  	n_s_usd =0.2;
		if( (( (this->wgc_status*0.2)+0.6)*0.2*954 )<=this->past_r_usd[1] && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.3*954 ) )  	n_s_usd =0.3;
		if( (( (this->wgc_status*0.2)+0.6)*0.3*954 )<=this->past_r_usd[1] && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.4*954 ) )  	n_s_usd =0.4;
		if( (( (this->wgc_status*0.2)+0.6)*0.4*954 )<=this->past_r_usd[1] && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.5*954 ) )  	n_s_usd =0.5;
		if( (( (this->wgc_status*0.2)+0.6)*0.5*954 )<=this->past_r_usd[1] && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.6*954 ) )  	n_s_usd =0.6;
		if( (( (this->wgc_status*0.2)+0.6)*0.6*954 )<=this->past_r_usd[1] && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.7*954 ) )  	n_s_usd =0.7;
		if( (( (this->wgc_status*0.2)+0.6)*0.7*954 )<=this->past_r_usd[1] && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.8*954 ) )  	n_s_usd =0.8;
		if( (( (this->wgc_status*0.2)+0.6)*0.8*954 )<=this->past_r_usd[1] && this->past_r_usd[1] < ( ((this->wgc_status*0.2)+0.6)*0.9*954 ) )  	n_s_usd =0.9;
		if( (( (this->wgc_status*0.2)+0.6)*0.9*954 )<=this->past_r_usd[1] ) 									n_s_usd =1;

		if(this->past_r_amb[1]<5) 				n_s_amb = 0.0;
		if(this->past_r_amb[1]>=5 && this->past_r_amb[1]<10) 	n_s_amb = 0.1;
		if(this->past_r_amb[1]>=10 && this->past_r_amb[1]<15) 	n_s_amb = 0.2;
		if(this->past_r_amb[1]>=15 && this->past_r_amb[1]<20) 	n_s_amb = 0.3;
		if(this->past_r_amb[1]>=20 && this->past_r_amb[1]<25) 	n_s_amb = 0.4;
		if(this->past_r_amb[1]>=25 && this->past_r_amb[1]<30) 	n_s_amb = 0.5;
		if(this->past_r_amb[1]>=30 && this->past_r_amb[1]<35) 	n_s_amb = 0.6;
		if(this->past_r_amb[1]>=35 && this->past_r_amb[1]<40) 	n_s_amb = 0.7;
		if(this->past_r_amb[1]>=40 && this->past_r_amb[1]<45) 	n_s_amb = 0.8;
		if(this->past_r_amb[1]>=45 && this->past_r_amb[1]<50) 	n_s_amb = 0.9;
		if(this->past_r_amb[1]>=50) 				n_s_amb =   1;
		
		int dice = std::rand() %100;
		//ERROR: Hacer funcion FUZZY propia y comparar con dice yt luego con la del VECINO
		if ( (fuzzy(this->s_usd, this->s_amb)*100) < dice && (fuzzy(this->s_usd, this->s_amb)< fuzzy(n_s_usd, n_s_amb))) this->field_saved = this->field_neighbour;
		holdIn(AtomicState::active, VTime(0,0,0,0));
	}else{
		passivate();
	}
	return *this;
}

Model &Farmer::outputFunction(const CollectMessage &msg)
{
	if(this->first_run){
		this->sendOutput(msg.time(), field, this->field_saved);
		this->first_run = false;
		return *this;
	}
	
	this->sendOutput(msg.time(), field, this->field_saved);
	this->sendOutput(msg.time(), u_amb, this->s_amb);
	this->sendOutput(msg.time(), u_usd, this->s_usd);
	this->sendOutput(msg.time(), satisfaction, fuzzy(this->s_usd, this->s_amb));
	return *this;
}
		    

Real fuzzy(Real usd, Real amb){
	return ( min(usd,amb) + (min((usd-1)*-1, amb) *0.1) + (min (usd, (amb-1)*-1) *0.8))/( min(usd,amb) + min((usd-1)*-1, amb) + min (usd, (amb-1)*-1) + min((usd-1)*-1, (amb-1)*-1) );
}
