#include <openssl/md5.h>
#include <uuid/uuid.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  // Ensure we have enough arguments
  if(argc < 3) return(1);

  // Fetch the arguments and their length
  char * unique_id = argv[1];
  char * accountcode = argv[2];
  int unique_id_length = strlen(unique_id);
  int accountcode_length = strlen(accountcode);

  // Allocate a string and copy the 2 arguments into it
  int string_length = unique_id_length+accountcode_length+1;
  char * string = malloc(string_length);
  memcpy(string, unique_id, unique_id_length);
  string[unique_id_length] = '-';
  memcpy(string + unique_id_length + 1, accountcode, accountcode_length);

  // Allocate memory for the MD5 hash and its UUID string
  unsigned char hash[16];
  unsigned char uuid[37];
  MD5(string, string_length, hash);
  uuid_unparse(hash, uuid);
  printf("SET VARIABLE CALL_UUID %s\n", uuid);
  return(0);
}
