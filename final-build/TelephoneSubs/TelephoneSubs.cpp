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

const float MIN_ONEYEAR_PAYMENT_MTH = 30.5f;
const float MAX_ONEYEAR_PAYMENT_MTH = 40.8f;
const float MIN_TWOYEAR_PAYMENT_MTH = 20.5f;
const float MAX_TWOYEAR_PAYMENT_MTH = 34.2f;

const float MIN_ONEYEAR_PAYMENT_MIN = 0.18f;
const float MAX_ONEYEAR_PAYMENT_MIN = 0.28f;
const float MIN_TWOYEAR_PAYMENT_MIN = 0.10f;
const float MAX_TWOYEAR_PAYMENT_MIN = 0.21f;

struct Subscribers // Структура от ТИП: Subscribers
{
    string subscriberName;
    string contractNumber;
    string phoneNumber;
    int contractPeriod;
    float pricePerMin;
    float monthlyPrice;
    int callHistory[MAX_CALLS_FOR_EACH] = { 0 }; // Запаметява в секунди (трябва да бъде обърнато в мин за фун: payTax();
};

void generator(Subscribers* Abonati, int& existingSubscribers, float& one_year_minn, float& one_year_monthh, float& two_year_minn, float& two_year_monthh);
void add_subscribers(Subscribers* Abonati, int& existingSubscribers);

void show_call_history(Subscribers* Abonati, int& exisitngSubscribers);
void show_subscribers(Subscribers* Abonati,int& existingSubscribers);

void search_by_highest_min_tax(Subscribers* Abonati, int& existingSubscribers);
void search_by_phone_number(Subscribers* Abonati, int& exisingSubscribers);
void validate_for_return_search(Subscribers* Abonati, int& existingSubscribers);

void sort_by_montly_payment(Subscribers* Abonati, int& existingSubscribers);

void write_file_text(Subscribers* Abonati, int& existingSubscribers);
void write_file_binary(Subscribers* Abonati, int& existingSubscribers);
void read_file_binary(Subscribers* Abonati, int& existingSubscribers);
void validate_for_file(Subscribers* Abonati, int& existingSubscribers);

void more_options(Subscribers* Abonati, int& existingSubscribers);

void two_year_name_search(Subscribers* Abonati, int& existingSubscribers);

void search_for_one_year(Subscribers* Abonati, int& existingSubscribers);
void search_for_two_years(Subscribers* Abonati, int& existingSubscribers);
void search_by_parametar(Subscribers* Abonati, int& existingSubscribers);

void generate_calls_one_subscriber(Subscribers* Abonati, int& existingSubscribers);
void generate_calls_all_subscribers(Subscribers* Abonati, int& existingSubscribers);
void generate_calls(Subscribers* Abonati, int& existingSubscribers);
void pay(Subscribers* Abonati, int& existingSubscribers);

