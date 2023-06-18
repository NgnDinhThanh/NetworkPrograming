#include <stdio.h>
#include <dirent.h>
#include <string.h>

 int main() 
 {

    DIR * dir = opendir(".");
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry ->d_type == DT_REG)
        {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
 }