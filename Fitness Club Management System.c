#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer {
    int reg_no;
    char name[50];
    char mobile_no[20];
    float bmi;
    char address[100];
    char package[20];
    char join_date[20];
};

void add_customer() {
    struct customer c;
    FILE *fp;
    int last_reg_no = 0;
    char line[200];

    fp = fopen("customer_records.txt", "r");

    // Read the last registration number from the file
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d", &last_reg_no);
    }

    fclose(fp);

    fp = fopen("customer_records.txt", "a");

    printf("Enter customer name: ");
    scanf(" %[^\n]", c.name); // use %[^\n] to read string with spaces

    printf("Enter customer mobile number: ");
    scanf(" %[^\n]", c.mobile_no); // use %[^\n] to read string with spaces


    printf("Enter customer BMI: ");
    scanf("%f", &c.bmi);

    printf("Enter customer address: ");
    scanf(" %[^\n]", c.address); // use %[^\n] to read string with spaces

    printf("Available packages: Gold, Silver, Platinum\n");
    int valid_package = 0;
    while (!valid_package) {
        printf("Enter customer package (Gold/Silver/Platinum): ");
        scanf("%s", c.package);
        if (strcmp(c.package, "Gold") == 0 || strcmp(c.package, "Silver") == 0 || strcmp(c.package, "Platinum") == 0) {
            valid_package = 1;
        } else {
            printf("Invalid package. Please choose Gold, Silver, or Platinum.\n");
        }
    }

    printf("Enter customer join date (DD/MM/YYYY): ");
    scanf("%s", c.join_date);

    // Generate unique registration number by incrementing the last registration number
    c.reg_no = last_reg_no + 1;

    fprintf(fp, "%d\t%s\t%s\t%.2f\t%s\t%s\t%s\n", c.reg_no, c.name, c.mobile_no, c.bmi, c.address, c.package, c.join_date);

    fclose(fp);

    printf("Customer details added successfully. Registration number: %d\n", c.reg_no);
}


void book_slot() {
    int slot_choice, num_booked;
    char line[256];
    FILE *fp;
    printf("Enter customer registration number: ");
    int reg_no;
    scanf("%d", &reg_no);
    // Get customer data from file
    fp = fopen("customer_records.txt", "r");
    int found_customer = 0;
    while (fgets(line, sizeof(line), fp)) {
        struct customer c;
        sscanf(line, "%d\t%s\t%s\t%f\t%s\t%s\t%s", &c.reg_no, c.name, c.mobile_no, &c.bmi, c.address, c.package, c.join_date);
        if (c.reg_no == reg_no) {
            printf("Customer found: %s\n", c.name);
            found_customer = 1;
            printf("Available time slots:\n");
            printf("1. 10:00 AM - 11:00 AM\n");
            printf("2. 11:00 AM - 12:00 PM\n");
            printf("3. 12:00 PM - 01:00 PM\n");
            printf("4. 01:00 PM - 02:00 PM\n");
            printf("5. 02:00 PM - 03:00 PM\n");
            printf("6. 03:00 PM - 04:00 PM\n");
            printf("Enter slot choice: ");
            scanf("%d", &slot_choice);
            // Check if slot is full (booked by 10 people)
            fp = fopen("slot_records.txt", "r");
            num_booked = 0;
            while (fgets(line, sizeof(line), fp)) {
                int slot;
                sscanf(line, "%d", &slot);
                if (slot == slot_choice) {
                    num_booked++;
                }
            }
            fclose(fp);
            if (num_booked >= 10) {
                printf("This slot is already booked by 10 people. Please choose another slot.\n");
            } else {
                fp = fopen("slot_records.txt", "a");
                fprintf(fp, "%d\t%d\n", reg_no, slot_choice);
                fclose(fp);
                printf("Slot booked successfully.\n");
            }
        }
    }
    fclose(fp);
    if (!found_customer) {
        printf("Customer not found.\n");
    }
}

void display_records() {
    char line[256];
    FILE *fp, *slot_fp;

    fp = fopen("customer_records.txt", "r");
    printf("Customer records:\n");
    while (fgets(line, sizeof(line), fp)) {
        struct customer c;
        sscanf(line, "%d\t%s\t%s\t%f\t%s\t%s\t%s", &c.reg_no, c.name, c.mobile_no, &c.bmi, c.address, c.package, c.join_date);
        printf("Registration Number: %d\n", c.reg_no);
        printf("Name: %s\n", c.name);
        printf("Mobile Number: %s\n", c.mobile_no);
        printf("BMI: %.2f\n", c.bmi);
        printf("Address: %s\n", c.address);
        printf("Package: %s\n", c.package);
        printf("Join Date: %s\n", c.join_date);

        // Get booked slot from file
        slot_fp = fopen("slot_records.txt", "r");
        while (fgets(line, sizeof(line), slot_fp)) {
            int reg_no, slot_choice;
            sscanf(line, "%d\t%d", &reg_no, &slot_choice);
            if (reg_no == c.reg_no) {
                printf("Time slot booked: ");
                switch (slot_choice) {
                    case 1:
                        printf("10:00 AM - 11:00 AM");
                        break;
                    case 2:
                        printf("11:00 AM - 12:00 PM");
                        break;
                    case 3:
                        printf("12:00 PM - 01:00 PM");
                        break;
                    case 4:
                        printf("01:00 PM - 02:00 PM");
                        break;
                    case 5:
                        printf("02:00 PM - 03:00 PM");
                        break;
                    case 6:
                        printf("03:00 PM - 04:00 PM");
                        break;
                }
                printf("\n");
                break;
            }
        }
        fclose(slot_fp);

        printf("\n");
    }
    fclose(fp);
}


