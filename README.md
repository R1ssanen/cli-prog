# cli-prog

Light and simplistic library for CLI progress and process visualization.

## Usage

Simply drop the header file *cliprog.h* into your project!

## API

The spinner configuration struct.

- `typedef struct {
    const char* Frames;
    uint8_t     Framerate;
} cliSpinnerConfig;`

    Frames must either be null, a valid null-terminated string or a string literal.

Create a new spinner instance.

- `cliSpinner cliCreateSpinner(const char* StartMsg, const cliSpinnerConfig* Conf)`

    Both arguments can be null, in which case default values are used.

Start the asynchronous spinner.

- `bool cliStartSpinner(cliSpinner* Proc)`

    Returns true on success.

Stop and destroy the spinner.

- `void cliStopSpinner(cliSpinner* Proc)`

    **Remember to call before exiting the scope of the spinner instance!**
