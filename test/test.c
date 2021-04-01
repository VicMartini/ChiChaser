#include "munit.h"
#include "../GrafoSt.h"

//gcc test.c munit.c munit.h ../HashTable.c ../List.c

/* This is just to disable an MSVC warning about conditional
 * expressions being constant, which you shouldn't have to do for your
 * code.  It's only here because we want to be able to do silly things
 * like assert that 0 != 1 for our demo. */
#if defined(_MSC_VER)
#pragma warning(disable: 4127)
#endif  

/* The setup function, if you provide one, for a test will be run
 * before the test, and the return value will be passed as the sole
 * parameter to the test function. */
static void*
test_list_setup(const MunitParameter params[], void* user_data) {
  list q = new_list();
  return q;
}


static MunitResult
test_list_is_null(const MunitParameter params[], void* fixture) {
  list q = (list) fixture;
  munit_assert_ptr(q, ==, NULL);
  return MUNIT_OK;
}


static MunitResult
test_list_is_empty(const MunitParameter params[], void* fixture) {
  list q = (list) fixture;
  vertice *item = NULL;
  // add a item 
  q = addr(item, q);
  munit_assert_false(is_empty(q));
  return MUNIT_OK;
}

static MunitResult
test_list_head(const MunitParameter params[], void* fixture) {
  list q = (list) fixture;
  vertice * ver;
  // agrego 3 elementos 
  q = addr_idemp(1, q);
  q = addr_idemp(2, q);
  q = addr_idemp(3, q);
  // tomo la cabeza de la lista
  ver = head(q);

  munit_assert_uint32(ver->nombre, == , 1);

  return MUNIT_OK;
}

static MunitResult
test_list_search(const MunitParameter params[], void* fixture) {
  list q = (list) fixture;
  vertice * ver;
  // agrego 3 elementos 
  q = addr_idemp(1,q);
  q = addr_idemp(2,q);
  q = addr_idemp(3,q);
  // busco un el 2 
  ver = search(2, q);
  // check que devuelve 
  munit_assert_uint32(ver->nombre, == , 2);

  return MUNIT_OK;
}

static MunitResult
test_list_search_false(const MunitParameter params[], void* fixture) {
  list q = (list) fixture;
  vertice * ver;
  // agrego 3 elementos 
  q = addr_idemp(1,q);
  q = addr_idemp(2,q);
  q = addr_idemp(3,q);
  // busco el valor 4 , debe devolver null
  ver = search(4, q);

  munit_assert_ptr_null(ver);

  return MUNIT_OK;
}

static MunitResult
test_search_in_list(const MunitParameter params[], void* fixture) {
  list q = (list) fixture;
  vertice * ver;
  // agrego 3 elementos 
  q = addr_idemp(1, q);
  q = addr_idemp(2, q);
  q = addr_idemp(3, q);
  //check que 4 no esta en la lista , debe ser falso
  munit_assert_false(in_list(4, q));
  return MUNIT_OK;
}

static char* file_params[] = {
  (char *)"./dimacs_files/BxB1100_999_54_2017",
  (char *)"./dimacs_files/GRD99704280",
  (char *)"./dimacs_files/CBQsv1000_77_150.txt",
  (char *)"./dimacs_files/R1999999_10123123_1",
   NULL
};

static MunitParameterEnum test_params[] = {
  { "file", file_params },
  { NULL, NULL },
};

static MunitResult
test_read_n_m_from_file(const MunitParameter params[], void* fixture) {
  FILE *f;
  const char *filename;
  Lado_st *Data=calloc(1, sizeof(Lado_st));
 
  Data->v = 0;
  Data->w = 0;
  filename = (const char *) munit_parameters_get(params, "file");
  /*
    The  freopen()  function  opens  the  file  whose name is the string
    pointed to by pathname and associates the stream pointed to by stream with it. 
    The original stream (if it exists) is closed.
    The mode argument is used just as in the fopen() function.
  */
  f = freopen(filename, "r", stdin);
  Data = parse_p_edge_n_m();
  munit_assert_uint32(Data->v, !=, 0);
  munit_assert_uint32(Data->w, !=, 0);
  free(Data);
  return MUNIT_OK;
}



static MunitResult
test_read_graph(const MunitParameter params[], void* fixture) {
  FILE *f;
  const char *filename;
  Grafo graph = NULL;

  filename = (const char *) munit_parameters_get(params, "file");
  /*
    The  freopen()  function  opens  the  file  whose name is the string
    pointed to by pathname and associates the stream pointed to by stream with it. 
    The original stream (if it exists) is closed.
    The mode argument is used just as in the fopen() function.
  */
  f = freopen(filename, "r", stdin);
  graph  = ConstruccionDelGrafo();
  // ckeck not null graph 
  munit_assert_ptr_not_null(graph);
  return MUNIT_OK;
}
/* To clean up after a test, you can use a tear down function.  The
 * fixture argument is the value returned by the setup function
 * above. */
static void
test_list_tear_down(void* fixture) {
  free(fixture);
}

static void
test_hash_tear_down(void* fixture) {
  free(fixture);
}


/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
  {
    (char*) "/test_is_null",
    test_list_is_null,
    test_list_setup,
    /* If you passed a callback for the fixture setup function, you
     * may want to pass a corresponding callback here to reverse the
     * operation. */
    test_list_tear_down,
    /* Finally, there is a bitmask for options you can pass here.  You
     * can provide either MUNIT_TEST_OPTION_NONE or 0 here to use the
     * defaults. */
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    (char*) "/test_is_empty",
    test_list_is_empty,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    (char*) "/test_head",
    test_list_head,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    (char*) "/test_search",
    test_list_search,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    (char*) "/test_search_false",
    test_list_search_false,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    (char*) "/test_search_in_list",
    test_search_in_list,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    (char*) "/test_read_n_m_from_file",
    test_read_n_m_from_file,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    test_params
    },
    {
    (char*) "/test_read_graph",
    test_read_graph,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    test_params
    },
  /* Usually this is written in a much more compact format; all these
   * comments kind of ruin that, though.  Here is how you'll usually
   * see entries written: */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* If you wanted to have your test suite run other test suites you
 * could declare an array of them.  Of course each sub-suite can
 * contain more suites, etc. */
/* static const MunitSuite other_suites[] = { */
/*   { "/second", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE }, */
/*   { NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE } */
/* }; */

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
  /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */
  (char*) "",
  /* The first parameter is the array of test suites. */
  test_suite_tests,
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
  MUNIT_SUITE_OPTION_NONE
};

/* This is only necessary for EXIT_SUCCESS and EXIT_FAILURE, which you
 * *should* be using but probably aren't (no, zero and non-zero don't
 * always mean success and failure).  I guess my point is that nothing
 * about µnit requires it. */
#include <stdlib.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */
  return munit_suite_main(&test_suite, NULL, argc, argv);
}