int main()
{

    Subscribers Abonati[MAX_SUBSCRIBERS];

    int first_choice;
    int forth_choice;

    int existingSubscribers = 0;

    bool return_menu_flag = 0;

    read_file_binary(Abonati, existingSubscribers); // Чете двоичен код при стартиране на програмата (Допълнение 3)

    do
    {
        cout 
            << "================================\n"
            << "Welcome to Telephone Manager!\n"
            << "================================\n"
            << "Here are the options we offer!\n"
            << "1. Add a subscriber.\n"
            << "2. Show all the subscribers.\n"
            << "3. Find a subscriber.\n"
            << "4. Sort the subscribers.\n"
            << "5. LOAD/SAVE subscribers.\n"
            << "6. More options.\n\n"
            << "Make your choice now: ";

        if (cin >> first_choice)
        {
            switch (first_choice)
            {
            case 1:
                add_subscribers(Abonati, existingSubscribers);

                break;

            case 2:
                show_subscribers(Abonati, existingSubscribers);
                break;

            case 3:
                validate_for_return_search(Abonati, existingSubscribers);
                break;

            case 4:
                sort_by_montly_payment(Abonati, existingSubscribers);
                break;

            case 5:
                validate_for_file(Abonati, existingSubscribers);
                break;

            case 6:
                more_options(Abonati, existingSubscribers);
                break;

            default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout 
                    << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                    << "Wrong Input!\n"
                    << "Please try again!\n"
                    << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
                break;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout 
                << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                << "Wrong Input!\n"
                << "Please try again!\n"
                << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
        }

    } while (true);

    // Допълнение 3
    write_file_text(Abonati, existingSubscribers);
    write_file_binary(Abonati, existingSubscribers);

    return 0;
}

void generator(Subscribers* Abonati, int& exisitngSubscribers, float& one_year_minn, float& one_year_monthh, float& two_year_minn, float& two_year_monthh)
{

    mt19937 mt(time(0)); // Сийд на генератора по време, така че да не се повтаря генерираното число

    Abonati[exisitngSubscribers].contractNumber = "BG" + to_string(mt() % 999999); // Генерира уникален номер на абоната
     
    Abonati[exisitngSubscribers].phoneNumber = "08" + to_string(mt() % 99999999); // Генериране уникален телефонен номер на абоната

    // Използавне на <random> генератор за генериране на таксуване от тип "float"
    uniform_real_distribution<float> one_year_min(MIN_ONEYEAR_PAYMENT_MIN, MAX_ONEYEAR_PAYMENT_MIN);
    one_year_minn = one_year_min(mt);

    uniform_real_distribution<float> one_year_month(MIN_ONEYEAR_PAYMENT_MTH, MAX_ONEYEAR_PAYMENT_MTH);
    one_year_monthh = one_year_month(mt);

    uniform_real_distribution<float> two_year_min(MIN_TWOYEAR_PAYMENT_MIN, MAX_TWOYEAR_PAYMENT_MIN);
    two_year_minn = two_year_min(mt);

    uniform_real_distribution<float> two_year_month(MIN_TWOYEAR_PAYMENT_MTH, MAX_TWOYEAR_PAYMENT_MTH);
    two_year_monthh = two_year_month(mt);

}

void add_subscribers(Subscribers* Abonati, int& existingSubscribers)
{
    float one_year_minn, one_year_monthh, two_year_minn, two_year_monthh;


    int choice_how_many;

    cout << "How many subscribers would you like to add?: ";

    if (cin >> choice_how_many && choice_how_many + existingSubscribers < MAX_SUBSCRIBERS)
    {
        for (int i = 0; i < choice_how_many; i++)
        {
            cout << "Please choose name of the " << i + 1 << " subscriber you want to add: ";

            cin >> Abonati[existingSubscribers].subscriberName;

            generator(Abonati, existingSubscribers, one_year_minn, one_year_monthh, two_year_minn, two_year_monthh);

            cout 
                << fixed << setprecision(2)
                << "\nHere are our special offers for you!\n"
                << "---------------------\n"
                << "| 1 YEAR contract:  |\n"
                << "| " << one_year_minn << " BGN CALL/MIN.|\n"
                << "|" << one_year_monthh << " BGN MONTHLY. |\n"
                << "---------------------" << endl;

            cout
                << "---------------------\n"
                << "| 2 YEAR contract:  |\n"
                << "| " << two_year_minn << " BGN CALL/MIN.|\n"
                << "|" << two_year_monthh << " BGN MONTHLY. |\n"
                << "---------------------\n";

            cout << "Please choose you're plan: ";

            do
            {
                if (cin >> Abonati[existingSubscribers].contractPeriod)
                {
                    switch (Abonati[existingSubscribers].contractPeriod)
                    {
                    case 1:
                        Abonati[existingSubscribers].contractPeriod = 1;
                        Abonati[existingSubscribers].pricePerMin = one_year_minn;
                        Abonati[existingSubscribers].monthlyPrice = one_year_monthh;
                        break;

                    case 2:
                        Abonati[existingSubscribers].contractPeriod = 2;
                        Abonati[existingSubscribers].pricePerMin = two_year_minn;
                        Abonati[existingSubscribers].monthlyPrice = two_year_monthh;
                        break;

                    default:
                        cout << "Wrong Input!\nPlease try again!" << endl;
                        cout << "Please choose you're plan: ";
                        continue;
                    }
                }
                else
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Wrong Input!\nPease try again!" << endl;
                    cout << "Please choose you're plan: ";
                    continue;
                }

                break;
            } while (true);
            
            cout
                << "\nSUBSCRIBER:" << endl
                << "Name: " << Abonati[existingSubscribers].subscriberName << endl
                << "Contract Number: " << Abonati[existingSubscribers].contractNumber << endl
                << "Phone Number: " << Abonati[existingSubscribers].phoneNumber << endl
                << "Contract Period: " << Abonati[existingSubscribers].contractPeriod << " YEAR/S" << endl
                << "CREATED SUCCESFULLY!" << endl
                << endl;

            existingSubscribers++;
        }
    }
}

