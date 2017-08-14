#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

#define EXITSTATUS 8
#define BUFSIZE 80
#define SECRET 3

//**************
//Special types
struct Node {
  int val;
  int order;
  struct Node *next;
};


typedef struct treeNode {
  int val;
  struct treeNode *left, *right;
} tNode;

//*****************
//Global variables
FILE *input_stream;
int num_input_strings = 0;
char buf_phases[560];
char array_123[16] = {105, 115, 114, 118, 101, 97, 119, 108, 111, 98, 112, 110, 117, 116, 102, 103};

struct Node node6 = { .val = 989, .order = 6, .next = NULL };
struct Node node5 = { .val = 3129, .order = 5, .next = &node6 };
struct Node node4 = { .val = 39, .order = 4, .next = &node5 };
struct Node node3 = { .val = 3524, .order = 3, .next = &node4 };
struct Node node2 = { .val = 715, .order = 2, .next = &node3 };
struct Node node1 = { .val = 24, .order = 1, .next = &node2 };

tNode n48 = {1001, NULL, NULL};
tNode n47 = {107, NULL, NULL};
tNode n46 = {47, NULL, NULL};
tNode n45 = {38, NULL, NULL};
tNode n44 = {34, NULL, NULL};
tNode n43 = {20, NULL, NULL};
tNode n42 = {7, NULL, NULL};
tNode n41 = {1, NULL, NULL};
tNode n34 = {409, &n47, &n48};
tNode n33 = {45, &n45, &n46};
tNode n32 = {28, &n43, &n44};
tNode n31 = {6, &n41, &n42};
tNode n22 = {50, &n33, &n34};
tNode n21 = {15, &n31, &n32};
tNode n1 =  {36, &n21, &n22};

char *disclaimer = "This challenge has been taken from \"Computer Systems: A Programmer\'s Perspective\", by Randal E. Bryant and David R. O\'Hallaron.\nAll credit goes to them.";

//*********
//Routines
void sig_handler(int sig){
  printf("\nSo you think you can stop the bomb with ctrl-c, do you?\n");
  sleep(3);
  printf("Well... ");
  fflush(stdout);
  sleep(1);
  printf("OK. :-)\n");
  exit(16);
}


void initialize_bomb(){
  signal(SIGINT, sig_handler);
}


void explode_bomb()
{
  printf("\nBOOM!!!\n");
  printf("The bomb has blown up.\n");
  exit(EXITSTATUS);
}


int blank_line(char *buf){
  char *mov_buf;
  int readchar;
  int result;

  mov_buf = buf;
  if (*buf){
    while (1){
      readchar = *mov_buf++;
      if (!isspace(readchar) && (iscntrl(readchar) || isprint(readchar)))
        break;
      if (!*mov_buf){
        result = 1;
	return result;
      }
    }
    result = 0;
  }
  else
    result = 1;

  return result;
}


char *skip(FILE *input){
  char *temp_buf;
  char *ret_buf;

  do{
    temp_buf = fgets((char *)(BUFSIZE * num_input_strings + buf_phases), BUFSIZE, input);
    ret_buf = temp_buf;
  }
  while (temp_buf && blank_line(temp_buf));

  return ret_buf;
}


char *read_line(){
  int length;
  int offset;
  char *line;

  if (!skip(input_stream)){
    if (input_stream == stdin){
      printf("Error: premature EOF on stdin\n");
      explode_bomb();
    }
    input_stream = stdin;
    if (!skip(input_stream)){
      printf("Error: premature EOF on stdin\n");
      explode_bomb();
    }
  }

  length = strlen(&buf_phases[BUFSIZE * num_input_strings]);
  if (length == (BUFSIZE-1)){
    printf("Error: Input line too long\n");
    explode_bomb();
  }

  offset = BUFSIZE * num_input_strings;
  if(buf_phases[offset + length - 1] == '\n')
    buf_phases[offset + length - 1] = 0;
  line = offset + buf_phases;
  ++num_input_strings;
  return line;
}


int string_length(char *str){
  char *ptrstr;
  int result;

  ptrstr = str;
  for (result = 0; *ptrstr; ++result)
  	++ptrstr;
  return result;
}


int strings_not_equal(char *str1, char *str2){
  int length1;
  char *ptr1;
  char *ptr2;

  length1 = string_length(str1);
  if (length1 != string_length(str2))
    return 1;

  ptr1 = str1;
  ptr2 = str2;
  if (*str1){
    while (*ptr1 == *ptr2){
      ++ptr1;
      ++ptr2;
      if (!*ptr1)
        return 0;
    }
    return 1;
  }
  return 0;
}


