#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///Hostel management system

struct Room
{
    char room_description[100];
    int roomID;
    double rentAmount;
    int isAvailable;

} roomArray[100];

struct customer
{

    char name[100];
    char contactNumber[100];
    int roomID;




} customerArray[100];

int flatNumberCount=0;
int customerCount=0;

void menu()
{
    printf("\n\n1.Add Customer\n");
    printf("2.Add Room Details\n");
    printf("3.Display all Avaibale Rooms information\n");
    printf("4.Display all Booked Rooms information\n");
    printf("5.Delete room By Id\n");
    printf("6.Save Information to File\n");
    printf("7.Exit");
}

void changeAvailabiltyOfRoom(int roomID)
{

    int index=searchBYid(roomID);
    if(index!=-1)
    {

        roomArray[index].isAvailable=0;

    }



}




void addCustomer()
{

    printf("Enter name of customer : ");
    scanf("%s",customerArray[customerCount].name);
    printf("Enter Contact number: ");
    scanf("%s",customerArray[customerCount].contactNumber);
    printf("Enter room ID : ");
    scanf("%d",&customerArray[customerCount].roomID);
    changeAvailabiltyOfRoom(customerArray[customerCount].roomID);
    customerCount++;


}
void addRoomDetails()
{
    printf("Enter room details : (no space between words!)\n");
    scanf("%s",roomArray[flatNumberCount].room_description);
    printf("Enter room ID : ");
    scanf("%d",&roomArray[flatNumberCount].roomID);
    roomArray[flatNumberCount].isAvailable=1;
    printf("Enter Rent per Month : ");
    scanf("%lf",&roomArray[flatNumberCount].rentAmount);
    printf("\n");
    flatNumberCount++;
    printf("\Room Details ADDED !\n");


}
void displayAvailableRooms()
{
    printf("Available Room Information : \n\n");
    printf("Total Room :  %d\n",flatNumberCount);
    for(int i=0; i<flatNumberCount; i++)
    {
        if(roomArray[i].isAvailable!=0)
        {
            printf("--------------------------------------------------------\n");

            printf("Room No                :  %d\n",i+1);
            printf("Room Details           :  %s\n",roomArray[i].room_description);
            printf("Room ID                :  %d\n",roomArray[i].roomID);
            printf("Rent                   :  %.2lf\n",roomArray[i].rentAmount);
            printf("--------------------------------------------------------\n");
        }
    }


}
void displayBookedRooms()
{
    printf("All Booked Room Information : \n\n");

    for(int i=0; i<flatNumberCount; i++)
    {
        if(roomArray[i].isAvailable==0)
        {
            printf("--------------------------------------------------------\n");
            printf("Customer Name          :  %s\n",customerArray[getCustomerIndexFromRoomID(roomArray[i].roomID)].name);


            printf("Room No                :  %d\n",i+1);
            printf("Room Details           :  %s\n",roomArray[i].room_description);
            printf("Room ID                :  %d\n",roomArray[i].roomID);
            printf("Rent                   :  %.2lf\n",roomArray[i].rentAmount);
            printf("--------------------------------------------------------\n");

        }
    }


}


