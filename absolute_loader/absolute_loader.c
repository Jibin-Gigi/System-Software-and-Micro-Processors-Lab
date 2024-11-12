#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *header, *text, *output;
    char header_record[50], line[100];

    header = fopen("header.txt", "r");
    text = fopen("text.txt", "r");
    output = fopen("output.txt", "w");

    if (header == NULL || text == NULL || output == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fscanf(header, "%s", header_record);
    char prgm_name[7];
    int j = 0;
    for (int i = 2; i < 8; i++) {
        prgm_name[j++] = header_record[i];
    }
    prgm_name[j] = '\0';

    fprintf(output, "Program name is %s\n", prgm_name);

    while (fgets(line, sizeof(line), text) != NULL) {
        if (line[0] == 'T') {
            char start[7];
            j = 0;
            for (int i = 2; i < 8; i++) {
                start[j++] = line[i];
            }
            start[j] = '\0';

            int address = strtol(start, NULL, 16);

            for (int i = 12; i < strlen(line); i += 2) {
                if (line[i] == '^') {
                    i -= 1;
                    continue;
                }
                
                char byte_str[3] = {line[i], line[i + 1], '\0'};
                int byte_value = strtol(byte_str, NULL, 16);

                fprintf(output, "%04x : %02x\n", address++, byte_value);
            }
        }
    }

    fclose(header);
    fclose(text);
    fclose(output);

    return 0;
}