#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

const int MAX_MEMBERS = 1000;  // Maximum number of members
const int MAX_TRANSACTIONS = 100;  // Maximum number of transactions

bool isPureInteger(const string& str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// Takes integer input
void Input(int *x)
{
    string userInput;
    *x = 0;
    cin >> userInput;
    if (isPureInteger(userInput))
    {
        *x = stoi(userInput);
    }
    return ;
}

bool isPureDouble(const string& str)
{
    istringstream ss(str);
    double value;
    ss >> value;
    return ss.eof() && !ss.fail();
}

// Takes double input
void InputD(double *x)
{
    string userInput;
    *x = 0.0;
    cin >> userInput;

    if (isPureDouble(userInput))
    {
        *x = stod(userInput);
    }
    return;
}

// Class for transaction history
class History
{
private:
    string transactionType;
    double amount;
    string dateAndTime;
    string notes;

public:
    History(string type, double amt, string dt, string n)
        : transactionType(type), amount(amt), dateAndTime(dt), notes(n) {}

    History() : transactionType(""), amount(0.0), dateAndTime(""), notes("") {}

    string getTransactionType() const
    {
        return transactionType;
    }
    double getAmount() const
    {
        return amount;
    }
    string getDateAndTime() const
    {
        return dateAndTime;
    }
    string getNotes() const
    {
        return notes;
    }
};
History transactionHistory[MAX_MEMBERS][MAX_TRANSACTIONS]; // Global array for transaction history

// Class for member data
class Member
{
private:
    string mobile;
    string name;
    double amount;
    string pin;
    bool Exist;
    History transactionHistory[MAX_TRANSACTIONS];
    int transactionCount;

public:
    Member(string m, string n, double amt, string p)
        : mobile(m), name(n), amount(amt), pin(p), Exist(true), transactionCount(0) {}

    Member() : mobile(""), name(""), amount(0.0), pin(""), Exist(false), transactionCount(0) {}

    void reduceAmount(double Amount)
    {
        if (Amount <= amount)
        {
            amount -= Amount;
        }
    }
    void increaseAmount(double Amount)
    {
        amount += Amount;
    }
    void setName(string Name)
    {
        name = Name;
    }
    void setPin(string Pin)
    {
        pin = Pin;
    }
    void setExist(bool exist)
    {
        Exist = exist;
    }
    string getMobile() const
    {
        return mobile;
    }
    string getName() const
    {
        return name;
    }
    double getAmount() const
    {
        return amount;
    }
    bool doesExist() const
    {
        return Exist;
    }
    string getPin() const
    {
        return pin;
    }

    void addTransaction(const History& transaction)
    {
        if (transactionCount < MAX_TRANSACTIONS)
        {
            transactionHistory[transactionCount++] = transaction;
        }
    }


    void displayTransactionHistory() const
    {
        cout << "Transaction History for " << name << ":" << endl;
        for (int i = 0; i < transactionCount; i++)
        {
            cout << "Type: " << transactionHistory[i].getTransactionType() << endl;
            cout << "Amount: " << transactionHistory[i].getAmount() << endl;
            cout << "Date and Time: " << transactionHistory[i].getDateAndTime() << endl;
            cout << "Notes: " << transactionHistory[i].getNotes() << endl;
            cout << "----------------------" << endl;
        }
    }
};
Member members[MAX_MEMBERS]; // Global array for members
int memberCount = 1;

// Function to search for a member
int searchMember(const string& mobile)
{
    for (int i = 0; i < memberCount; i++)
    {
        if (members[i].getMobile() == mobile && members[i].doesExist())
        {
            return i; // Return index of the existing member
        }
    }
    return -1;
}

// Function to generate & check OTP
bool generateOTP()
{
    srand(static_cast<unsigned>(time(0)));
    int otp = rand() % 9000 + 1000;

    int otp_input;
    time_t lastGeneratedTime = time(nullptr);
    time_t currentTime = time(nullptr);
    bool resend = true;
    int i=0,x=0;

    cout << "myCash OTP: " << otp << endl;
    while (currentTime - lastGeneratedTime < 180 && i<=3 && x<5)   // 3 minutes for OTP resend
    {
        int op;
        if((currentTime - lastGeneratedTime <= 120))
        {
            cout << "Press 1 to enter OTP" << endl;
            cout << "Press 2 to resend OTP" << endl;

            Input(&op);
        }
        else
        {
            cout << endl << "     OTP Expired!    " << endl << endl;
            cout << "Press 2 to resend OTP" << endl;

            Input(&op);
        }

        if(op == 1 && (time(nullptr) - lastGeneratedTime <= 120) && i < 4)
        {
            i++;
            if(i < 4)
            {
                cout << "Enter OTP: ";
                Input(&otp_input);

                if((time(nullptr) - lastGeneratedTime <= 120))
                {
                    if (otp_input == otp)
                    {
                        return 1; // OTP is correct
                    }
                    else cout << "Invalid OTP(" << i << "). Try again.(" << 3-i << " chance left)" << endl << endl;
                }
            }
        }
        else if(op == 2 && (time(nullptr) - lastGeneratedTime <= 180))
        {
            cout << "Resending OTP..." << endl << endl;
            otp = rand() % 9000 + 1000;
            lastGeneratedTime = time(nullptr); // Update lastGeneratedTime
            cout << "myCash OTP: " << otp << endl;
            i=0;

        }
        else if((time(nullptr) - lastGeneratedTime < 180)) x++,cout << "Wrong key pressed" << endl << endl;


        currentTime = time(nullptr);
    }

    if(currentTime - lastGeneratedTime >= 180) cout << "      TIMW EXPIRED\n" << endl;
    else if(i > 3) cout << "     Out of chances!\n" << endl;
    else if(x > 4) cout << "     Way to many wrong key pressed!\n" << endl;

    return 0;
}

// Function to get current date and time
string getCurrentDateTime()
{
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", currentTime);
    return buffer;
}

// Function to clear the console window
void clearWindow()
{
    system("cls");
}

// Function to mask pin
string getMaskedInput()
{
    string input = "";
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == '\r')   // Check if Enter key is pressed
        {
            cout << endl;
            break;
        }
        else if (ch == '\b')
        {
            if (!input.empty())
            {
                input.pop_back();
                _putch('\b');
                _putch(' ');
                _putch('\b');
            }
        }
        else if (isprint(ch))
        {
            _putch('*');
            input += ch;
        }
    }
    return input;
}

