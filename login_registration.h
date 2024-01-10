#include "Admin.h"

using namespace std;

client c;
trainer t;
admin a;

void heading()
{
    cout << "\n\n\n\t\t\t\t\t\t  <<-------------- GYM MANAGEMENT SYSTEM -------------->>\n\n\n\n\n\n\n\n\n";
}
void person::main_page()
{
    system("cls");
    heading();
    int ans;

    cout << "\n\n\t\t\t\t\t\t\t\tWho are you?\n\n\t\t\t\t\t\t\t\tPress>> 1-Customer\n\n\t\t\t\t\t\t\t\tPress>> 2-Trainer\n\n\t\t\t\t\t\t\t\tPress>> 3-Admin\n\n\t\t\t\t\t\t\t\tPress>> 4-Exit\n\n";
    cout << "\t\t\t\t\t\t\t\t_________________________\n";
    do
    {
        cout << "\n\t\t\t\t\t\t\t\tChoose the correct option: ";
        cin >> ans;
        switch (ans)
        {
        case 1:
            c.login_Register();
            break;

        case 2:
            t.login_Register();
            break;

        case 3:
            a.login_Register();
            system("cls");
            break;
        case 4:
            cout << "\n\n\t\t\t\t\t\t\t**Thankyou for using our software...Have a nice day :)**\n\n";
            Sleep(50);
            exit(0);
            break;
        default:
            cout << "\n\t\t\t\t\t\t\t\tWrong choice...Enter again!\n";
            break;
        }
    } while (ans < 1 || ans > 4);
}
void client::login_Register()
{
    char id2[20], pass[20], bogusid[20];
    static int count = 0;
    int success = 0, i = 0;
    char ch;
    int choice;

    system("cls");
    heading();
    cout << "\n\n\t\t\t\t\t\t\t\tPress>> 1-To Register:\n\n\t\t\t\t\t\t\t\tPress>> 2-To login:\n\n\n\t\t\t\t\t\t\t\tPress>> 3-To Exit\n";
    cout << "\t\t\t\t\t\t\t\t_________________________\n";
    cout << "\n\t\t\t\t\t\t\t\tChoose your desired option: ";
    cin >> choice;
    do
    {
        if (choice == 1)
        {
            clientregister();
        }
        else if (choice == 2)
        {
            ifstream fin;
            fin.open("client.dat", ios::binary | ios::in);
            if (!fin)
            {
                cout << "\n\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
                main_page();
            }
            else
            {
                system("cls");
                cout << "\n\n\t\t\t<-----------------------------------------------------CLIENT LOGIN------------------------------------------------------------->\n";
                cout << "\n\n\n\t\t\t\t\t\t\t\tEnter your ID(e.g 22k-4212): ";
                cin >> ws;
                cin.get(id2, 50);

                cout << "\n\n\n\t\t\t\t\t\t\t\tEnter your password: ";
                while (true)
                {
                    ch = getch();

                    if (ch == 13)
                    {
                        pass[i] = '\0';
                        break;
                    }
                    else if (ch == 8)
                    {
                        if (i > 0)
                        {
                            i--;
                            cout << "\b \b";
                        }
                    }
                    else
                    {
                        if (i <= 8)
                        {
                            pass[i] = ch;
                            i++;
                            cout << "*";
                        }
                    }
                }
                while (fin.read(reinterpret_cast<char *>(this), sizeof(*this)))
                {
                    if (strcmp(id2, this->id) == 0 && strcmp(pass, this->password) == 0)
                    {
                        cout << "\n\n\n\t\t\t\t\t\t\t\tLogin Successful....Press enter to continue\n";
                        getch();
                        success = 1;
                        fin.close();
                        customer_menu(id2);
                    }
                }
                if (success != 1)
                {
                    cout << "\n\n\t\t\t\t\t\t\t\tIncorrect login details....Press enter to try again!\n";
                    Beep(523, 500);
                    getch();
                    count++;
                    if (count == 4)
                    {
                        cout << "\n\n\n\t\t\t\t\t**You have reached maximum number of tries...Restart the software to proceed!**\n";
                        exit(0);
                    }
                    client::login_Register();
                }
                fin.close();
            }
        }
        else if (choice == 3)
        {
            main_page();
        }
        else
        {
            cout << "Wrong choice...Enter again!\n";
        }
    } while (choice < 1 || choice > 3);
}
void client::clientregister()
{
    system("cls");
    char name[20], card_number[20], gender[20], phone[20], choice, *password, *bogusid;
    float fees, amount;
    int duration, months, ans;
    bool check = false, loop = false;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Add a Client ---------------->";

    ofstream fout;
    ifstream file2;
    fout.open("tempclient.dat", ios::binary | ios::out);

    if (!fout)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in creating file\n";
    }
    else
    {
        do
        {
            bogusid = this->id_validation();
            if (this->checkid(bogusid, "tempclient.dat") == true)
            {
                cout << "\n\n\t\t\t\t\t\t\t\tID already exists!\n";
                check = true;
            }
            else
            {
                check = false;
                cout << "\n\n\t\t\t\t\t\t\t\tEnter Client's name: ";
                cin >> ws;
                cin.get(name, 20);

                cout << "\n\n\t\t\t\t\t\t\t\tEnter Client's gender: ";
                cin >> ws;
                cin.get(gender, 20);
                if (gender[0] >= 'a' && gender[0] <= 'z')
                {
                    gender[0] -= 32;
                }

                cout << "\n\n\t\t\t\t\t\t\t\tEnter Client's phone#: ";
                cin >> ws;
                cin.get(phone, 20);

                strcpy(this->id, bogusid);
                strcpy(this->name, name);
                strcpy(this->gender, gender);
                strcpy(this->phone_number, phone);

                cout << "\n\n\t\t\t\t\t\t\t\tDo you want Membership (Yes[y]/No[n]):";
                cin >> choice;
                if (choice == 'Y' || choice == 'y')
                {
                    this->is_member = true;
                    cout << "\n\n\t\t\t\t\t\t\t\tChoose from the below: " << endl
                         << "\n\n\t\t\t\t\t\t\t\t1.Platinum(3000 RS/- per month)" << endl
                         << "\n\n\t\t\t\t\t\t\t\t2.Gold(1500 Rs/- per month)" << endl;
                    cout << "\n\n\t\t\t\t\t\t\t\tChoice: ";
                    cin >> ans;
                    cout << "\n\n\t\t\t\t\t\t\t\tHow many months of membership would you like to buy: ";
                    cin >> months;
                    do
                    {
                        if (ans == 1)
                        {
                            char type[] = "Platinum";
                            fees = 3000;
                            duration = 1 * months;
                            Membership.create_membership(type, duration, fees, bogusid); // should be in temp file as well
                            this->due_ammount += (fees * months);                        // fees kitni pay krni hai
                            break;
                        }
                        else if (ans == 2)
                        {
                            char type[] = "Gold";
                            fees = 1500;
                            duration = 1 * months;
                            Membership.create_membership(type, duration, fees, bogusid);
                            this->due_ammount += (fees * months);
                            break;
                        }
                        else
                        {
                            cout << "\n\n\t\t\t\t\t\t\t\tWrong choice\n";
                        }
                    } while (ans < 1 || ans > 2);
                }
                else
                {
                    this->is_member = false;
                    due_ammount = 1000;
                }
            }
        } while (check == true);
        password = this->pass_validation();
        strcpy(this->password, password);
        cout << "\n\n\t\t\t\t\t\t\t\tYour due amount is: " << this->due_ammount << endl;
        cout << "\n\n\t\t\t\t\t\t\t\tPayment option is available for online payments through credit or debit cards only:\n";
        cout << "\n\n\t\t\t\t\t\t\t\tEnter card number: ";
        cin >> ws;
        cin.get(card_number, 20);
        do
        {
            cout << "How much would you like to pay: ";
            cin >> this->paid;
            due_ammount -= paid;
            if (this->paid < 1000)
            {
                cout << "\n\n\t\t\t\t\t\t\t\tAmount unacceptable...Minimum amount is 1000 rs/-";
                cout << "\n\n\t\t\t\t\t\t\t\tWould you like to 1-Exit or 2-Enter again\n";
                cin >> choice;
                if (choice == 1)
                {
                    fout.close();
                    main_page();
                }
                else if (choice == 2)
                {

                    cout << due_ammount;
                    loop = true;
                }
            }
            else
            {
                this->feespaid = true;
            }
        } while (loop == true);
        // enter_body_stats(this->id);
        fout.write(reinterpret_cast<char *>(this), sizeof(*this));
        fout.close();
    }
    main_page();
}
bool person::checkid(char id2[], string filename)
{
    ifstream fin;
    fin.open(filename, ios::binary | ios::in);
    if (!fin)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        while (fin.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (strcmp(this->id, id2) == 0)
            {
                fin.close();
                return true;
            }
        }
    }
    fin.close();
    return false;
}
void trainer::login_Register()
{
    char id2[20], pass[20];
    static int count = 0;
    int success = 0, i = 0;
    char ch;
    int choice;

    system("cls");
    heading();
    cout << "\n\n\t\t\t\t\t\t\t\tPress>> 1-To login:\n\n\n\t\t\t\t\t\t\t\tPress>> 2-To Exit";
    cout << "\t\t\t\t\t\t\t\t_________________________\n";
    cout << "\n\t\t\t\t\t\t\t\tChoose your desired option: ";
    do
    {
        if (choice == 1)
        {
            ifstream fin;
            fin.open("trainers.dat", ios::binary | ios::in);
            if (!fin)
            {
                cout << "\n\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
                getch();
            }
            else
            {
                system("cls");
                cout << "\n\n\t\t\t<-----------------------------------------------------TRAINER LOGIN------------------------------------------------------------->\n";
                cout << "\n\n\n\t\t\t\t\t\t\t\tEnter trainer ID(e.g T-123): ";
                cin >> ws;
                cin.get(id2, 20);

                cout << "\n\n\n\t\t\t\t\t\t\t\tEnter password: ";
                while (true)
                {
                    ch = getch();

                    if (ch == 13)
                    {
                        pass[i] = '\0';
                        break;
                    }
                    else if (ch == 8)
                    {
                        if (i > 0)
                        {
                            i--;
                            cout << "\b \b";
                        }
                    }
                    else
                    {
                        if (i <= 10)
                        {
                            pass[i] = ch;
                            i++;
                            cout << "*";
                        }
                    }
                }
                while (fin.read(reinterpret_cast<char *>(this), sizeof(*this)))
                {
                    if (strcmp(id2, this->id) == 0 && strcmp(pass, this->password) == 0)
                    {
                        cout << "\n\n\n\t\t\t\t\t\t\t\tLogin Successful....Press enter to continue\n";
                        getch();
                        success = 1;
                        fin.close();
                        trainer_menu(id2);
                    }
                }
                if (success != 1)
                {
                    cout << "\n\n\t\t\t\t\t\t\t\tIncorrect login details....Press enter to try again!\n";
                    getch();
                    Beep(523, 500);
                    count++;
                    if (count == 4)
                    {
                        cout << "\n\n\n\t\t\t\t\t**You have reached maximum number of tries...Restart the software to proceed!**\n";
                        exit(0);
                    }
                    trainer::login_Register();
                }
                fin.close();
            }
        }
        else if (choice == 2)
        {
            main_page();
        }
        else
        {
            cout << "Wrong choice...Enter again!\n";
        }
    } while (choice < 1 && choice > 3);
}

