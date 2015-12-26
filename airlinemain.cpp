#include<iostream>
#include<iomanip>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <string>
#include <fstream>
#include <string.h>

using namespace std;

void seatValidation(int &x, int &reX, int &wayVal, int &seatVal);
double BasePrice(double, double, int, int, char);
double BagPrice(int, int);

int main()
{
    srand(time(NULL));
    double PricePerTicket, TotalPrice, ExtraBags, FinalPrice; //base price per ticket, price of all tickets before bag fee, bag fee, and final price that need to be outputted
    int deptNum, arrivalNum;
    int way, stop, bags, seat, deptTime, returnTime, A, B, C,
        reA, reB, reC, reseat, adult, child, seatReserve;
    string a, deptDate, returnDate, adults[100], children[100], ID[100], birthDay[100];
    char classRe, ch;
    string dateVal, dateValTwo;
    ofstream receipt("Travel Receipt.txt");

    //Destination input (Departure and Arrival)
    cout << "1. Portland(PDX) \n" << "2. Los Angeles (LAX) \n" << "3. Dallas (DFW) \n" << "4. Chicago (ORD) \n" << "5. New York (JFK) \n";
    cout << "Example: enter number 1 for Portland" << endl;
    do
    {
        cout << "\nPlease choose the departure (number): ";
        cin >> deptNum;

        if (deptNum > 5 || deptNum <= 0) //validates the departure number
        {
            a = "n";
            continue; //skips the rest of the statements and checks condition
        }

        cout << "You entered: " << deptNum << "\n\n" << "Is that correct? (Y/N)" << endl;
        cin >> a;

        while (a != "n" && a != "N" && a != "y" && a != "Y") //validates the input for the "a" variable
        {
            cout << "\nINVALID INPUT" << endl;
            cout << "You entered: " << deptNum << "\n" << "Is that correct? (Y/N)" << endl;
            cin >> a;

        }

    }
    while (a == "N" || a == "n");

    do
    {
        cout << "\nPlease choose the arrival destination (number):" << endl;
        cin >> arrivalNum;

    }
    while (arrivalNum > 5 || arrivalNum <= 0);    //validates arrivalNum

    while (deptNum == arrivalNum)
    {
        cout << "\nThe departure and arrival destination cannot be the same place" << endl;
        cout << "Please re-enter the arrival destination (number):" << endl;
        cin >> arrivalNum;
    }

    //Round trip or one way
    do
    {
        cout << "\nOne way or Round-trip? (enter 1 for one way, 2 for Roundtrip)" << endl;
        cin >> way;
    }
    while (way != 1 && way != 2);    //validates whether one way or roundtrip

    //Nonstop or one stop
    do
    {
        cout << "\nNon-stop or one stop? (enter 1 for non-stop, 2 for one stop)" << endl;
        cin >> stop;

    }
    while (stop != 1 && stop != 2);

    // input time of flight depend on one way or roundtrip
    if (way == 1)
    {
        cout << "Date (MM/DD/YYYY): " << endl;
        cin >> deptDate;

        do
        {

            cout << "\nTime (enter hours only from 0 to 23): " << endl;
            cin >> deptTime;

        }
        while (deptTime < 0 || deptTime > 23);
    }
    else if (way == 2)
    {
        cout << "\nDeparture Date (MM/DD/YYYY): " << endl;
        cin >> deptDate;

        do //validate departure time
        {
            cout << "\nTime (enter hours only from 0 to 23): " << endl;
            cin >> deptTime;

        }
        while (deptTime < 0 || deptTime > 23);

        cout << "\nReturn Date (MM/DD/YYYY): " << endl;
        cin >> returnDate;

        do //validate return time
        {
            cout << "\nTime (enter hours only from 0 to 23): " << endl;
            cin >> returnTime;

        }
        while (returnTime < 0 || returnTime > 23);
    }

    //The highest class (luxury class) is A, and the lowest class (economy class) is E. Each class will be different $100 in price.
    //example price class E + 100 = price class D

    // generate random number of seats for each class
    cout << "\n" << endl;
    cout << "On " << deptDate << " at: " << deptTime << ":00. We offer:" << endl;
    cout << "Class \t\t Number of Seat" << endl;
    cout << "=========================================" << endl;
    A = rand() % 10 + 1;
    B = rand() % 10 + 1;
    C = rand() % 10 + 1;
    seat = rand() % 10 + 1;

    //show how many seats on each class
    cout << "First    \t\t" << A << endl;
    cout << "Business \t\t" << B << endl;
    cout << "Economy \t\t" << C << endl;

    if (way == 2)
    {
        cout << "\n" << endl;
        cout << "On " << returnDate << " at: " << returnTime << ":00. We offer:" << endl;
        cout << "Class \t\t Number of Seat" << endl;
        cout << "=========================================" << endl;
        reseat = rand() % 10 + 1;
        reA = rand() % 10 + 1;
        reB = rand() % 10 + 1;
        reC = rand() % 10 + 1;


        cout << "First    \t\t" << reA << endl;
        cout << "Business \t\t" << reB << endl;
        cout << "Economy \t\t" << reC << endl;
    }

    // Passenger choose the class and how many seats they want.
    do
    {
        cout << "\nWhich class do you want to reserve? " << "Enter F: First, B: Business, E: Economy" << endl;
        cin >> classRe;
    }
    while (classRe != 'f' && classRe != 'b' && classRe != 'e' &&
            classRe != 'F' && classRe != 'B' && classRe != 'E'); //validates input for class

    cout << "\nHow many seat do you want to reserve? ";
    cin >> seatReserve;

    /*
    -------------------------------------------------------------------------------------------------
    THE STATEMENTS UNDER THIS CHECK WHICH CLASS WAS RESERVED (variable classRe) AND THEN COMPARES
    HOW MANY SEATS THE USER RESERVED AND COMPARES IT TO AVAILABLE SEATS (comparing the variables
    seatReserve and re'[A,B,C]' and 'A,B,C'). PROCESSING IS DONE VIA seatValidation FUNCTION
    --------------------------------------------------------------------------------------------------
    */

    if (classRe == 'F' || classRe == 'f')
    {
        seatValidation(A, reA, way, seatReserve);
    }
    else if (classRe == 'B' || classRe == 'b')
    {
        seatValidation(B, reB, way, seatReserve);
    }
    else if (classRe == 'E' || classRe == 'e')
    {
        seatValidation(C, reC, way, seatReserve);
    }
    else if (classRe == 'S' || classRe == 's')
    {
        seatValidation(seat, reseat, way, seatReserve);
    }

    //Input information of passenger(s) (Name, ID, Birthday if child)
    cout << "how many adults? ";
    cin >> adult;
    cout << "how many children? ";
    cin >> child;

    // validate adult + child = seatreserve
    while (adult + child != seatReserve)
    {
        cout << "Please re-input number of adults: ";
        cin >> adult;
        cout << "Please re-input number of children: ";
        cin >> child;
    }

    cin.get(ch);
    for (int i = 0; i < adult; i++)
    {
        cout << "Please enter name (First/Last) of adult " << i + 1 << ": ";
        getline(cin, adults[i]);
    }

    for (int i = 0; i < adult; i++)
    {
        cout << "Please enter ID/DL/passport number of adult " << i + 1 << ": ";
        cin >> ID[i];
    }
    cin.get(ch);
    for (int i = 0; i < child; i++)
    {
        cout << "Please enter name (First/Last) of child " << i + 1 << ": ";
        getline(cin, children[i]);
    }

    for (int i = 0; i < child; i++)
    {
        cout << "Please enter birthday of child (MM/DD/YYYY) " << i + 1 << ": ";
        cin >> birthDay[i];
    }

    //show list of information of  adults
    cout << "Aldult \t\t Name \t\t ID/DL/Passport No" << endl;
    cout << "=================================================" << endl;
    for (int i = 0; i < adult; i++)
    {
        cout << i + 1 << " \t\t " << adults[i] << " \t\t " << ID[i] << endl;
    }


    //show list of information of children
    cout << "\nChildren \t Name \t\t Date of birth" << endl;
    cout << "=================================================" << endl;
    for (int i = 0; i < child; i++)
    {
        cout << i + 1 << " \t\t " << children[i] << " \t\t " << birthDay[i] << endl;
    }

    cout << "\nHow many bags do you want to check? (Total, for all passengers): ";
    cin >> bags;

    //PROCESSING AND OUTPUT GOES HERE:

    //This is the base price of all tickets that needs to be outputted
    PricePerTicket = BasePrice(deptNum, arrivalNum, stop, way, classRe); //price per ticket
    TotalPrice = PricePerTicket * seatReserve; //total price of all tickets

    //This is the fee for extra bags
    ExtraBags = BagPrice(bags, seatReserve);

    //This is the final price of all tickets
    FinalPrice = TotalPrice + ExtraBags;

    if (receipt.is_open()) //Prints everything out to text file so user can print out receipt
    {
        cout << "\nWe've sent you a receipt to print out, thanks for flying with us!" << endl;

        receipt << "\n\n\n\n";
        receipt << "######################################################";

        int revsevation;
        revsevation = rand() % 1000000 + 100000;
        receipt << "\n\n         THIS IS YOUR AIRPLANE TICKET RECEIPT " << endl;
        receipt << "Reservation code: " << revsevation << endl;
        receipt << "====================================================" << endl;
        //show list of information of  adults
        receipt << "Adult \t\t Name \t\t ID/DL/Passport No" << endl;
        receipt << "====================================================" << endl;
        for (int i = 0; i < adult; i++)
        {
            receipt << i + 1 << " \t\t " << adults[i] << " \t\t " << ID[i] << endl;
        }

        //show list of information of children
        receipt << "\nChildren \t Name \t\t Date of birth" << endl;
        receipt << "====================================================" << endl;
        for (int i = 0; i < child; i++)
        {
            receipt << i + 1 << " \t\t " << children[i] << " \t\t " << birthDay[i] << endl;
        }

        string deptName, arrivalName;

        switch (deptNum)
        {
        case 1:
            deptName = " Portland(PDX)";
            break;
        case 2:
            deptName = "Los Angeles (LAX)";
            break;
        case 3:
            deptName = "Dallas (DFW)";
            break;
        case 4:
            deptName = "Chicago (ORD)";
            break;
        case 5:
            cout << "New York (JFK)";
            break;
        }
        switch (arrivalNum)
        {
        case 1:
            arrivalName = " Portland(PDX)";
            break;
        case 2:
            arrivalName = "Los Angeles (LAX)";
            break;
        case 3:
            arrivalName = "Dallas (DFW)";
            break;
        case 4:
            arrivalName = "Chicago (ORD)";
            break;
        case 5:
            arrivalName = "New York (JFK)";
            break;
        }

        if(way == 1)
        {
                 receipt << "====================================================" << endl;
        receipt << "Trip:" << deptName << "=====>" << arrivalName << endl;
        receipt << "Flight duration: " << abs(deptNum - arrivalNum) * 2 << " hours" << endl;
        receipt << "Departure Date:  " << deptDate << endl;
        receipt << "Daparture time:  " << deptTime<<":00" << endl;
        receipt << "Arrival time:    " << deptTime + abs(deptNum - arrivalNum) * 2 << ":00"  << endl;
        receipt << "------------------------------------------------------" << endl;
        //EXAMPLE OUTPUT TO SHOW CALCULATION
        receipt << setprecision(2) << fixed;
        receipt << "Price per ticket:    " << setw(10)<<"$"<<PricePerTicket<<endl;
        receipt << "Extra Bag fees:      " << setw(10)<<"$"<< ExtraBags<<endl;
        receipt << "Tax:                 " << setw(10) << "$" << 0.08*FinalPrice << endl;
        receipt << "Total price:         " << setw(10) << "$" << FinalPrice + 0.08*FinalPrice << endl;
        receipt << "\nThank's for flying with us! Have a safe flight!" << endl;
        }
        else
        {
        receipt << "====================================================" << endl;
        receipt << "Trip:" << deptName << "=====>" << arrivalName << endl;
        receipt << "Flight duration: " << abs(deptNum - arrivalNum) * 2 << " hours" << endl;
        receipt << "Departure Date:  " << deptDate << endl;
        receipt << "Daparture time:  " << deptTime<<":00" << endl;
        receipt << "Arrival time:    " << deptTime + abs(deptNum - arrivalNum) * 2 << ":00"  << endl;
        receipt << "------------------------------------------------------" << endl;
        receipt << "ReturnTrip:" << arrivalName << "=====>" << deptName << endl;
        receipt << "Flight duration: " << abs(deptNum - arrivalNum) * 2 << " hours" << endl;
        receipt << "Departure Date:  " << returnDate<<endl;
        receipt << "Daparture time:  " << returnTime <<":00"<<  endl;
        receipt << "Arrival time:    " << returnTime + abs(deptNum - arrivalNum) * 2<<":00" << endl;
        receipt << "==================================================" << endl;
        //EXAMPLE OUTPUT TO SHOW CALCULATION
        receipt << setprecision(2) << fixed;
        receipt << "Price per ticket:    " << setw(10)<<"$"<<PricePerTicket<<endl;
        receipt << "Extra Bag fees:      " << setw(10)<<"$"<< ExtraBags<<endl;
        receipt << "Tax:                 " << setw(10) << "$" << 0.08*FinalPrice << endl;
        receipt << "Total price:         " << setw(10) << "$" << FinalPrice + 0.08*FinalPrice << endl;
        receipt << "\nThank's for flying with us! Have a safe flight!" << endl;
        }
    }
    else
    {
        cout << "\n";
        cout << "######################################################";

        //Output print everything
        int revsevation;
        revsevation = rand() % 1000000 + 100000;
        cout << "\n\n         THIS IS YOUR AIRPLANE TICKET RECEIPT " << endl;
        cout << "Reservation code: " << revsevation << endl;
        cout << "====================================================" << endl;
        //show list of information of  adults
        cout << "Adult \t\t Name \t\t ID/DL/Passport No" << endl;
        cout << "====================================================" << endl;
        for (int i = 0; i < adult; i++)
        {
            cout << i + 1 << " \t\t " << adults[i] << " \t\t " << ID[i] << endl;
        }

        //show list of information of children
        cout << "\nChildren \t Name \t\t Date of birth" << endl;
        cout << "====================================================" << endl;
        for (int i = 0; i < child; i++)
        {
            cout << i + 1 << " \t\t " << children[i] << " \t\t " << birthDay[i] << endl;
        }

        string deptName, arrivalName;

        switch (deptNum)
        {
        case 1:
            deptName = " Portland(PDX)";
            break;
        case 2:
            deptName = "Los Angeles (LAX)";
            break;
        case 3:
            deptName = "Dallas (DFW)";
            break;
        case 4:
            deptName = "Chicago (ORD)";
            break;
        case 5:
            cout << "New York (JFK)";
            break;
        }
        switch (arrivalNum)
        {
        case 1:
            arrivalName = " Portland(PDX)";
            break;
        case 2:
            arrivalName = "Los Angeles (LAX)";
            break;
        case 3:
            arrivalName = "Dallas (DFW)";
            break;
        case 4:
            arrivalName = "Chicago (ORD)";
            break;
        case 5:
            arrivalName = "New York (JFK)";
            break;
        }

        if (way == 1)
        {

        cout << "====================================================" << endl;
        cout << "Trip:" << deptName << "=====>" << arrivalName << endl;
        cout << "Flight duration: " << abs(deptNum - arrivalNum) * 2 << " hours" << endl;
        cout << "Departure Date:  " << deptDate << endl;
        cout << "Daparture time:  " << deptTime<<":00" << endl;
        cout << "Arrival time:    " << deptTime + abs(deptNum - arrivalNum) * 2 << ":00"  << endl;
        cout << "------------------------------------------------------" << endl;
        //EXAMPLE OUTPUT TO SHOW CALCULATION
        cout << setprecision(2) << fixed;
        cout << "Price per ticket:    " << setw(10)<<"$"<<PricePerTicket<<endl;
        cout << "Extra Bag fees:      " << setw(10)<<"$"<< ExtraBags<<endl;
        cout << "Tax:                 " << setw(10) << "$" << 0.08*FinalPrice << endl;
        cout << "Total price:         " << setw(10) << "$" << FinalPrice + 0.08*FinalPrice << endl;
        cout << "\nThank's for flying with us! Have a safe flight!" << endl;

        }
        else
        {

        cout << "====================================================" << endl;
        cout << "Trip:" << deptName << "=====>" << arrivalName << endl;
        cout << "Flight duration: " << abs(deptNum - arrivalNum) * 2 << " hours" << endl;
        cout << "Departure Date:  " << deptDate << endl;
        cout << "Daparture time:  " << deptTime<<":00" << endl;
        cout << "Arrival time:    " << deptTime + abs(deptNum - arrivalNum) * 2 << ":00"  << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "ReturnTrip:" << arrivalName << "=====>" << deptName << endl;
        cout << "Flight duration: " << abs(deptNum - arrivalNum) * 2 << " hours" << endl;
        cout << "Departure Date:  " << returnDate<<endl;
        cout << "Daparture time:  " << returnTime <<":00"<<  endl;
        cout << "Arrival time:    " << returnTime + abs(deptNum - arrivalNum) * 2<<":00" << endl;
        cout << "==================================================" << endl;
        //EXAMPLE OUTPUT TO SHOW CALCULATION
        cout << setprecision(2) << fixed;
        cout << "Price per ticket:    " << setw(10)<<"$"<<PricePerTicket<<endl;
        cout << "Extra Bag fees:      " << setw(10)<<"$"<< ExtraBags<<endl;
        cout << "Tax:                 " << setw(10) << "$" << 0.08*FinalPrice << endl;
        cout << "Total price:         " << setw(10) << "$" << FinalPrice + 0.08*FinalPrice << endl;
        cout << "\nThank's for flying with us! Have a safe flight!" << endl;

        }
    }

    char h;
    cin >> h;
    return 0;
}

