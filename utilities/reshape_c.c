#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include<string.h>

const int a = 100;
int main()
{
    FILE *f_read; //file to be read
    FILE *f_write; //file to be written
    double myvariable;
    f_read = fopen("foobar_read.CSV", "r"); //opens read file
    if (f_read == NULL)
    {
        printf("Error reading file\n");
        return 1;
    }
    else
    {
        printf("Reading file\n");
    }

    double merda1, merda2, lastz;

    //reads the first three values in order to memorize the first temperature
    fscanf(f_read, "%lf", &merda1);
    fscanf(f_read, "%lf", &merda2);
    fscanf(f_read, "%lf", &lastz);
    
    fclose(f_read); //closes read file
    f_read = fopen("foobar_read.CSV", "r"); //and reopens it
    if (f_read == NULL)
    {
        printf("Error reading file\n");
        return 1;
    }
    else
    {
        printf("Reading file\n");
    }

    f_write = fopen("foobar_write.csv", "w"); //open writing file
    
    int i=0;
    
    double x0,y0,z0,gama0;
    double x1,y1,z1,gama1;
    int check=0;
    
    while (!feof(stdin))
    {
        fscanf(f_read,"%lf",&x0);
        fscanf(f_read,"%lf",&y0);
        if (feof(f_read))
        {
            printf("Eccheccazzo"); //end of file
            break;
        }
        fscanf(f_read,"%lf",&z0);
        fscanf(f_read,"%lf",&gama0);
        fscanf(f_read,"%lf",&x1);
        fscanf(f_read,"%lf",&y1);
        fscanf(f_read,"%lf",&z1);
        fscanf(f_read,"%lf",&gama1);
        
        if(z0!=lastz) //if the values in the position of temperatures
        {//are different
            printf("%15f",lastz);
            y0 = gama0;
            z0= x1;
            gama0 = y1;
            x1 = z1;
            y1 = gama1;
            fscanf(f_read, "%lf", &z1);
            fscanf(f_read, "%lf", &gama1);
        }
        
        lastz = z0; //memorizes last temperature value

        //and if the free energy value is less or equal to zero...
        if (y0 <= 0)
        {
            fprintf(f_write,"{{%.30lf,%.30lf,%.30lf},%.30lf}\n", x0, y0, z0, gama0);
        }
        if (y1 <= 0)
        {
            fprintf(f_write,"{{%.30lf,%.30lf,%.30lf},%.30lf}\n", x1, y1, z1, gama1);
        }
    }

    fclose(f_read);
    fclose(f_write);
    
    return 0;
}
