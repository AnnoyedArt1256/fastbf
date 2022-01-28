#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


char program[1048576*4];
FILE *fp;

int strluoj(char in[],int o) {
    for(int n=0;n<strlen(in);n++) {
        if (in[n]==o) { return 1; }
    }
    return 0;
}

long PC, SP, loop = 0;
long lSize;
uint8_t stack[300000];
uint8_t commands[300000];
uint8_t count[300000];
long loopp[300000];
int main(int argc, char *argv[]) {
  if (argc == 1) {
       printf("Input a BrainF**k program: ");
       scanf("%s", program);
       getchar();
  } else {
  	fp = fopen(argv[1], "r");
        if (fp == NULL) {
  	   printf("Input a BrainF**k program: ");
  	   scanf("%s", program);
           getchar();
        } else {
          int i = 0;
          for (char t;(t=getc(fp))!=EOF;i++) {
            program[i] = t;
          }
        }
  }
  long i = -1;
  long j = 0;
  long stp = 0;
  while (i < (long)strlen(program)) {
      if (strluoj("+-<>,.[]",program[i])) {
        if (strluoj("+-<>",program[i])) {  
          j = 0;
          while(program[i]==program[i+j]) {
             j++;
          }
          commands[stp] = program[i];
          count[stp] = j;
          i += j;
          stp++;
        } else {
          commands[stp] = program[i];
          count[stp] = 1;
          stp++;    
          i++;
        }
      } else {
       i++;
      }
  }
  for (i=0;i<strlen(commands);i++) {
     PC = i;
     if (commands[PC] == 91) {
        loop = 1;
        while (loop) {
          PC++;
          if (commands[PC] == 91) loop++;
          if (commands[PC] == 93) loop--;
        }    
     } else
     if (commands[PC] == 93) {
        PC -= 2;
        loop -= 1;
        while (loop) {
          if (commands[PC] == 91) loop++;
          if (commands[PC] == 93) loop--;
          PC--;
        }  
     }
     loopp[i] = PC;
  }
  PC = 0;
  loop = 0;
  while (PC < strlen(commands)) {
    switch (commands[PC]) {
    case 43: {
      stack[SP]+=count[PC];
      break;
    }
    case 45: {
      stack[SP]-=count[PC];
      break;
    }
    case 60: {
      SP-=count[PC];
      break;
    }
    case 62: {
      SP+=count[PC];
      break;
    }
    case 46: {
      putchar(stack[SP]);
      break;
    }
    case 44: {
      printf("Input a character: ");
      stack[SP] = getchar();
      break;
    }
    case 91: {
      if (!stack[SP]) {
       PC = loopp[PC];
      };
      break;
    }
    case 93: {
      if (stack[SP]) {
       PC = loopp[PC];
      };
      break;
    }

    }
    PC++;

  }
  return 0;
}