// Function to wait for user to return to the main menu
void waitForReturnToMainMenu()
{
    cout << "Press any key to return to the main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearWindow();
}

// Function to wait for user to return to the update menu
void waitForReturnToUpdateMenu()
{
    cout << "Press any key to return to the update menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearWindow();
}

// Function to wait for user to return to the Login menu
void waitForReturnToLoginMenu()
{
    cout << "Press any key to return to the Login menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearWindow();
}

// Function for member registration
void registerMember()
{
    string mobile, name, pin, reEnteredPin;
    cout << "Enter Mobile No. (11-digit): ";
    cin >> mobile;

    if (mobile.length() != 11 || mobile.substr(0, 2) != "01" || mobile[2] < '1' || mobile[2] > '9')
    {
        cout << "Invalid mobile number format." << endl;
        return;
    }

    if (searchMember(mobile) != -1)
    {
        cout << "Member with this mobile number already exists." << endl;
        return;
    }

    cin.ignore();  // Clear newline character
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter pin (5-digit): ";
    pin = getMaskedInput();

    cout << "Reconfirm pin: ";
    reEnteredPin = getMaskedInput();

    if (pin != reEnteredPin)
    {
        cout << "Pins do not match. Registration failed." << endl;
        return;
    }

    if(!generateOTP())
    {
        cout << "Registration failed." << endl;
    }

    members[memberCount++] = Member(mobile, name, 0, pin);
    cout << "Registration is Successful" << endl;
}

