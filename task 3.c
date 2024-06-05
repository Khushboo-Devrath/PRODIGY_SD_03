#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "contacts.txt"
#define NAME_LEN 50
#define PHONE_LEN 11
#define EMAIL_LEN 30

typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

void add_contact_no();
void view_contacts_no();
void edit_contact_no();
void delete_contact_no();
void save_contact_no(Contact contact);

int main() {
    int choice;

    while (1) {
        printf("\nYour Contact Management System\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                add_contact_no();
                break;
            case 2:
                view_contacts_no();
                break;
            case 3:
                edit_contact_no();
                break;
            case 4:
                delete_contact_no();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void add_contact_no() {
    Contact contact;

    printf("Enter name: ");
    fgets(contact.name, NAME_LEN, stdin);
    contact.name[strcspn(contact.name, "\n")] = 0;  // remove newline character

    printf("Enter phone number: ");
    fgets(contact.phone, PHONE_LEN, stdin);
    contact.phone[strcspn(contact.phone, "\n")] = 0;  // remove newline character

    printf("Enter email address: ");
    fgets(contact.email, EMAIL_LEN, stdin);
    contact.email[strcspn(contact.email, "\n")] = 0;  // remove newline character

    save_contact_no(contact);
    printf("Contact added successfully.\n");
}

void save_contact_no(Contact contact) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s\n", contact.name, contact.phone, contact.email);
    fclose(file);
}

void view_contacts_no() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No contacts found.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, "\n");

        printf("Name: %s\nPhone: %s\nEmail: %s\n", name, phone, email);
        printf("------------------------\n");
    }

    fclose(file);
}

void edit_contact_no() {
    char name[NAME_LEN];
    Contact contact;
    int found = 0;

    printf("Enter the name of the contact to edit: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;  
    
    FILE *file = fopen(FILENAME, "r");
    FILE *tempfile = fopen("temp.txt", "w");

    if (file == NULL || tempfile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *stored_name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, "\n");

        if (strcmp(stored_name, name) == 0) {
            found = 1;

            printf("Enter new phone number: ");
            fgets(contact.phone, PHONE_LEN, stdin);
            contact.phone[strcspn(contact.phone, "\n")] = 0;  // remove newline character

            printf("Enter new email address: ");
            fgets(contact.email, EMAIL_LEN, stdin);
            contact.email[strcspn(contact.email, "\n")] = 0;  // remove newline character

            fprintf(tempfile, "%s,%s,%s\n", stored_name, contact.phone, contact.email);
        } else {
            fprintf(tempfile, "%s,%s,%s\n", stored_name, phone, email);
        }
    }

    fclose(file);
    fclose(tempfile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Contact edited successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}

void delete_contact_no() {
    char name[NAME_LEN];
    int found = 0;

    printf("Enter the name of the contact to delete: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;  // remove newline character

    FILE *file = fopen(FILENAME, "r");
    FILE *tempfile = fopen("temp.txt", "w");

    if (file == NULL || tempfile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *stored_name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, "\n");

        if (strcmp(stored_name, name) != 0) {
            fprintf(tempfile, "%s,%s,%s\n", stored_name, phone, email);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempfile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}