void show_call_history(Subscribers* Abonati, int& exisitngSubscribers)
{
    int subscriber_choosen;

    cout
        << "Which subscriber you want to see?\n"
        << "(every subscriber is shown with number)\n"
        << "Please choose: ";

    if (cin >> subscriber_choosen)
    {
        subscriber_choosen = subscriber_choosen - 1;
        if (Abonati[subscriber_choosen].callHistory[0] > 0)
        {
            for (int j = 0; j < MAX_CALLS_FOR_EACH; j++)
            {
                if (Abonati[subscriber_choosen].callHistory[j] > 0)
                {
                    cout << "Call Number <" << j + 1 << "> :" << Abonati[subscriber_choosen].callHistory[j] << " seconds." << endl;
                }
                else {
                    break;
                }
            }
        }
        else if (Abonati[subscriber_choosen].callHistory[0] == 0)
        {
            cout 
                << "\nThis subscriber has no call history yet.\n"
                << "Make some calls and then try again!\n" << endl;
        }
        else
        {
            cout << "Invalid subscriber or choice!" << endl;
        }
    }
    else
    {
        cin.clear();
        cin.ignore();
        cout
            << "\n-/-/-/-/-/-/-/-/-/-/-\n"
            << "Wrong Input!\n"
            << "Please try again!\n"
            << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
    }
}

void show_subscribers(Subscribers* Abonati, int& existingSubscribers)
{
    char want_to_see;

    for (int i = 0; i < existingSubscribers; i++)
    {
        cout
            << "--------- " << i+1 << " ----------\n"
            << "Name: " << Abonati[i].subscriberName << endl
            << "Contract Number: " << Abonati[i].contractNumber << endl
            << "Phone Number: " << Abonati[i].phoneNumber << endl
            << "Contract Period: " << Abonati[i].contractPeriod << " YEAR/S." << endl
            << "Price Per Min: " << Abonati[i].pricePerMin << " BGN." << endl
            << "Montly Price: " << Abonati[i].monthlyPrice << " BGN." << endl
            << "---------------------" << endl;
    }

    cout << "Do you want to see any subscriber call history? (Y/N): ";

    if (cin >> want_to_see)
    {
        want_to_see = tolower(want_to_see);
        switch (want_to_see)
        {
        case 'y':
            show_call_history(Abonati, existingSubscribers);
            break;
        case 'n':
            break;
        default:
            cin.clear();
            cin.ignore();
            cout
                << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                << "Wrong Input!\n"
                << "Please try again!\n"
                << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
        }
    }
    else
    {
        cin.clear();
        cin.ignore();
        cout
            << "\n-/-/-/-/-/-/-/-/-/-/-\n"
            << "Wrong Input!\n"
            << "Please try again!\n"
            << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
    }
}

void show_one_subscriber(Subscribers* Abonati, int& existingSubscribers, int& looking_for_number)
{
    cout
        << endl << endl
        << "Name: " << Abonati[looking_for_number].subscriberName << endl
        << "Contract Number: " << Abonati[looking_for_number].contractNumber << endl
        << "Phone Number: " << Abonati[looking_for_number].phoneNumber << endl
        << "Contract Period: " << Abonati[looking_for_number].contractPeriod << " YEAR/S." << endl
        << "Price Per Min: " << Abonati[looking_for_number].pricePerMin << " BGN." << endl
        << "Montly Price: " << Abonati[looking_for_number].monthlyPrice << " BGN." << endl
        << "---------------------" << endl << endl;
}

