#include <iostream>
#include <random>
#include <time.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_SUBSCRIBERS = 30;
const int MAX_CALLS_FOR_EACH = 100;

struct Subscribers
{
    string subscriberName;
    string contractNumber;
    string phoneNumber;
    int contractPeriod;
    float pricePerMin;
    float monthlyPrice;
    int callHistory[MAX_CALLS_FOR_EACH] = {0}; // In sec's
};

void addSubs(Subscribers* Abonati, int& existingSubscribers)
{
    int n;
    cout << "Choose how many subs you want to add: ";
    if (cin >> n && (n + existingSubscribers) < MAX_SUBSCRIBERS)
    {
        for (int i = 0; i < n; i++) {
            cout << "Please choose name of the " << i + 1 << " subscriber: ";
            cin >> Abonati[existingSubscribers].subscriberName;
            mt19937 mt(time(0));

            Abonati[existingSubscribers].contractNumber = "BG" + to_string(mt() % 999999);

            uniform_real_distribution<float> one_y_min(0.4, 0.7);
            float one_year_perMin = one_y_min(mt) + 0.01;
            uniform_real_distribution<float> one_y_mth(30.5, 40.8);
            float one_year_perMth = one_y_mth(mt) + 0.01;
            uniform_real_distribution<float> two_y_min(0.2, 0.6);
            float two_year_perMin = two_y_min(mt);
            uniform_real_distribution<float> two_y_mth(20.5, 34.2);
            float two_year_perMth = two_y_mth(mt);


            cout << "Here are the prices for 1 and 2 years contracts:"
                << "\n------------------------------------"
                << fixed << setprecision(1)
                << "\n1 YEAR\nPrice on call per min: " << one_year_perMin << " BGN\nPrice per month : " << one_year_perMth << " BGN"
                << "\n------------------------------------"
                << "\n2 YEARS\nPrice on call per min: " << two_year_perMin << " BGN\nPrice per month: " << two_year_perMth << " BGN"
                << "\n------------------------------------"
                << "\nNow, please choose your plan : ";



            while (true)
            {
                if (cin >> Abonati[existingSubscribers].contractPeriod)
                {
                    switch (Abonati[existingSubscribers].contractPeriod)
                    {
                    case 1:
                        Abonati[existingSubscribers].pricePerMin = one_year_perMin;
                        Abonati[existingSubscribers].monthlyPrice = one_year_perMth;
                        cout << "Your plan is now set to period of [1 YEAR/S]" << endl;
                        break;
                    case 2:
                        Abonati[existingSubscribers].pricePerMin = two_year_perMin;
                        Abonati[existingSubscribers].monthlyPrice = two_year_perMth;
                        cout << "Your plan is now set to period of [2 YEAR/S]" << endl;
                        break;
                    default:
                        cout << "The plan you've selected doesn't exist!\nPlease choose correct plan: ";
                        continue;
                    }
                    break;
                }
                else
                {
                    cout << "Wrong Input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter a number: ";
                }
            }

            Abonati[existingSubscribers].phoneNumber = "08" + to_string(mt() % 99999999);

            cout << "\nYour phone number is: " << Abonati[existingSubscribers].phoneNumber << endl;

            existingSubscribers++;
        }
    }
    else
    {
        cin.clear();
        cin.ignore();
        cout << "Wrong Input!" << endl;
    }
}

void showSubs(Subscribers* Abonati, int& existingSubscribers)
{
    for (int i = 0; i < existingSubscribers; ++i)
    {
        cout << "-------------------------------------" << endl;
        cout << "Name: " << Abonati[i].subscriberName << endl;
        cout << "Contract Number: " << Abonati[i].contractNumber << endl;
        cout << "Period: " << Abonati[i].contractPeriod << " YEAR/S" << endl;
        cout << "Phone Number: " << Abonati[i].phoneNumber << endl;
        cout << "Price per MIN: " << Abonati[i].pricePerMin << " BGN" << endl;
        cout << "Monthly Price: " << Abonati[i].monthlyPrice << " BGN" << endl;
        cout << "-------------------------------------" << endl;
    }
}

