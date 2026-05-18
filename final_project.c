#include <stdio.h>
#include <string.h>

// Defining Colors
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

#define MAX_LIMIT 20

// All Functions Of Management System

void addcustomer();
void showdetails();
void updatecustomer();
void availability();
void generateBill();
void deletecustomer();
void printmenu();
void charges();
void loadData();
void saveData();

// Structure storing customer information
struct customer
{
    char name[20];
    char phone_number[12];
    char idproof[10];
    char CNICno[14];
    char check_in_date[20];
    char check_out_date[20];
    char room_type[10];
    int roomno;
    int booked;
    int days;
    char booking_type[10];
    char purpose_of_visit[10];
};

struct customer Customer[MAX_LIMIT];
int count = 0;
int room = 0;

//----------------Main Function---------------//

int main()
{
    printf("\n\n\t\t\t\t\t================================\n"); // hotel name
    printf("\t\t\t\t\t|\tHOTEL SEA BREEZE\t|\n");
    printf("\t\t\t\t\t================================\n\n");
    int choice, password;
    char user[20];

    // login system

    printf("---------\n");
    printf("| Log In |\n");
    printf("---------\n");

    printf("Enter the username: ");
    scanf("%s", user);

    printf("Enter the password: ");
    scanf("%d", &password);

    if (strcmp(user, "admin") != 0 || password != 12345)
    {
        printf("Invalid username or password\n");
    }
    else
    {
        printf("\nSuccesfull Login...\n\n");
        loadData();

        while (1)
        {
            printmenu();
            scanf("%d", &choice);

            if (choice <= 0 || choice > 8)
            {
                printf("Invalid Choice\n");
                continue;
            }

            switch (choice)
            {
            case 1:
                addcustomer();
                break;
            case 2:
                showdetails();
                break;
            case 3:
                updatecustomer();
                break;
            case 4:
                availability();
                break;
            case 5:
                generateBill();
                break;
            case 6:
                deletecustomer();
                break;
            case 7:
                charges();
                break;
            case 8:
                saveData();
                printf("Data Saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid Choice\n");
            }
        }
    }
    return 0;
}

void loadData() // Loads all stored customer records from the file "hotel_data.txt"
{
    FILE *fp = fopen("hotel_data.txt", "r");
    if (fp == NULL)
    {
        return;
    }

    while (!feof(fp))
    {
        struct customer c;
        char line[200];

        if (fgets(line, sizeof(line), fp) != NULL)
        {
            if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,],%s",
                       c.name, c.phone_number, c.idproof, c.CNICno, c.check_in_date,
                       c.check_out_date, c.room_type, &c.roomno, &c.days,
                       c.booking_type, c.purpose_of_visit) == 11)
            {
                c.booked = 1;
                Customer[count++] = c;
            }
        }
    }
    fclose(fp);
}

void saveData() // Saves all customer records
{
    FILE *fp = fopen("hotel_data.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving data.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%d,%d,%s,%s\n",
                Customer[i].name, Customer[i].phone_number, Customer[i].idproof,
                Customer[i].CNICno, Customer[i].check_in_date,
                Customer[i].check_out_date, Customer[i].room_type,
                Customer[i].roomno, Customer[i].days,
                Customer[i].booking_type, Customer[i].purpose_of_visit);
    }

    fclose(fp);
}
//----------Adding Customer-------------//

