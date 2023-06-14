#include "nuclei.h"
#include "linked.c"

//The code handles the parsing part. I had to edit .ncl files because my code treats every sign such as: (, ', ) separately.
//So I added space after and before each sign e.g. ( SET A ' 5 ' ). I tried to add those spaces in the main function, 
//however it did not work out as expected. The code also handles some of the interpreter cases. 
//I had to modify my makefile a bit, but it is very similar. I changed it due to errors that I faced.
//When I typed "make all" in terminal, no errors. 

int main(int argc, char * argv[]) {
  if (argc < 2) {
    printf("No input file provided\n");
    return 0;
  }
  FILE * file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("File not found\n");
    return 0;
  }
  struct Program prog = {0};
  int i = 0;
  while (fscanf(file, "%s", prog.tokens[i]) == 1 && i < MAX_TOKENS) {
    i++;
  }
  test1();
  fclose(file);
  numVariables = 50;
  for (int i = 0; i < numVariables; i++) {
    variables[i].name = "";
    variables[i].value = 0;
  }
  variables[0].name = "A";
  variables[1].name = "B";
  variables[2].name = "C";
  variables[3].name = "D";
  variables[4].name = "E";
  variables[5].name = "F";
  variables[6].name = "G";
  variables[7].name = "H";
  
  Prog( & prog);
  #ifdef INTERP
  #else
  printf("Parsed OK\n");
  #endif
  return 0;
}
void Prog(struct Program *p) {
  if (strcmp(p->tokens[p->current_token], "(") != 0) {
    test_variable = 1;
    ERROR( "No BEGIN statement?\n" );
    return;
  }
  p->current_token++;
  INSTRCTS(p);
}

void INSTRCTS(struct Program * p) {
  while (p -> tokens[p -> current_token]) {
    if (strcmp(p -> tokens[p -> current_token], "(") == 0) {
      if (strcmp(p -> tokens[p -> current_token + 1], "SET") == 0 ||
        strcmp(p -> tokens[p -> current_token + 1], "PRINT") == 0 ||
        strcmp(p -> tokens[p -> current_token + 1], "CAR") == 0 ||
        strcmp(p -> tokens[p -> current_token + 1], "CDR") == 0 ||
        strcmp(p -> tokens[p -> current_token + 1], "CONS") == 0 ||
        strcmp(p -> tokens[p -> current_token + 1], "WHILE") == 0 ||
        strcmp(p -> tokens[p -> current_token + 1], "IF") == 0)
      {
        INSTRCT(p);
        if (strcmp(p -> tokens[p -> current_token], ")") != 0) {
          test_variable = 1;
          printf("Error1: expected ')' but found %s\n", p -> tokens[p -> current_token]);
          ERROR("No closing bracket?\n");
          return;
        }
      } else {
        test_variable = 1;
        printf("Error2: expected instruction but found %s\n", p -> tokens[p -> current_token + 1]);
        ERROR("No Instruction?\n");
        return;
      }
    } else if (strcmp(p -> tokens[p -> current_token], ")") == 0) {
      return;
    } else {
      test_variable = 1;
      printf("Error3: expected instruction or end of instructions but found %s\n", p -> tokens[p -> current_token]);
      ERROR("No Instruction?\n");
      return;
    }
    if (p -> tokens[p -> current_token] == NULL) {
      test_variable = 1;
      printf("Error: unexpected end of input\n");
      return;
    }
    p -> current_token++;
  }
}

void INSTRCT(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "(") == 0) {
    p -> current_token++;
    FUNC(p);
    if (strcmp(p -> tokens[p -> current_token], ")") != 0) {
      printf("Errorinstrct: expected ')' but found %s\n", p -> tokens[p -> current_token]);
      ERROR("No Closing bracket?\n");
    }
  } else {
    printf("Errorinstrct: expected '(' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("No Opening Bracket?\n");
  }
}

void FUNC(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "SET") == 0) {
    IOFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "PRINT") == 0) {
    IOFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "CAR") == 0) {
    LISTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "CDR") == 0) {
    LISTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "CONS") == 0) {
    LISTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "RETFUNC") == 0) {
    RETFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "IF") == 0) {
    IF(p);
  } else if (strcmp(p -> tokens[p -> current_token], "WHILE") == 0) {
    LOOP(p);
  } else {
    printf("Errorfunc: expected function but found %s\n", p -> tokens[p -> current_token]);
    ERROR("No Function?\n");
  }
  p -> current_token++;
}

