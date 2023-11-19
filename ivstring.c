

#ifndef IVSTRING_HEADER
#define IVSTRING_HEADER

#include <bits/pthreadtypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct ivstring{
  uint64_t size;
  char *data;
} iv_string_t;

typedef struct ivmultistring {
  uint64_t size;
  uint64_t capacity;
  iv_string_t **multidata;
} iv_multistring_t;

iv_string_t *
iv_string(const char *name) {
   iv_string_t *iv_string = malloc(sizeof(iv_string_t)); 
   if (!iv_string) { 
     return NULL; 
   } 
  iv_string->size = strlen(name) + 1;
  iv_string->data = malloc(iv_string->size * sizeof(char));
  if (!iv_string->data)
    return NULL;

  memset(iv_string->data, 0, iv_string->size);
  memcpy(iv_string->data, name, iv_string->size);
    
  return iv_string;
}

void 
iv_string_free(iv_string_t * iv_string) {
  if (iv_string != NULL) {
    free(iv_string->data);
    free(iv_string);
  }
}

const char *
iv_string_c(iv_string_t *iv_string) {
  if (iv_string && iv_string->data)  {
    return iv_string->data;
  }
  return NULL;
}

iv_string_t *
iv_string_append(iv_string_t *string, const char *cstr) {
  if (!cstr)
    return NULL;

  uint64_t ivstring_size = string->size;
  uint64_t cstr_size = strlen(cstr);

  string->size = ivstring_size + cstr_size + 1;
  string->data = realloc(string->data, string->size * sizeof(char));
  if (!string->data)
    return NULL;

  // -1 to overwrite the '\0' of the string->data before
  memcpy(string->data + ivstring_size - 1, cstr, cstr_size);
  string->data[string->size - 1] = '\0';

  return string;
}

iv_multistring_t *
iv_string_split(iv_string_t *string, const char *delim) {

  const int max_strings = 10000000;
  iv_multistring_t * ivmultistring = malloc(sizeof(iv_multistring_t));
  if (!ivmultistring) return NULL;

  ivmultistring->multidata = malloc(max_strings * sizeof(iv_string_t*));
  if (!ivmultistring->multidata) {
    return NULL;
  }
  char *saveptr = NULL;
  char *ptr = strtok_r(string->data, delim, &saveptr);
  if (!ptr) {
    return NULL;
  }

  ivmultistring->multidata[0] = iv_string(ptr);

  int index = 1;
  while ((ptr = strtok_r(NULL, delim, &saveptr))) {
    ivmultistring->multidata[index] = iv_string(ptr);
    index++;
  }
  ivmultistring->size = index;

#ifdef DEBUG
  char ch = getchar();
#endif

#ifdef FAST
  puts("OPTIMIZING!!!!");
  ivmultistring->multidata = realloc(ivmultistring->multidata, index * sizeof(iv_string_t*));
#endif

  return ivmultistring;
}

iv_multistring_t *
iv_multistring() {
  iv_multistring_t *multistring = malloc(sizeof(iv_multistring_t));
  if (!multistring) return NULL;
  const int n = 10;
  multistring->size = 0;
  multistring->capacity = n;
  multistring->multidata = malloc(n * sizeof(iv_string_t*));

  return multistring;
}

iv_multistring_t *
iv_multistring_add(iv_multistring_t * multistring) {
  if (multistring->multidata[multistring->size - 1] == NULL) {
    multistring->multidata = malloc()
  }
  return multistring;
}

iv_string_t *
iv_multistring_at(iv_multistring_t *multistring, int64_t index) {
  if (multistring) {
    if (index >= multistring->size) {
      return NULL;
    }
    return multistring->multidata[index];
  }
  return NULL;
}



iv_string_t *
iv_multistring_join(iv_multistring_t *multistring, const char *delim) {
  iv_string_t * string = iv_multistring_at(multistring, 0);
  iv_string_append(string, delim);
  for (int i = 1; i < multistring->size; i++) {
    iv_string_append(string, iv_string_c(iv_multistring_at(multistring, i)));
    iv_string_append(string, delim);
  }
  string->data[string->size - 1] = 0;
  return string;
}

char
iv_string_at(iv_string_t *string, int64_t index) {
  if (string) {
    if (index < 0 || index >= string->size) {
      return '0';
    } 
    return string->data[0];
  }
  return 0;
}
void
iv_multistring_free(iv_multistring_t *multistring) {
  if (multistring) {
    if (multistring->multidata){
      for (int i = 0; i < multistring->size; i++){
        iv_string_t * str = iv_multistring_at(multistring, i);
        iv_string_free(str);
      }
      free(multistring->multidata);
    }
    free(multistring);
  }
}



/* iv_multistring_t  */
/* iv_string_split(iv_string_t * string, const char * delim) { */
/*   if (!string || !delim) { */
/*     return NULL; */
/*   } */
/*   iv_string_t **multi_string = malloc(100 * sizeof(iv_string_t *)); */
/*   if (!multi_string) { */
/*     return NULL; */
/*   } */
/*   int i = 0; */
/*   char *saveptr = NULL; */
/*   char * ptr = strtok_r(string->data, delim, &saveptr); */
/*   multi_string[0] = ptr; */
/*   for (; i < 100; i++) { */

/*   } */
/*   char *saveptr; */


/* } */



#endif
