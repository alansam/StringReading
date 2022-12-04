#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define xstr(S) str(S)
#define str(X) #X
#define STR_LEN 52
#define SCN_STR_LEN xstr(STR_LEN)

static
char const * const data[] = {
  "A 12 Skipping Rope",
  "B 30 Football",
  "C 7 Yoga Mat",
};
static
size_t const data_sz = sizeof data / sizeof *data;

char ** item_detail(int * itemNum, int * col, int * row) {
  char ** notebook = NULL;

  *itemNum = data_sz;
  notebook = malloc(sizeof(char *) * (*itemNum));

  for (size_t i_ = 0ul; i_ < (*itemNum); ++i_) {
    notebook[i_] = calloc(STR_LEN, sizeof(char));
    strcpy(notebook[i_], data[i_]);
  }

  return notebook;
}

int main(int argc, char const * argv[]) {
  int total_item = 0;
  int row = 0;
  int col = 0;
  char ** Notebook = NULL;

  Notebook = item_detail(&total_item, &row, &col);
  // printf("@%p: %d, %d, %d\n", Notebook, total_item, row, col);
  char (* item_name)[STR_LEN] = calloc(total_item, sizeof(*item_name));
  int * each_amt = calloc(total_item, sizeof(int));
  char * shelve_name = calloc(total_item, sizeof(char));

  for (size_t i_ = 0; i_ < total_item; ++i_) {
    printf(">>> <%s>\n", Notebook[i_]);
    sscanf(Notebook[i_],
           "%c %d %" SCN_STR_LEN "[^\n]s",
           &shelve_name[i_],
           &each_amt[i_],
           item_name[i_]);
  }

  for (size_t d_ = 0; d_ < total_item; ++d_) {
    printf("shelf %2zu: ", d_ + 1);
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

  return 0;
}
