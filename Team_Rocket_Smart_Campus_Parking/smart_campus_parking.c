#include <stdio.h>
#include <string.h>

#define MAX_SLOTS 10
#define CAR_RATE 20
#define BIKE_RATE 10

struct ParkingSlot
{
    char vehicleNumber[20];
    char vehicleType[10];
    int entryHour;
    int entryMinute;
    int occupied;
    int hasFastag;
};

/* Function Prototypes */
void vehicleEntry(struct ParkingSlot parking[]);
void vehicleExit(struct ParkingSlot parking[]);
void searchVehicle(struct ParkingSlot parking[]);
void displayParking(struct ParkingSlot parking[]);
void viewHistory(void);

int main()
{
    struct ParkingSlot parking[MAX_SLOTS];
    int choice, i;

    /* Initially all parking slots are empty */
    for (i = 0; i < MAX_SLOTS; i++)
    {
        parking[i].occupied = 0;
    }

    do
    {
        printf("\n+--------------------------------------------------+\n");
        printf("|          SMART CAMPUS PARKING SYSTEM             |\n");
        printf("|                  TEAM ROCKET                     |\n");
        printf("+--------------------------------------------------+\n");
        printf("|  1. Vehicle Entry                                |\n");
        printf("|  2. Vehicle Exit                                 |\n");
        printf("|  3. Search Vehicle                               |\n");
        printf("|  4. Display Parking Status                       |\n");
        printf("|  5. View Parking History                         |\n");
        printf("|  6. Exit                                         |\n");
        printf("+--------------------------------------------------+\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            vehicleEntry(parking);
            break;

        case 2:
            vehicleExit(parking);
            break;

        case 3:
            searchVehicle(parking);
            break;

        case 4:
            displayParking(parking);
            break;

        case 5:
            viewHistory();
            break;

        case 6:
            printf("\n+--------------------------------------------------+\n");
            printf("|                    THANK YOU                     |\n");
            printf("|          Smart Campus Parking System             |\n");
            printf("+--------------------------------------------------+\n");
            break;

        default:
            printf("\nInvalid choice! Please enter 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}

/* ================= VEHICLE ENTRY ================= */

void vehicleEntry(struct ParkingSlot parking[])
{
    char vehicleNumber[20];
    int type;
    int hour, minute;
    int fastagChoice;
    int slot = -1;
    int i;

    printf("\n+--------------------------------------------------+\n");
    printf("|                  VEHICLE ENTRY                   |\n");
    printf("+--------------------------------------------------+\n");

    printf("\nEnter vehicle number: ");
    scanf("%19s", vehicleNumber);

    /* Check Duplicate Vehicle */
    for (i = 0; i < MAX_SLOTS; i++)
    {
        if (parking[i].occupied == 1 &&
            strcmp(parking[i].vehicleNumber, vehicleNumber) == 0)
        {
            printf("\n+--------------------------------------------------+\n");
            printf("|                     WARNING                      |\n");
            printf("+--------------------------------------------------+\n");
            printf("| Vehicle is already parked!                       |\n");
            printf("+--------------------------------------------------+\n");
            return;
        }
    }

    /* Find Empty Parking Slot */
    for (i = 0; i < MAX_SLOTS; i++)
    {
        if (parking[i].occupied == 0)
        {
            slot = i;
            break;
        }
    }

    if (slot == -1)
    {
        printf("\n+--------------------------------------------------+\n");
        printf("|                  PARKING FULL                    |\n");
        printf("+--------------------------------------------------+\n");
        printf("| No parking slots are currently available.        |\n");
        printf("+--------------------------------------------------+\n");
        return;
    }

    /* Vehicle Type */
    printf("\nSelect Vehicle Type\n");
    printf("1. Car  - Rs. %d/hour\n", CAR_RATE);
    printf("2. Bike - Rs. %d/hour\n", BIKE_RATE);
    printf("Enter choice: ");
    scanf("%d", &type);

    if (type == 1)
    {
        strcpy(parking[slot].vehicleType, "Car");
    }
    else if (type == 2)
    {
        strcpy(parking[slot].vehicleType, "Bike");
    }
    else
    {
        printf("Invalid vehicle type!\n");
        return;
    }

    /* Entry Time */
    printf("Enter entry time (HH MM): ");
    scanf("%d %d", &hour, &minute);

    if (hour < 0 || hour > 23 ||
        minute < 0 || minute > 59)
    {
        printf("Invalid entry time!\n");
        return;
    }

    /* FASTag */
    printf("FASTag available? (1 = Yes, 0 = No): ");
    scanf("%d", &fastagChoice);

    if (fastagChoice != 0 && fastagChoice != 1)
    {
        printf("Invalid FASTag choice!\n");
        return;
    }

    /* Store Vehicle Details */
    strcpy(parking[slot].vehicleNumber, vehicleNumber);

    parking[slot].entryHour = hour;
    parking[slot].entryMinute = minute;
    parking[slot].hasFastag = fastagChoice;
    parking[slot].occupied = 1;

    /* Confirmation */
    printf("\n+--------------------------------------------------+\n");
    printf("|              VEHICLE PARKED SUCCESSFULLY         |\n");
    printf("+--------------------------------------------------+\n");
    printf("| Vehicle Number : %-30s|\n",
           parking[slot].vehicleNumber);

    printf("| Vehicle Type   : %-30s|\n",
           parking[slot].vehicleType);

    printf("| Parking Slot   : P%02d                           |\n",
           slot + 1);

    printf("| Entry Time     : %02d:%02d                          |\n",
           parking[slot].entryHour,
           parking[slot].entryMinute);

    if (parking[slot].hasFastag == 1)
    {
        printf("| FASTag         : Available                      |\n");
    }
    else
    {
        printf("| FASTag         : Not Available                  |\n");
    }

    printf("+--------------------------------------------------+\n");
}

/* ================= VEHICLE EXIT ================= */

void vehicleExit(struct ParkingSlot parking[])
{
    char vehicleNumber[20];
    char paymentMode[10];

    int exitHour, exitMinute;
    int entryTotal, exitTotal;
    int duration;
    int hours, minutes;
    int billableHours;
    int rate;
    int slot = -1;
    int i;

    float charge;

    FILE *fp;

    printf("\n+--------------------------------------------------+\n");
    printf("|                   VEHICLE EXIT                   |\n");
    printf("+--------------------------------------------------+\n");

    printf("\nEnter vehicle number: ");
    scanf("%19s", vehicleNumber);

    /* Find Vehicle */
    for (i = 0; i < MAX_SLOTS; i++)
    {
        if (parking[i].occupied == 1 &&
            strcmp(parking[i].vehicleNumber, vehicleNumber) == 0)
        {
            slot = i;
            break;
        }
    }

    if (slot == -1)
    {
        printf("\n+--------------------------------------------------+\n");
        printf("|                VEHICLE NOT FOUND                 |\n");
        printf("+--------------------------------------------------+\n");
        return;
    }

    printf("\nVehicle Type : %s\n",
           parking[slot].vehicleType);

    printf("Entry Time   : %02d:%02d\n",
           parking[slot].entryHour,
           parking[slot].entryMinute);

    printf("Enter exit time (HH MM): ");
    scanf("%d %d", &exitHour, &exitMinute);

    if (exitHour < 0 || exitHour > 23 ||
        exitMinute < 0 || exitMinute > 59)
    {
        printf("Invalid exit time!\n");
        return;
    }

    /* Convert Entry and Exit Times to Minutes */
    entryTotal =
        parking[slot].entryHour * 60 +
        parking[slot].entryMinute;

    exitTotal =
        exitHour * 60 + exitMinute;

    if (exitTotal < entryTotal)
    {
        printf("Exit time cannot be earlier than entry time!\n");
        return;
    }

    /* Calculate Duration */
    duration = exitTotal - entryTotal;

    if (duration == 0)
    {
        duration = 1;
    }

    hours = duration / 60;
    minutes = duration % 60;

    /* Charge Every Started Hour */
    billableHours = (duration + 59) / 60;

    /* Select Parking Rate */
    if (strcmp(parking[slot].vehicleType, "Car") == 0)
    {
        rate = CAR_RATE;
    }
    else
    {
        rate = BIKE_RATE;
    }

    charge = billableHours * rate;

    /* Simulated Payment Mode */
    if (parking[slot].hasFastag == 1)
    {
        strcpy(paymentMode, "FASTag");
    }
    else
    {
        strcpy(paymentMode, "Cash");
    }

    /* Receipt */
    printf("\n+--------------------------------------------------+\n");
    printf("|                 PARKING RECEIPT                  |\n");
    printf("+--------------------------------------------------+\n");

    printf("| Vehicle Number : %-30s|\n",
           parking[slot].vehicleNumber);

    printf("| Vehicle Type   : %-30s|\n",
           parking[slot].vehicleType);

    printf("| Parking Slot   : P%02d                           |\n",
           slot + 1);

    printf("+--------------------------------------------------+\n");

    printf("| Entry Time     : %02d:%02d                          |\n",
           parking[slot].entryHour,
           parking[slot].entryMinute);

    printf("| Exit Time      : %02d:%02d                          |\n",
           exitHour,
           exitMinute);

    printf("| Duration       : %d hr %d min",
           hours,
           minutes);

    /* Alignment for duration */
    if (hours < 10 && minutes < 10)
        printf("                     |\n");
    else if (hours < 10 || minutes < 10)
        printf("                    |\n");
    else
        printf("                   |\n");

    printf("| Billable Hours : %-30d|\n",
           billableHours);

    printf("+--------------------------------------------------+\n");

    printf("| Rate           : Rs. %-2d/hour                   |\n",
           rate);

    printf("| Parking Charge : Rs. %-25.2f|\n",
           charge);

    printf("| Payment Mode   : %-30s|\n",
           paymentMode);

    if (parking[slot].hasFastag == 1)
    {
        printf("| Payment Status : Successful (Simulated)         |\n");
    }

    printf("+--------------------------------------------------+\n");
    printf("|              VEHICLE EXIT SUCCESSFUL             |\n");
    printf("+--------------------------------------------------+\n");

    /* Save Record Using File Handling */
    fp = fopen("parking_records.txt", "a");

    if (fp != NULL)
    {
        fprintf(fp,
                "%s %s %02d:%02d %02d:%02d %d %.2f %s\n",
                parking[slot].vehicleNumber,
                parking[slot].vehicleType,
                parking[slot].entryHour,
                parking[slot].entryMinute,
                exitHour,
                exitMinute,
                duration,
                charge,
                paymentMode);

        fclose(fp);

        printf("Parking record saved successfully!\n");
    }
    else
    {
        printf("Unable to save parking record!\n");
    }

    /* Free Parking Slot */
    parking[slot].occupied = 0;
}

/* ================= SEARCH VEHICLE ================= */

void searchVehicle(struct ParkingSlot parking[])
{
    char vehicleNumber[20];
    int i;

    printf("\n+--------------------------------------------------+\n");
    printf("|                  SEARCH VEHICLE                  |\n");
    printf("+--------------------------------------------------+\n");

    printf("\nEnter vehicle number: ");
    scanf("%19s", vehicleNumber);

    for (i = 0; i < MAX_SLOTS; i++)
    {
        if (parking[i].occupied == 1 &&
            strcmp(parking[i].vehicleNumber, vehicleNumber) == 0)
        {
            printf("\n+--------------------------------------------------+\n");
            printf("|                  VEHICLE FOUND                   |\n");
            printf("+--------------------------------------------------+\n");

            printf("| Vehicle Number : %-30s|\n",
                   parking[i].vehicleNumber);

            printf("| Vehicle Type   : %-30s|\n",
                   parking[i].vehicleType);

            printf("| Parking Slot   : P%02d                           |\n",
                   i + 1);

            printf("| Entry Time     : %02d:%02d                          |\n",
                   parking[i].entryHour,
                   parking[i].entryMinute);

            printf("| Status         : Parked                         |\n");

            if (parking[i].hasFastag == 1)
            {
                printf("| FASTag         : Available                      |\n");
            }
            else
            {
                printf("| FASTag         : Not Available                  |\n");
            }

            printf("+--------------------------------------------------+\n");

            return;
        }
    }

    printf("\n+--------------------------------------------------+\n");
    printf("|                VEHICLE NOT FOUND                 |\n");
    printf("+--------------------------------------------------+\n");
}

/* ================= PARKING STATUS ================= */

void displayParking(struct ParkingSlot parking[])
{
    int i;
    int occupied = 0;
    int cars = 0;
    int bikes = 0;

    printf("\n+------------------------------------------------------------------+\n");
    printf("|                         PARKING STATUS                           |\n");
    printf("+------------------------------------------------------------------+\n");

    printf("| %-4s | %-10s | %-15s | %-6s | %-5s | %-6s |\n",
           "Slot",
           "Status",
           "Vehicle",
           "Type",
           "Entry",
           "FASTag");

    printf("+------------------------------------------------------------------+\n");

    for (i = 0; i < MAX_SLOTS; i++)
    {
        if (parking[i].occupied == 1)
        {
            printf("| P%02d  | %-10s | %-15s | %-6s | %02d:%02d | %-6s |\n",
                   i + 1,
                   "OCCUPIED",
                   parking[i].vehicleNumber,
                   parking[i].vehicleType,
                   parking[i].entryHour,
                   parking[i].entryMinute,
                   parking[i].hasFastag ? "Yes" : "No");

            occupied++;

            if (strcmp(parking[i].vehicleType, "Car") == 0)
            {
                cars++;
            }
            else
            {
                bikes++;
            }
        }
        else
        {
            printf("| P%02d  | %-10s | %-15s | %-6s | %-5s | %-6s |\n",
                   i + 1,
                   "AVAILABLE",
                   "-",
                   "-",
                   "-",
                   "-");
        }
    }

    printf("+------------------------------------------------------------------+\n");

    printf("| Total Slots: %-2d   Occupied: %-2d   Available: %-2d               |\n",
           MAX_SLOTS,
           occupied,
           MAX_SLOTS - occupied);

    printf("| Cars Parked: %-2d   Bikes Parked: %-2d                             |\n",
           cars,
           bikes);

    printf("+------------------------------------------------------------------+\n");
}

/* ================= PARKING HISTORY ================= */

void viewHistory(void)
{
    FILE *fp;
    char ch;

    fp = fopen("parking_records.txt", "r");

    printf("\n+--------------------------------------------------+\n");
    printf("|                 PARKING HISTORY                  |\n");
    printf("+--------------------------------------------------+\n");

    if (fp == NULL)
    {
        printf("| No parking history available.                    |\n");
        printf("+--------------------------------------------------+\n");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(fp);

    printf("+--------------------------------------------------+\n");
}