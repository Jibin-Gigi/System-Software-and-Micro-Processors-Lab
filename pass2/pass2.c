#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void string_to_hex(const char* input, char* hex_value) {
    while (*input) {
        sprintf(hex_value, "%02X", (unsigned char) *input);
        input++;
        hex_value += 2;
    }
}

int main() {
    FILE *intermediate, *optab, *length_size, *symtab, *header, *text, *end, *output;
    char label[20], opcode[20], operand[20], object_code[20], address[20];
    char optab_data[20], optab_hex[4], symtab_symbol[20], symtab_address[5];
    bool opcode_found, symbol_found;

    intermediate = fopen("intermediate.txt", "r");
    optab = fopen("optab.txt", "r");
    length_size = fopen("prgm_length_size.txt", "r");
    symtab = fopen("symtab.txt", "r");
    header = fopen("header.txt", "w");
    text = fopen("text.txt", "w");
    end = fopen("end.txt", "w");
    output = fopen("output.txt", "w");

    int prgm_length = 0x00;
    int txt_size = 0x00;

    //reading first line
    fscanf(intermediate, "%s %s %s %s", address, label, opcode, operand);
    fscanf(length_size, "%x %x", &prgm_length, &txt_size);

    int counter = txt_size;

    fprintf(header, "H ^ 00%s ^ %06X ^ %06X\n", label, strtol(operand, NULL, 16), prgm_length);
    fprintf(end, "E ^ %06X\n", strtol(operand, NULL, 16));
    fprintf(text, "T ^ %06X ^ %02X", strtol(operand, NULL, 16), txt_size);

    fprintf(output, "%-7s %-7s %-7s %-7s\n", address, label, opcode, operand);
    fscanf(intermediate, "%s %s %s %s", address, label, opcode, operand);

    while (strcmp(opcode, "END") != 0) {
        rewind(optab);
        opcode_found = false;
        strcpy(object_code, "000000");

        // Searching in OPTAB
        while (fscanf(optab, "%s %s", optab_data, optab_hex) != EOF) {
            if (strcmp(optab_data, opcode) == 0) {
                opcode_found = true;
                rewind(symtab);
                symbol_found = false;

                // Searching in SYMTAB
                while (fscanf(symtab, "%s %s", symtab_symbol, symtab_address) != EOF) {
                    if (strcmp(symtab_symbol, operand) == 0) {
                        sprintf(object_code, "%s%s", optab_hex, symtab_address);
                        symbol_found = true;
                        break;
                    }
                }
                break;
            }
        }

        // Handling BYTE and WORD directives
        if (!opcode_found || !symbol_found) {
            if (strcmp(opcode, "BYTE") == 0) {
                char demo_str[20];
                int j = 0;
                for (int i = 2; i < strlen(operand) - 1; i++) {
                    demo_str[j++] = operand[i];
                }
                demo_str[j] = '\0';

                if (operand[0] == 'X') {
                    strcpy(object_code, demo_str);
                } else if (operand[0] == 'C') {
                    string_to_hex(demo_str, object_code);
                }

            } else if (strcmp(opcode, "WORD") == 0) {
                sprintf(object_code, "%06X", atoi(operand));

            } else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0) {
                strcpy(object_code, "");
            }
        }

        fprintf(output, "%-7s %-7s %-7s %-7s %s\n", address, label, opcode, operand, object_code);
        if (strlen(object_code) > 0) {
            fprintf(text, " %s ^", object_code);
            counter -= (strlen(object_code) / 2);
        }

        fscanf(intermediate, "%s %s %s %s", address, label, opcode, operand);

        if (counter <= 0) {
            fprintf(text, "\nT ^ %06X ^ %02X", strtol(address, NULL, 16), txt_size);
            counter = txt_size;
        }
    }

    fclose(intermediate);
    fclose(optab);
    fclose(length_size);
    fclose(symtab);
    fclose(header);
    fclose(text);
    fclose(end);
    fclose(output);

    return 0;
}
