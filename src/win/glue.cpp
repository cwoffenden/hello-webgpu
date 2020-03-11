/**
 * Entry point for the 'real' application.
 *
 * \param[in] argc count of program arguments in argv
 * \param[in] argv program arguments (excluding the application)
 */
extern "C" int __main__(int /*argc*/, char* /*argv*/[]);

/**
 * Entry point. Workaround for Emscripten needing an \c async start.
 */
int main(int argc, char* argv[]) {
    return __main__(argc, argv);
}
