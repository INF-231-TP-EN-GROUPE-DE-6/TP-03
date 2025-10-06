#include <stdio.h>
int main(){
    FILE *f = fopen ("/home/boyz/School_projects/TP-03/ppmviewer/Images/test2.ppm","r");
    char ligne[100];
    while (fgets(ligne, sizeof(ligne), f)){
        printf("%s",ligne);
    }
}