void RETFUNC(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "CAR") == 0) {
    // call the appropriate function for parsing a CAR function
    LISTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "CDR") == 0) {
    LISTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "CONS") == 0) {
    LISTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "PLUS") == 0) {
    INTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "MINUS") == 0) {
    INTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "MULTIPLY") == 0) {
    INTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "DIVIDE") == 0) {
    INTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "LENGTH") == 0) {
    INTFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "LESS") == 0) {
    BOOLFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "GREATER") == 0) {
    BOOLFUNC(p);
  } else if (strcmp(p -> tokens[p -> current_token], "EQUAL") == 0) {
    BOOLFUNC(p);
  } else {
    printf("Error: Invalid Return Function %s\n", p -> tokens[p -> current_token]);
    ERROR("No retfunc?\n");
  }
}

void LISTFUNC(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "CAR") == 0) {
    p -> current_token++;
    LIST(p);
    p -> current_token++;
  } else if (strcmp(p -> tokens[p -> current_token], "CDR") == 0) {
    p -> current_token++;
    LIST(p);
    p -> current_token++;
  } else if (strcmp(p -> tokens[p -> current_token], "CONS") == 0) {
    p -> current_token++;
    LIST(p);
    p -> current_token++;
    LIST(p);
    p -> current_token++;
  } else {
    printf("Error: expected 'CAR', 'CDR' or 'CONS' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid List Function.\n");
  }
}

//Extension to current grammar
void INTFUNC(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "PLUS") == 0 ||
    strcmp(p -> tokens[p -> current_token], "MINUS") == 0 ||
    strcmp(p -> tokens[p -> current_token], "MULTIPLY") == 0 ||
    strcmp(p -> tokens[p -> current_token], "DIVIDE") == 0)
  {
    p -> current_token++;
    LIST(p);
    p -> current_token++;
    LIST(p);
    if (isalpha(p -> tokens[p -> current_token][0]) && strlen(p -> tokens[p -> current_token]) == 1 && isupper(p -> tokens[p -> current_token][0])) {
      p -> current_token++;
    }
  } else if (strcmp(p -> tokens[p -> current_token], "LENGTH") == 0) {
    p -> current_token++;
    LIST(p);
    p -> current_token++;
  } else {
    printf("Error: expected 'PLUS', 'MINUS', 'MULTIPLY', 'DIVIDE' or 'LENGTH' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid Integer Function.\n");
  }
}

void BOOLFUNC(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "LESS") == 0) {
    p -> current_token++;
    LIST(p);
    p -> current_token++;
    LIST(p);
    p -> current_token++;
  } else if (strcmp(p -> tokens[p -> current_token], "GREATER") == 0) {
    p -> current_token++;
    LIST(p);
    p -> current_token++;
    LIST(p);
    p -> current_token++;
  } else if (strcmp(p -> tokens[p -> current_token], "EQUAL") == 0) {
    p -> current_token++;
    LIST(p);
    p -> current_token++;
    LIST(p);
    p -> current_token++;
  } else {
    printf("Error: expected 'LESS', 'GREATER' or 'EQUAL' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid Boolean Function.\n");
  }
}

void IOFUNC(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "SET") == 0) {
    SET(p);
  } else if (strcmp(p -> tokens[p -> current_token], "PRINT") == 0) {
    PRINT(p);
    if (strcmp(p -> tokens[p -> current_token], "\"") == 0) {
      if (strcmp(p -> tokens[p -> current_token], "\"") != 0) {
        printf("Error: expected '\"' but found %s\n", p -> tokens[p -> current_token]);
        ERROR("Invalid String Format.\n");
      }
    }
  } else {
    printf("Error: expected 'SET' or 'PRINT' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid Input/Output Function.\n");
  }
}

void SET(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "SET") == 0) {
    p -> current_token++;
    //interpreter
    char * varName = p -> tokens[p -> current_token];
    int value = atoi(p -> tokens[p -> current_token + 2]);
    if (isalpha(p -> tokens[p -> current_token + 1][0]) && isupper(p -> tokens[p -> current_token + 1][0]) && strlen(p -> tokens[p -> current_token + 1]) == 1) {
      // Find variable with the same name as the next token
      for (int i = 0; i < numVariables; i++) {
        if (strcmp(p -> tokens[p -> current_token + 1], variables[i].name) == 0) {
          value = variables[i].value;
          break;
        }
      }
    }
    for (int i = 0; i < numVariables; i++) {
      if (strcmp(varName, variables[i].name) == 0) {
        variables[i].value = value;
        break;
      }
    }
    VAR(p);
    p -> current_token++;
    LIST(p);
  } else {
    printf("Error: expected 'SET' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid SET Function.\n");
  }
}

