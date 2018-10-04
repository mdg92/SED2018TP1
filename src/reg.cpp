#include "pmodeladm.h"
#include "register.h"

#include "neighbour.h"
#include "field.h"
#include "tables.h"
#include "farmer.h"


void register_atomics_on(ParallelModelAdmin &admin)
{
	admin.registerAtomic(NewAtomicFunction<Farmer>(), FARMER_NAME);
	admin.registerAtomic(NewAtomicFunction<Field>(), FIELD_NAME);
	admin.registerAtomic(NewAtomicFunction<Table>(), TABLE_NAME);
	admin.registerAtomic(NewAtomicFunction<Neighbour>(), ATOMIC_MODEL_NAME);
}