void findSubsByNum(Subscribers* Abonati, int& existingSubscribers)
{
    bool found = 0;
    string phoneSearch;
    cout << "Enter a phone number: ";
    cin >> phoneSearch;
    for (int i = 0; i < existingSubscribers; ++i)
    {
        if (phoneSearch == Abonati[i].phoneNumber)
        {
            cout << "-------------------------------" << endl << endl;
            cout << "\tUSER FOUND!" << endl;
            cout << "Name: " << Abonati[i].subscriberName << endl;
            cout << "Contact Number: " << Abonati[i].contractNumber << endl;
            cout << "Period: " << Abonati[i].contractPeriod << " YEAR/S" << endl;
            cout << "Phone Number: " << Abonati[i].phoneNumber << endl;
            cout << "Price per MIN: " << Abonati[i].pricePerMin << " BGN" << endl;
            cout << "Monthly Price: " << Abonati[i].monthlyPrice << " BGN" << endl;
            cout << "-------------------------------" << endl << endl;
            found = 1;
        }
        if (i == existingSubscribers && found == 0)
        {
            cout << "Subscriber not found!" << endl;
        }
    }
}

void findSubsByHighRate(Subscribers* Abonati, int& existingSubscribers)
{
    for (int i = 0; i < existingSubscribers - 1; ++i)
    {
        for (int j = 0; j < existingSubscribers - i - 1; ++j)
        {
            if (Abonati[j].pricePerMin < Abonati[j + 1].pricePerMin)
            {
                swap(Abonati[j], Abonati[j + 1]);
            }
        }
    }
    for (int k = 0; k < 3; k++)
    {
        cout << endl << "-------------------" << endl;
        cout << "Name: " << Abonati[k].subscriberName << endl;
        cout << "Price per Min: " << Abonati[k].pricePerMin << " BGN." << endl;
        cout << "-------------------" << endl;
    }
}

void sortSubsByMountlyTax(Subscribers* Abonati, int& existingSubscribers)
{
    for (int i = 0; i < existingSubscribers - 1; ++i)
    {
        for (int j = 0; j < existingSubscribers - i - 1; ++j)
        {
            if (Abonati[j].monthlyPrice > Abonati[j + 1].monthlyPrice)
            {
                swap(Abonati[j], Abonati[j + 1]);
            }
        }
    }
}

void fileOutText(Subscribers* Abonati, int& existingSubscribers)
{
    ofstream outFile("subscriber_info.txt");

    cout << fixed << setprecision(2);

    if (outFile.is_open())
    {
        outFile << "Existing subscribers: " << existingSubscribers << endl << endl;

        for (int i = 0; i < existingSubscribers; i++)
        {
            outFile << "Subscriber Name: " << Abonati[i].subscriberName << endl;
            outFile << "Contract Number: " << Abonati[i].contractNumber << endl;
            outFile << "Phone Number: " << Abonati[i].phoneNumber << endl;
            outFile << "Contract Period: " << Abonati[i].contractPeriod << " YEAR/S." << endl;
            outFile << "Price Per Min Call: " << Abonati[i].pricePerMin << " BGN." << endl;
            outFile << "Monthly Price: " << Abonati[i].monthlyPrice << " BGN." << endl;
            if (Abonati[i].callHistory[0] == 0)
            {
                outFile << "HAS NO CALL HISTORY YET." << endl << endl;
            }
            else
            {
                outFile << "Calls: " << endl;
                for (int k = 0; k < MAX_CALLS_FOR_EACH; k++)
                {
                    if (!(Abonati[i].callHistory[k] == 0))
                        outFile << "Time of Call Number: <" << k + 1 << "> : " 
                        << Abonati[i].callHistory[k] << " sec's." 
                        << "\n------------------------------" << endl;
                    else
                    {
                        break;
                    }
                }
                outFile << "\n";
            }
        }
    }
   
}

void fileOut(Subscribers* Abonati, int& existingSubscribers)
{
    ofstream outFileBin("outfile.bin", ios::out | ios::binary);

    if (!outFileBin.is_open())
    {
        cout << "Error writing to file!" << endl;
        return;
    }

    for (int i = 0; i < existingSubscribers; i++)
    {
        int nameSize = Abonati[i].subscriberName.size();
        outFileBin.write(reinterpret_cast<const char*>(&nameSize), sizeof(int));
        outFileBin.write(Abonati[i].subscriberName.data(), nameSize);

        int contractNumberSize = Abonati[i].contractNumber.size();
        outFileBin.write(reinterpret_cast<const char*>(&contractNumberSize), sizeof(int));
        outFileBin.write(Abonati[i].contractNumber.data(), contractNumberSize);

        int phoneNumberSize = Abonati[i].phoneNumber.size();
        outFileBin.write(reinterpret_cast<const char*>(&phoneNumberSize), sizeof(int));
        outFileBin.write(Abonati[i].phoneNumber.data(), phoneNumberSize);

        outFileBin.write(reinterpret_cast<const char*>(&Abonati[i].contractPeriod), sizeof(int));
        outFileBin.write(reinterpret_cast<const char*>(&Abonati[i].pricePerMin), sizeof(float));
        outFileBin.write(reinterpret_cast<const char*>(&Abonati[i].monthlyPrice), sizeof(float));
        outFileBin.write(reinterpret_cast<const char*>(&Abonati[i].callHistory), sizeof(int) * MAX_CALLS_FOR_EACH);
    }

    outFileBin.close();

    cout << endl << "Subscribers saved successfully!" << endl;
}