void PRINT(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "PRINT") == 0) {
    #ifdef INTERP
    PRINTINTERP(p);
    #else
    #endif
    p -> current_token++;
    char * varName = p -> tokens[p -> current_token];
    for (int i = 0; i < numVariables; i++) {
      if (strcmp(varName, variables[i].name) == 0) {
        #ifdef INTERP
        printf("%d\n", variables[i].value);
        #else
        #endif
        break;
      }
    }
    if (strcmp(p -> tokens[p -> current_token], "\"") == 0) {
      STRING(p);
      #ifdef INTERP
      printf("%s\n", str);
      #else
      #endif
      if (strcmp(p -> tokens[p -> current_token], "\"") != 0) {
        printf("Error: expected '\"' but found %s\n", p -> tokens[p -> current_token]);
        ERROR("Invalid String Format.\n");
      }
    } else {
      LIST(p);
    }
  } else {
    printf("Error: expected 'PRINT' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid PRINT Function.\n");
  }
}

void PRINTINTERP(struct Program * p) {
  lisp * input = NULL;
  for (int i = p -> current_token + 1; i < MAX_TOKENS; i++) {
    if (isdigit(p -> tokens[i][0])) {
      int value = atoi(p -> tokens[i]);
      lisp * atom = lisp_atom(value);
      input = lisp_cons(atom, input);
    } else if (strcmp(p -> tokens[i], "CONS") == 0) {
      i++;
      i++;
      int value = atoi(p -> tokens[i]);
      lisp * atom = lisp_atom(value);
      input = lisp_cons(atom, input);
    } else if (strcmp(p -> tokens[i], "CAR") == 0) {
    } else if (strcmp(p -> tokens[i], "NIL") == 0) {
      input = lisp_cons(NULL, input);
    } else if (p -> tokens[i][0] == '\'') {
      int j = i + 1;
      char output_str[LISTSTRLEN];
      lisp_tostring(input, output_str);
      while (j < MAX_TOKENS && strcmp(p -> tokens[j], "'") != 0) {
        j++;
      }
      if (j == MAX_TOKENS) {
        printf("%s\n", output_str);
        return;
      }
      i = j;
    }
  }
}

void IF(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "IF") == 0) {
    p -> current_token++;
    if (strcmp(p -> tokens[p -> current_token], "(") == 0) {
      p -> current_token++;
      BOOLFUNC(p); // parse the condition
      if (strcmp(p -> tokens[p -> current_token], ")") == 0) {
        p -> current_token++;
        if (strcmp(p -> tokens[p -> current_token], "(") == 0) {
          p -> current_token++;
          INSTRCTS(p);
          if (strcmp(p -> tokens[p -> current_token], ")") == 0) {
            p -> current_token++;
            p -> current_token++;
            INSTRCTS(p);
          } else {
            printf("ErrorIF: expected ')' but found %s\n", p -> tokens[p -> current_token]);
            ERROR("No closing bracket for if-true-instrcts?\n");
          }
        } else {
          printf("ErrorIF: expected '(' but found %s\n", p -> tokens[p -> current_token]);
          ERROR("No opening bracket for if-true-instrcts?\n");
        }
      } else {
        printf("ErrorIF: expected ')' but found %s\n", p -> tokens[p -> current_token]);
        ERROR("No closing bracket for condition?\n");
      }
    } else {
      printf("ErrorIF: expected '(' but found %s\n", p -> tokens[p -> current_token]);
      ERROR("No opening bracket for condition?\n");
    }
  } else {
    printf("ErrorIF: expected 'IF' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("No IF statement?\n");
  }
} 
            
void LOOP(struct Program * p) {
  if (strcmp(p -> tokens[p -> current_token], "WHILE") == 0) {
    p -> current_token++;
    if (strcmp(p -> tokens[p -> current_token], "(") == 0) {
      p -> current_token++;
      BOOLFUNC(p); // parse the condition
      if (strcmp(p -> tokens[p -> current_token], ")") == 0) {
        p -> current_token++;
        if (strcmp(p -> tokens[p -> current_token], "(") == 0) {
          p -> current_token++;
          INSTRCTS(p); // parse the loop-instructions
          if (strcmp(p -> tokens[p -> current_token], ")") == 0) {
            p -> current_token--;
            // Loop-statement successfully parsed
          } else {
            printf("ErrorLOOP: expected ')' but found %s\n", p -> tokens[p -> current_token]);
            ERROR("No closing bracket for loop-instructions?\n");
          }
        } else {
          printf("ErrorLOOP: expected '(' but found %s\n", p -> tokens[p -> current_token]);
          ERROR("No opening bracket for loop-instructions?\n");
        }
      } else {
        printf("ErrorLOOP: expected ')' but found %s\n", p -> tokens[p -> current_token]);
        ERROR("No closing bracket for condition?\n");
      }
    } else {
      printf("ErrorLOOP: expected '(' but found %s\n", p -> tokens[p -> current_token]);
      ERROR("No opening bracket for condition?\n");
    }
  } else {
    printf("ErrorLOOP: expected 'LOOP' but found %s\n", p -> tokens[p -> current_token]);
    ERROR("No LOOP statement?\n");
  }
}
               
