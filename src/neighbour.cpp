#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "neighbour.h"

using namespace std;


Neighbour::Neighbour(const string &name) :
	Atomic(name),
	out(addOutputPort("out")),
	/*corn(addOutputPort("corn")),
	soy(addOutputPort("soy")),
	wheat(addOutputPort("wheat")),*/
	frequency_time(365,0,0,0)
{
}


Model &Neighbour::initFunction()
{
	std::srand(std::time(nullptr)); 
	holdIn(AtomicState::active, VTime(365,0,0,0));
	return *this;
}

Model &Neighbour::internalFunction(const InternalMessage &)
{
	holdIn(AtomicState::active, this->frequency_time);
	return *this;
}


Model &Neighbour::outputFunction(const CollectMessage &msg)
{
	int first_index = std::rand()%3;
	int second_index = (std::rand()%2 + 1 + first_index)%3;
	int third_index = 3 - first_index - second_index;
	int percents [3];
	percents[first_index] = std::rand() %100;
	percents[second_index] = std::rand() %(100 - percents[first_index]);
	percents[third_index] = 100 - percents[first_index]- percents[second_index];
	assert(first_index<3 && second_index<3 && third_index<3 && first_index!=second_index && second_index != third_index);
	assert(percents[0]+percents[1]+percents[2]==100);

	Tuple<Real> out_value{percents[0],percents[1],percents[2]};
	sendOutput(msg.time(), out, out_value);
	/*this->sendOutput(msg.time(), corn, percents[0]);
	this->sendOutput(msg.time(), soy, percents[1]);
	this->sendOutput(msg.time(), wheat, percents[2]);*/
	return *this;
}
