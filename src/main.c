#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  puts( "Ivy (version 0.1)\n"
        "Type 'q' for quit\n"); 
  while (1) {
    printf("> ");
    fflush(stdout);
    char inp[256];
    fgets(inp, sizeof(inp), stdin);
    if (strcmp(inp, "q\n") == 0) {
      break;
    }
  }
  return 0;
}
