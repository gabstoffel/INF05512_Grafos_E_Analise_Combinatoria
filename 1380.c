#include <stdio.h>
#include <string.h>

int pisanoPeriod(int m) {
    
    int fn_1 = 0;
    int fn = 1;
    int result = 0;
    int pisPeriod = m % 1500;

    if(pisPeriod == 1 || pisPeriod == 0)
        return pisPeriod;
        
    for (int i = 0; i < pisPeriod - 1; i++) {

        result = fn + fn_1;
        fn_1 = fn;
        fn = result % 1000;

    }

    return result % 1000;
}


int main()
{

    int t = 0;
    int k = 0;
    int result = 0;


    scanf("%d", &t);
    char kString[1000000];
    while (t--) {
        k = 0;
        scanf("%s", &kString);
        
        for(int j=0; j < strlen(kString); j++){
            k = k * 10 + (kString[j] - 48);
            k = k % 1500;
        }
        result = pisanoPeriod(k);
        printf("%03d\n", result);

    }
    return 0;
}
