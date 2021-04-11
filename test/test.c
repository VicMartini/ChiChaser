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
test_list_setup(const MunitParameter params[], void *user_data)
{
  list q = new_list();
  return q;
}

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

static MunitResult
test_list_is_null(const MunitParameter params[], void *fixture)
{
  list q = (list)fixture;
  munit_assert_ptr(q, ==, NULL);
  return MUNIT_OK;
}

static MunitResult
test_list_is_empty(const MunitParameter params[], void *fixture)
{
  list q = (list)fixture;
  // add a item
  q = addl(1, 2, q);
  munit_assert_false(is_empty(q));
  return MUNIT_OK;
}

static MunitResult
test_list_head(const MunitParameter params[], void *fixture)
{
  list q = (list)fixture;
  u32 v;
  // agrego 3 elementos
  q = addl(1, 1, q);
  q = addl(2, 1, q);
  q = addl(3, 1, q);
  // tomo la cabeza de la lista
  v = head(q);

  munit_assert_uint32(v, ==, 1);

  return MUNIT_OK;
}

static MunitResult
test_list_search(const MunitParameter params[], void *fixture)
{
  list q = (list)fixture;
  u32 v;

  for (u32 i = 0; i <= 3; i++)
  {

    q = addl(i, i, q);
  }
  // busco el 2
  v = search(2, q);
  munit_assert_uint32(v, ==, 2);
  return MUNIT_OK;
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

static MunitResult
test_read_n_m_from_file(const MunitParameter params[], void *fixture)
{
  FILE *f = NULL;
  const char *filename;
  Lado_st *Data = calloc(1, sizeof(Lado_st));

  Data->v = 0;
  Data->w = 0;
  filename = (const char *)munit_parameters_get(params, (const char *)"one_file");
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
  fclose(f);
  return MUNIT_OK;
}

static MunitResult
test_read_graph(const MunitParameter params[], void *fixture)
{

  Grafo graph = (Grafo)fixture;
  u32 max_degree = 0;
  u32 min_degree = 0xFFFFFFFF;

  // ckeck not null graph
  munit_assert_ptr_not_null(graph);
  munit_assert_uint32(NumeroDeVertices(graph), ==, 100);
  munit_assert_uint32(NumeroDeLados(graph), ==, 1470);
  munit_assert_uint32(delta(graph), !=, min_degree);
  munit_assert_uint32(Delta(graph), !=, max_degree);
  return MUNIT_OK;
}

static MunitResult
test_copy_graph(const MunitParameter params[], void *fixture)
{

  Grafo graph = (Grafo)fixture;
  Grafo clone_graph = NULL;

  clone_graph = CopiarGrafo(graph);

  munit_assert_ptr_not_null(clone_graph);
  munit_assert_uint32(delta(graph), ==, delta(clone_graph));
  munit_assert_uint32(Delta(graph), ==, Delta(clone_graph));

  munit_assert_uint32(NumeroDeLados(graph), ==, NumeroDeLados(clone_graph));
  munit_assert_uint32(NumeroDeVertices(graph), ==, NumeroDeVertices(clone_graph));
  for (u32 i = 0; i < NumeroDeVertices(graph); i++)
  {
    munit_assert_uint32(Nombre(i, graph), ==, Nombre(i, clone_graph));
    munit_assert_uint32(graph->orden[i], ==, clone_graph->orden[i]);
    for (u32 j = 0; j < Grado(i, graph); j++)
    {
      //printf("ori=%d, clon=%d \n", NombreVecino(j, i, graph), NombreVecino(j, i, clone_graph));
      munit_assert_uint32(NombreVecino(j, i, graph), ==, NombreVecino(j, i, clone_graph));
    }
  }

  return MUNIT_OK;
}

static MunitResult
test_check_load_graph(const MunitParameter params[], void *fixture)
{

  Grafo graph = (Grafo)fixture;
  Lado_st **array = NULL;
  Lado_st *info = NULL;
  hash_table ht;
  u32 v, w;
  FILE *f = NULL;
  const char *filename = NULL;
  // parseo y pongo en un array
  filename = (const char *)munit_parameters_get(params, "file");
  f = freopen(filename, "r", stdin);
  info = parse_p_edge_n_m();
  ht = new_ht(info->v);
  array = parse_edge_from_dimacs(info);
  for (u32 i = 0; i < info->w; i++)
  {
    v = ht_get(array[i]->v, ht);
    w = ht_get(array[i]->w, ht);

    if (v == L)
    {

      u32 key = array[i]->v;
      v = array[i]->v;
      ht_put(key, v, ht);
    }
    if (v == L)
    {

      u32 key = array[i]->w;
      w = array[i]->w;
      ht_put(key, w, ht);
    }
  }

  for (u32 i = 0; i < info->w; i++)
  {
    // obtengo el nombre real
    u32 n = Nombre(i, graph);
    // como se guarda el key == nombreReal en la hash
    // obtengo de la hash el vertice con nombre real
    v = ht_get(n, ht);
    if (v != L)
    {
      //check
      munit_assert_uint32(v, ==, n);
    }
  }
  fclose(f);
  return MUNIT_OK;
}

static MunitResult
test_check_pesos(const MunitParameter params[], void *fixture)
{

  Grafo graph = (Grafo)fixture;

  for (u32 i = 0; i < NumeroDeLados(graph); i++)
  {
    for (u32 j = 0; j < Grado(i, graph); i++)
    {
      FijarPesoLadoConVecino(j, i, i, graph);
    }
  }
  for (u32 i = 0; i < NumeroDeLados(graph); i++)
  {
    for (u32 j = 0; j < Grado(i, graph); i++)
    {
      munit_assert_uint32(PesoLadoConVecino(j, i, graph), ==, i);
    }
  }
  return MUNIT_OK;
}

static MunitResult
test_check_manos(const MunitParameter params[], void *fixture)
{

  Grafo graph = (Grafo)fixture;
  u32 sum_grados = 0;

  for (u32 i = 0; i < NumeroDeVertices(graph); i++)
  {
    sum_grados += Grado(i, graph);
  }
  munit_assert_uint32(sum_grados, ==, 2 * NumeroDeLados(graph));
  return MUNIT_OK;
}

static MunitResult
test_check_fijar_orden(const MunitParameter params[], void *fixture)
{

  Grafo graph = (Grafo)fixture;

  printf("\n");
  for (u32 i = 0; i < 10; i++)
  {
    printf("-%d-", graph->orden[i]);
  }
  printf("\n");
  u32 tmp, N;
  N = 9;
  for (u32 i = 0; i <= N; i++)
  {
    tmp = N - i;
    FijarOrden(i, graph, N - i);
    FijarOrden(tmp, graph, i);
    printf("-%d-", graph->orden[i]);
  }

  return MUNIT_OK;
}
static MunitResult
test_check_color_vertice(const MunitParameter params[], void *fixture)
{

  Grafo graph = (Grafo)fixture;
  for (u32 i = 0; i < NumeroDeVertices(graph); i++)
  {
    FijarColor(i, i, graph);
  }

  for (u32 i = 0; i < NumeroDeVertices(graph); i++)
  {
    munit_assert_uint32(Color(i, graph), ==, i);
  }

  return MUNIT_OK;
}

static MunitResult
test_check_copys(const MunitParameter params[], void *fixture)
{
  /* 
Cargar un grafo, colorear los vertices,
copiarlo, hacerle cambios al original (tanto en el orden como en los colores),
hacerle OTROS cambios a la copia, imprimir los datos de ambas copias
a ver si estan haciendo los cambios en la copia correcta.
Luego destruir la copia, crear otra copia, y repetir.
 */
  Grafo graph = (Grafo)fixture;
  Grafo copy_graph;
  u32 N, tmp;
  for (u32 i = 0; i < NumeroDeVertices(graph); i++)
  {
    FijarColor(1, i, graph);
  }

  copy_graph = CopiarGrafo(graph);

  N = NumeroDeVertices(graph);

  for (u32 i = 0; i < N; i++)
  {
    FijarColor(20, i, graph);
    FijarColor(100, i, copy_graph);
    tmp = N - i - 1;
    FijarOrden(i, graph, N - 1);
    FijarOrden(tmp, graph, i);
  }

  for (u32 i = 0; i < 10; i++)
  {
    // me fijo que tengan distintos colores
    munit_assert_uint32(Color(i, graph), !=, Color(i, copy_graph));
  }

  for (u32 i = 0; i < N; i++)
  {
    // me fijo que tengan distintos ordenes
    munit_assert_uint32(graph->orden[i], !=, copy_graph->orden[i]);
  }
  //destruyo
  DestruccionDelGrafo(copy_graph);
  // hago una nueva copia
  copy_graph = CopiarGrafo(graph);

  for (u32 i = 0; i < N; i++)
  { // deberia tener el mismo color luego de la primera modificación
    munit_assert_uint32(Color(i, graph), ==, Color(i, copy_graph));
  }

  return MUNIT_OK;
}

static MunitResult
test_check_color_vecino(const MunitParameter params[], void *fixture)
{
  Grafo graph = (Grafo)fixture;
  u32 i, vecino;
  i = 2;
  for (u32 j = 0; j < Grado(i, graph); j++)
  {
    vecino = OrdenVecino(j, i, graph);
    FijarColor(21, vecino, graph);
  }

  for (u32 j = 0; j < Grado(i, graph); j++)
  {
    munit_assert_uint32(ColorVecino(j, i, graph), ==, 21);
  }

  return MUNIT_OK;
}
/* To clean up after a test, you can use a tear down function.  The
 * fixture argument is the value returned by the setup function
 * above. */
static void
test_list_tear_down(void *fixture)
{
  free(fixture);
}

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
static MunitTest test_list[] = {
    {(char *)"/test_is_null",
     test_list_is_null,
     test_list_setup,
     test_list_tear_down,
     MUNIT_TEST_OPTION_NONE,
     NULL},
    {(char *)"/test_is_empty",
     test_list_is_empty,
     test_list_setup,
     test_list_tear_down,
     MUNIT_TEST_OPTION_NONE,
     NULL},
    {(char *)"/test_head",
     test_list_head,
     test_list_setup,
     test_list_tear_down,
     MUNIT_TEST_OPTION_NONE,
     NULL},
    {(char *)"/test_list_search",
     test_list_search,
     test_list_setup,
     test_list_tear_down,
     MUNIT_TEST_OPTION_NONE,
     NULL},

    /* Usually this is written in a much more compact format; all these
   * comments kind of ruin that, though.  Here is how you'll usually
   * see entries written: */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static MunitTest test_suite_graph_basic[] = {
    {(char *)"/test_read_n_m_from_file",
     test_read_n_m_from_file,
     NULL,
     NULL,
     MUNIT_TEST_OPTION_NONE,
     test_params_one},
    {(char *)"/test_read_graph",
     test_read_graph,
     test_graph_one_file_setup,
     test_graph_one_file_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params_one},
    {(char *)"/test_copy_graph",
     test_copy_graph,
     test_graph_all_files_setup,
     test_graph_all_files_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params},
    {(char *)"/test_check_load_graph",
     test_check_load_graph,
     test_graph_all_files_setup,
     test_graph_all_files_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params},
    {(char *)"/test_check_manos",
     test_check_manos,
     test_graph_one_file_setup,
     test_graph_one_file_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params_one},
    {(char *)"/test_check_pesos",
     test_check_pesos,
     test_graph_one_file_setup,
     NULL,
     MUNIT_TEST_OPTION_NONE,
     test_params_one},
    {(char *)"/test_check_FijarOrden",
     test_check_fijar_orden,
     test_graph_one_file_setup,
     test_graph_one_file_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params_one},
    {(char *)"/test_check_color_vertice",
     test_check_color_vertice,
     test_graph_one_file_setup,
     test_graph_one_file_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params_one},
    {(char *)"/test_check_color_vecino",
     test_check_color_vecino,
     test_graph_one_file_setup,
     test_graph_one_file_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params_one},
    {(char *)"/test_check_copys",
     test_check_copys,
     test_graph_one_file_setup,
     test_graph_one_file_tear_down,
     MUNIT_TEST_OPTION_NONE,
     test_params_one},
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

static const MunitSuite test_suite_list = {
    /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */
    (char *)"test_list",
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
    MUNIT_SUITE_OPTION_NONE};

static const MunitSuite test_suite_graph = {
    /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */

    (char *)"test_suite_graph_basic",
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

  munit_suite_main(&test_suite_list, NULL, argc, argv);
  munit_suite_main(&test_suite_graph, NULL, argc, argv);
  return 0;
}