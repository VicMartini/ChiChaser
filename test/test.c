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
  vertice *ptr;
  
  for (u32 i = 0; i <= 3; i++)
  {
    vertice *v = malloc(sizeof(vertice));
    v->nombre = i;
    q = addl(i, v, q);
  }
  // busco el 2 
  ptr = search(2, q);
  munit_assert_uint32(ptr->nombre,==, 2);
  return MUNIT_OK;
}

/* parametros , cuando se hace un test y se necesita parametros 
   se crea una arreglo y se pasa a MunitParameterEnum 
   luego en la suite se agrega el nombre como parametro en este caso file_params
   esto es para que el test use esos parametros.
   luego con munit_parameters_get(params, "file") los obtenemos .

*/
static char* file_params[] = {
  (char *)"./dimacs_files/q10",
  (char *)"./dimacs_files/q13",
  /* (char *)"./dimacs_files/school1",
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
  (char *)"./dimacs_files/GRD505041100", */
   NULL
};

static char* one_file_params[] = {
  (char *)"./dimacs_files/q10",
   NULL
};

static MunitParameterEnum test_params[] = {
  {(char*) "file", file_params },
  { NULL, NULL },
};

static MunitParameterEnum test_params_one[] = {
  {(char*) "one_file", one_file_params},
  { NULL, NULL },
};

static MunitResult
test_read_n_m_from_file(const MunitParameter params[], void* fixture) {
  FILE *f;
  const char *filename;
  Lado_st *Data = calloc(1, sizeof(Lado_st));
 
  Data->v = 0;
  Data->w = 0;
  filename = (const char *) munit_parameters_get(params, (const char*)"one_file");
  /*
    The  freopen()  function  opens  the  file  whose name is the string
    pointed to by pathname and associates the stream pointed to by stream with it. 
    The original stream (if it exists) is closed.
    The mode argument is used just as in the fopen() function.
  */
  f = freopen(filename, "r", stdin);
  Data = parse_p_edge_n_m();

  munit_assert_uint32(Data->v, ==, 100);
  munit_assert_uint32(Data->w, ==, 1470);
  
  return MUNIT_OK;
}


static MunitResult
test_read_graph(const MunitParameter params[], void* fixture) {
  FILE *f;
  const char *filename;
  Grafo graph = NULL;
  u32 max_degree = 0;
  u32 min_degree = 0xFFFFFFFF;


  filename = (const char *) munit_parameters_get(params, "one_file");
  f = freopen(filename, "r", stdin);
  graph  = ConstruccionDelGrafo();
  fclose(f);
  // ckeck not null graph 
  munit_assert_ptr_not_null(graph);
  munit_assert_uint32(NumeroDeVertices(graph),==, 100);
  munit_assert_uint32(NumeroDeLados(graph),==, 1470);
  munit_assert_uint32(delta(graph),!=, min_degree);
  munit_assert_uint32(Delta(graph),!=, max_degree);
  return MUNIT_OK;
}


static MunitResult
test_copy_graph(const MunitParameter params[], void* fixture) {
  FILE *f;
  const char *filename;
  Grafo graph = NULL;
  Grafo clone_graph = NULL;

  filename = (const char *) munit_parameters_get(params, "file");
  f = freopen(filename, "r", stdin);
  graph  = ConstruccionDelGrafo();
  clone_graph = CopiarGrafo(graph);
  
  
  munit_assert_ptr_not_null(clone_graph);
  munit_assert_uint32(delta(graph), ==, delta(clone_graph));
  munit_assert_uint32(Delta(graph), ==, Delta(clone_graph));

  munit_assert_uint32(NumeroDeLados(graph), ==, NumeroDeLados(clone_graph));
  munit_assert_uint32(NumeroDeVertices(graph), ==, NumeroDeVertices(clone_graph));
  for (int i = 0; i < NumeroDeVertices(graph); i++)
  {
    munit_assert_uint32(Nombre(i, graph), == , Nombre( i, clone_graph));
    munit_assert_uint32(graph->orden[i], ==, clone_graph->orden[i]);
  }
  
  return MUNIT_OK;
}

static MunitResult
test_delete_graph(const MunitParameter params[], void* fixture) {
  FILE *f;
  const char *filename;
  Grafo graph = NULL;

  filename = (const char *) munit_parameters_get(params, "one_file");
  f = freopen(filename, "r", stdin);
  graph  = ConstruccionDelGrafo();
  
  DestruccionDelGrafo(graph);

  // check vertices null
  munit_assert_ptr_null(graph->vertices);
  // check array orden es null
  munit_assert_ptr_null(graph->orden);
  
  return MUNIT_OK;
}

static MunitResult
test_check_load_graph(const MunitParameter params[], void* fixture) {
  FILE *f;
  const char *filename;
  Grafo graph = NULL;
  Lado_st **array = NULL;
  Lado_st *info = NULL;
  filename = (const char *) munit_parameters_get(params, "one_file");
  f = freopen(filename, "r", stdin);
  graph  = ConstruccionDelGrafo();
  fclose(f);
  f = freopen(filename, "r", stdin);
  info = parse_p_edge_n_m();
  array = parse_edge(info);
  
   //TO DO 
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
static MunitTest test_list[] = {
  {
    (char*) "/test_is_null",
    test_list_is_null,
    test_list_setup,
    test_list_tear_down,
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
    (char*) "/test_list_search",
    test_list_search,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  
  /* Usually this is written in a much more compact format; all these
   * comments kind of ruin that, though.  Here is how you'll usually
   * see entries written: */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static MunitTest test_suite_graph_basic[] = {
  {
    (char*) "/test_read_n_m_from_file",
    test_read_n_m_from_file,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    test_params_one
  },
  {
    (char*) "/test_read_graph",
    test_read_graph,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    test_params_one
  },
  {
    (char*) "/test_copy_graph",
    test_copy_graph,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    test_params
  },
  {
    (char*) "/test_delete_graph",
    test_delete_graph,
    test_list_setup,
    test_list_tear_down,
    MUNIT_TEST_OPTION_NONE,
    test_params_one
  },
  {
    (char*) "/test_check_load_graph",
    test_check_load_graph,
    NULL,
    NULL,
    MUNIT_TEST_OPTION_NONE,
    test_params_one
  },
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
static const MunitSuite test_suite_list = {
  /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */
  (char*) "test_list",
  /* The first parameter is the array of test suites. */
  test_list,
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


static const MunitSuite test_suite_graph = {
  /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */
  (char*) "test_suite_graph_basic",
  /* The first parameter is the array of test suites. */
  test_suite_graph_basic,
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
  munit_suite_main(&test_suite_list, NULL, argc, argv);
  munit_suite_main(&test_suite_graph, NULL, argc, argv);
  return 0;
}