void search_by_phone_number(Subscribers* Abonati, int& exisingSubscribers)
{
    string number_looking;
    char full_info;
    bool is_number_found = 0;
    cout << "Please type the desire number here: ";

    cin >> number_looking;

    for (int i = 0; i < exisingSubscribers; i++)
    {
        if (number_looking == Abonati[i].phoneNumber)
        {
            cout
                << "\nSUBSCRIBER: " << number_looking << " FOUND!\n"
                << "Name: " << Abonati[i].subscriberName << endl
                << "Do you want to see full info? (Y/N) : ";

            if (cin >> full_info)
            {
                full_info = tolower(full_info);
                switch (full_info)
                {
                case 'y':
                    show_one_subscriber(Abonati, exisingSubscribers, i);
                    break;
                case 'n':
                    break;
                default:
                    break;
                }
            }
            else
            {
                cin.clear();
                cin.ignore();
                cout
                    << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                    << "Wrong Input!\n"
                    << "Please try again!\n"
                    << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
            }
        }
    }
}

void search_by_highest_min_tax(Subscribers* Abonati, int& existingSubscribers)
{

    Subscribers CopyOfAbonati[MAX_SUBSCRIBERS];


        for (int i = 0; i < existingSubscribers - 1; ++i)
        {
            bool any_swapped = 0;

            for (int j = 0; j < existingSubscribers - i - 1; ++j)
            {
                if (Abonati[j].pricePerMin < Abonati[j + 1].pricePerMin)
                {
                    swap(Abonati[j], Abonati[j + 1]);
                    any_swapped = 1;
                }

            }

            if (!any_swapped)
            {
                break;
            }
        }

        for (int k = 0; k < 1; k++)
        {
            CopyOfAbonati[k] = Abonati[k];

                cout
                    << "\n--------- " << "HIGHEST" << " ----------\n"
                    << "Name: " << Abonati[k].subscriberName << endl
                    << "Contract Number: " << Abonati[k].contractNumber << endl
                    << "Phone Number: " << Abonati[k].phoneNumber << endl
                    << "Contract Period: " << Abonati[k].contractPeriod << " YEAR/S." << endl
                    << "PRICE PER MIN: " << Abonati[k].pricePerMin << " BGN." << endl
                    << "Montly Price: " << Abonati[k].monthlyPrice << " BGN." << endl
                    << "---------------------" << endl;
        }
}

void validate_for_return_search(Subscribers* Abonati, int& existingSubscribers)
{
    int search_choice;

    cout
        << "\nHere are the way's to find a subscriber:\n"
        << "1. Search by phone number.\n"
        << "2. Search by high per call/min tax.\n"
        << "3. Return." << endl
        << "Please make your choice: ";

    if (cin >> search_choice)
    {
        switch (search_choice)
        {
        case 1:
            search_by_phone_number(Abonati, existingSubscribers);
            break;

        case 2:
            search_by_highest_min_tax(Abonati, existingSubscribers);
            break;
        case 3:
            break;
        default:
            cin.clear();
            cin.ignore();
            cout
                << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                << "Wrong Input!\n"
                << "Please try again!\n"
                << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
            break;
        }
    }
    else
    {
        cin.clear();
        cin.ignore();
        cout
            << "\n-/-/-/-/-/-/-/-/-/-/-\n"
            << "Wrong Input!\n"
            << "Please try again!\n"
            << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
    }
}

void sort_by_montly_payment(Subscribers* Abonati, int& existingSubscribers)
{
    for (int i = 0; i < existingSubscribers - 1; i++)
    {
        bool any_swapped = 0;

        for (int j = 0; j < existingSubscribers - i - 1; j++)
        {
            if (Abonati[j].monthlyPrice > Abonati[j + 1].monthlyPrice)
            {
                swap(Abonati[j], Abonati[j + 1]);
                any_swapped = 1;
            }
        }

        if (!any_swapped)
        {
            break;
        }
    }
}

