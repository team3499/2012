
#include "Commands/DAG.h"

DAG::DAG()
{
	while(1){
		AddSequential(new AutoGroup());
		AddSequential(new Turn());
		AddSequential(new Delay(5));
	}
}