// Function for member login
int memberLogin()
{
    string mobile, pin;

    cout << "Enter Mobile No. (11-digit): ";
    cin >> mobile;

    int memberIndex = searchMember(mobile);
    if (memberIndex == -1)
    {
        cout << "Member with this mobile number does not exist." << endl;
        return -1;
    }

    cout << "Enter PIN: ";
    pin = getMaskedInput();

    if (members[memberIndex].getPin() == pin)
    {
        cout << "Login is Successful" << endl << endl;
        cout  << "                   Welcome " << members[memberIndex].getName() << "\n\n";

        waitForReturnToMainMenu(); // Wait and clear after successful login
        return memberIndex;
    }
    else
    {
        cout << "Incorrect PIN. Login failed." << endl;
        return -1;
    }
}

// Function to update member's name or PIN
void updateMember(int x)
{
    while(true)
    {
        int memberIndex = x;

        int option;
        cout << "********** Update Member Menu ********" << endl;
        cout << "1. Update Name" << endl;
        cout << "2. Update PIN" << endl;
        cout << "3. Update Name and PIN" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "Enter Your Option (1-4): ";
        Input(&option);

        switch (option)
        {
        case 1:
        {
            string newName;
            cout << "Enter New Name: ";
            cin.ignore(); // Clear the newline character from previous input
            getline(cin, newName);

            if(generateOTP())
            {
                members[memberIndex].setName(newName);
                cout << "Name updated successful." << endl;
            }
            else
            {
                cout << "Name updated failed." << endl;
            }
            waitForReturnToUpdateMenu();
            break;
        }
        case 2:
        {
            string newPin, confirmNewPin;
            cout << "Enter New PIN (5-digit): ";
            newPin = getMaskedInput();
            cout << "Confirm New PIN: ";
            confirmNewPin = getMaskedInput();
            if (newPin == confirmNewPin && newPin.size() == 5)
            {
                if(generateOTP())
                {
                    members[memberIndex].setPin(newPin);
                    cout << "PIN updated successful." << endl;
                }
                else
                {
                    cout << "PIN updated failed." << endl;
                }
            }
            else
            {
                cout << "PIN update failed. PINs do not match or not 5 digits." << endl;
            }
            waitForReturnToUpdateMenu();
            break;
        }
        case 3:
        {
            string newName, newPin, confirmNewPin;
            cout << "Enter New Name: ";
            cin.ignore(); // Clear the newline character from previous input
            getline(cin, newName);
            cout << "Enter New PIN (5-digit): ";
            newPin = getMaskedInput();
            cout << "Confirm New PIN: ";
            confirmNewPin = getMaskedInput();
            if (newPin == confirmNewPin && newPin.size() == 5)
            {
                if(generateOTP())
                {
                    members[memberIndex].setName(newName);
                    members[memberIndex].setPin(newPin);
                    cout << "Name and PIN updated successful." << endl;
                }
                else
                {
                    cout << "Name and PIN updated failed." << endl;
                }
            }
            else
            {
                cout << "Name and PIN update failed. PINs do not match or not 5 digits." << endl;
            }
            waitForReturnToUpdateMenu();
            break;
        }
        case 4:
            cout << "Returning to Main Menu." << endl;
            return;
        default:
            cout << "Invalid option. Please enter a valid option." << endl;
            waitForReturnToUpdateMenu();
        }
    }
}

// Function to remove an existing member
void removeMember(int x)
{
    int memberIndex = x;

    string enteredPin, actualPin;
    cout << "Enter PIN: ";
    enteredPin = getMaskedInput();

    actualPin = members[memberIndex].getPin();
    if (enteredPin != actualPin)
    {
        cout << "Incorrect PIN. Removal failed." << endl;
        return;
    }

    members[memberIndex].setExist(false); // Set Exist flag to false
    cout << "Member removed successfully." << endl;
}