void write_file_text(Subscribers* Abonati, int& existingSubscribers)
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

void write_file_binary(Subscribers* Abonati, int& existingSubscribers)
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

void read_file_binary(Subscribers* Abonati, int& existingSubscribers)
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
    cout << endl << "Successfully loaded subscribers!" << endl;
}

void validate_for_file(Subscribers* Abonati, int& existingSubscribers)
{
    int file_choice;

    cout
        << "\nHere are the way's to manage a file:\n"
        << "1. Save to file.\n"
        << "2. Load from file.\n"
        << "3. Return." << endl
        << "Please make your choice: ";

    if (cin >> file_choice)
    {
        switch (file_choice)
        {
        case 1:
            write_file_text(Abonati, existingSubscribers);
            write_file_binary(Abonati, existingSubscribers);
            break;

        case 2:
            read_file_binary(Abonati, existingSubscribers);
            break;
        case 3:
            break;
        default:
            cin.clear();
            cin.ignore();
            cout
                << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                << "Wrong Input!\n"
                << "Please try again!\n"
                << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
            break;
        }
    }
    else
    {
        cin.clear();
        cin.ignore();
        cout
            << "\n-/-/-/-/-/-/-/-/-/-/-\n"
            << "Wrong Input!\n"
            << "Please try again!\n"
            << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
    }
}

