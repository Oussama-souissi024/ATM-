
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowLoginScreen();
void ShowATMMainMenue();
void ShowQuichWithdrawScreen();
void ShowNormalWithdrawScreen();
void ShowDepositAmountscreen();
void showCheckBalanceScreen();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

enum enATMMainMenueOption { eQuichWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5 };

sClient CurrentClient;//global variable

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient  ConvertLineClientToRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double
    return Client;
}

string ConvertClientRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

vector <sClient> LoadClientDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::in);//Read Mode
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineClientToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {                
            DataLine = ConvertClientRecordToLine(C);
            MyFile << DataLine << endl;
        }
        MyFile.close();
    }
    return vClients;
}

void GoBackToATMMenueOption()
{
    cout << "\n\nPress any key to go back to ATM Main Menue...";
    system("pause>0");
    ShowATMMainMenue();
}

short ReadATMMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short ReadQuichWithdrawOption()
{
    cout << "  Choose what do you want to do? [1 to 9]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

bool IsValidAccountNumberAndPinCode(string AcountNumber, string PinCode , sClient& CurrentClient)
{
    vector <sClient> vClients = LoadClientDataFromFile(ClientsFileName);
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AcountNumber && C.PinCode == PinCode)
        {
            CurrentClient = C;
            return true;
        }
    }
    return false;
}

bool authentication()
{
    string AccountNumber = "", PinCode = "";
    cout << "\nEnter AccountNumber?  ";
    getline(cin >> ws, AccountNumber);
    cout << "\nEnter PinCode?  ";
    getline(cin >> ws, PinCode);
    return (IsValidAccountNumberAndPinCode(AccountNumber, PinCode,CurrentClient));
}

void AddAmountToClientBalance(double  Amount)
{
    vector <sClient> vClients = LoadClientDataFromFile(ClientsFileName);
    cout << "\nAre you sure you want perform this transaction y/n   ";
    char Answer = 'N';
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        CurrentClient.AccountBalance -= Amount;
        cout << "\n\nDone successfully. New Balance : " << CurrentClient.AccountBalance   ;
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == CurrentClient.AccountNumber)
            {
                C.AccountBalance = CurrentClient.AccountBalance;
                break;
            }
        }
        SaveCleintsDataToFile(ClientsFileName, vClients);
        GoBackToATMMenueOption();
    }
    else
        GoBackToATMMenueOption();
}

void PerformDepositScreen()
{
    short Amount = 0;
    cout << "\n\nEnter a Positive Amount   ";
    cin >> ws >> Amount;
    while (Amount <= 0)
    {
        cout << "\n\nEror Amount Negative or Null, Please Enter Author Amount   ";
        cin >> ws >> Amount;
    }
    AddAmountToClientBalance(-Amount);
}

void PerformNormalWithdraw()
{
    int Amount = 0;
    cout << "\n\n Enter Ammount Multiple Of 5's  ";
    cin >> ws >>Amount;
    while (Amount % 5 != 0)
    {
        cout << "\nThis amount is not multiple of 5 Please enter an author amount";
        cin >> ws >> Amount;
    }
    AddAmountToClientBalance(Amount);
}

short GetQuickWithdrawrawMenueOption(short Option)
{
    switch (Option)
    {
    case 1:
        return 20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 100;
    default:
        return 0;
    }
}

void PerformQuickWithdrawrawMenueOption()
{
    short Option = ReadQuichWithdrawOption();
    if (Option < 1 || Option > 8)// EXIT
        return;
    short WithdrawAmount = GetQuickWithdrawrawMenueOption(Option);
    if (WithdrawAmount > CurrentClient.AccountBalance)
    {
        cout << "\nThe amout exceeds your balance, make anathor choice .\n";
        cout << "\nPress any key";
        system("pause>0");
        ShowQuichWithdrawScreen();
        return;
    }
    AddAmountToClientBalance(WithdrawAmount);
}

void PerformATMMainMenueOption(enATMMainMenueOption ClientOption)
{
    switch (ClientOption)
    {
    case enATMMainMenueOption::eQuichWithdraw:
        ShowQuichWithdrawScreen();
        GoBackToATMMenueOption();
        break;
    case enATMMainMenueOption::eNormalWithdraw:
        ShowNormalWithdrawScreen();
        GoBackToATMMenueOption();
        break;
    case enATMMainMenueOption::eDeposit:
        ShowDepositAmountscreen();
        GoBackToATMMenueOption();
        break;
    case enATMMainMenueOption::eCheckBalance:
        showCheckBalanceScreen();
        GoBackToATMMenueOption();
        break;
    case enATMMainMenueOption::eLogout:
        ShowLoginScreen();
        break;
    }
}

void showCheckBalanceScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tCheck Balance  Screen\n";
    cout << "===========================================\n";
    cout << "\n\nYour Balance is : " << CurrentClient.AccountBalance;
}

void ShowDepositAmountscreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tDeposit  Screen\n";
    cout << "===========================================\n";
    cout << "\nYour Balance :  " << CurrentClient.AccountBalance;
    PerformDepositScreen();
}

void ShowNormalWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw Screen\n";
    cout << "===========================================\n";
    cout << "\nYour Balance :  " << CurrentClient.AccountBalance;
    PerformNormalWithdraw();
}

void ShowQuichWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] 20  ";                 cout << "\t[2] 50\n";
    cout << "\t[3] 100 ";                 cout << "\t[4] 200\n";
    cout << "\t[5] 400 ";                 cout << "\t[6] 600\n";
    cout << "\t[7] 800 ";                 cout << "\t[8] 1000\n";
    cout << "\t[9] EXIT ";
    cout << "\n===========================================\n";
    cout << "\nYour Balance is : " << CurrentClient.AccountBalance   ;
    PerformQuickWithdrawrawMenueOption();

}

void ShowLoginScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "===========================================\n";
    while (!authentication())
    {
        cout << " Invalid AccountNumber/Password \n";
    }
    ShowATMMainMenue();
}

void ShowATMMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n"; 
    cout << "===========================================\n";
    PerformATMMainMenueOption((enATMMainMenueOption)ReadATMMainMenueOption());
 }


int main()
{
    ShowLoginScreen();
    system("Pause>0");
}



