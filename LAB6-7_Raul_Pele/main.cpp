#include "tests.h"
#include "Console.h"
#include "DisciplineService.h"
#include "DisciplineRepo.h"
#include "DisciplineFileRepo.h"
#include "RepoLab.h"
#include "validators.h"

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>

int main() {
	{//DisciplineFileRepo discRepo{"disciplines.txt"};
		float p = (float) 0.6;
		RepoLab discRepo{p};
	DisciplineValidator validator;
	DisciplineService discSrv{ discRepo , validator};
	Console console{ discSrv };

	runTests();
	console.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}