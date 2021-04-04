#include "tests.h"
#include "Console.h"
#include "DisciplineService.h"
#include "DisciplineRepo.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {
	{DisciplineRepo discRepo;
	DisciplineService discSrv{ discRepo };
	Console console{ discSrv };


	runTests();
	console.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}