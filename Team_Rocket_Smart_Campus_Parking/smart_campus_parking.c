#include <stdio.h>
#include <string.h>

#define MAX_SLOTS 10
#define RATE_PER_HOUR 20

struct ParkingSlot
{
    char vehicleNumber[20];
    int entryTime;
    int occupied;
};

void vehicleEntry(struct ParkingSlot parking[]);
void vehicleExit(struct ParkingSlot parking[]);
void searchVehicle(struct ParkingSlot parking[]);
void displayParking(struct ParkingSlot parking[]);

int main()
{
    struct ParkingSlot parking[MAX_SLOTS];
    int choice, i;

    /* Initially all slots are empty */
    for (i = 0; i < MAX_SLOTS; i++)
    {
        parking[i].occupied = 0;
    }

    // Lakshya Garg

    do
    {
        printf("\n========================================\n");
        printf("      SMART CAMPUS PARKING SYSTEM\n");
        printf("             TEAM ROCKET\n");
        printf("========================================\n");
        printf("1. Vehicle Entry\n");
        printf("2. Vehicle Exit\n");
        printf("3. Search Vehicle\n");
        printf("4. Display Parking Status\n");
        printf("5. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
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
            printf("\nThank you for using the Parking System!\n");
            break;

        default:
            printf("\nInvalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}

// Sanskar_Singh

/* Vehicle Entry */
void vehicleEntry(struct ParkingSlot parking[])
{
    char vehicleNumber[20];
    int entryTime;
    int i;
    int slot = -1;

    printf("\n--- VEHICLE ENTRY ---\n");

    printf("Enter vehicle registration number: ");
    scanf("%19s", vehicleNumber);

    /* Check duplicate entry */
    for (i = 0; i < MAX_SLOTS; i++)
    {
        if (parking[i].occupied == 1 &&
            strcmp(parking[i].vehicleNumber, vehicleNumber) == 0)
        {
            printf("Vehicle is already parked!\n");
            return;
        }
    }

    /* Find empty slot */
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
        printf("PARKING FULL!\n");
        return;
    }

    printf("Enter entry time (0-23): ");
    scanf("%d", &entryTime);

    if (entryTime < 0 || entryTime > 23)
    {
        printf("Invalid entry time!\n");
        return;
    }

    strcpy(parking[slot].vehicleNumber, vehicleNumber);
    parking[slot].entryTime = entryTime;
    parking[slot].occupied = 1;

    printf("\nVehicle parked successfully!\n");
    printf("Vehicle Number : %s\n", parking[slot].vehicleNumber);
    printf("Parking Slot   : %d\n", slot + 1);
    printf("Entry Time     : %d:00\n", entryTime);
}
// Nishchal_Khati

/* Vehicle Exit */
void vehicleExit(struct ParkingSlot parking[])
{
    char vehicleNumber[20];
    int exitTime, duration;
    int i;
    int slot = -1;
    float charge;

    printf("\n--- VEHICLE EXIT ---\n");

    printf("Enter vehicle registration number: ");
    scanf("%19s", vehicleNumber);

    /* Find vehicle */
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
        printf("Vehicle not found!\n");
        return;
    }

    printf("Entry Time: %d:00\n", parking[slot].entryTime);

    printf("Enter exit time (0-23): ");
    scanf("%d", &exitTime);

    if (exitTime < 0 || exitTime > 23)
    {
        printf("Invalid exit time!\n");
        return;
    }

    if (exitTime < parking[slot].entryTime)
    {
        printf("Exit time cannot be earlier than entry time!\n");
        return;
    }

    duration = exitTime - parking[slot].entryTime;

    /* Minimum charge for one hour */
    if (duration == 0)
    {
        duration = 1;
    }

    charge = duration * RATE_PER_HOUR;

    printf("\n========== PARKING RECEIPT ==========\n");
    printf("Vehicle Number : %s\n", parking[slot].vehicleNumber);
    printf("Parking Slot   : %d\n", slot + 1);
    printf("Entry Time     : %d:00\n", parking[slot].entryTime);
    printf("Exit Time      : %d:00\n", exitTime);
    printf("Duration       : %d hour(s)\n", duration);
    printf("Parking Charge : Rs. %.2f\n", charge);
    printf("=====================================\n");

    /* Make slot empty */
    parking[slot].occupied = 0;

    printf("Vehicle exited successfully!\n");
}

// Lakshya_Garg

/* Search Vehicle */
void searchVehicle(struct ParkingSlot parking[])
{
    char vehicleNumber[20];
    int i;

    printf("\n--- SEARCH VEHICLE ---\n");

    printf("Enter vehicle registration number: ");
    scanf("%19s", vehicleNumber);

    for (i = 0; i < MAX_SLOTS; i++)
    {
        if (parking[i].occupied == 1 &&
            strcmp(parking[i].vehicleNumber, vehicleNumber) == 0)
        {
            printf("\nVehicle found!\n");
            printf("Vehicle Number : %s\n", parking[i].vehicleNumber);
            printf("Parking Slot   : %d\n", i + 1);
            printf("Entry Time     : %d:00\n", parking[i].entryTime);
            printf("Status         : Parked\n");
            return;
        }
    }

    printf("Vehicle not found!\n");
}

// Sanskar_Singh

/* Display Parking Status */
void displayParking(struct ParkingSlot parking[])
{
    int i;
    int occupied = 0;

    printf("\n========== PARKING STATUS ==========\n");

    for (i = 0; i < MAX_SLOTS; i++)
    {
        if (parking[i].occupied == 1)
        {
            printf("Slot %d : OCCUPIED - %s\n",
                   i + 1, parking[i].vehicleNumber);

            occupied++;
        }
        else
        {
            printf("Slot %d : AVAILABLE\n", i + 1);
        }
    }

    // Nishchal_Khati

    printf("------------------------------------\n");
    printf("Total Slots     : %d\n", MAX_SLOTS);
    printf("Occupied Slots  : %d\n", occupied);
    printf("Available Slots : %d\n", MAX_SLOTS - occupied);
    printf("====================================\n");
}

// Lakshya_Garg