#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[256];
  int age;
  float height;
} person;

int print_info(person* p) {
  printf("%s is %d years old and %f feet tall.\n", 
    p->name, p->age, p->height);
  return 0;
}

int main(int argc, char** argv)
{
  FILE* my_file  = NULL;
  char* filename = argv[1];
  char buffer[256];
  
  if (NULL == (my_file = fopen(filename, "r"))) {
    printf("womp: failed to open %s\n", filename);
    exit(-1);
  }
  
  while (fgets(buffer, 256, my_file) != NULL) {
    char name[256];
    int age = 0;
    float height = 0.0;
    if (3 != sscanf(buffer, "%s %d %f", name, &age, &height)) {
      printf("womp: failed to parse line\n");
      exit(-1);
    }
    
    // allocate space on stack for your struct
    person a_person;
    strcpy(a_person.name, name);
    a_person.age = age;
    a_person.height = height;
    print_info(&a_person);
    
    // allocate space on heap for your struct
    // note the different ways we can access its data
    person* a_person_on_heap = (person*)malloc(sizeof(person));
    strcpy(a_person_on_heap->name, name);
    a_person_on_heap->age = age;
    (*a_person_on_heap).height = height;
    print_info(a_person_on_heap);
  }
  
  fclose(my_file);
  
  return 0;
}