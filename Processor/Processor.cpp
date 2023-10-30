#include <stdio.h>
#include "Processor_funcs.h"

int main() {
    char input_name[100] = "";
    scanf("%s", input_name);
    processing(input_name);
    return 0;
}
