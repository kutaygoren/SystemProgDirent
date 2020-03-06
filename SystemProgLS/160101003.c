#include "160101003.h"

int main(int argc, char *argv[])
{
  //ls
  if(argc == 2)
  {
    dir(argv[1],0);
  }

  //ls -d $PWD/*
  else if(argc == 3 && strcmp(argv[1],"-d") == 0)
  {
    dirD(argv[2],0);
  }

  else if(argc == 3 && strcmp(argv[1],"out.txt") == 0)
  {
    dirOut(argv[2],0);
  }

  else if(argc == 3 && strcmp(argv[1],"-r") == 0)
  {
    dirRev(argv[2],0);
  }

  return(0);
}
