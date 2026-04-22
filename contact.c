#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGTH 100

typedef struct Contact {
  char name[INPUT_LENGTH];
  char address[INPUT_LENGTH];
  char email[INPUT_LENGTH];
  char number[INPUT_LENGTH];
} Contact;

Contact contact_array[100];
char *contactFILE = "contact_book_data.csv";

int read_from_csv(Contact contact_array[]);
void print_contact(const Contact *contact);
void trim_newline(char *str);
int add_new_entry(); 
void showHelp();
int list_contacts();

int main() {
  char choice_buffer;
  int running = 1;

  printf("----Welcome to the contact book----/n");
  showHelp();

  while (running) {
    printf("Enter command (a/l/h/q): ");

    scanf("%a", &choice_buffer);
        
      char cmd = tolower(choice_buffer);

    switch(cmd) {
      case 'a' :
      add_new_entry();
      break;

      case 'l' :
      list_contacts();
      break;

      case 'q' :
      printf("Goodbye!\n");
      running = 0;
      break;

      default:
      printf("Not a known command! retry.");
      break;
    }
  }

  return 0;
}

int add_new_entry() {
  FILE *fptr;

  fptr = fopen(contactFILE, "a");

  char name[INPUT_LENGTH];
  char address[INPUT_LENGTH];
  char email[INPUT_LENGTH];
  char number[INPUT_LENGTH];

  // Enter name
  printf("Enter name: \n");
  fgets(name, INPUT_LENGTH, stdin); trim_newline(name);

  // Enter address
  printf("Enter address: \n");
  fgets(address, INPUT_LENGTH, stdin); trim_newline(address);

  // Enter email
  printf("Enter email: \n");
  fgets(email, INPUT_LENGTH, stdin); trim_newline(email);

  // Enter number
  printf("Enter number: \n");
  fgets(number, INPUT_LENGTH, stdin); trim_newline(number);

  // Append
  fprintf(fptr, "\n%s,%s,%s,%s", name, address, email, number);
  fclose(fptr); // Close

  printf("\nSaved contact!\n\n");

  return 0;
}

int list_contacts() {
  int contact_count = read_from_csv(contact_array);

  if (contact_count == 0) {
    printf("No contacts found or file is empty.");
    return 0;
  }

  printf("\n----Contacts Found-----\n");
  for (int i = 0; i < contact_count; i++) { 
    print_contact(&contact_array[i]); 
  }                    

  return 0;
}

void print_contact(const Contact *contact) {
  printf("Name: %s\n", contact->name);
  printf("Address: %s\n", contact->address);
  printf("Email: %s\n", contact->email);
  printf("Number: %s\n", contact->number);
  printf("\n");
}

void showHelp() {
  printf("\n Commands:\n");
  printf("a - Add new contact\n");
  printf("l - list of all contacts\n");
  printf("h - show this interface\n");
  printf("q - quit\n");
}

void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int read_from_csv(Contact contact_array[]) {
  FILE *fptr =fopen(contactFILE, "r");

  if (fptr == NULL) {
    return 0;
  }
  

  char buffer[(INPUT_LENGTH * 4 + 5)]; 
                        
  int i = 0; 

  while(fgets(buffer, sizeof(buffer), fptr)) {
    
    trim_newline(buffer);
    char *field = strtok(buffer, ",");
    int x = 0;

    while (field != NULL) {
      if (x == 0) {
        strncpy(contact_array[i].name, field, INPUT_LENGTH-1);
      } else if (x == 1) {
        strncpy(contact_array[i].address, field, INPUT_LENGTH-1);
      } else if (x == 2) {
        strncpy(contact_array[i].email, field, INPUT_LENGTH - 1);
      } else if (x == 3) {
        strncpy(contact_array[i].number, field, INPUT_LENGTH - 1);
      }
      
      x++;
       field = strtok(NULL, ",");
    }
    i++;
    
  }  


  fclose(fptr);

  return i;
}