void fileIn(Subscribers* Abonati, int& existingSubscribers)
{
    ifstream inFile("outfile.bin", ios::in | ios::binary);

    if (!inFile.is_open())
    {
        cerr << "Error opening file for reading.\n";
        return;
    }

    existingSubscribers = 0;

    while (inFile.peek() != EOF && existingSubscribers < MAX_SUBSCRIBERS)
    {
        int nameSize, contractNumberSize, phoneNumberSize;

        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(int));
        Abonati[existingSubscribers].subscriberName.resize(nameSize);
        inFile.read(&Abonati[existingSubscribers].subscriberName[0], nameSize);

        inFile.read(reinterpret_cast<char*>(&contractNumberSize), sizeof(int));
        Abonati[existingSubscribers].contractNumber.resize(contractNumberSize);
        inFile.read(&Abonati[existingSubscribers].contractNumber[0], contractNumberSize);

        inFile.read(reinterpret_cast<char*>(&phoneNumberSize), sizeof(int));
        Abonati[existingSubscribers].phoneNumber.resize(phoneNumberSize);
        inFile.read(&Abonati[existingSubscribers].phoneNumber[0], phoneNumberSize);

        inFile.read(reinterpret_cast<char*>(&Abonati[existingSubscribers].contractPeriod), sizeof(int));

        inFile.read(reinterpret_cast<char*>(&Abonati[existingSubscribers].pricePerMin), sizeof(float));
        inFile.read(reinterpret_cast<char*>(&Abonati[existingSubscribers].monthlyPrice), sizeof(float));

        cout << fixed << setprecision(2);

        inFile.read(reinterpret_cast<char*>(Abonati[existingSubscribers].callHistory), sizeof(int) * MAX_CALLS_FOR_EACH);

        existingSubscribers++;
    }

    inFile.close();
    cout << endl << "Successfully load subscribers!" << endl;
}

void subscribersTwoYear(Subscribers* Abonati, int& existingSubscribers)
{
    int copySize = 0;
    Subscribers AbonatiCopy[MAX_SUBSCRIBERS];

    for (int i = 0; i < existingSubscribers; i++)
        if (Abonati[i].contractPeriod == 2)
        {
            AbonatiCopy[copySize] = Abonati[i];
            copySize++;
        }

    if (copySize == 0)

        cout << "None of the subscribers have 2 YEAR'S CONTRACT" << endl;

    else
    {
        for (int j = 0; j < copySize; j++)
        {
            for (int k = 0; k < copySize - j - 1; k++)
            {
                if (AbonatiCopy[k].subscriberName[0] > AbonatiCopy[k + 1].subscriberName[0])
                {
                    swap(AbonatiCopy[k], AbonatiCopy[k + 1]);
                }
            }
        }
    }
    
    if (copySize > 0)
    for (int r = 0; r < copySize; r++)
    {
        cout << "-------------------------------------" << endl;
        cout << "Name: " << AbonatiCopy[r].subscriberName << endl;
        cout << "Contract Number: " << AbonatiCopy[r].contractNumber << endl;
        cout << "Period: " << AbonatiCopy[r].contractPeriod << " YEAR/S" << endl;
        cout << "Phone Number: " << AbonatiCopy[r].phoneNumber << endl;
        cout << "Price per MIN: " << AbonatiCopy[r].pricePerMin << " BGN" << endl;
        cout << "Monthly Price: " << AbonatiCopy[r].monthlyPrice << " BGN" << endl;
        cout << "-------------------------------------" << endl;
    }
    
    
}

