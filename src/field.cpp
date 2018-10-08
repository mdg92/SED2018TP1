#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "field.h"

using namespace std;


Field::Field(const string &name) :
	Atomic(name),
	seed(addInputPort("seed")),
	reaped(addOutputPort("reaped"))
{
}


Model &Field::initFunction()
{
	this->content = Tuple<Real> {0,0,0};
	passivate();
	return *this;
}


Model &Field::externalFunction(const ExternalMessage &msg)
{
	//[(!) update common variables]	
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();
	this->timeLeft = this->sigma - this->elapsed;
	if (this->content == Tuple<Real> {0,0,0} ){
		this->content = Tuple<Real>::from_value(msg.value());
		holdIn(AtomicState::active, VTime(365,0,0,0));
	}else{
		holdIn(AtomicState::active, timeLeft);
	}
	
	return *this;
}


Model &Field::internalFunction(const InternalMessage &)
{
	this->content = Tuple<Real> {0,0,0};
	passivate();
	return *this ;
}


Model &Field::outputFunction(const CollectMessage &msg)
{
	sendOutput(msg.time(), reaped, this->content);
	return *this ;
}