void addcustomer()
{
    if (count >= MAX_LIMIT)
    {
        printf("Maximum Limit Reached\n");
        return;
    }

    printf("\nEnter Customer Name: ");
    scanf(" %[^\n]", Customer[count].name); // Read full name including spaces

    printf("\nEnter Phone Number: ");
    scanf("%s", Customer[count].phone_number);

    printf("\nEnter ID Proof: ");
    scanf(" %[^\n]", Customer[count].idproof);

    printf("\nEnter CNIC Number (Without Hyphen): ");
    scanf("%s", Customer[count].CNICno);

    printf("\nEnter Check-In Date (DD-MM-YYYY): ");
    scanf("%s", Customer[count].check_in_date);

    printf("\nEnter Check-Out Date (DD-MM-YYYY): ");
    scanf("%s", Customer[count].check_out_date);

    printf("\nEnter Number Of Days Stayed: ");
    scanf("%d", &Customer[count].days);

    int choice_2;
    printf("\nSelect Room Type:\n1. Single\n2. Double\n");
    scanf("%d", &choice_2);

    switch (choice_2)
    {
    case 1:
        strcpy(Customer[count].room_type, "Single");
        break;
    case 2:
        strcpy(Customer[count].room_type, "Double");
        break;
    default:
        strcpy(Customer[count].room_type, "Unknown");
        break;
    }

    printf("\nEnter Booking Type (Walk-In / Online): ");
    scanf(" %[^\n]", Customer[count].booking_type);

    printf("\nEnter Purpose Of Visit: ");
    scanf(" %[^\n]", Customer[count].purpose_of_visit);

    // Assign the first available room

    int assignedRoom = -1;

    for (int i = 1; i <= MAX_LIMIT; i++)
    {
        int alreadyBooked = 0; // Reset for each room check

        for (int j = 0; j < count; j++)
        {
            if (Customer[j].roomno == i)
            {
                alreadyBooked = 1;
                break;
            }
        }

        if (!alreadyBooked)
        {
            assignedRoom = i;
            break;
        }
    }

    if (assignedRoom == -1)
    {
        printf("All rooms are currently booked\n");
        return;
    }
    Customer[count].roomno = assignedRoom;
    Customer[count].booked = 1;

    printf("\nRoom Number Assigned: %d", Customer[count].roomno);
    printf("\nRoom Booked Successfully\n\n");

    count++;
    saveData();
}
//----------Displaying Details-------------//
void showdetails()
{
    if (count == 0)
    {
        printf("No Data Found.\n");
        return;
    }

    int room;
    printf("\nEnter The Room No: ");
    scanf("%d", &room);

    printf(GREEN "\n%-22s %-18s %-13s %-6s %-10s %-12s %-12s %-6s %-12s %-12s\n",
           "Name", "CNIC", "Phone", "Room", "Type",
           "Check-In", "Check-Out", "Days", "Booking", "Purpose" RESET);

    printf("--------------------------------------------------------------------------------------------------------------------------------\n");

    int found = 0;

    for (int i = 0; i < count; i++)
    {
        if (room == Customer[i].roomno)
        {
            found = 1;

            printf("%-22s %-18s %-13s %-6d %-10s %-12s %-12s %-6d %-12s %-12s\n\n\n",
                   Customer[i].name,
                   Customer[i].CNICno,
                   Customer[i].phone_number,
                   Customer[i].roomno,
                   Customer[i].room_type,
                   Customer[i].check_in_date,
                   Customer[i].check_out_date,
                   Customer[i].days,
                   Customer[i].booking_type,
                   Customer[i].purpose_of_visit);
        }
    }

    if (!found)
    {
        printf("\nNo Record Found for Room %d\n", room);
    }
}

//----------Menu Options-------------//

void printmenu()
{
    printf("============================================================\n");
    printf("|\t\t HOTEL MANAGEMENT SYSTEM \t\t   |\n");
    printf("============================================================\n\n");
    printf("1 --> Add Customer\n");
    printf("2 --> Show Details\n");
    printf("3 --> Update Information\n");
    printf("4 --> Room Availability\n");
    printf("5 --> Generate Bill\n");
    printf("6 --> Delete Customer\n");
    printf("7 --> View Hotel Charges\n");
    printf("8 --> Exit\n");
    printf("Enter Your Choice:\n");
}

//----------Updating Details-------------//

void updatecustomer()
{
    int found = 0;
    if (count == 0)
    {
        printf("No Data Found\n");
        return;
    }

    int room, num, extended_date;
    printf("\nEnter The Room No: ");
    scanf("%d", &room);

    for (int i = 0; i < count; i++)
    {
        if (room == Customer[i].roomno) // Find customer by room number
        {
            found = 1;
            printf("\n1 -> Update Name\n");
            printf("2 -> Update Phone Number\n");
            printf("3 -> Update Check Out Date\n");
            printf("4 -> Update Room No\n");
            printf("Enter Your Choice : ");
            scanf("%d", &num);

            switch (num)
            {
            case 1:
                printf("\nEnter The Customer Name: ");
                scanf(" %[^\n]", Customer[i].name);
                break;

            case 2:
                printf("\nEnter Phone Number: ");
                scanf("%s", Customer[i].phone_number);
                break;

            case 3:
                printf("\nEnter The Check Out Date (DD-MM-YYYY): ");
                scanf("%s", Customer[i].check_out_date);
                printf("\nEnter No Of Days Extended : ");
                scanf("%d", &extended_date);
                Customer[i].days += extended_date;
                break;

            case 4:
            {
                int newRoom, alreadyBooked;

                do
                {
                    printf("\nEnter The New Room No: ");
                    scanf("%d", &newRoom);

                    if (newRoom < 1 || newRoom > MAX_LIMIT)
                    {
                        printf("Invalid Room Number. Please Try Again.\n");
                        continue;
                    }

                    alreadyBooked = 0;
                    for (int j = 0; j < count; j++) // checking if the room is already booked
                    {
                        if (Customer[j].roomno == newRoom && j != i)
                        {
                            alreadyBooked = 1;
                            break;
                        }
                    }

                    if (alreadyBooked)
                        printf("Room %d Is Already Booked. Please Choose Another Room.\n", newRoom);

                } while (alreadyBooked); // Keep asking until a free room is selected

                Customer[i].roomno = newRoom;
                Customer[i].booked = 1;
                printf("Room Number Updated Successfully.\n");
                break;
            }

            default:
                printf("Invalid Choice\n");
            }
        }
    }
    if (found == 0)
    {
        printf("\nNo Data Found For Room No %d\n", room);
    }
    else if (found == 1)
    {
        printf("\nInformation Updated Succesfully\n");
    }

    saveData();
}
//----------Checking Room Availability------------//

