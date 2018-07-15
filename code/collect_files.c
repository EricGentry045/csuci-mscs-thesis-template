#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void listdir(const char *name)
{
  DIR *dir;
  struct dirent *entry;
  if (!(dir = opendir(name)))
  {
    return;
  }
  while ((entry = readdir(dir)) != NULL)
  {
    if (entry->d_type == DT_DIR)
    {
      char path[1024];
      if (strncmp(entry->d_name, ".", 1) == 0 || strncmp(entry->d_name, "..", 2) == 0)
      {
        continue;
      }
      snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
      listdir(path);
    }
    else
    {
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