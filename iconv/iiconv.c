#include <stdio.h>
#include <memory.h>

int main()
{
  // 1. write file to in_file
  FILE* fp;
  char path[512]=".";
  int encode_type=1;    // UTF-8 -> IBM-1363
  char in_filename[512]="input.txt";
  char command[512];
  char out_msg[1024*60];

  // 1. write file to in_file
  #if 0
  fp = fopen(in_filename, "w");
  if( fp == NULL ){
    perror("fopen");
    return -1;
  }
  fwrite(in_msg, 1, in_len, fp);
  fclose(fp);
  #endif

  sprintf(command, "%s/iconv.sh %d %s", path, encode_type, in_filename );
  fp = popen(command, "r");
  if (fp == NULL){
    perror("popen");
    return -1;
  }


  // 2. read file from out_file
  char* pOut = (char*)out_msg;
  char buffer[1024+1];
  size_t len=0;
  size_t total_len=0;
  char out_filename[64];
  char *pResult = out_filename;
  memset(out_filename, 0, sizeof(out_filename));

  pResult = fgets(out_filename, sizeof(out_filename)-1, fp);
  if( pResult == (char*)NULL){
          perror("fgets");
          return -1;
  }
  printf ("Result : %s\n", out_filename);
  if( strncmp(out_filename, "FAIL", 4) == 0 ){
          printf("Failed to convert\n");
          pclose(fp);
          return -1;
  }

  int status = pclose(fp);
  if (status == -1) {
          perror("Error closing pipe");
          return -1;
  }

  memset(out_msg, 0, sizeof(out_msg));
  fp = fopen(out_filename, "r");
  if( fp == NULL ){
          perror("fopen");
          return -1;
  }

  while(1) {
          len=fread(buffer, 1, 1024, fp);
          if( len == 0 ) break;
          memcpy(pOut, buffer, len);
          total_len += len;
          pOut += len;
  }

  printf ("Total length : %d\n", (int)total_len);
  printf ("Result : %s\n", out_msg);

  fclose(fp);
  unlink(out_filename);

  return 0;
}

