
#include "Commands/DAG.h"

DAG::DAG()
{
	AddSequential(new Turn());
	AddSequential(new Delay(5));
}