void admin::login_Register()
{
    char ch;
    static int count1 = 0;
    string username, pass;
    system("cls");
    cout << "\n\n\t\t\t<-----------------------------------------------------ADMIN LOGIN------------------------------------------------------------->\n";
    cout << "\n\n\t\t\t\t\t\t\t\tEnter your username: ";
    cin >> ws;
    getline(cin, username);

    cout << "\n\n\t\t\t\t\t\t\t\tEnter your password:";
    while (true)
    {
        ch = getch();

        if (ch == 13)
        {
            break;
        }
        else if (ch == 8)
        {
            if (!pass.empty())
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            pass.push_back(ch);
            cout << "*";
        }
    }

    if ((username == "admin") && (pass == "admin"))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tLogin Successfull...Press any key to continue...";
        getch();
        menu();
    }
    else
    {
        cout << "\n\n\t\t\t\t\t\t\t\tInncorrect Username or Password!\n";
        Beep(523, 500);
        count1++;
        cout << "\n\n\t\t\t\t\t\t\t\tPress any key to continue...";
        getch();
        system("CLS");
        heading();
    }

    if (count1 == 4)
    { /*//------>MAXIMUM ATTEMPTS CHECK*/
        cout << "\n\n\t\t\t\t\t**Sorry, close and restart the software, as you have reached the maximum number of attempts!**";
        exit(0);
    }
    else if (count1 >= 1)
    {
        login_Register();
    }
}

