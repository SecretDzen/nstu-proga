#include <stdio.h>
#include <windows.h>
#include <string.h>

#define SIZE 256
#define LAB_TEMP "./lab1/input.text"

int delete_spaces(char* str, const char* pair);

int main(int argc, char* argv[]) {
    HANDLE fIn, fOut;
    DWORD bytesIn, bytesOut;
    char str[SIZE], newStr[SIZE];

    if (argc != 3) {
      printf("Wrong params number.\n");
      printf("\t<prog_name> <file_name> <space_numbers>\n");
      return -1;
    }

	if (strlen(argv[2]) < 1) {
      printf("Expected a positive number of spaces to delete in 2nd param.\n");
      printf("\tWrong param: %s (%lld)\n", argv[2], strlen(argv[2]));
      return -1;
    }

    fIn = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (fIn == INVALID_HANDLE_VALUE) {
      printf("===OPEN ERROR===\nCannot find file: %s\n", argv[1]);
      printf("ERROR CODE: %lx\n", GetLastError());
      return -1;
    }

    fOut = CreateFile(LAB_TEMP, GENERIC_WRITE, 0, NULL,
                        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (fOut == INVALID_HANDLE_VALUE) {
      printf("===CREATE ERROR===\n Cannot create file: %s\n", LAB_TEMP);
      printf("ERROR CODE: %lx\n", GetLastError());
      CloseHandle(fIn);
      return -1;
    }

    while (ReadFile(fIn, str, SIZE, &bytesIn, NULL) && bytesIn > 0) {
        int counter = 0;
        int len = strlen(str);
        int stopFlag = (int) *argv[2] - 48;

        for (int i = 0; i < len; i++) {
            if (str[i] == ' ' && counter != stopFlag) counter++;
            else newStr[i - counter] = str[i];
        }
        if (!WriteFile(fOut, newStr, bytesIn - counter, &bytesOut, NULL)) {
        printf("Wild Error Apeared! ");
        printf("ERROR CODE: %lx\n", GetLastError());
        }
    }    
    CloseHandle(fIn);
    CloseHandle(fOut);
    return 0;
}
