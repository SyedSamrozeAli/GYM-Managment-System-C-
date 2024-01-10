#include "login_registration.h"

using namespace std;
void client::customer_menu(char id2[20])
{
    system("cls");
    int choice;
    ifstream fin;
    fin.open("client.dat", ios::binary | ios::in);

    while (fin.read(reinterpret_cast<char *>(this), sizeof((*this))))
    {
        if (strcmp(id2, this->id) == 0)
        {
            cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome " << this->name << " ---------------->";
            cout << " \n\n\t\t\t\t\t\t\t\t___________________________________________\n";
            cout << " \n\n\t\t\t\t\t\t\t\t<1> View Profile\n";
            cout << " \n\n\t\t\t\t\t\t\t\t<2> View Body Stats \n";
            cout << " \n\n\t\t\t\t\t\t\t\t<3> View Workout Schedule\n";
            cout << " \n\n\t\t\t\t\t\t\t\t<4> Logout\n";
            cout << " \n\n\t\t\t\t\t\t\t\t___________________________________________\n";
            cout << " \n\n\t\t\t\t\t\t\t\tChoice: ";
            cin >> choice;
            do
            {
                switch (choice)
                {
                case 1:
                    view_profile(id2);
                    break;
                case 2:
                    view_body_stats(id2);
                    break;
                case 3:
                    view_workout_schedule();
                    break;
                case 4:
                    logout();
                    main_page();
                    break;
                default:
                    cout << "Wrong input!\n";
                }
            } while (choice < 1 || choice > 5);
        }
    }
    fin.close();
}
void client::view_profile(char id2[50])
{

    bool found = false;
    system("cls");
    ifstream fin, fin2;
    fin.open("client.dat", ios::binary | ios::in);
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Your profile ---------------->";
    if (!fin.is_open())
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in creating file\n";
    }
    else
    {
        while (fin.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (strcmp(this->id, id2) == 0)
            {
                found = true;
                cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
                cout << "\n\t\t\t\t\t\t\t\tName: " << this->name << endl
                     << "\n\t\t\t\t\t\t\t\tGender: " << this->gender << endl
                     << "\n\t\t\t\t\t\t\t\tPhone: " << this->phone_number << endl
                     << "\n\t\t\t\t\t\t\t\tID: " << this->id << endl
                     << "\n\t\t\t\t\t\t\t\tPassword: " << this->password << endl;
                cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
                if (this->is_member == true)
                {
                    Membership.display_membership(this->id);
                }
                cout << "\n\t\t\t\t\t\t\t\tRemaining balance is: " << due_ammount << endl;
            }
        }
        if (found == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tID not found!\n";
        }
    }
    fin.close();
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to return to main menu\n";
    getch();
    customer_menu(this->id);
}
void trainer::trainer_menu(char id2[50])
{

    system("cls");
    int choice;
    ifstream fin;
    fin.open("trainers.dat", ios::binary | ios::in);

    while (fin.read(reinterpret_cast<char *>(this), sizeof(*this)))
    {
        if (strcmp(id2, this->id) == 0)
        {
            cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome " << this->name << " ---------------->";
            cout << " \n\n\t\t\t\t\t\t\t\t___________________________________________\n";
            cout << " \n\n\t\t\t\t\t\t\t\t<1> View Profile\n";
            cout << " \n\n\t\t\t\t\t\t\t\t<2> View All Clients \n";
            cout << " \n\n\t\t\t\t\t\t\t\t<3> Request Inventory\n";
            cout << " \n\n\t\t\t\t\t\t\t\t<5> View Shedule \n";
            cout << " \n\n\t\t\t\t\t\t\t\t<7> Logout\n";
            cout << " \n\n\t\t\t\t\t\t\t\t___________________________________________\n";
            cout << " \n\n\t\t\t\t\t\t\t\tChoice: ";
            cin >> choice;
            do
            {
                switch (choice)
                {
                case 1:

                    view_profile(id2);
                    break;
                case 2:
                    show_clients();
                    break;
                case 3:
                    request_inventory();
                    break;
                case 4:
                    request_updatedetails();
                    break;
                case 5:
                    view_schedule();
                    break;
                case 7:
                    logout();
                    main_page();
                    break;
                default:
                    cout << "Wrong input!\n";
                }
            } while (choice < 1 || choice > 6);
        }
    }
    fin.close();
}

void trainer::view_profile(char id2[50])
{

    bool found = false;
    system("cls");
    ifstream fin;
    fin.open("trainers.dat", ios::binary | ios::in);
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Your profile ---------------->";
    if (!fin.is_open())
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in creating file\n";
    }
    else
    {
        while (fin.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (strcmp(this->id, id2) == 0)
            {
                cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
                cout << "\n\t\t\t\t\t\t\t\tName: " << this->name << endl
                     << "\n\t\t\t\t\t\t\t\tGender: " << this->gender << endl
                     << "\n\t\t\t\t\t\t\t\tPhone: " << this->phone_number << endl
                     << "\n\t\t\t\t\t\t\t\tID: " << this->id << endl
                     << "\n\t\t\t\t\t\t\t\tID: " << this->salary << endl
                     << "\n\t\t\t\t\t\t\t\tPassword: " << this->password << endl;
                cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
                found = true;
            }
        }
        if (found == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tID not found!\n";
        }
    }
    fin.close();
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to return to main menu\n";
    getch();
    trainer_menu(this->id);
}
void client::view_body_stats(char id2[])
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Your Body Statistics ---------------->";
    cout << "\n\t\t\t\t\t\t\t\tWeight: " << stats.weight << endl
         << "\n\t\t\t\t\t\t\t\tHeight: " << stats.height << endl
         << "\n\t\t\t\t\t\t\t\tWaist Measurements: " << stats.waist << endl
         << "\n\t\t\t\t\t\t\t\tNeck measurements: " << stats.neck << endl
         << "\n\t\t\t\t\t\t\t\tHip measuremenets: " << stats.hips << endl
         << "\n\t\t\t\t\t\t\t\tBody fat percentage: " << stats.bodyFatPercentage << "%" << endl
         << "\n\t\t\t\t\t\t\t\tBMI: " << stats.BMI << "kg/m^2" << endl;
    cout << "\n\t\t\t\t\t\t\t\tPress enter to continue\n";
    getch();
    customer_menu(id2);
}
void trainer::show_clients()
{
    system("cls");
    ifstream fin;
    fin.open("trainers.dat", ios::binary | ios::in);
    while (fin.read(reinterpret_cast<char *>(this), sizeof(*this)))
    {
        for (int i = 0; i < numberofClients; i++)
        {
            cout << &array_of_clients[i] << endl;
        }
    }
}
