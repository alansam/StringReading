#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  MARK: - Definitions
//  MARK:  Macros
#define xstr(S) str(S)
#define str(X) #X
#define STR_LEN 52
#define SCN_STR_LEN xstr(STR_LEN)

//  MARK: Constants
static
char const * const data[] = {
  "A 12 Skipping Rope",
  "B 30 Football",
  "C 7 Yoga Mat",
};
static
size_t const data_sz = sizeof data / sizeof *data;

/*
 *  MARK:  struct inventory
 */
typedef struct inventory inventory;
struct inventory {
  char id;
  int amount;
  char name[STR_LEN];
};
// static
// size_t const inventory_sz = sizeof(inventory);

static
int sample00(int argc, char const * argv[]);

static
int sample01(int argc, char const * argv[]);

//  MARK: Implementation
/*
 *  MARK:  item_detail()
 *
 *  Collect sample data into an array ready for processing. 
 */
char ** item_detail(int * itemNum, int * col, int * row) {
  char ** notebook = NULL;

  *itemNum = data_sz;
  notebook = malloc(sizeof(char *) * (*itemNum));
  if (notebook == NULL) {
    fprintf(stderr, "malloc() unsuccessful. Aborting.\n");
    exit(EXIT_FAILURE);
  }

  for (size_t i_ = 0ul; i_ < (*itemNum); ++i_) {
    notebook[i_] = calloc(STR_LEN, sizeof(char));
    if (notebook[i_] == NULL) {
      fprintf(stderr, "calloc() unsuccessful. Aborting.\n");
      exit(EXIT_FAILURE);
    }
    strcpy(notebook[i_], data[i_]);
  }

  return notebook;
}

/*
 *  MARK:  item_detail_free()
 *
 *  Release sample data working storage.
 */
char ** item_detail_free(size_t notes, char ** notebook) {
  if (notebook != NULL) {
    if (notes != 0) {
      for (size_t n_ = 0ul; n_ < notes; ++n_) {
        if (notebook[n_] != NULL) {
          free(notebook[n_]);
          notebook[n_] = NULL;
        }
      }
    }
    free(notebook);
    notebook = NULL;
  }

  return notebook;
}

/*
 *  MARK:  main()
 */
int main(int argc, char const * argv[]) {

  sample00(argc, argv);
  sample01(argc, argv);

  return EXIT_SUCCESS;
}

/*
 *  MARK:  sample00()
 *
 *  Process sample data and insert into arrays.
 */
static
int sample00(int argc, char const * argv[]  ) {
  printf("In function %s()\n", __func__);

  int total_item = 0;
  int row = 0;
  int col = 0;
  char ** Notebook = NULL;

  Notebook = item_detail(&total_item, &row, &col);
  // printf("@%p: %d, %d, %d\n", Notebook, total_item, row, col);
  char (* item_name)[STR_LEN] = calloc(total_item, sizeof(*item_name));
  if (item_name == NULL) {
    fprintf(stderr, "calloc() unsuccessful. Aborting.\n");
    exit(EXIT_FAILURE);
  }
  int * each_amt = calloc(total_item, sizeof(int));
  if (each_amt == NULL) {
    fprintf(stderr, "calloc() unsuccessful. Aborting.\n");
    exit(EXIT_FAILURE);
  }
  char * shelve_name = calloc(total_item, sizeof(char));
  if (shelve_name == NULL) {
    fprintf(stderr, "calloc() unsuccessful. Aborting.\n");
    exit(EXIT_FAILURE);
  }

  for (size_t i_ = 0ul; i_ < total_item; ++i_) {
    printf(">>> <%s>\n", Notebook[i_]);
    sscanf(Notebook[i_],
           "%c %d %" SCN_STR_LEN "[^\n]s",
           // "%c %d %[^\n]s",
           &shelve_name[i_],
           &each_amt[i_],
           item_name[i_]);
  }

  for (size_t d_ = 0ul; d_ < total_item; ++d_) {
    printf("shelf %2zu: ", d_ + 1ul);
    if (shelve_name[d_] == '\0') {
      printf("empty\n");
    }
    else {
      printf("%c, %2d, <%s>\n",
             shelve_name[d_],
             each_amt[d_],
             item_name[d_]);
    }
  }
  putchar('\n');
  free(item_name);
  free(each_amt);
  free(shelve_name);
  item_detail_free(total_item, Notebook);

  return EXIT_SUCCESS;
}

/*
 *  MARK:  sample01()
 *
 *  Process sample data and insert into array of struct inventory.
 */
static
int sample01(int argc, char const * argv[]) {
  printf("In function %s()\n", __func__);

  int total_item = 0;
  int row = 0;
  int col = 0;
  char ** Notebook = NULL;

  Notebook = item_detail(&total_item, &row, &col);
  inventory * items = calloc(total_item, sizeof(inventory));
  if (items == NULL) {
    fprintf(stderr, "calloc() unsuccessful. Aborting.\n");
    exit(EXIT_FAILURE);
  }

  for (size_t i_ = 0ul; i_ < total_item; ++i_) {
    printf(">>> <%s>\n", Notebook[i_]);
    sscanf(Notebook[i_],
           "%c %d %" SCN_STR_LEN "[^\n]s",
           // "%c %d %[^\n]s",
           &items[i_].id,
           &items[i_].amount,
           items[i_].name);
  }

  for (size_t d_ = 0ul; d_ < total_item; ++d_) {
    printf("shelf %2zu: ", d_ + 1ul);
    if (items[d_].id == '\0') {
      printf("empty\n");
    }
    else {
      printf("%c, %2d, <%s>\n",
             items[d_].id,
             items[d_].amount,
             items[d_].name);
    }
  }
  putchar('\n');
  free(items);
  item_detail_free(total_item, Notebook);

  return EXIT_SUCCESS;
}

//  MARK: - End