void seatValidation(int &x, int &reX, int &wayVal, int &seatVal)
{
    if (wayVal == 1)
    {
        while (seatVal > x || seatVal < 1)
        {
            cout << "Invalid amount of seats, try again" << endl;
            cin >> seatVal;
        }
    }
    else if (wayVal == 2)
    {
        while (seatVal > x || seatVal > reX || seatVal < 1)
        {
            cout << "Invalid amount of seats, try again" << endl;
            cin >> seatVal;
        }
    }
}


//Function to determine base price per ticket
double BasePrice(double DepartAP, double ArrivAP, int Nonstop, int Way, char Class)
{
    double BasePrice, Comparison, ChildDiscount;


    Comparison = DepartAP - ArrivAP; //VALIDATION NEEDED: Absolute value of the difference between DepartAP and ArrivAP must be between 1 and 4

    if (Comparison == 1 || Comparison == -1)
    {
        BasePrice = 100;
        if (Class == 'B') //Adding cost of higher classes (Business or First)
            BasePrice += 100;
        else if (Class == 'F')
            BasePrice += 200;
        if (Way == 2)
            BasePrice *= 2; //if both ways, price is doubled
        //no nonstop charge, flight is automatically nonstop
    }
    else if (Comparison == 2 || Comparison == -2)
    {
        BasePrice = 200;
        if (Class == 'B')
            BasePrice += 100;
        else if (Class == 'F')
            if (Way == 2)
                BasePrice *= 2;
        if (Nonstop == 1)
            BasePrice += 150;
    }
    else if (Comparison == 3 || Comparison == -3)
    {
        BasePrice = 300;
        if (Class == 'B')
            BasePrice += 100;
        else if (Class == 'F')
            if (Way == 2)
                BasePrice *= 2;
        if (Nonstop == 1)
            BasePrice += 150;
    }
    else
    {
        BasePrice = 400;
        if (Class == 'B')
            BasePrice += 100;
        else if (Class == 'F')
            if (Way == 2)
                BasePrice *= 2;
        if (Nonstop == 1)
            BasePrice += 150;
    }

    return BasePrice;

}

//function to determine extra bag fee
double BagPrice(int Bags, int seatReserve)
{
    double BagFee;
    int ExtraBags;

    ExtraBags = Bags - seatReserve;

    BagFee = ExtraBags * 50;
    return BagFee;
}