void two_year_name_search(Subscribers* Abonati, int& existingSubscribers)
{
    int copy_size = 0;

    Subscribers AbonatiCopy[MAX_SUBSCRIBERS];

    for (int i = 0; i < existingSubscribers; i++)
        if (Abonati[i].contractPeriod == 2)
        {
            AbonatiCopy[copy_size] = Abonati[i];
            copy_size++;
        }

    if (copy_size == 0)

        cout << "None of the subscribers have 2 YEAR'S CONTRACT" << endl;

    else
    {
        for (int j = 0; j < copy_size; j++)
        {
            bool any_swapped = 0;

            for (int k = 0; k < copy_size - j - 1; k++)
            {
                if (AbonatiCopy[k].subscriberName[0] > AbonatiCopy[k + 1].subscriberName[0])
                {
                    swap(AbonatiCopy[k], AbonatiCopy[k + 1]);
                    any_swapped = 1;
                }
            }

            if (!any_swapped)
                break;
        }
    }

    if (copy_size > 0)
        for (int r = 0; r < copy_size; r++)
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
void search_for_one_year(Subscribers* Abonati, int& existingSubscribers)
{
    float min_tax;
    int two_years_subscribers = 0;
    bool any_found = 0;

    for (int i = 0; i < existingSubscribers; i++)
    {
        if (Abonati[i].contractPeriod == 1)
        {
            two_years_subscribers++;
            any_found = 1;
        }
    }

    if (any_found)
    {
        any_found = 0;
        cout << "Please choose minimum montly tax: ";

        if (cin >> min_tax)
        {
            for (int j = 0; j < two_years_subscribers; j++)
            {
                if (Abonati[j].monthlyPrice > min_tax)
                {
                    any_found = 1;

                    cout
                        << "\n---------------------------\n"
                        << "Name: " << Abonati[j].subscriberName << endl
                        << "Contract Number: " << Abonati[j].contractNumber << endl
                        << "Phone Number: " << Abonati[j].phoneNumber << endl
                        << "Contract Period: " << Abonati[j].contractPeriod << " YEAR/S." << endl
                        << "PRICE PER MIN: " << Abonati[j].pricePerMin << " BGN." << endl
                        << "Montly Price: " << Abonati[j].monthlyPrice << " BGN." << endl
                        << "---------------------------\n";
                }
            }

            if (!any_found)
            {
                cout << "None of the subscribers met your requirements!" << endl;
            }
        }
    }
}

void search_for_two_years(Subscribers* Abonati, int& existingSubscribers)
{
    float min_tax;
    int two_years_subscribers = 0;
    bool any_found = 0;

    for (int i = 0; i < existingSubscribers; i++)
    {
        if (Abonati[i].contractPeriod == 2)
        {
            two_years_subscribers++;
            any_found = 1;
        }
    }

    if (any_found)
    {
        any_found = 0;
        cout << "Please choose minimum montly tax: ";

        if (cin >> min_tax)
        {
            for (int j = 0; j < two_years_subscribers; j++)
            {
                if (Abonati[j].monthlyPrice > min_tax)
                {
                    any_found = 1;

                    cout
                        << "\n---------------------------\n"
                        << "Name: " << Abonati[j].subscriberName << endl
                        << "Contract Number: " << Abonati[j].contractNumber << endl
                        << "Phone Number: " << Abonati[j].phoneNumber << endl
                        << "Contract Period: " << Abonati[j].contractPeriod << " YEAR/S." << endl
                        << "PRICE PER MIN: " << Abonati[j].pricePerMin << " BGN." << endl
                        << "Montly Price: " << Abonati[j].monthlyPrice << " BGN." << endl
                        << "---------------------------\n";
                }
            }

            if (!any_found)
            {
                cout << "None of the subscribers met your requirements!" << endl;
            }
        }
    }
}

void search_by_parametar(Subscribers* Abonati, int& existingSubscribers)
{
    int parametar_choice;

    cout << "Search by contract period and min monthly tax.\n"
        << "Choose contract period (1 or 2): ";

    if (cin >> parametar_choice)
    {
        switch (parametar_choice)
        {
        case 1:
            search_for_one_year(Abonati, existingSubscribers);
            break;
        case 2:
            search_for_two_years(Abonati, existingSubscribers);
            break;
        default:
            cin.clear();
            cin.ignore();
            cout
                << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                << "Wrong Input!\n"
                << "Please try again!\n"
                << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
            break;
        }
    }
    else {
        cin.clear();
        cin.ignore();
        cout
            << "\n-/-/-/-/-/-/-/-/-/-/-\n"
            << "Wrong Input!\n"
            << "Please try again!\n"
            << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
    }
}

void generate_calls_one_subscriber(Subscribers* Abonati, int& existingSubscribers)
{
    string search_phone_number;
    bool is_number_found = 0;
    int number_of_calls;
    cout << "Please type the phone number of desire subscriber: ";

    cin >> search_phone_number;

    for (int i = 0; i < existingSubscribers; i++)
    {
        if (search_phone_number == Abonati[i].phoneNumber)
        {
            mt19937 mt(time(0));

            number_of_calls = mt() % 100;

            for (int j = 0; j < number_of_calls; j++)
            {
                Abonati[i].callHistory[j] = mt() % 3600 + 30;
            }
        }
    }


    if (!is_number_found)
    {
        cin.clear();
        cin.ignore();
        cout << "Number not found!\n" << endl;
    }
    else
        cout << "Succesfully generated calls!" << endl;

}

void generate_calls_all_subscribers(Subscribers* Abonati, int& existingSubscribers)
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

    cout << "Succesfully generated calls!" << endl;
}

void generate_calls(Subscribers* Abonati, int& existingSubscribers)
{
    int generate_choice;

    do
    {
        cout
            << "\nOptions for call generation:\n"
            << "1. Generate for single subscriber.\n"
            << "2. Generate for all subscribers.\n"
            << "3. Return.\n"
            << "Please choose: ";

        if (cin >> generate_choice)
        {
            switch (generate_choice)
            {
            case 1:
                generate_calls_one_subscriber(Abonati, existingSubscribers);
                break;
            case 2:
                generate_calls_all_subscribers(Abonati, existingSubscribers);
                break;
            case 3:
                break;
            default:
                cin.clear();
                cin.ignore();
                cout
                    << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                    << "Wrong Input!\n"
                    << "Please try again!\n"
                    << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
                continue;
            }
        }
        else
        {
            cin.clear();
            cin.ignore();
            cout
                << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                << "Wrong Input!\n"
                << "Please try again!\n"
                << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
            continue;
        }
        break;
    } while (true);
}

