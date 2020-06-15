#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char ch;
FILE *file, *file2;
void print_file(char *);
void exit_file_error(void);
void perform_test(char *, int);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_file("./files/usage");
    exit(EXIT_FAILURE);
  }
  if (strcmp(argv[1], "-a") == 0)
    print_file("./files/alphabet");
  else if (strcmp(argv[1], "-A") == 0)
    print_file("./files/alphabet-extra");
  else if (strcmp(argv[1], "-at") == 0)
    perform_test("./files/test-alphabet", 10);
  return 0;
}

void print_file(char filename[]) {
  file = fopen(filename, "r");
  if (file == NULL) {
    exit_file_error();
  }
  while ((ch = getc(file)) != EOF) {
    putc(ch, stdout);
  }
  fclose(file);
}

void perform_test(char *dir, int count) {
  char filename[strlen(dir) + 5];
  char answer[300], correct_answer[300];
  int asked[count];
  int index = 0, current_question, i, score = 0;
  _Bool been_asked;
  srand(time(0));
  for (i = 0; i < count; i++) asked[i] = -1;
  while (index < count) {
    answer[0] = '\0';
    correct_answer[0] = '\0';
    current_question = rand() % count;
    been_asked = 0;
    for (i = 0; i < count; i++) {
      if (asked[i] == current_question) {
        been_asked = 1;
        break;
      }
    }
    if (been_asked) continue;
    asked[index] = current_question;
    sprintf(filename, "%s/%d", dir, current_question);
    print_file(filename);
    if (fgets(answer, 300, stdin) == NULL) exit(EXIT_FAILURE);
    answer[strlen(answer) - 1] = '\0';
    sprintf(filename, "%s/%da", dir, current_question);
    file2 = fopen(filename, "r");
    if (file2 == NULL) {
      exit_file_error();
    }
    i = 0;
    while ((ch = getc(file2)) != EOF)
      correct_answer[i++] = ch;
    fclose(file2);
    correct_answer[i - 1] = '\0';
    if (strcmp(answer, correct_answer) == 0) {
      printf("Correct!\n\n");
      score++;
    } else {
      printf("Incorrect. The answer is: %s\n\n", correct_answer);
    }
    index++;
  }
  printf("You got %d correct out of %d.\n", score, count);
}

void exit_file_error() {
  printf("Error: could not find file\n");
  exit(EXIT_FAILURE);
}
