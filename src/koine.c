#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>

char ch;
FILE *file, *file2;
void print_file(char *);
void less_file(char *);
void exit_file_error(char *);
void perform_test(char *);
int count_tests(char *);
void print_vocabulary(char **);
void flashcard(char **);
void exit_with_usage(void);
void update(void);

int main(int argc, char *argv[]) {
  if (argc < 2) exit_with_usage();
  if (strcmp(argv[1], "-f") == 0) {
    if (argc < 3) exit_with_usage();
    flashcard(argv);
  } else if (strcmp(argv[1], "-a") == 0)
    print_file("./files/alphabet");
  else if (strcmp(argv[1], "-A") == 0)
    less_file("./files/alphabet-extra");
  else if (strcmp(argv[1], "-at") == 0)
    perform_test("./files/test-alphabet");
  else if (strcmp(argv[1], "-c") == 0)
    less_file("./files/cases");
  else if (strcmp(argv[1], "-ct") == 0)
    perform_test("./files/test-cases");
  else if (strcmp(argv[1], "-h") == 0)
    print_file("./files/usage");
  else if (strcmp(argv[1], "--update") == 0)
    update();
  else if (strcmp(argv[1], "-v") == 0) {
    if (argc < 4)
      less_file("./files/vocabulary/words.csv");
    else
    print_vocabulary(argv);
  }
  return 0;
}

void flashcard(char *argv[]) {
  char arg1[100], arg2[100];
  _Bool sp = 0;
  int i, i1 = 0, i2 = 0;
  for (i = 0; i <= strlen(argv[2]); i++) {
    if (argv[2][i] == '-')
      sp = 1;
    else if (sp)
      arg2[i2++] = argv[2][i];
    else
      arg1[i1++] = argv[2][i];
  }
  arg1[i1] = '\n';
  arg2[i2] = '\n';
  int input_num, line_begin, num;
  if (sp) {
    input_num = atoi(arg2);
    num = input_num * 7;
    line_begin = (atoi(arg1) * 7) - 6;
  } else {
    input_num = atoi(arg1);
    num = input_num * 7;
    line_begin = num - 6;
  }
  int line_nr = 1, tabc = 0;
  char filename[] = "./files/vocabulary/words.csv";
  if (input_num < 1 || input_num > 771) exit_with_usage();
  file = fopen(filename, "r");
  if (file == NULL) {
    exit_file_error(filename);
  }
  while ((ch = getc(file)) != EOF && line_nr <= num) {
    if (line_begin <= line_nr) {
      if (tabc >= 1) putchar(ch);
      if (ch == '\t') tabc++;
      if (tabc == 2) {
        getchar();
        tabc = 1;
      }
      if (ch == '\n') putchar('\n');
    }
    if (ch == '\n') {
      line_nr++;
      tabc = 0;
    }
  }
  fclose(file);
}

void print_vocabulary(char *argv[]) {
  char path[200] = "./files/vocabulary/";
  strcat(path, argv[2]);
  strcat(path, "/");
  strcat(path, argv[3]);
  DIR *dir = opendir(path);
  if (dir) {
    strcat(path, "/vocabulary");
    less_file(path);
  } else {
    exit_with_usage();
  }
}

void print_file(char filename[]) {
  file = fopen(filename, "r");
  if (file == NULL) {
    exit_file_error(filename);
  }
  while ((ch = getc(file)) != EOF) {
    putc(ch, stdout);
  }
  fclose(file);
}

void less_file(char filename[]) {
  file = fopen(filename, "r");
  if (file == NULL) {
    exit_file_error(filename);
  }
  char cmd[200] = "less ";
  strcat(cmd, filename);
  system(cmd);
  fclose(file);
}

void perform_test(char *dir) {
  int count = count_tests(dir);
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
      exit_file_error(filename);
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

int count_tests(char *dir_name) {
  int c = 0;
  struct dirent *d;
  DIR *dir = opendir(dir_name);
  if (dir == NULL) return c;
  while ((d = readdir(dir)) != NULL) {
    if (d->d_type == DT_REG && d->d_name[0] != '.') c++;
  }
  return (c <= 1 ? 0 : (c / 2));
}

void exit_file_error(char *path) {
  printf("Error! Could not find file: %s\n", path);
  exit(EXIT_FAILURE);
}

void update() {
  system("git pull ; gcc -O3 -Wno-unused-result -o koine ./src/koine.c");
}

void exit_with_usage() {
  print_file("./files/usage");
  exit(EXIT_FAILURE);
}