void oneYearSearch(Subscribers* Abonati, int& existingSubscribers)
{
    Subscribers oneYear[MAX_SUBSCRIBERS];
    float priceChoose;
    bool foundAny;
    int copySize = 0;

    for (int i = 0; i < existingSubscribers; i++)
        if (Abonati[i].contractPeriod == 1)
        {
            oneYear[copySize] = Abonati[i];
            copySize++;
        }

    cout << "What minimum montly tax above we looking at: ";

    if (cin >> priceChoose)
    {
        for (int j = 0; j < copySize; j++)
        {
            if (oneYear[j].monthlyPrice > priceChoose)
            {
                cout << "-------------------------------------" << endl;
                cout << "Name: " << oneYear[j].subscriberName << endl;
                cout << "Contract Number: " << oneYear[j].contractNumber << endl;
                cout << "Period: " << oneYear[j].contractPeriod << " YEAR/S" << endl;
                cout << "Phone Number: " << oneYear[j].phoneNumber << endl;
                cout << "Price per MIN: " << oneYear[j].pricePerMin << " BGN" << endl;
                cout << "Monthly Price: " << oneYear[j].monthlyPrice << " BGN" << endl;
                cout << "-------------------------------------" << endl;
            }
        }
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nWrong Input!\nPlease try again!" << endl;
    }

}

void twoYearSearch(Subscribers* Abonati, int& existingSubscribers)
{
    Subscribers twoYear[MAX_SUBSCRIBERS];
    float priceChoose;
    bool foundAny;
    int copySize = 0;

    for (int i = 0; i < existingSubscribers; i++)
        if (Abonati[i].contractPeriod == 2)
        {
            twoYear[copySize] = Abonati[i];
            copySize++;
        }

    cout << "What minimum montly tax above we looking at: ";

    if (cin >> priceChoose)
    {
        for (int j = 0; j < copySize; j++)
        {
            if (twoYear[j].monthlyPrice > priceChoose)
            {
                cout << "-------------------------------------" << endl;
                cout << "Name: " << twoYear[j].subscriberName << endl;
                cout << "Contract Number: " << twoYear[j].contractNumber << endl;
                cout << "Period: " << twoYear[j].contractPeriod << " YEAR/S" << endl;
                cout << "Phone Number: " << twoYear[j].phoneNumber << endl;
                cout << "Price per MIN: " << twoYear[j].pricePerMin << " BGN" << endl;
                cout << "Monthly Price: " << twoYear[j].monthlyPrice << " BGN" << endl;
                cout << "-------------------------------------" << endl;
            }
        }
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nWrong Input!\nPlease try again!" << endl;
    }

}

void subscribersByUserInput(Subscribers* Abonati, int& existingSubscribers)
{
    int choice;
    cout << "Search by contract period and min monthly tax.\n"
        << "Choose contract period (1 or 2): ";
    
    if (cin >> choice)
    {
        switch (choice)
        {
        case 1:
            oneYearSearch(Abonati, existingSubscribers);
            break;
        case 2:
            twoYearSearch(Abonati, existingSubscribers);
        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nWrong Input!\nPlease try again!" << endl;
            break;
        }
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nWrong Input!\nPlease try again!" << endl;
    }
}

void generateCalls(Subscribers* Abonati, int& existingSubscribers)
{
    mt19937 mt(time(0));

    int numberOfCalls;
    for (int i = 0; i < existingSubscribers; i++)
    {
        numberOfCalls = mt() % 100;
        for (int r = 0; r < numberOfCalls; r++)
        {
            Abonati[i].callHistory[r] = mt() % 3600 + 30;
        }


    }
}

void payTax(Subscribers* Abonati, int& exisistingSubscribers)
{
    string numberFinder;
    bool isNumberFound = 0;
    double callHistoryTotal = 0;
    char choiceChar;
    cout << "Type desire number you want to pay for: ";
    cin >> numberFinder;

    for (int i = 0; i < exisistingSubscribers; i++)
    {
        if (numberFinder == Abonati[i].phoneNumber)
        {
            isNumberFound = 1;
            for (int k = 0; k < MAX_CALLS_FOR_EACH; k++)
            {
                if (Abonati[i].callHistory[k] > 0)
                {
                    callHistoryTotal += Abonati[i].callHistory[k];
                }
                else
                {
                    break;
                }
            }

            if (callHistoryTotal > 0)
            {
                callHistoryTotal = callHistoryTotal / 60;
                
                cout << "You have total of: " << callHistoryTotal << " minutes in calls!" << endl;

                callHistoryTotal = ceil(callHistoryTotal) * Abonati[i].pricePerMin;
                callHistoryTotal += Abonati[i].monthlyPrice;

                cout << "You have: " << callHistoryTotal << " BGN to pay.\n"
                    << "Would you like to do it now? (Y/N): ";

                if (cin >> choiceChar)
                {
                    switch (choiceChar)
                    {
                    case 'y':
                        cout << "Payment completed!" << endl;
                        for (int r = 0; r < 100; r++)
                        {
                            Abonati[i].callHistory[r] = { 0 };
                        }
                        break;
                    case 'n':
                        cout << "You have time until 1 number of the next month to pay: " << callHistoryTotal << " BGN!" << endl;
                        break;
                    default:
                        break;
                    }
                }

            }
            else
            {
                callHistoryTotal = Abonati[i].monthlyPrice;
            }

        }
    }

    if (!isNumberFound)
    {
        cout << "Number not found!" << endl;
    }
}

