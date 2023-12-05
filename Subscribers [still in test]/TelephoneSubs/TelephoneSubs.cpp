#include <iostream>
#include <random>
#include <time.h>
#include <iomanip>
#include <string>
#include <fstream>

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
    if (cin >> n && (n + existingSubscribers) <= MAX_SUBSCRIBERS)
        for (int i = 0; i < n; i++) {
            cout << "Please choose name of the " << i + 1 << " subscriber: ";
            cin >> Abonati[existingSubscribers].subscriberName;
            mt19937 mt(time(0));

            mt19937 gen(mt());

            Abonati[existingSubscribers].contractNumber = "BG" + to_string(mt() % 999999);

            uniform_real_distribution<float> one_y_min(2.3, 5.6);
            float one_year_perMin = one_y_min(mt) + 0.01;
            uniform_real_distribution<float> one_y_mth(30.5, 40.8);
            float one_year_perMth = one_y_mth(mt) + 0.01;
            uniform_real_distribution<float> two_y_min(1.3, 4.6);
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
    else
        cout << "Wrong Input or reached max subscribers!" << endl;
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
    for (int i = 0; i < existingSubscribers; i++)
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
        // Write the size of the string, followed by the string data
        int nameSize = Abonati[i].subscriberName.size();
        outFileBin.write(reinterpret_cast<const char*>(&nameSize), sizeof(int));
        outFileBin.write(Abonati[i].subscriberName.c_str(), nameSize);

        int contractNumberSize = Abonati[i].contractNumber.size();
        outFileBin.write(reinterpret_cast<const char*>(&contractNumberSize), sizeof(int));
        outFileBin.write(Abonati[i].contractNumber.c_str(), contractNumberSize);

        int phoneNumberSize = Abonati[i].phoneNumber.size();
        outFileBin.write(reinterpret_cast<const char*>(&phoneNumberSize), sizeof(int));
        outFileBin.write(Abonati[i].phoneNumber.c_str(), phoneNumberSize);

        // Write the remaining non-string data
        outFileBin.write(reinterpret_cast<const char*>(&Abonati[i].contractPeriod), sizeof(int));
        outFileBin.write(reinterpret_cast<const char*>(&Abonati[i].pricePerMin), sizeof(float));
        outFileBin.write(reinterpret_cast<const char*>(&Abonati[i].monthlyPrice), sizeof(float));
        outFileBin.write(reinterpret_cast<const char*>(Abonati[i].callHistory), sizeof(int) * MAX_CALLS_FOR_EACH);
    }

    outFileBin.close();

    cout << "Subscribers saved successfully!" << endl;
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

        // Read the size of the string, then read the string data
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(int));
        Abonati[existingSubscribers].subscriberName.resize(nameSize);
        inFile.read(&Abonati[existingSubscribers].subscriberName[0], nameSize);

        inFile.read(reinterpret_cast<char*>(&contractNumberSize), sizeof(int));
        Abonati[existingSubscribers].contractNumber.resize(contractNumberSize);
        inFile.read(&Abonati[existingSubscribers].contractNumber[0], contractNumberSize);

        inFile.read(reinterpret_cast<char*>(&phoneNumberSize), sizeof(int));
        Abonati[existingSubscribers].phoneNumber.resize(phoneNumberSize);
        inFile.read(&Abonati[existingSubscribers].phoneNumber[0], phoneNumberSize);

        // Read the remaining non-string data
        inFile.read(reinterpret_cast<char*>(&Abonati[existingSubscribers].contractPeriod), sizeof(int));
        inFile.read(reinterpret_cast<char*>(&Abonati[existingSubscribers].pricePerMin), sizeof(float));
        inFile.read(reinterpret_cast<char*>(&Abonati[existingSubscribers].monthlyPrice), sizeof(float));
        inFile.read(reinterpret_cast<char*>(Abonati[existingSubscribers].callHistory), sizeof(int) * MAX_CALLS_FOR_EACH);

        existingSubscribers++;
    }

    inFile.close();
    cout << "Done!" << endl;
}

int main()
{
    Subscribers Abonati[MAX_SUBSCRIBERS];
    int choice;
    int existingSubscribers = 0;    

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
                        main();
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

    return 0;
}
