#include "tests.h"
#include "Console.h"
#include "DisciplineService.h"
#include "DisciplineRepo.h"

int main() {
	DisciplineRepo discRepo;
	DisciplineService discSrv{ discRepo };
	Console console{ discSrv };

	runTests();
	console.run();

	return 0;
}