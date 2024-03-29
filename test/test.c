#include "munit.h"
#include "../RomaVictor.h"

#define L 0xFFFFFFFF
//gcc test.c munit.c munit.h ../HashTable.c ../List.c

/* This is just to disable an MSVC warning about conditional
 * expressions being constant, which you shouldn't have to do for your
 * code.  It's only here because we want to be able to do silly things
 * like assert that 0 != 1 for our demo. */
#if defined(_MSC_VER)
#pragma warning(disable : 4127)
#endif

/* The setup function, if you provide one, for a test will be run
 * before the test, and the return value will be passed as the sole
 * parameter to the test function. */

static void *
test_graph_one_file_setup(const MunitParameter params[], void *user_data)
{
  Grafo graph = NULL;
  FILE *f;
  const char *filename;
  filename = (const char *)munit_parameters_get(params, "one_file");
  f = freopen(filename, "r", stdin);
  graph = ConstruccionDelGrafo();
  fclose(f);
  return graph;
}

static void *
test_graph_all_files_setup(const MunitParameter params[], void *user_data)
{
  Grafo graph = NULL;
  FILE *f;
  const char *filename;
  filename = (const char *)munit_parameters_get(params, "file");
  f = freopen(filename, "r", stdin);
  graph = ConstruccionDelGrafo();
  fclose(f);
  return graph;
}

static void *
test_graph_ordernat_files_setup(const MunitParameter params[], void *user_data)
{
  Grafo graph = NULL;
  FILE *f;
  const char *filename;
  filename = (const char *)munit_parameters_get(params, "files_orden_natural");
  f = freopen(filename, "r", stdin);
  graph = ConstruccionDelGrafo();
  fclose(f);
  return graph;
}

/* parametros , cuando se hace un test y se necesita parametros 
   se crea una arreglo y se pasa a MunitParameterEnum 
   luego en la suite se agrega el nombre como parametro en este caso file_params
   esto es para que el test use esos parametros.
   luego con munit_parameters_get(params, "file") los obtenemos .

*/
static char *file_params[] = {
    (char *)"./dimacs_files/q10",
    (char *)"./dimacs_files/q13",
    (char *)"./dimacs_files/school1",
    (char *)"./dimacs_files/CBQsc100_200_11_1517",
    (char *)"./dimacs_files/CBQsv10_22_61.txt",
    (char *)"./dimacs_files/KC",
    (char *)"./dimacs_files/KD",
    (char *)"./dimacs_files/KM",
    (char *)"./dimacs_files/Octo.txt",
    (char *)"./dimacs_files/BxB1100_999_54_2017",
    (char *)"./dimacs_files/bxb777_999_12",
    (char *)"./dimacs_files/R1999999_10123123_1",
    (char *)"./dimacs_files/Gf12345_12111222_457_15",
    (char *)"./dimacs_files/CBQsv1000_77_150.txt",
    (char *)"./dimacs_files/GRD99704280",
    (char *)"./dimacs_files/GRD22154753987",
    (char *)"./dimacs_files/DG100",
    (char *)"./dimacs_files/PG64",
    (char *)"./dimacs_files/GRD505041100",
    NULL};




static char *files_orden_natural[] = {
    (char *)"./dimacs_files/q10",
    (char *)"./dimacs_files/q13",
    (char *)"./dimacs_files/school1",
    (char *)"./dimacs_files/CBQsc100_200_11_1517",
    (char *)"./dimacs_files/CBQsv10_22_61.txt",
    (char *)"./dimacs_files/KC",
    (char *)"./dimacs_files/KD",
    (char *)"./dimacs_files/KM",
    (char *)"./dimacs_files/Octo.txt",
    (char *)"./dimacs_files/BxB1100_999_54_2017",
    (char *)"./dimacs_files/Gf12345_12111222_457_15",
    (char *)"./dimacs_files/CBQsv1000_77_150.txt",
    (char *)"./dimacs_files/GRD99704280",
    (char *)"./dimacs_files/DG100",
    (char *)"./dimacs_files/PG64",
    NULL};

static char *one_file_params[] = {
    (char *)"./dimacs_files/q10",
    NULL};

static MunitParameterEnum test_params[] = {
    {(char *)"file", file_params},
    {NULL, NULL},
};

static MunitParameterEnum test_params_one[] = {
    {(char *)"one_file", one_file_params},
    {NULL, NULL},
};

static MunitParameterEnum test_params_orden_natural[] = {
    {(char *)"files_orden_natural", files_orden_natural},
    {NULL, NULL},
};


static MunitResult
orden_natural(const MunitParameter params[], void *fixture)
{
  Grafo G = (Grafo)fixture;
  u32 n = NumeroDeVertices(G);
  u32 result;
  for(u32 i = 0; i < n; ++i)
    {
        FijarOrden(i, G, i);
    }
  result = Greedy(G);
  printf("Result:%d \n", result);

  if(result == 16 ||
     result == 21 ||
     result == 42 ||
     result == 77 ||
     result == 16 ||
     result == 100 ||
     result == 500 ||
     result == 1000 ||
     result == 339 ||
     result == 5 ||
     result == 600 ||
     result == 173 ||
     result == 6)
     return MUNIT_OK;
  
  return MUNIT_FAIL;
}

/* To clean up after a test, you can use a tear down function.  The
 * fixture argument is the value returned by the setup function
 * above. */

static void
test_graph_one_file_tear_down(void *fixture)
{

  DestruccionDelGrafo(fixture);
}

static void
test_graph_all_files_tear_down(void *fixture)
{

  DestruccionDelGrafo(fixture);
}

/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */


    static MunitTest test_suite_parte_tres[] = {
    {(char *)"/orden_natural",
     orden_natural,
     test_graph_ordernat_files_setup,
     test_graph_all_files_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params_orden_natural},
   
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
/* If you wanted to have your test suite run other test suites you
 * could declare an array of them.  Of course each sub-suite can
 * contain more suites, etc. */
/* static const MunitSuite other_suites[] = { */
/*   { "/second", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE }, */
/*   { NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE } */
/* }; */

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */


  static const MunitSuite test_suite_part3 = {
    /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */

    (char *)"test_suite_parte_tres",
    /* The first parameter is the array of test suites. */
    test_suite_parte_tres,
    /* In addition to containing test cases, suites can contain other
   * test suites.  This isn't necessary in this example, but it can be
   * a great help to projects with lots of tests by making it easier
   * to spread the tests across many files.  This is where you would
   * put "other_suites" (which is commented out above). */
    NULL,
    /* An interesting feature of µnit is that it supports automatically
   * running multiple iterations of the tests.  This is usually only
   * interesting if you make use of the PRNG to randomize your tests
   * cases a bit, or if you are doing performance testing and want to
   * average multiple runs.  0 is an alias for 1. */
    1,
    /* Just like MUNIT_TEST_OPTION_NONE, you can provide
   * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
    MUNIT_SUITE_OPTION_NONE};


/* This is only necessary for EXIT_SUCCESS and EXIT_FAILURE, which you
 * *should* be using but probably aren't (no, zero and non-zero don't
 * always mean success and failure).  I guess my point is that nothing
 * about µnit requires it. */
#include <stdlib.h>

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */

  //munit_suite_main(&test_suite_list, NULL, argc, argv);
  //munit_suite_main(&test_suite_graph, NULL, argc, argv);
    munit_suite_main(&test_suite_part3, NULL, argc, argv);
  return 0;
}