void search_customer() {
    int reg_no;
    printf("Enter customer registration number: ");
    scanf("%d", &reg_no);

    FILE *fp = fopen("customer_records.txt", "r");
    char line[256];
    int customer_found = 0;
    while (fgets(line, sizeof(line), fp)) {
        struct customer c;
        sscanf(line, "%d\t%s\t%s\t%f\t%s\t%s\t%s", &c.reg_no, c.name, c.mobile_no, &c.bmi, c.address, c.package, c.join_date);
        if (c.reg_no == reg_no) {
            customer_found = 1;
            printf("Registration Number: %d\n", c.reg_no);
            printf("Name: %s\n", c.name);
            printf("Mobile Number: %s\n", c.mobile_no);
            printf("BMI: %.2f\n", c.bmi);
            printf("Address: %s\n", c.address);
            printf("Package: %s\n", c.package);
            printf("Join Date: %s\n", c.join_date);

            // Check if customer has booked a time slot
            FILE *slot_fp = fopen("slot_records.txt", "r");
            char slot_line[256];
            int slot_booked = 0;
            while (fgets(slot_line, sizeof(slot_line), slot_fp)) {
                int slot_reg_no, slot_choice;
                sscanf(slot_line, "%d\t%d", &slot_reg_no, &slot_choice);
                if (slot_reg_no == reg_no) {
                    slot_booked = 1;
                    printf("Time Slot: ");
                    switch (slot_choice) {
                        case 1:
                            printf("10:00 AM - 11:00 AM\n");
                            break;
                        case 2:
                            printf("11:00 AM - 12:00 PM\n");
                            break;
                        case 3:
                            printf("12:00 PM - 01:00 PM\n");
                            break;
                        case 4:
                            printf("01:00 PM - 02:00 PM\n");
                            break;
                        case 5:
                            printf("02:00 PM - 03:00 PM\n");
                            break;
                        case 6:
                            printf("03:00 PM - 04:00 PM\n");
                            break;
                        default:
                            break;
                    }
                }
            }
            fclose(slot_fp);

            if (!slot_booked) {
                printf("Time Slot: Not Booked\n");
            }
            break;
        }
    }
    fclose(fp);

    if (!customer_found) {
        printf("Customer not found.\n");
    }
}


void delete_customer() {
    int reg_no;
    char line[256], confirmation;
    FILE *fp, *temp;

    printf("Enter customer registration number to delete: ");
    scanf("%d", &reg_no);

    // Get customer data from file
    fp = fopen("customer_records.txt", "r");
    temp = fopen("temp.txt", "w");
    int found_customer = 0;
    while (fgets(line, sizeof(line), fp)) {
        struct customer c;
        sscanf(line, "%d\t%s\t%s\t%f\t%s\t%s\t%s", &c.reg_no, c.name, c.mobile_no, &c.bmi, c.address, c.package, c.join_date);
        if (c.reg_no == reg_no) {
            found_customer = 1;
            printf("Customer found: %s\n", c.name);
            printf("Are you sure you want to delete this record? (Y/N): ");
            scanf(" %c", &confirmation);
            if (confirmation == 'Y' || confirmation == 'y') {
                printf("Deleting customer record...\n");
                continue;
            } else {
                printf("Customer record not deleted.\n");
                fprintf(temp, "%d\t%s\t%s\t%.2f\t%s\t%s\t%s\n", c.reg_no, c.name, c.mobile_no, c.bmi, c.address, c.package, c.join_date);
            }
        } else {
            fprintf(temp, "%d\t%s\t%s\t%.2f\t%s\t%s\t%s\n", c.reg_no, c.name, c.mobile_no, c.bmi, c.address, c.package, c.join_date);
        }
    }
    fclose(fp);
    fclose(temp);

    // Replace original file with modified temp file
    if (found_customer) {
        remove("customer_records.txt");
        rename("temp.txt", "customer_records.txt");
        printf("Customer record deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("Customer not found.\n");
    }
}
int main() {
    int choice;

    do {
        printf("\nGym Management System\n");
        printf("1. Add customer\n");
        printf("2. Book time slot\n");
        printf("3. Display records\n");
        printf("4. Search records\n");
        printf("5. Delete record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        int result = scanf("%d", &choice);
        if (result != 1) {
            // Clear input buffer in case of invalid input
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number between 1 and 6.\n");
            continue;  // Skip to the next iteration of the loop
        }
        if (choice < 1 || choice > 6) {
            printf("Invalid input! Please enter a number between 1 and 6.\n");
            continue;  // Skip to the next iteration of the loop
        }
        switch (choice) {
            case 1:
                add_customer();
                break;
            case 2:
                book_slot();
                break;
            case 3:
                display_records();
                break;
            case 4:
                search_customer();
                break;
            case 5:
                delete_customer();
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}
