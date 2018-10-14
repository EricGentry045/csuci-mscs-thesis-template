/*
 * collect_files
 * 
 * created for the SEAKER project
 * California State University Channel Islands
 * 2018
 * Original Author: Eric Gentry
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void listdir(const char *name)
{
  DIR *dir;
  struct dirent *entry;
  struct stat path_stat;
  if (!(dir = opendir(name)))
  {
    // failure to run opendir
    // this would most likely be caused by an unsupported drive format
    return;
  }
  while ((entry = readdir(dir)) != NULL)
  {
    // make the full filename
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

    // the first part works with most drive types, except exFat... the second part fixes that
    if (entry->d_type == DT_DIR || (stat(path, &path_stat)==0 && S_ISDIR(path_stat.st_mode)))
    {
      if (strncmp(entry->d_name, ".", 1) == 0 || strncmp(entry->d_name, "..", 2) == 0)
      {
        // skip recording entries for current and parent directories
        continue;
      }

      // this is a directory, so walk that path...
      listdir(path);
    }
    else
    {
      // just print the filename
      printf("%s/%s\n", name, entry->d_name);
    }
  }
  closedir(dir);
}

int main(void)
{
  listdir(".");
  return 0;
}