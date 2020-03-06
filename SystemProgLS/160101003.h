#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

//ls -- Tüm subdirectoryler gösterilecek şekilde yapılmıştır.
void dir(char *directory,int depth)
{
    DIR *folder;
    struct dirent *entry;
    struct stat filestat;

    //İstenilen directoryde arama yapabilmek için chdir() fonksiyonu ile
    //directory değiştiriliyor.
    if(chdir(directory))
    {
        fprintf(stderr,"Error changing to %s\n",directory);
        exit(1);
    }

    //Directory değiştirildiği için değişmiş olan directoryi açıyor.
    folder = opendir(".");
    if(folder == NULL)
    {
        fprintf(stderr,"Unable to read directory %s\n",directory);
        exit(1);
    }

    printf("%*s%s\n",depth,"-",directory);

    //Subdirectoryler varsa recursive olarak subdirectoryleri açıyor.
    //Yani eğer bir subdirectory varsa o directory için dir() fonksiyonunu
    //tekrar çağırıyor ve subdirectoryler bitene kadar devam ediyor.
    while( (entry=readdir(folder)) )
    {
      stat(entry->d_name,&filestat);
      //Dosyanın directory olup olmadığının kontrolü S_ISDIR ile sağlanıyor.
      if( S_ISDIR(filestat.st_mode) )
      {
          //"." ve ".." kirliliği oluşmasın diye.
          if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
            continue;
          //Directory olduğundan tekrar çağırılıyor.
          dir(entry->d_name,depth+1);
      }

      //Directory olmadığı durumlarda dosya direkt olarak yazdırılıyor.
      else
        printf("%*s%s\n",depth+1,"-",entry->d_name);
    }

    chdir("..");
    closedir(folder);
}

//ls -d $PWD/* -- Yazılmış olan düz ls'ten tek farkı 2 tane getcwd
//fonksiyonu eklenmiştir.
void dirD(char *directory,int depth)
{
    DIR *folder;
    struct dirent *entry;
    struct stat filestat;
    char s[100];

    //İstenilen directoryde arama yapabilmek için chdir() fonksiyonu ile
    //directory değiştiriliyor.
    if(chdir(directory))
    {
      fprintf(stderr,"Error changing to %s\n",directory);
      exit(1);
    }

    //Directory değiştirildiği için değişmiş olan directoryi açıyor.
    folder = opendir(".");
    if(folder == NULL)
    {
      fprintf(stderr,"Unable to read directory %s\n",directory);
      exit(1);
    }

    printf("%s\n", getcwd(s, 100));

    //Subdirectoryler varsa recursive olarak subdirectoryleri açıyor.
    //Yani eğer bir subdirectory varsa o directory için dir() fonksiyonunu
    //tekrar çağırıyor ve subdirectoryler bitene kadar devam ediyor.
    while( (entry=readdir(folder)) )
    {
      stat(entry->d_name,&filestat);
      //Dosyanın directory olup olmadığının kontrolü S_ISDIR ile sağlanıyor.
      if( S_ISDIR(filestat.st_mode) )
      {
        //"." ve ".." kirliliği oluşmasın diye.
        if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
          continue;
        //Directory olduğundan tekrar çağırılıyor.
        dirD(entry->d_name,depth+1);
      }

      //Directory olmadığı durumlarda dosya direkt olarak yazdırılıyor.
      else
      {
        printf("%s/", getcwd(s, 100));
        printf("%s\n",entry->d_name);
      }
    }

    chdir("..");
    closedir(folder);
}

//ls > out.txt
void dirOut(char *directory,int depth)
{
    DIR *folder;
    struct dirent *entry;
    struct stat filestat;
    FILE* output = fopen("out.txt", "w");

    //İstenilen directoryde arama yapabilmek için chdir() fonksiyonu ile
    //directory değiştiriliyor.
    if(chdir(directory))
    {
        fprintf(stderr,"Error changing to %s\n",directory);
        exit(1);
    }

    //Directory değiştirildiği için değişmiş olan directoryi açıyor.
    folder = opendir(".");
    if(folder == NULL)
    {
        fprintf(stderr,"Unable to read directory %s\n",directory);
        exit(1);
    }

    while( (entry=readdir(folder)) )
    {
      if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
        continue;
      //Verilen dizindeki dosyaları out.txt'ye yazıyor.
      fprintf(output,"%s\n",entry->d_name);
    }

    chdir("..");
    fflush(output);
    fclose(output);
    closedir(folder);
}

void dirRev(char *directory,int depth)
{
    DIR *folder;
    struct dirent *entry;
    struct stat filestat;
    char *arr[100];
    int i = 0;

    //İstenilen directoryde arama yapabilmek için chdir() fonksiyonu ile
    //directory değiştiriliyor.
    if(chdir(directory))
    {
        fprintf(stderr,"Error changing to %s\n",directory);
        exit(1);
    }

    //Directory değiştirildiği için değişmiş olan directoryi açıyor.
    folder = opendir(".");
    if(folder == NULL)
    {
        fprintf(stderr,"Unable to read directory %s\n",directory);
        exit(1);
    }

    while( (entry=readdir(folder)) )
    {
      if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
      {
        continue;
      }

      arr[i] = malloc (1 + strlen(entry->d_name));
      strcpy(arr[i], entry->d_name);
      //printf("%s\n", arr[i]); Normal sıra ile sıralanması.
      i++;
    }

    for ( ; i > 0; i--) {
      printf("%s\n", arr[i-1]); //Reverse order.
      free(arr[i-1]); //Aynı zamanda ayrılmış memoryleri serbest bırakıyor.
    }

    chdir("..");
    closedir(folder);
}
