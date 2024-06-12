#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp = fopen("random.txt", "a");
    int queue[8] = {0,};

    srand(time(NULL));

    for(int i = 0; i < 8; i++) {
        queue[i] = (rand() % 199) + 1;
        if (i < 7) {
            printf("%d, ", queue[i]);
            fprintf(fp, "%d, ", queue[i]);
        }
        else fprintf(fp, "%d\n", queue[i]);
        
    }
    printf("\n");

    
    fclose(fp);
    return 0;
}