void LIST(struct Program * p) {
  if (isalpha(p -> tokens[p -> current_token][0]) && strlen(p -> tokens[p -> current_token]) == 1 && isupper(p -> tokens[p -> current_token][0]))
  {
    VAR(p);
  } else if (p -> tokens[p -> current_token][0] == '(') {
    p -> current_token++;
    RETFUNC(p);
    if (strcmp(p -> tokens[p -> current_token], ")") != 0) {
      printf("Error: expected ')' but found %s\n", p -> tokens[p -> current_token]);
      ERROR("Invalid List Format.\n");
    }
  } else if (p -> tokens[p -> current_token][0] == '\'') {
    LITERAL(p);
  } else if (strcmp(p -> tokens[p -> current_token], "NIL") == 0) {
  } else {
    printf("Error: expected variable, literal or NIL but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid List.\n");
  }
}

void VAR(struct Program * p) {
  if (isalpha(p -> tokens[p -> current_token][0]) && isupper(p -> tokens[p -> current_token][0]) && strlen(p -> tokens[p -> current_token]) == 1) {
  } else {
    printf("Error: expected variable but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid Variable.\n");
  }
}

void STRING(struct Program * p) {
  int i = 0;
  p -> current_token++;
  while (p -> tokens[p -> current_token][i] != '\"') {
    if (p -> tokens[p -> current_token][i] == '\0') {
      printf("Error: unexpected end of input\n");
      ERROR("Invalid String Format.\n");
    }
    while (strcmp(p -> tokens[p -> current_token], "\"") != 0) {
      strcat(str, p -> tokens[p -> current_token]);
      strcat(str, " "); // Add a space between each token
      p -> current_token++;
    }
  }
}

void LITERAL(struct Program * p) {
  if (p -> tokens[p -> current_token][0] != '\'') {
    printf("Error: expected single-quoted list but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid list format.\n");
  }
  p -> current_token++;
  int i = 0;
  int cnt4 = 1;
  while (p -> tokens[p -> current_token][i] != '\'') {
    p -> current_token++;
    car_var = atoi(p -> tokens[p -> current_token]);
    if (car_var > 0 && car_var < 10 && cnt4 == 1) {
      car_var = atoi(p -> tokens[p -> current_token]);
      #ifdef INTERP
      printf("%i\n", car_var);
      cnt4++;
      #else
      #endif
    }
  }
  if (p -> tokens[p -> current_token][i] != '\'') {
    printf("Error: expected closing single quote but found %s\n", p -> tokens[p -> current_token]);
    ERROR("Invalid list format.\n");
  }
}