void pay(Subscribers* Abonati, int& existingSubscribers)
{
    string number_finder;
    bool is_number_found = 0;
    double call_history_total = 0;
    char choice_char;

    cout << "Type desire number you want to pay for: ";

    cin >> number_finder;

    for (int i = 0; i < existingSubscribers; i++)
    {
        if (number_finder == Abonati[i].phoneNumber)
        {
            is_number_found = 1;
            for (int k = 0; k < MAX_CALLS_FOR_EACH; k++)
            {
                if (Abonati[i].callHistory[k] > 0)
                {
                    call_history_total += Abonati[i].callHistory[k];
                }
            }

            if (call_history_total == 0 || call_history_total < 0)
            {
                cout << "\nThe subscriber has no call history.\n"
                    << "You have to pay only montly price which is: " << Abonati[i].monthlyPrice << " BGN"
                    << endl << "Whould you like to pay it now? (Y/N): ";

                cin >> choice_char;

                switch (choice_char)
                {
                case 'y':
                    cout << "Succesfully paid: " << Abonati[i].monthlyPrice << " BGN." << endl;
                    break;
                case 'n':
                    cout << "Ok, but remember you have time to pay: " << Abonati[i].monthlyPrice << " BGN\n"
                        << "until next 1 number of the month" << endl;
                    break;
                default:
                    cin.clear();
                    cin.ignore();
                    cout << "Wrong Input!\nPlease try again!" << endl;
                    break;
                }

            }
            else
            {
                call_history_total = (ceil(call_history_total) / 60) * Abonati[i].pricePerMin;

                cout << "You have to pay: " << call_history_total << " BGN for calls.\n"
                    << "And: " << Abonati[i].monthlyPrice << " BGN montly price." << endl;

                call_history_total += Abonati[i].monthlyPrice;

                cout << "In Total of: " << call_history_total << " BGN.\n"
                    << "Would you like to pay now? (Y/N): ";

                cin >> choice_char;

                switch (choice_char)
                {
                case 'y':
                    cout << "Succesfully paid: " << call_history_total << " BGN.\n";
                    for (int j = 0; j < MAX_CALLS_FOR_EACH; j++)
                    {
                        Abonati[i].callHistory[j] = 0;
                    }
                    break;
                case 'n':
                    cout << "Ok, but remember you have time to pay: " << call_history_total << " BGN until 1 number of the month!" << endl;
                    break;
                default:
                    break;
                }
            }
        }
    }

    if (!is_number_found)
    {
        cout << "\nInvalid Number!\nPlease try again!" << endl;
    }
}

void more_options(Subscribers* Abonati, int& existingSubscribers)
{
    int option_choose;

    do
    {
        cout
            << "\nMore Options:\n"
            << "1. [TWO YEAR] contract subscribers.\n"
            << "2. Search subscribers by parameters.\n"
            << "3. Generate calls.\n"
            << "4. Pay.\n"
            << "5. Return." << endl
            << "Please make your choice: ";

        if (cin >> option_choose)
        {
            switch (option_choose)
            {
            case 1:
                two_year_name_search(Abonati, existingSubscribers);
                continue;
            
            case 2:
                search_by_parametar(Abonati, existingSubscribers);
                break;

            case 3:
                generate_calls(Abonati, existingSubscribers);
                break;

            case 4:
                pay(Abonati, existingSubscribers);
                break;

            case 5:
                break;

            default:
                cin.clear();
                cin.ignore();
                cout
                    << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                    << "Wrong Input!\n"
                    << "Please try again!\n"
                    << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
                break;
            }
        }
        else
        {
            cin.clear();
            cin.ignore();
            cout
                << "\n-/-/-/-/-/-/-/-/-/-/-\n"
                << "Wrong Input!\n"
                << "Please try again!\n"
                << "-/-/-/-/-/-/-/-/-/-/-\n" << endl;
        }
        break;
    } while (true);
}