int main()
{
    Subscribers Abonati[MAX_SUBSCRIBERS];
    int choice;
    int existingSubscribers = 0;    
    bool breakFlag = 0;

    fileIn(Abonati, existingSubscribers);

    while (true)
    {
        cout << "--------------------------------------\n"
            << "Welcome to Telephone Subscribers\n"
            << "1. Add Subscriber.\n"
            << "2. Show all subscribers.\n"
            << "3. Find subscriber.\n"
            << "4. Sort subscribers.\n"
            << "5. Manage file.\n"
            << "6. More.\n\n"
            << "Please choose: ";

        if (cin >> choice)
        {
            switch (choice)
            {
            case 1:
                addSubs(Abonati, existingSubscribers);
                break;
            case 2:
                showSubs(Abonati, existingSubscribers);
                break;
            case 3:
                breakFlag = 0;
                while (true)
                {

                    int choice2;
                    cout << "\n---------------------------------"
                        << "\nHere's 3 options:"
                        << "\n1. Search by Phone Number."
                        << "\n2. Search by highest tax per min."
                        << "\n3. Return."
                        << "\nPlease choose: ";

                    if (cin >> choice2)
                    {
                        switch (choice2)
                        {
                        case 1:
                            findSubsByNum(Abonati, existingSubscribers);
                            break;
                        case 2:
                            findSubsByHighRate(Abonati, existingSubscribers);
                            break;
                        case 3:
                            breakFlag = 1;
                            break;
                        default:
                            cout << "\nSomething went wrong!\nPlease try again!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                    }
                    else
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nWrong Input!\nPlease try again!" << endl;
                    }
                    if (breakFlag)
                        break;
                }
                break;
            case 4:
                sortSubsByMountlyTax(Abonati, existingSubscribers);
                break;
            case 5:
                int choice3;
                cout << "1. Output to file.\n2. Load from file.\nPlease choose: ";
                if (cin >> choice3)
                {
                    switch (choice3)
                    {
                    case 1:
                        fileOut(Abonati, existingSubscribers);
                        fileOutText(Abonati, existingSubscribers);
                        break;
                    case 2:
                        fileIn(Abonati, existingSubscribers);
                        break;
                    case 3:
                        main();
                        break;
                    default:
                        cout << "Something went wrong!";
                        break;
                    }
                }
                else
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Wrong Input!\nPlease try again: ";
                }
                break;
            case 6:
                breakFlag = 0;
                while (true)
                {
                    int choice6;
                    cout << "1. Show subscribers (2 YEAR'S A-Z).\n"
                        << "2. Find subscribers 2.\n"
                        << "3. Generate Calls.\n"
                        << "4. Pay.\n"
                        << "5. Return.\n"
                        << "Please choose: ";
                    if (cin >> choice6)
                    {
                        switch (choice6)
                        {
                        case 1:
                            subscribersTwoYear(Abonati, existingSubscribers);
                            break;
                        case 2:
                            subscribersByUserInput(Abonati, existingSubscribers);
                            break;
                        case 3:
                            generateCalls(Abonati, existingSubscribers);
                            break;
                        case 4:
                            payTax(Abonati, existingSubscribers);
                            break;
                        case 5:
                            breakFlag = 1;
                            break;
                        default:
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\nWrong Input!\nPlease try again!" << endl;
                            break;
                        }
                    }
                    else
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nWrong Input!\nPlease try again!" << endl;
                    }
                    if (breakFlag)
                    {
                        break;
                    }
                }
                break;
            default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nWrong Input!\nPlease try again!" << endl;
                break;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nWrong Input!\nPlease try again!" << endl;
        }
        
            
    }

   fileOut(Abonati, existingSubscribers);
   fileOutText(Abonati, existingSubscribers);

    return 0;
}