// Function to send money to another member
void sendMoney(int x)
{
    string receiverMobile, senderPin;

    int senderIndex = x;

    cout << "Enter Receiver's Mobile No. (11-digit): ";
    cin >> receiverMobile;

    int receiverIndex = searchMember(receiverMobile);
    if (receiverIndex == -1)
    {
        cout << "Receiver member with this mobile number does not exist." << endl;
        return;
    }

    double amount;
    cout << "Enter Amount to Send: ";
    InputD(&amount);

    if (amount <= 0 || amount > members[senderIndex].getAmount())
    {
        cout << "Invalid amount to send." << endl;
        return;
    }

    if (!generateOTP())
    {
        cout << "Transaction aborted." << endl;
        return;
    }

    // Record the transaction in the sender's history
    string senderName = members[senderIndex].getName();
    string receiverName = members[receiverIndex].getName();
    string transactionType = "send money";
    string dateAndTime = getCurrentDateTime();
    string notes = senderName + " sent " + to_string(amount) + " of money to " + receiverName;

    History senderTransaction(transactionType, amount, dateAndTime, notes);
    members[senderIndex].addTransaction(senderTransaction);

    // Record the transaction in the receiver's history
    transactionType = "receive money";
    notes = receiverName + " received " + to_string(amount) + " of money from " + senderName;

    History receiverTransaction(transactionType, amount, dateAndTime, notes);
    members[receiverIndex].addTransaction(receiverTransaction);

    // Update member balances
    members[senderIndex].reduceAmount(amount);
    members[receiverIndex].increaseAmount(amount);

    cout << "Money sent successfully." << endl;
}

// Function for cash-in (deposit money)
void cashIn(int x)
{

    int memberIndex = x;

    double amount;
    cout << "Enter Amount to Cash-In: ";
    InputD(&amount);

    if (amount <= 0)
    {
        cout << "Invalid amount for cash-in." << endl;
        return;
    }

    members[memberIndex].increaseAmount(amount);

    // Record the cash-in transaction
    string memberName = members[memberIndex].getName();
    string transactionType = "cash-in";
    string dateAndTime = getCurrentDateTime();
    string notes = memberName + " cashed in " + to_string(amount);

    History cashInTransaction(transactionType, amount, dateAndTime, notes);
    members[memberIndex].addTransaction(cashInTransaction);

    cout << "Cash-in successful." << endl;
}

// Function for cash-out (withdraw money)
void cashOut(int x)
{

    int memberIndex = x;

    double amount;
    cout << "Enter Amount to Cash-Out: ";
    InputD(&amount);

    if (amount <= 0 || amount > members[memberIndex].getAmount())
    {
        cout << "Invalid amount for cash-out." << endl;
        return;
    }

    if (!generateOTP())
    {
        cout << "Cash-out aborted." << endl;
        return;
    }

    members[memberIndex].reduceAmount(amount);

    // Record the cash-out transaction
    string memberName = members[memberIndex].getName();
    string transactionType = "cash-out";
    string dateAndTime = getCurrentDateTime();
    string notes = memberName + " cashed out " + to_string(amount);

    History cashOutTransaction(transactionType, amount, dateAndTime, notes);
    members[memberIndex].addTransaction(cashOutTransaction);

    cout << "Cash-out successful." << endl;
}

// Function for paying a bill
void payBill(int x)
{

    int memberIndex = x;

    double amount;
    cout << "Enter Amount to Pay: ";
    InputD(&amount);

    if (amount <= 0 || amount > members[memberIndex].getAmount())
    {
        cout << "Invalid amount for bill payment." << endl;
        return;
    }

    if (!generateOTP())
    {
        cout << "Bill payment aborted." << endl;
        return;
    }

    members[memberIndex].reduceAmount(amount);

    // Record the bill payment transaction
    string memberName = members[memberIndex].getName();
    string transactionType = "pay bill";
    string dateAndTime = getCurrentDateTime();
    string notes = memberName + " paid " + to_string(amount) + " as a bill";

    History billPaymentTransaction(transactionType, amount, dateAndTime, notes);
    members[memberIndex].addTransaction(billPaymentTransaction);

    cout << "Bill payment successful." << endl;
}