char *person::id_validation()
{

    static char id[20];
    cout << "\n\n\t\t\t\t\t\t\t\tEnter the ID(22k-4212): ";
    cin >> ws;
    cin.get(id, 20);

    for (int i = 0; i < strlen(id); i++)
    {
        if (id[i] == ' ')
        {
            for (int j = i; j < strlen(id); j++)
            {
                id[j] = id[j + 1];
            }
        }
        else if (id[i] >= 'a' && id[i] <= 'z')
        {
            id[i] -= 32;
        }
    }
    return id;
}
char *person::pass_validation()
{
    int number, special, capital, smll, success;
    number = special = capital = smll = success = 0;
    static char pass[20];
    cout << "\n\n\t\t\t\t\t\t\t\tPasword must have at least one:\n\t\t\t\t\t\t\t\t-Captital letter\n\t\t\t\t\t\t\t\t-Small letter\n\t\t\t\t\t\t\t\t-Special character(!,@,#,$,%,*)\n\t\t\t\t\t\t\t\t-Numeric character\n\t\t\t\t\t\t\t\t-Atmost 10 characters";
    do
    {
        do
        {
            cout << "\n\n\t\t\t\t\t\t\t\tEnter Password: ";
            cin >> ws;
            cin.get(pass, 20);
            if (strlen(pass) > 10)
            {
                cout << "\n\t\t\t\t\t\t\t\tPassword should be atmost 10 charcaters!\n";
            }
        } while (strlen(pass) > 10);

        for (int i = 0; pass[i] != '\0'; i++)
        {
            if (pass[i] >= '0' && pass[i] <= '9')
            {
                number++;
            }
            if (pass[i] >= 'a' && pass[i] <= 'z')
            {
                smll++;
            }
            if (pass[i] >= 'A' && pass[i] <= 'Z')
            {
                capital++;
            }
            if (pass[i] == '!' || pass[i] == '@' || pass[i] == '#' || pass[i] == '$' || pass[i] == '%' || pass[i] == '*')
            {
                special++;
            }
        }
        if (number == 0 || special == 0 || capital == 0 || smll == 0)
        {
            cout << "\n\n\t\t\t\t\t\t\t\tInvalid Password\n\n\t\t\t\t\t\t\t\tPlease enter the details again.";
            cout << "\n\n\t\t\t\t\t\t\t\tPress any key to continue...";
            getch();
            success = 1;
        }
        else
        {
            cout << "\n\n\t\t\t\t\t\t\t\tAccount Created Successfully\n\n";
            getch();
            break;
        }
    } while (success == 1);
    return pass;
}
