#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Assembler_funcs.h"

int main() {
    char input_name[100] = "";
    char output_name[100] = "";
    scanf("%s %s", input_name, output_name);
    assembler_translate(input_name, output_name);
    return 0;
}