// Function to check balance
void checkBalance(int x)
{

    double balance = members[x].getAmount();
    cout << "Your current balance is: " << balance << endl;
}

// Function to display transaction history of logged-in member
void history(int loggedInMemberIndex)
{

    members[loggedInMemberIndex].displayTransactionHistory();
}

// Function for the main menu
void mainMenu(int x)
{
    int option;
    while (true)
    {
        cout << "********** MyCash Main Menu **********" << endl;
        cout << "1. Update Member" << endl;
        cout << "2. Remove Member" << endl;
        cout << "3. Send Money" << endl;
        cout << "4. Cash-in" << endl;
        cout << "5. Cash-out" << endl;
        cout << "6. Pay Bill" << endl;
        cout << "7. Check Balance" << endl;
        cout << "8. History" << endl;
        cout << "9. Logout" << endl;
        cout << "Enter Your Option (1-9): ";
        Input(&option);

        switch (option)
        {
        case 1:
            clearWindow();
            updateMember(x);
            waitForReturnToMainMenu();
            break;
        case 2:
            removeMember(x);
            clearWindow();
            return ;
        case 3:
            sendMoney(x);
            waitForReturnToMainMenu();
            break;
        case 4:
            cashIn(x);
            waitForReturnToMainMenu();
            break;
        case 5:
            cashOut(x);
            waitForReturnToMainMenu();
            break;
        case 6:
            payBill(x);
            waitForReturnToMainMenu();
            break;
        case 7:
            checkBalance(x);
            waitForReturnToMainMenu();
            break;
        case 8:
            history(x);
            waitForReturnToMainMenu();
            break;
        case 9:
            cout << "Logging out..." << endl;
            clearWindow();
            return;
        default:
            cout << "Invalid option. Please enter a valid option (1-9)." << endl;
            waitForReturnToMainMenu();
        }
    }
}
void loadMemberDataFromFile(const char* filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open the file for reading." << endl;
        return;
    }

    int index = 0;
    string m, n, p;
    double amt;

    while (file >> m >> n >> amt >> p)
    {
        members[index] = Member(m, n, amt, p); // Use the constructor to initialize Member object
        index++;
    }

    file.close();
    memberCount = index; // Update memberCount to the number of loaded members
}


// Function to save the data of members with Exist = true to a text file
void saveDataToFile(const char* filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open the file for writing." << endl;
        return;
    }

    for (int i = 0; i < MAX_MEMBERS; i++)
    {
        if (members[i].doesExist())
        {
            file << members[i].getMobile() << " " << members[i].getName() << " " << members[i].getAmount() << " " << members[i].getPin() << endl;
        }
    }
    file.close();
}


int main()
{
    int option;
    // Load member data from the text file
    loadMemberDataFromFile("Data.txt");

    while (true)
    {
        cout << "*** MyCash Login Menu **" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Your Option: ";
        Input(&option);

        switch (option)
        {
        case 1:
        {
            int X = memberLogin();
            if (X!=-1)
            {
                clearWindow();
                mainMenu(X);
            }
            else
            {
                waitForReturnToLoginMenu();
            }
        }
        break;
        case 2:
            registerMember();
            waitForReturnToLoginMenu();
            break;
        case 3:
            // Before the program exits, save the data to the text file
            saveDataToFile("Data.txt");
            cout << "Exiting MyCash. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid option. Please enter a valid option (1-3)." << endl;
            waitForReturnToLoginMenu();
        }
    }

    return 0;
}
