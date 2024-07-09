#include "cliprog.h"

i32 main(i32 argc, char** argv) {

    cliSpinner Spinner1 = cliCreateSpinner("Heavy process 1...", NULL);
    if (!cliStartSpinner(&Spinner1)) { return 1; }

    sleep(3); // main thread work simulation
    cliStopSpinner(&Spinner1);

    puts("First process complete.");

    cliSpinnerConfig Conf     = { .Frames = ".oO@*", .Framerate = 8 };
    cliSpinner       Spinner2 = cliCreateSpinner("Heavy process 2...", &Conf);
    if (!cliStartSpinner(&Spinner2)) { return 1; }

    sleep(4); // main thread work simulation
    cliStopSpinner(&Spinner2);

    puts("Second process complete.");

    return 0;
}