void test1(void) {
//IFDEF here, because during testing I do not want to print the values to the terminal.
#ifdef INTERP
#else
//Test case PROG 
struct Program p1 = {{"(","(", "SET", "X", "\'" ,"5", "\'", ")", ")"}, 0};
Prog(&p1);
assert(strcmp(p1.tokens[2], "SET") == 0);
assert(test_variable != 1);
//Test cases INSTRCTS
struct Program p2 = {{"(", "SET", "G", "\'" ,"5", "\'", ")", ")"}, 0};
INSTRCTS(&p2);
assert(strcmp(p2.tokens[2], "G") == 0);
assert(test_variable != 1);

struct Program p3 = {{ "(", "SET", "G", "\'" ,"5", "\'", ")",
    "(", "PRINT", "\"", "Hello, World!" ,"\"", ")", ")"}, 0};
INSTRCTS(&p3);
assert(p3.current_token == 13);
//Test case INSTRCT
struct Program p4 = {{"(", "SET", "X", "\'" ,"5", "\'", ")"}, 0};
INSTRCT(&p4);
//asserts that the current token after the function call should be ")"
assert(strcmp(p4.tokens[p4.current_token], ")") == 0);
//Test cases FUNC
struct Program p5 = {{"SET", "C", "\'" ,"99", "\'", ")"}, 0};
FUNC(&p5);
assert(strcmp(p5.tokens[p5.current_token], ")") == 0);

struct Program p6 = {{ "WHILE", "(", "GREATER", "A", "\'", "5", "\'", ")", 
"(", "(", "PRINT", "\"", "A is greater than 5", "\"", ")", ")"}, 0};
//Note: print_program(&p6);
//print_program function was used to print as a string for easier debugging and testing
FUNC(&p6);
assert(strcmp(p6.tokens[0], "WHILE") == 0);
//Test cases RETFUNC
struct Program p7 = {{"PLUS", "X", "Y", ")"}, 0};
RETFUNC(&p7);
assert(strcmp(p7.tokens[p7.current_token], ")") == 0);

struct Program p8 = {{"CONS", "X", "Y", ")"}, 0};
RETFUNC(&p8);
assert(strcmp(p8.tokens[p8.current_token], ")") == 0);
//Test cases LISTFUNC
struct Program p9 = {{"CAR", "X", ")"}, 0};
LISTFUNC(&p9);
assert(strcmp(p9.tokens[p9.current_token], ")") == 0);

struct Program p10 = {{"CONS", "A", "B", ")"}, 0};
LISTFUNC(&p10);
assert(strcmp(p10.tokens[p10.current_token], ")") == 0);
//Test case INTFUNC
struct Program p11 = {{"LENGTH", "X", ")"}, 0};
INTFUNC(&p11);
assert(strcmp(p11.tokens[p11.current_token], ")") == 0);
//Test case BOOLFUNC
struct Program p12 = {{"GREATER", "X", "Y", ")"}, 0};
BOOLFUNC(&p12);
assert(strcmp(p12.tokens[p12.current_token], ")") == 0);
//Test case IOFUNC
struct Program p13 = {{"PRINT", "\"", "Hello, World!", "\"", ")"}, 0};
IOFUNC(&p13);
assert(strcmp(p13.tokens[p13.current_token], "\"") == 0);
assert(p13.current_token == 3);
//Test case SET
struct Program p14 = {{"SET", "A", "NIL"}, 0};
SET(&p14);
assert(strcmp(p14.tokens[0], "SET") == 0);
assert(strcmp(p14.tokens[1], "A") == 0);
assert(strcmp(p14.tokens[2], "NIL") == 0);
//Test cases PRINT
////Test case: checks if the PRINT function correctly prints the string
struct Program p15 = {{"PRINT", "\"", "Hello, World!" ,"\"", ")"}, 0};
PRINT(&p15);
assert(strcmp(p15.tokens[2], "Hello, World!") == 0);
////Test case: checks if the PRINT function correctly prints Variable
char expected_output[] = "B";
struct Program p16 = {{"PRINT", "B" , ")"}, 0};
IOFUNC(&p16);
assert(strcmp(expected_output, p16.tokens[1]) == 0);
//Test case LIST
struct Program p17 = {{"X", ")"}, 0};
LIST(&p17);
assert(strcmp(p17.tokens[p17.current_token], "X") == 0);

struct Program p18 = {{"'", "(", "1", "2", "3","'", ")", ")"}, 0};
LIST(&p18);
assert(strcmp(p18.tokens[p18.current_token], "'") == 0);
//Test case VAR
struct Program p19 = {{"H", ")"}, 0};
VAR(&p19);
assert(strcmp(p19.tokens[p19.current_token], "H") == 0);
//Test case STRING
struct Program p20 = {{"PRINT", "\"", "Hello, World!", "\"", ")"}, 0};
STRING(&p20);
assert(strcmp(p20.tokens[p20.current_token], "\"") == 0);

struct Program p21 = {{"PRINT", "\"", "This is a string test","\"", ")"}, 0};
STRING(&p21);
assert(strcmp(p21.tokens[2], "This is a string test") == 0);
//Test case LITERAL
struct Program p22 = {{"'", "1", "2", "3", "(", "4", "5", ")", "'", ")"}, 0};
LITERAL(&p22);
assert(strcmp(p22.tokens[p22.current_token], "'") == 0);
assert(strcmp(p22.tokens[2], "2") == 0);
#endif
}
void print_program(struct Program *p) {
    printf("Program tokens: ");
    for (int i = 0; i < MAX_TOKENS; i++) {
        printf("%s ", p->tokens[i]);
    }
    printf("\n");
}