void availability()
{
    printf("\nROOM AVAILABILITY STATUS:\n");

    for (int i = 1; i <= MAX_LIMIT; i++)
    {
        int booked = 0;
        for (int j = 0; j < count; j++)
        {
            if (Customer[j].roomno == i)
            {
                booked = 1;
                break;
            }
        }

        if (booked)
            printf("----------------------\nRoom no %d -> BOOKED\n----------------------\n", i);
        else
            printf(GREEN "Room no %d -> AVAILABLE\n" RESET, i); // Added Color
    }
    printf("\n");
}

//----------Deleting Customer Details-------------//
void deletecustomer()
{
    int found = 0;
    if (count == 0)
    {
        printf("\nNo customer details to delete\n");
        return;
    }

    printf("\nEnter the room no to delete: ");
    scanf("%d", &room);

    for (int i = 0; i < count; i++)
    {
        if (room == Customer[i].roomno)
        {
            found = 1;
            for (int j = i; j < count - 1; j++)
            {
                Customer[j] = Customer[j + 1];
            }
            count--;
            printf("\nCustomer record for room %d is deleted.\n", room);
            break;
        }
    }
    if (found == 0)
    {
        printf("No Data Found!\n");
    }

    saveData();
}

//----------Generating Bill Automatically By Entering Room No-------------//
void generateBill()
{
    if (count == 0)
    {
        printf("No Data Found.\n");
        return;
    }

    int room;
    float room_rent, service_charge;
    printf("\nEnter Room No. to Generate Bill: ");
    scanf("%d", &room);

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (Customer[i].roomno == room)
        {
            found = 1;

            // Apply room charges based on the customer's selected room type (Single or Double)

            if (strcmp(Customer[i].room_type, "Single") == 0)
            {
                room_rent = 10000.0;
                service_charge = 1200.0;
            }
            else if (strcmp(Customer[i].room_type, "Double") == 0)
            {
                room_rent = 20000.0;
                service_charge = 2000.0;
            }

            double total = room_rent * Customer[i].days + service_charge; // Calculate total bill

            // Printing the billing information
            printf("\n=================================\n");
            printf("             BILL                \n");
            printf("=================================\n\n");

            printf(" Customer Name   : %s\n", Customer[i].name);
            printf(" Room Type       : %s\n", Customer[i].room_type);
            printf(" Check-In Date   : %s\n", Customer[i].check_in_date);
            printf(" Check-Out Date  : %s\n", Customer[i].check_out_date);
            printf(" Days Stayed     : %d\n", Customer[i].days);
            printf(" Service Charge  : %.2f\n", service_charge);

            printf("---------------------------------\n");
            printf(" Total Amount    : %.2lf PKR\n", total);
            printf("=================================\n");
        }
    }
    if (!found)
        printf("No Booking Found.\n\n");
}

//----------To Display Hotel Charges-------------//

void charges()
{
    printf("\n=================================\n");
    printf("         HOTEL ROOM CHARGES       \n");
    printf("=================================\n\n");

    printf("Room Charges:\n");
    printf("  Single Room : 10,000 Rs per day\n");
    printf("  Double Room : 20,000 Rs per day\n\n");

    printf("Service Charges:\n");
    printf("  Single Room : 1,200 Rs\n");
    printf("  Double Room : 2,000 Rs\n");

    printf("\n=================================\n\n");
}
