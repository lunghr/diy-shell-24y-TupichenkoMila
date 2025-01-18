#include <argtable3.h>
#include <loaders/loaders.h>
#include <string.h>

int main(int argc, char **argv) {

  struct arg_str *script = arg_str0("s", "script", "<script>",
                                    "Script to run [dedup / io-thpt-read]");
  struct arg_int *iterations =
      arg_int0("i", "iterations", "<n>", "Number of iterations");
  struct arg_int *threads =
      arg_int0("t", "threads", "<n>", "Number of threads");
  struct arg_end *end = arg_end(20);
  void *argtable[] = {script, iterations, threads, end};
  const char *progname = "benchmark";

  int nerrors = arg_parse(argc, argv, argtable);
  if (nerrors > 0) {
    arg_print_errors(stderr, end, progname);
    arg_print_syntax(stderr, argtable, "\n");
    arg_print_glossary(stderr, argtable, "  %-25s %s\n");
    return EXIT_FAILURE;
  }

  const char *script_name = script->count > 0 ? script->sval[0] : NULL;
  size_t iter_count = iterations->count > 0 ? iterations->ival[0] : 10;
  size_t thread_count = threads->count > 0 ? threads->ival[0] : 1;

  if (script_name == NULL) {
    fprintf(stderr, "Script name is required\n");
    return EXIT_FAILURE;
  }
  if (iter_count <= 0) {
    fprintf(stderr, "Iterations must be greater than 0\n");
    return EXIT_FAILURE;
  }
  if (thread_count <= 0) {
    fprintf(stderr, "Threads must be greater than 0\n");
    return EXIT_FAILURE;
  }

  const char *deduplication_script = "dedup";
  const char *iothpt_read_script = "io-thpt-read";

  if (strcmp(script_name, deduplication_script) == 0) {
    RunDeduplicateBenchmark(iter_count, thread_count);
  } else if (strcmp(script_name, iothpt_read_script) == 0) {
    RunIoThtpReadBenchmark(iter_count, thread_count);
  } else {
    fprintf(stderr, "Unknown script name: %s\n", script_name);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}