void readDataFromFile()
{
    FILE *roomFIle,*customerfile;
    roomFIle=fopen("roomInfo.txt","r+");
    customerfile=fopen("customerInformation.txt","r+");
    if(roomFIle==NULL || customerfile==NULL)
    {
        printf("Running program for the first time,saving information to file...\n\n\n");

        saveInformationToFile();
        exit(1);
    }
    else
    {


        while(fscanf(roomFIle,"%s %d %d %lf",roomArray[flatNumberCount].room_description,&roomArray[flatNumberCount].roomID,&roomArray[flatNumberCount].isAvailable,&roomArray[flatNumberCount].rentAmount)!=EOF)
        {
            flatNumberCount++;
        }
        while(fscanf(customerfile,"%s %d %d",customerArray[customerCount].name,&customerArray[customerCount].contactNumber,&customerArray[customerCount].roomID)!=EOF)
        {
            customerCount++;
        }

        // printf("THE FILE HASBEEN READ SUCCESSFULLY! YOU CAN NOW DISPLAY THE INFORMATION\n");

    }

    fclose(roomFIle);
    fclose(customerfile);




}
void saveInformationToFile()
{
    FILE *roomFIle;
    FILE *customerfile;
    roomFIle=fopen("roomInfo.txt","w");
    customerfile=fopen("customerInformation.txt","w");

    for(int i=0; i<flatNumberCount; i++)
    {

        fprintf(roomFIle,"%s %d %d %.2lf\n",roomArray[i].room_description,roomArray[i].roomID,roomArray[i].isAvailable,roomArray[i].rentAmount);

    }
    for(int i=0; i<customerCount; i++)
    {

        fprintf(customerfile,"%s %d %d",customerArray[i].name,customerArray[i].contactNumber,customerArray[i].roomID);
    }
    fclose(roomFIle);
    fclose(customerfile);

    printf("\n\nSaved to file successfully!\n\n");


}

int getCustomerIndexFromRoomID(int roomID)
{
    int index=-1;


    for(int i=0; i<customerCount; i++)
    {
        if(customerArray[i].roomID==roomID)
        {

            index=i;
            return index;
        }


    }

    return index;



}
int searchBYid(int id)
{
    int index=-1;


    for(int i=0; i<flatNumberCount; i++)
    {
        if(roomArray[i].roomID==id)
        {

            index=i;
            return index;
        }


    }

    return index;


}
void deleteRoomByID()
{
    int targetID;
    printf("Enter ID to Delete : ");
    scanf("%d",&targetID);

    int index=searchBYid(targetID);

    if(index!=-1)
    {

        for(int i=index; i<flatNumberCount; i++)
        {
            roomArray[i]=roomArray[i+1];

        }
        flatNumberCount--;
        printf("\nDELETED!\n");

    }
    else
    {

        printf("\n\nID NOT FOUND\n\n");
    }






}
void test()
{

    strcat(roomArray[0].room_description,"2_ROOM,1_KITCHEN,1_BATHROOM,1_BALCONY");
    roomArray[0].isAvailable=1;
    roomArray[0].roomID=100;
    roomArray[0].rentAmount=5000;


    strcat(roomArray[1].room_description,"3_ROOM,1_KITCHEN,2_BATHROOM,2_BALCONY");
    roomArray[1].isAvailable=1;
    roomArray[1].roomID=101;
    roomArray[1].rentAmount=8000;


    strcat(roomArray[2].room_description,"1_ROOM,1_KITCHEN,1_BATHROOM,1_BALCONY");
    roomArray[2].isAvailable=1;
    roomArray[2].roomID=102;
    roomArray[2].rentAmount=3500;

    flatNumberCount=3;
    saveInformationToFile();




}

int main()
{

    int option=0;

    printf("|------------------------------------------------|\n");
    printf("|  WELCOME TO NSU BOYS HOSTEL MANAGEMENT SYSTEM! |\n");
    printf("|------------------------------------------------|\n");

    readDataFromFile();


    while(option!=7)
    {
        menu();
        printf("\nEnter your option: \n");
        scanf("%d",&option);


        if(option==1)
        {
            addCustomer();
        }
        else if(option==2)
        {
            addRoomDetails();
        }
        else if(option==3)
        {
            displayAvailableRooms();
        }
        else if(option==4)
        {
            displayBookedRooms();
        }
        else if(option==5)
        {
            deleteRoomByID();
        }
        else if(option==6)
        {
            saveInformationToFile();
        }
        else if(option==7)
        {
            printf("|-------------------------------------|\n");
            printf("|  THANKS FOR USING THE APPLICATION!  |\n");
            printf("|-------------------------------------|\n");
            exit(1);
        }
        else
        {
            printf("INVALID OPTION\n");
        }


    }





    return 0;
}
