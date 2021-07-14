#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <conio.h>
#include <sys/stat.h>
#include <windows.h>
#include <time.h>
#include <string.h>

DIR *directory;
struct dirent *dirContent;
char fileList[100][50];

clock_t startTime;

int *toBeSorted;

int option, file;

char line[256];

double finTime;

struct stat checkFolder = {0};

void getTime() {
    startTime = clock() - startTime;
    finTime = ((double)startTime)/CLOCKS_PER_SEC;
}

void printTime() {
    printf("\n\nTime elapsed: %.4f", finTime);
}

void setTime() {
    startTime = clock();
}

void clr() {
    system("cls");
}

void decrescentOrdering(int *rawLine, int len) {
    
    clr();
    printf("\n\ninput array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", rawLine[i]);
    }
    setTime();

    //sorting
    for (int i = len; i > 0; i--)
    {
        for (int x = i;  x >= 0; x--)
        {
            if (rawLine[x] == rawLine[x-1])
            {
                continue;
            } 
            else if (rawLine[x] < rawLine[x-1]) 
            {
                int temp = rawLine[x-1];
                rawLine[x-1] = rawLine[x];
                rawLine[x] = temp;
            }
            else
            {
                break;
            }
        }
    }

    getTime();

    //print
    printf("\n\noutput: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", rawLine[i]);
    }

    printTime();

    getchar();
}

void dicotonicSearch(int *rawLine, int len) {

    clr();
    printf("\nEnter value to search: ");
    int search;
    scanf("%d", &search);

    for (int i = len; i > 0; i--)
    {
        for (int x = 0;  x < i; x++)
        {
            if (rawLine[x] > rawLine[x+1])
            {
                int temp = rawLine[x+1];
                rawLine[x+1] = rawLine[x];
                rawLine[x] = temp;
            }
        }
    }

    printf("\n\ninput array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", rawLine[i]);
    }

    setTime();

    int x, y, out;
    x = 0;
    y = len;
    out = -1;
    while (x <= y)
    {
        int i = (int)(x+y)/2;
            if (rawLine[i] == search)
            {
                out = i;
                break;
            } else if(search > rawLine[i]) {
                x = i+1;
            } else if(search < rawLine[i]) {
                y = i-1;
            }
    }

    getTime();

    if (out != -1)
    {
        printf("\n\nFound %d at position %d", search, out);
    } else {
        printf("\n\nResearched number has not been found");
    }
    
    printTime();
    
    getchar();
}

void bubbleSort(int *rawLine, int len) {

    clr();
    printf("\n\ninput array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", rawLine[i]);
    }

    //sorting   

    for (int i = len; i > 0; i--)
    {
        for (int x = 0;  x < i; x++)
        {
            if (rawLine[x] > rawLine[x+1])
            {
                int temp = rawLine[x+1];
                rawLine[x+1] = rawLine[x];
                rawLine[x] = temp;
            }
        }
    }

    getTime();
    
    printf("\n\noutput array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", rawLine[i]);
    }

    printTime();

    printf("\n\nPress Enter to go back to main menu");
    getchar();
    return;
}

void main() {
    int a = 1;

    while (a)
    {
                clr();
        printf("_________________________________________________________\n\n");
        printf("Welcome to Array Sorter written in C by XEDGit\n\n");
        printf("\tChoose an option: (1: Bubble Sorting |2: Dicotonic search |3: W.I.P. Decrescent Ordering)\n\t");
        int x;
        scanf("%d", &x);
        if (x > 3 || x< 0)
            continue;
        option = x;
        clr();

        if (stat("./Array Sorter Files", &checkFolder) == -1) {
            mkdir("./Array Sorter Files");
        }

        printf("_________________________________________________________\n\n");
        printf("\t\t  Array Sorter\n\n\n");

        directory = opendir("./Array Sorter Files");
        int label = 0;

        while ((dirContent = readdir(directory)) != NULL)
        {
            printf("\t%d\t", label);
            strcpy(fileList[label], dirContent->d_name);
            printf("%s\n", dirContent->d_name);
            label += 1;
        }
        printf("\t%d\tBack\n\n", label);
            
        closedir(directory);
        printf("\tChoose file number:\n");
        int y;
        scanf("\t%d", &file);

        while (file > label || file < 2)
        {
            printf("\tError. Insert valid file number:\n");
            printf("");
            scanf("\t%d", &file);
        }

        if (file == label)
        {
            label = 0;
            main();
            return;
        }

        label = 0;

        //get line
        char fullPath[50] = "./Array Sorter Files/";
        strcat(fullPath, fileList[file]);
        FILE *file = fopen(fullPath, "r");

        if (file == NULL)
        {
            clr();
            printf("error accessing file");
            getchar();
            return;
        }

        fgets(line, 256, file);
        fclose(file);

        //transform str[] in int[]
        int len = strlen(line);
        int numArray[100];
        int index = 0;
        int arrIndex = 0;
        int end = 0;

        while (line[index] != '\0') {

            end = 0;
            int out = 0;
            for (int i = 0; i < len+1; i++)
            {
                if (line[index+i] == ' ' || line[index+i] == '\0')
                {
                    end++;
                    i++;
                    index += i;
                    break;
                }

                out *= 10;
                out += (line[index+i] - '0');
            }

            numArray[arrIndex] = out;
            arrIndex++;
        }
        
        int *finArray = malloc(sizeof(int)*arrIndex);
        memcpy(finArray, numArray, sizeof(int)*arrIndex);

        setTime();

        switch (option)
        {
        case 1:
            bubbleSort(finArray, arrIndex);
            getchar();
            break;

        case 2:
            dicotonicSearch(finArray, arrIndex);
            getchar();
            break;

        // case 3:
        //     decrescentOrdering(finArray, arrIndex);
        //     getchar();
        //     break;

        default:
            break;
        }
    }
}