int read_six_numbers(char *str, int *numbers){
  int result;

  result = sscanf(str, "%d %d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4], &numbers[5]);

  if ( result <= 5 )
    explode_bomb();

  return result;
}

int phase_1(char *input){
  int result;

  result = strings_not_equal(input, "Public speaking is very easy.");
  if (result)
    explode_bomb();
  return result;
}


int phase_2(char *input){
  int index;
  int result;
  int numbers[6];

  read_six_numbers(input, numbers);
  if (numbers[0] != 3)
    explode_bomb();

  index = 1;
  do{
    result = numbers[index - 1] * (index + 1);
    if (numbers[index] != result)
      explode_bomb();
    ++index;
  }
  while (index <= 5);
  return result;
}


int phase_3(char *input){
  int result;
  char hardcoded_ch;
  int n1;
  char c2;
  int n2;

  if (sscanf(input, "%d %c %d", &n1, &c2, &n2) <= 2)
    explode_bomb();

  result = n1;
  switch (n1){
    case 0:
      hardcoded_ch = 113;
      if ( n2 != 777 )
        explode_bomb();
      return result;
    case 1:
      hardcoded_ch = 98;
      if ( n2 != 214 )
        explode_bomb();
      return result;
    case 2:
      hardcoded_ch = 98;
      if ( n2 != 755 )
        explode_bomb();
      return result;
    case 3:
      hardcoded_ch = 107;
      if ( n2 != 251 )
        explode_bomb();
      return result;
    case 4:
      hardcoded_ch = 111;
      if ( n2 != 160 )
        explode_bomb();
      return result;
    case 5:
      hardcoded_ch = 116;
      if ( n2 != 458 )
        explode_bomb();
      return result;
    case 6:
      hardcoded_ch = 118;
      if ( n2 != 780 )
        explode_bomb();
      return result;
    case 7:
      hardcoded_ch = 98;
      if ( n2 != 524 )
        explode_bomb();
      return result;
    default:
      explode_bomb();
      return result;
  }
  if (hardcoded_ch != c2)
    explode_bomb();

  return result;
}


int func4(int num){
  int aux;
  int result;

  if (num <= 1)
    result = 1;
  else
  {
    aux = func4(num - 1);
    result = aux + func4(num - 2);
  }
  return result;
}


int phase_4(char *input){
  int result;
  int num;

  if (sscanf(input, "%d", &num) != 1 || num <= 0)
    explode_bomb();

  result = func4(num);

  if (result != 89)
    explode_bomb();

  return result;
}


int phase_5(char *input){
  int index;
  int result;
  char newarr[6];
  char v4;

  if (string_length(input) != 6)
    explode_bomb();

  index = 0;
  do{
    newarr[index] = array_123[input[index] & 0xF];
    ++index;
  }
  while ( index <= 5 );

  v4 = 0;
  result = strings_not_equal(newarr, "lakers");
  if (result)
    explode_bomb();

  return result;
}


int phase_6(char *input){
  int read_nums[6];
  int index1;
  int i;
  int index2;
  struct Node *node_ptr;
  int j;
  struct Node *current_node;
  int index3;
  struct Node *next_node;
  struct Node *some_node;
  int index4;
  int result;
  struct Node *first_node;
  struct Node *ptrs[6];

  read_six_numbers(input, read_nums);

  index1 = 0;
  do{
    if ((unsigned int)(read_nums[index1] - 1) > 5)
      explode_bomb();

    for (i = index1 + 1; i <= 5; ++i){
      if (read_nums[index1] == read_nums[i])
        explode_bomb();
    }
    ++index1;
  }
  while ( index1 <= 5 );

  //Fetch pointers to every node, in the order given by input
  index2 = 0;
  do{
    node_ptr = &node1;
    for (j = 1; j < read_nums[index2]; ++j)
      node_ptr = node_ptr->next;
    ptrs[index2++] = node_ptr;
  }
  while ( index2 <= 5 );


  //Overwrite next_node_ptr to reflect input order
  current_node = ptrs[0];
  first_node = ptrs[0];
  index3 = 1;
  do
  {
    next_node = ptrs[index3];
    current_node->next = next_node;
    current_node = next_node;
    ++index3;
  }
  while ( index3 <= 5 );
  next_node->next = NULL;


  //Check they are in descendent order
  some_node = first_node;
  index4 = 0;
  do
  {
    result = some_node->val;
    if (some_node->val < some_node->next->val)
      explode_bomb();
    some_node = some_node->next;
    ++index4;
  }
  while ( index4 <= 4 );

  return result;
}


int fun7(tNode *node, int val){
  int result;

  if (node){
    if (val >= node->val){
      if (val == node->val)
        result = 0;
      else
        result = 2 * fun7(node->right, val) + 1;
    }
    else
      result = 2 * fun7(node->left, val);
  }
  else
    result = -1;

  return result;
}


void secret_phase(){
  char *input;
  int target;

  input = read_line();
  target = atoi(input);

  if ((unsigned int)(target - 1) > 1000)
    explode_bomb();

  if (fun7(&n1, target) != 5)
    explode_bomb();

  printf("Wow! You've defused the secret stage!\n");
  //phase_defused();
}


void phase_defused(){
  int v0;
  char v1[12];

  if (num_input_strings == 6){
    if (sscanf(&buf_phases[BUFSIZE * SECRET], "%d %s", &v0, v1) == 2 && !strings_not_equal(v1, "austinpowers")){
      printf("Curses, you've found the secret phase!\n");
      printf("But finding it and solving it are quite different...\n");
      secret_phase();
    }
    printf("Congratulations! You've defused the bomb!\n");
  }
}


int main(int argc, char **argv){

  switch(argc){
    case 1:  //No input file, use stdin
      input_stream = stdin;
      break;

    case 2:  //Read from input file
      if(!(input_stream = fopen(argv[1], "r"))){
        printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
        exit(EXITSTATUS);
      }
      break;

    default:  //wrong number of arguments
      printf("Usage: %s [<input_file>]", argv[0]);
      exit(EXITSTATUS);
  }

  initialize_bomb();

  printf("\nWelcome to my fiendish little bomb. You have 6 phases with\n");
  printf("which to blow yourself up. Have a nice day!\n\n");

  phase_1(read_line());
  phase_defused();
  printf("Phase 1 defused. How about the next one?\n");

  phase_2(read_line());
  phase_defused();
  printf("That's number 2. Keep going!\n");

  phase_3(read_line());
  phase_defused();
  printf("Halfway there!\n");

  phase_4(read_line());
  phase_defused();
  printf("So you got that one. Try this one.\n");

  phase_5(read_line());
  phase_defused();
  printf("Good work!  On to the next...\n");

  phase_6(read_line());
  phase_defused();

  fclose(input_stream);
  return 0;
}
