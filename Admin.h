#include "Header.h"
using namespace std;

void admin::menu()
{
    system("cls");
    int choice;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome Admin ---------------->";
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    cout << "\n\n\t\t\t\t\t\t\t\t<1> Enter into Client Database" << endl
         << "\n\n\t\t\t\t\t\t\t\t<2> Enter into Trainer Database" << endl
         << "\n\n\t\t\t\t\t\t\t\t<3> Enter into Inventory Database" << endl
         << "\n\n\t\t\t\t\t\t\t\t<4> Enter into Monetary Database" << endl
         << "\n\n\t\t\t\t\t\t\t\t<5> Enter into Membership Database" << endl
         << "\n\n\t\t\t\t\t\t\t\t<6> Logout" << endl;
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    do
    {
        cout << "\n\n\t\t\t\t\t\t\t\tChoose your desired option: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            client_database();
            break;
        case 2:
            trainer_database();
            break;
        case 3:
            Inventory_database();
            break;
        case 4:
            Monetary_database();
            break;
        case 5:
            // Membership_database();
            break;
        case 6:
            logout();
            main_page();
            break;
        default:
            cout << "Wrong Choice!\n";
        }
    } while (choice < 1 || choice > 5);
}

void admin ::client_database()
{
    system("cls");
    int choice;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome Admin ---------------->";
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    cout << "\n\n\t\t\t\t\t\t\t\t<1> Add new client" << endl // add personal info except ID and Password
         << "\n\n\t\t\t\t\t\t\t\t<2> Display All clients" << endl
         << "\n\n\t\t\t\t\t\t\t\t<3> Remove a client" << endl
         << "\n\n\t\t\t\t\t\t\t\t<4> Update Client Information " << endl
         << "\n\n\t\t\t\t\t\t\t\t<5> Allot Trainer to Client " << endl
         << "\n\n\t\t\t\t\t\t\t\t<6> Search a Client  " << endl
         << "\n\n\t\t\t\t\t\t\t\t<7> Manage Client Attendance  " << endl
         << "\n\n\t\t\t\t\t\t\t\t<8> View Total Clients " << endl
         << "\n\n\t\t\t\t\t\t\t\t<9> Go Back" << endl;
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    do
    {
        cout << "\n\n\t\t\t\t\t\t\t\tChoose your desired option: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            add_client();
            break;
        case 2:
            display_all_clients();
            break;
        case 3:
            remove_client();
            break;
        case 4:
            update_client();
            break;
        case 5:
            allot_trainer();
            break;
        case 6:
            search_client();
            break;
        case 7:
            Client_attendance_menu();
            break;
        case 8:
            gettotalclient();
            break;
        case 9:
            menu();
            break;
        default:
            cout << "Wrong Choice!\n";
        }
    } while (choice < 1 || choice > 8);
}

// Client
void admin::add_client()
{
    ofstream file, fout;
    ifstream file2, fin;

    if (details.number_of_client < maximum_client_number)
    {
        fout.open("client.dat", ios::binary | ios::app);
        fin.open("tempclient.dat", ios::binary | ios::in);
        while (fin.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            if (Client.feespaid == true)
            {
                fout.write(reinterpret_cast<char *>(&Client), sizeof(Client));
                cout << "Client successfully added to the system!\n";
                wallet.amount = Client.paid;
                wallet.recieve = true;
                wallet.send = false;
                strcpy(wallet.sender_id, Client.id);
                char buffer[30];
                strcpy(buffer, strcat(Client.id, "2233"));
                wallet.setid(buffer);
                wallet.setdate(getdate());
                wallet.setime(gettime());
                ofstream fout;
                fout.open("transaction_history.dat", ios::app);
                fout.write(reinterpret_cast<char *>(&wallet), sizeof(wallet));
                fout.close();
            }
            else
            {
                cout << "\n\n\n\n\t\t\t\t\t\t\t\tClient cannot be added into the system!\n";
                break;
            }
        }
        getch();
        fin.close();
        fout.close();
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\tClient cannot be added into the system!\n";
    }

    file2.open("Admin.dat", ios::binary | ios::in);
    file2.read(reinterpret_cast<char *>(&details), sizeof(details));
    details.number_of_client++;
    file2.close();

    file.open("Admin.dat", ios::binary | ios::out);
    file.write(reinterpret_cast<char *>(&details), sizeof(details));
    file.close();
    getch();
    client_database();
}
void admin::allot_trainer()
{
    system("cls");
    char gender[50], expertise[20], time[20], search_id[50], trainer_id[50];
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Allot a Trainer to a Client ---------------->";
    ifstream file;
    fstream file2;
    file.open("trainers.dat", ios::binary | ios::in);
    file2.open("client.dat", ios::binary | ios::in | ios::out | ios::ate);
    cout << "\n\n\t\t\t\t\t\t\t\tEnter Client ID: ";
    cin.ignore();
    cin.get(search_id, 50);
    cout << "\n\n\t\t\t\t\t\t\t\t<-Selection Criteria->";

    cout << "\n\n\t\t\t\t\t\t\t\tEnter Trainer's gender: ";
    cin >> ws;
    cin.get(gender, 50);

    cout << "\n\n\t\t\t\t\t\t\t\tEnter Trainer's expertise: ";
    cin >> ws;
    cin.get(expertise, 20);

    char ans;
    cout << "\n\n\t\t\t\t\t\t\t\tSelect trainer's alloted time at gym: \n\n\t\t\t\t\t\t\t\t1)Morning\n\t\t\t\t\t\t\t\t2)Afternoon\n\t\t\t\t\t\t\t\t3)Night\n\t\t\t\t\t\t\t\tSelect(1/2/3): ";
    cin >> ws;
    cin >> ans;
    if (ans == '1')
        strcpy(time, "Morning");
    else if (ans == '2')
        strcpy(time, "Afternoon");
    else if (ans == '3')
        strcpy(time, "Night");

    if (!(file))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t<-------------- Displaying All Selected Trainers Details By Matching the Selection Criteria  ---------------->\n\n";
        while (file.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
        {
            if (strcmp(Trainer.time, time) == 0 || strcmp(Trainer.gender, gender) == 0 || strcmp(Trainer.expertise, expertise) == 0)
            {
                cout << "\n\t\t\t\t\t\t\t\tID: " << Trainer.id << endl
                     << "\t\t\t\t\t\t\t\tName: " << Trainer.name << endl
                     << "\t\t\t\t\t\t\t\tGender: " << Trainer.gender << endl
                     << "\t\t\t\t\t\t\t\tPhone: " << Trainer.phone_number << endl
                     << "\t\t\t\t\t\t\t\tTraining Time at Gym: " << Trainer.time << endl
                     << "\t\t\t\t\t\t\t\tTrainer Expertise:" << Trainer.expertise << endl;
                cout << "\t\t\t\t\t\t\t\t_______________________\n";
            }
        }
        file.close();
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Trainer's ID to be Allocated from the List: ";
        cin >> ws;
        cin.get(trainer_id, 20);
        file2.seekg(0);
        bool flag = false;
        if (!(file2))
        {
            cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
        }
        else
        {
            while (file2.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
            {
                if (strcmp(Client.id, search_id) == 0)
                {
                    flag = true;

                    Client.Train = client_alloted(&Client, trainer_id);
                    strcpy(Client.trainer_id, trainer_id);
                    if (strcmp(Client.Train->id, trainer_id) == 0)
                    {
                        file2.seekp(-(long)sizeof(Client), ios_base::cur);
                        file2.write(reinterpret_cast<char *>(&Client), sizeof(Client));
                        break;
                    }
                }
            }
            file2.close();
            if (flag == false)
            {
                cout << "\n\t\t\t\t\t\t\t\tClient with this ID currently not added in the system!\n";
            }
        }
        cout << "\n\t\t\t\t\t\t\t\tSuccessfully Trainer Alotted\n";
    }

    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n ";
    getch();
    client_database();
}

void admin::display_all_clients()
{
    system("cls");
    ifstream fin;
    fin.open("client.dat", ios::binary | ios::in);

    if (!(fin))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Displaying All Clients Details ---------------->\n\n";
        while (fin.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            cout << "\n\t\t\t\t\t\t\t\tName: " << Client.name << endl
                 << "\n\t\t\t\t\t\t\t\tGender: " << Client.gender << endl
                 << "\n\t\t\t\t\t\t\t\tPhone: " << Client.phone_number << endl
                 << "\n\t\t\t\t\t\t\t\tID: " << Client.id << endl
                 << "\n\t\t\t\t\t\t\t\tPassword: " << Client.password << endl
                 << "\n\t\t\t\t\t\t\t\tTrainer Allocated: " << Client.trainer_id << endl;
            if (Client.is_member == true)
            {
                Client.Membership.display_membership(Client.id);
            }
            cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
        }
    }
    fin.close();
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    client_database();
}
void admin::search_client()
{
    system("cls");
    int choice;
    char search_id[20], search_name[20], mem_type[20], search_gender[20];
    ifstream fin;
    bool found = false;
    fin.open("client.dat", ios::binary | ios::in);
    if (!(fin))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Search a Client ---------------->";
        //     cout << "\n\t\t\t\t\t\t\t\t1.BY NAME\n"
        //          << "\n\t\t\t\t\t\t\t\t2.BY MEMBERSHIP\n"
        //          << "\n\t\t\t\t\t\t\t\t3.BY ID\n"
        //          << "\n\t\t\t\t\t\t\t\t4.BY GENDER\n"
        //          << endl;
        // here:
        //     cout << "\n\t\t\t\t\t\t\t\tChoice: ";
        //     cin >> choice;
        //     if (choice == 1)
        //     {
        //         cout << "\n\n\t\t\t\t\t\t\t\tEnter search name: ";
        //         cin >> ws;
        //         cin.get(search_name, 20);
        //     }
        //     else if (choice == 2)
        //     {
        //         cout << "\n\n\t\t\t\t\t\t\t\tEnter search membership type: ";
        //         cin >> ws;
        //         cin.get(mem_type, 20);
        //         if (mem_type[0] >= 'a' && mem_type[0] <= 'z')
        //         {
        //             mem_type[0] -= 32;
        //         }
        //     }
        //     else if (choice == 3)
        //     {
        //         cout << "\n\n\t\t\t\t\t\t\t\tEnter Client ID: ";
        //         cin.ignore();
        //         cin.get(search_id, 20);
        //         for (int i = 0; i < strlen(search_id); i++)
        //         {
        //             if (search_id[i] >= 'a' && search_id[i] <= 'z')
        //             {
        //                 search_id[i] -= 32;
        //             }
        //         }
        //     }
        //     else if (choice == 4)
        //     {
        //         cout << "\n\n\t\t\t\t\t\t\t\tEnter search gender:  ";
        //         cin.ignore();
        //         cin.get(search_gender, 20);
        //         if (search_gender[0] >= 'a' && search_gender[0] <= 'z')
        //         {
        //             search_gender[0] -= 32;
        //         }
        //     }
        //     else
        //     {
        //         cout << "\n\t\t\t\t\t\t\t\tWrong Choice\n";
        //         goto here;
        //     }
        //     while (fin.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        //     {
        //         if ((strcmp(Client.id, search_id) == 0))
        //         {
        //             display(Client);
        //             found = true;
        //         }
        //         else if ((strcmp(Client.name, search_name) == 0))
        //         {
        //             display(Client);
        //             found = true;
        //         }
        //         else if ((strcmp(Client.gender, search_gender) == 0))
        //         {
        //             display(Client);
        //             found = true;
        //         }
        //         else if ((strcmp(Client.Membership.type, mem_type) == 0))
        //         {
        //             display(Client);
        //             found = true;
        //         }
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Client ID: ";
        cin.ignore();
        cin.get(search_id, 20);
        while (fin.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            if (strcmp(search_id, Client.id) == 0)
            {
                cout << "\n\t\t\t\t\t\t\t\tName: " << Client.name << endl
                     << "\n\t\t\t\t\t\t\t\tGender: " << Client.gender << endl
                     << "\n\t\t\t\t\t\t\t\tPhone: " << Client.phone_number << endl
                     << "\n\t\t\t\t\t\t\t\tID: " << Client.id << endl
                     << "\n\t\t\t\t\t\t\t\tPassword: " << Client.password << endl
                     << "\n\t\t\t\t\t\t\t\tTrainer Allocated: " << Client.trainer_id << endl;
                if (Client.is_member == true)
                {
                    Client.Membership.display_membership(Client.id);
                }
                cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
            }
        }

        if (found == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tClient not found!\n\n";
        }
    }
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    fin.close();
    client_database();
}

void admin::remove_client()
{
    system("cls");
    ifstream fin, file;
    ofstream fout, file2;
    bool flag = false;
    char delete_id[20];

    fin.open("client.dat", ios::binary | ios::in);
    if (!fin)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Delete a Client ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Client ID to be deleted: ";
        cin.ignore();
        cin.get(delete_id, 20);

        fout.open("temp.dat", ios::binary | ios::out);
        while (fin.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            if (strcmp(delete_id, Client.id) != 0)
            {
                fout.write(reinterpret_cast<char *>(&Client), sizeof(Client));
            }
            else
            {
                Client.Membership.cancel_membership(delete_id, Client.id);
                flag = true;
            }
        }
        if (flag == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tClient not found!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\tDeleted successfully!\n";
            file.open("Admin.dat", ios::binary | ios::in);
            file.read(reinterpret_cast<char *>(&details), sizeof(details));
            --details.number_of_client;
            file.close();

            file2.open("Admin.dat", ios::binary | ios::out);
            file2.write(reinterpret_cast<char *>(&details), sizeof(details));
            file2.close();
        }
    }

    fin.close();
    fout.close();
    remove("client.dat");
    rename("temp.dat", "client.dat");

    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    client_database();
}
void admin::update_client()
{
    system("cls");
    fstream file;
    char update_id[20];
    char *new_password;
    int choice;
    bool flag = false, check = false;

    file.open("client.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!file)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {

        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Update a Client's Details ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Client ID to be updated: ";
        cin.ignore();
        cin.get(update_id, 20);

        file.seekg(0);
        while (file.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            if (strcmp(update_id, Client.id) == 0)
            {

                do
                {
                    flag = true;
                    cout << "\n\n\n\n\t\t\t\t\t\t\t\tWhich field you want to update? \n\n";
                    cout << "\n\t\t\t\t\t\t\t\t<1> Name\n";
                    cout << "\n\t\t\t\t\t\t\t\t<2> Gender\n";
                    cout << "\n\t\t\t\t\t\t\t\t<3> Phone# \n";
                    cout << "\n\t\t\t\t\t\t\t\t<4> Password \n";
                    cout << "\n\t\t\t\t\t\t\t\t__________________________\n";
                    cout << "\n\t\t\t\t\t\t\t\tEnter Choice: ";
                    cin >> choice;

                    switch (choice)
                    {

                    case 1:
                        cout << "\n\t\t\t\t\t\t\t\tEnter new Name: ";
                        cin >> ws;
                        cin.get(Client.name, 50);
                        break;
                    case 2:
                        cout << "\n\t\t\t\t\t\t\t\tEnter new Gender: ";
                        cin >> ws;
                        cin.get(Client.gender, 50);
                        break;
                    case 3:
                        cout << "\n\t\t\t\t\t\t\t\tEnter new Phone#: ";
                        cin >> ws;
                        cin.get(Client.phone_number, 50);
                        break;
                    case 4:
                        cout << "\n\t\t\t\t\t\t\t\tEnter new Password: ";
                        new_password = Client.pass_validation();
                        strcpy(Client.password, new_password);
                        break;
                    default:
                        cout << "Invalid choice...Enter again!\n";
                    }
                    file.seekp(-(long)sizeof(Client), ios_base::cur);

                } while (choice < 1 || choice > 5);

                file.write(reinterpret_cast<char *>(&Client), sizeof(Client));
            }
        }

        if (flag == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tClient not found!\n";
            cout << "\n\t\t\t\t\t\t\t\tPress Enter to continue!\n";
            getch();
        }
        file.close();
        client_database();
    }
}
void admin::gettotalclient()
{
    ifstream fin;
    fin.open("Admin.dat", ios::binary | ios::in);
    if (!fin)
    {
        cout << "\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        fin.read(reinterpret_cast<char *>(&details), sizeof(details));
        cout << "\n\n\t\t\t\t\t\t\t\t Total clients are: " << details.number_of_client << endl;
    }
    getch();
    client_database();
}

void admin::trainer_database()
{
    system("cls");
    int choice;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome Admin ---------------->";
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    cout << "\n\n\t\t\t\t\t\t\t\t<1> Add new trainer" << endl // add personal info except ID and Password
         << "\n\n\t\t\t\t\t\t\t\t<2> Display All trainer" << endl
         << "\n\n\t\t\t\t\t\t\t\t<3> Remove a trainer" << endl
         << "\n\n\t\t\t\t\t\t\t\t<4> Update trainer Information " << endl
         << "\n\n\t\t\t\t\t\t\t\t<5> Search a trainer  " << endl
         << "\n\n\t\t\t\t\t\t\t\t<6> View Total trainers " << endl
         << "\n\n\t\t\t\t\t\t\t\t<7> Go Back" << endl;
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    cout << "\n\n\t\t\t\t\t\t\t\tChoose your desired option: ";
    do
    {
        cin >> choice;
        switch (choice)
        {
        case 1:
            add_trainer();
            break;
        case 2:
            display_all_trainers();
            break;
        case 3:
            remove_trainer();
            break;
        case 4:
            update_trainer();
            break;
        case 5:
            search_trainer();
            break;
        case 6:
            gettotaltrainers();
            break;
        case 7:
            menu();
            break;
        default:
            cout << "Wrong Choice!\n";
        }
    } while (choice < 1 || choice > 7);
}
void admin::Inventory_database()
{
    system("cls");
    int choice;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome Admin ---------------->";
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    cout << "\n\n\t\t\t\t\t\t\t\t<1> Add Inventory" << endl
         << "\n\n\t\t\t\t\t\t\t\t<2> Display All Inventory" << endl
         << "\n\n\t\t\t\t\t\t\t\t<3> Remove Inventory" << endl
         << "\n\n\t\t\t\t\t\t\t\t<4> Update Inventory" << endl
         << "\n\n\t\t\t\t\t\t\t\t<5> Display Specific Inventory" << endl
         << "\n\n\t\t\t\t\t\t\t\t<6> Search Inventory " << endl
         << "\n\n\t\t\t\t\t\t\t\t<7> Go Back" << endl;
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    do
    {
        cout << "\n\n\t\t\t\t\t\t\t\tChoose your desired option: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            add_inventory();
            break;
        case 2:
            display_all_inventory();
            break;
        case 3:
            remove_inventory();
            break;
        case 4:
            update_inventory();
            break;
        case 5:
            display_specific();
            break;
        case 6:
            search_inventory();
            break;
        case 7:
            menu();
            break;
        default:
            cout << "Wrong Choice!\n";
        }
    } while (choice < 1 || choice > 7);
}

// Trainer
void admin::add_trainer()
{
    system("cls");
    char bogusid[20], name[20], gender[20], phone[20], expertise[20], time[20], *password;
    float salary;
    bool check;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Add a Trainer ---------------->";

    ofstream fout;
    ofstream file;
    ifstream file2;
    fout.open("trainers.dat", ios::binary | ios::app);

    if (!(fout))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {

        do
        {
            cout << "\n\n\t\t\t\t\t\t\t\tEnter the trainer ID(e.g T-123): ";
            cin >> ws;
            cin.get(bogusid, 20);
            if (Trainer.checkid(bogusid, "trainers.dat") == true)
            {
                cout << "\n\n\t\t\t\t\t\t\t\tID already exists!\n";
                check = true;
            }
            else
            {
                cout << "\n\n\t\t\t\t\t\t\t\tEnter trainer's name: ";
                cin >> ws;
                cin.get(name, 20);

                cout << "\n\n\t\t\t\t\t\t\t\tEnter trainer's gender: ";
                cin >> ws;
                cin.get(gender, 20);

                cout << "\n\n\t\t\t\t\t\t\t\tEnter trainer's phone#: ";
                cin >> ws;
                cin.get(phone, 20);

                cout << "\n\n\t\t\t\t\t\t\t\tEnter trainer's expertise: ";
                cin >> ws;
                cin.get(expertise, 20);

                cout << "\n\n\t\t\t\t\t\t\t\tEnter trainer's salary: ";
                cin >> salary;

                char ans;
                cout << "\n\n\t\t\t\t\t\t\t\tSelect trainer's alloted time at gym: \n\n\t\t\t\t\t\t\t\t1)Morning\n\t\t\t\t\t\t\t\t2)Afternoon\n\t\t\t\t\t\t\t\t3)Night\n\t\t\t\t\t\t\t\tSelect(1/2/3): ";
                cin >> ws;
                cin >> ans;
                if (ans == '1')
                    strcpy(time, "Morning");
                else if (ans == '2')
                    strcpy(time, "Afternoon");
                else if (ans == '3')
                    strcpy(time, "Night");

                strcpy(Trainer.id, bogusid);
                strcpy(Trainer.name, name);
                strcpy(Trainer.gender, gender);
                strcpy(Trainer.phone_number, phone);
                strcpy(Trainer.expertise, expertise);
                strcpy(Trainer.time, time);
                Trainer.salary = salary;
                Trainer.numberofClients = 0;
                check = false;
            }
        } while (check == true);

        password = pass_validation();
        strcpy(Trainer.password, password);
        fout.write(reinterpret_cast<char *>(&Trainer), sizeof(Trainer));

        file2.open("Admin.dat", ios::binary | ios::in);
        file2.read(reinterpret_cast<char *>(&details), sizeof(details));
        details.number_of_trainers++;
        file2.close();

        file.open("Admin.dat", ios::binary | ios::out);
        file.write(reinterpret_cast<char *>(&details), sizeof(details));
        file.close();

        fout.close();
        trainer_database();
    }
}
trainer *admin::client_alloted(client *Clients, char trainer_id[])
{
    fstream file;
    bool flag = false;
    file.open("trainers.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!(file))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tTrainer File not created yet!\n";
    }
    else
    {
        file.seekg(0);
        while (file.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
        {
            if (strcmp(Trainer.id, trainer_id) == 0)
            {
                flag = true;
                Trainer.array_of_clients[Trainer.numberofClients++] = *Clients;
                file.seekp(-(long)sizeof(Trainer), ios_base::cur);
                file.write(reinterpret_cast<char *>(&Trainer), sizeof(Trainer));
                break;
            }
        }

        if (flag == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tTrainer with this ID currently not added in the system!\n";
        }
    }
    return &Trainer;
    file.close();
}
void admin::search_trainer()
{
    system("cls");
    char search_id[20];
    ifstream fin;
    bool found = false;
    fin.open("trainers.dat", ios::binary | ios::in);

    if (!(fin))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Search a Trainer ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Trainer ID: ";
        cin.ignore();
        cin.get(search_id, 20);
        while (fin.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
        {
            if (strcmp(search_id, Trainer.id) == 0)
            {
                cout << "\n\t\t\t\t\t\t\t\tName: " << Trainer.name << endl
                     << "\n\t\t\t\t\t\t\t\tGender: " << Trainer.gender << endl
                     << "\n\t\t\t\t\t\t\t\tPhone: " << Trainer.phone_number << endl
                     << "\n\t\t\t\t\t\t\t\tID: " << Trainer.id << endl
                     << "\n\t\t\t\t\t\t\t\tPassword: " << Trainer.password << endl;
                found = true;
            }
        }
        if (found == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tTrainer not found!\n\n";
        }
    }
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    fin.close();
    trainer_database();
}
void admin::display_all_trainers()
{

    system("cls");
    ifstream fin;
    fin.open("trainers.dat", ios::binary | ios::in);
    if (!(fin))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Displaying All Trainers Details ---------------->\n\n";
        while (fin.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
        {

            cout << "\n\t\t\t\t\t\t\t\tName: " << Trainer.name << endl
                 << "\n\t\t\t\t\t\t\t\tGender: " << Trainer.gender << endl
                 << "\n\t\t\t\t\t\t\t\tPhone: " << Trainer.phone_number << endl
                 << "\n\t\t\t\t\t\t\t\tID: " << Trainer.id << endl
                 << "\n\t\t\t\t\t\t\t\tPassword: " << Trainer.password << endl
                 << "\n\t\t\t\t\t\t\t\tClients Allocated: \n";
            for (int i = 0; i < Trainer.numberofClients; i++)
            {
                cout << &Trainer.array_of_clients[i] << endl;
            }
            cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
        }
    }
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    fin.close();
    trainer_database();
};
void admin::remove_trainer()
{

    system("cls");
    ifstream fin;
    ofstream fout;
    ofstream file;
    ifstream file2;
    bool flag = false;
    char delete_id[20];

    fin.open("trainers.dat", ios::binary | ios::in);
    file.open("Admin.dat", ios ::binary | ios::out);

    if (!fin)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Delete a Trainer ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Trainer ID to be deleted: ";
        cin.ignore();
        cin.get(delete_id, 20);

        fout.open("temp.dat", ios::binary | ios::out);
        while (fin.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
        {
            if (strcmp(delete_id, Trainer.id) != 0)
            {
                fout.write(reinterpret_cast<char *>(&Trainer), sizeof(Trainer));
            }
            else
            {
                flag = true;
            }
        }
        if (flag == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tTrainer not found!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\tDeleted successfully!\n";

            file2.open("Admin.dat", ios::binary | ios::in);
            file2.read(reinterpret_cast<char *>(&details), sizeof(details));
            --details.number_of_trainers;
            file2.close();

            file.write(reinterpret_cast<char *>(&details), sizeof(details));
        }
    }

    fin.close();
    fout.close();
    file.close();
    remove("trainers.dat");
    rename("temp.dat", "trainers.dat");
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    trainer_database();
}
void admin::update_trainer()
{
    system("cls");
    fstream file;
    char update_id[20];
    char *new_password;
    int choice;
    bool flag = false, check = false;

    file.open("trainers.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!file)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {

        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Update a Trainer's Details ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Trainer ID to be updated: ";
        cin >> ws;
        cin.get(update_id, 20);

        file.seekg(0);
        while (file.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
        {
            if (strcmp(update_id, Trainer.id) == 0)
            {

                do
                {
                    flag = true;
                    cout << "\n\n\n\n\t\t\t\t\t\t\t\tWhich field you want to update? \n\n";
                    cout << "\n\t\t\t\t\t\t\t\t<1> Name\n";
                    cout << "\n\t\t\t\t\t\t\t\t<2> Gender\n";
                    cout << "\n\t\t\t\t\t\t\t\t<3> Phone# \n";
                    cout << "\n\t\t\t\t\t\t\t\t<4> Password \n";
                    cout << "\n\t\t\t\t\t\t\t\t__________________________\n";
                    cout << "\n\t\t\t\t\t\t\t\tEnter Choice: ";
                    cin >> choice;

                    switch (choice)
                    {

                    case 1:
                        cout << "\n\t\t\t\t\t\t\t\tEnter new Name: ";
                        cin >> ws;
                        cin.get(Client.name, 50);
                        break;
                    case 2:
                        cout << "\n\t\t\t\t\t\t\t\tEnter new Gender: ";
                        cin >> ws;
                        cin.get(Client.gender, 50);
                        break;
                    case 3:
                        cout << "\n\t\t\t\t\t\t\t\tEnter new Phone#: ";
                        cin >> ws;
                        cin.get(Client.phone_number, 50);
                        break;
                    case 4:
                        cout << "\n\t\t\t\t\t\t\t\tEnter new Password: ";
                        new_password = pass_validation();
                        strcpy(Client.password, new_password);
                        break;
                    default:
                        cout << "Invalid choice...Enter again!\n";
                    }
                    file.seekp(-(long)sizeof(Trainer), ios_base::cur);
                } while (choice < 1 || choice > 5);
                file.write(reinterpret_cast<char *>(&Trainer), sizeof(Trainer));
            }
        }

        if (flag == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tTrainer not found!\n";
            cout << "\n\t\t\t\t\t\t\t\tPress Enter to continue!\n";
            getch();
        }
        trainer_database();
    }
}
// void admin::show_clients()
// {
//     ifstream fin;
//     fin.open("clients.dat", ios::binary | ios::in);
//     while (fin.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
//     {
//         for (int i = 0; i < Trainer.numberofClients; i++)
//         {
//             if (strcmp(Trainer.array_of_clients[i], Client.id) == 0)
//             {
//                 cout << &Trainer.array_of_clients[i] << endl;
//             }
//         }
//     }
//     fin.close();
// }
void admin::gettotaltrainers()
{
    ifstream fin;
    fin.open("Admin.dat", ios::binary | ios::in);
    if (!fin)
    {
        cout << "\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        fin.read(reinterpret_cast<char *>(&details), sizeof(details));
        cout << "\n\n\t\t\t\t\t\t\t\t Total Trainers are: " << details.number_of_trainers << endl;
    }
    getch();
    trainer_database();
}

// Inventory
void admin ::add_inventory()
{
    system("cls");
    fstream fout;
    bool check;
    char id_num[20], id[20], name[20], idname[5];
    int quantity;
    float price;
    ifstream afin;
    ofstream afout;
    afin.open("Admin.dat", ios::binary | ios::in);
    afin.read(reinterpret_cast<char *>(&details), sizeof(details));
    afin.close();

    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Add Inventory ---------------->";
    cout << "\n\n\t\t\t\t\t\t\t\tEnter Equipment name: ";
    cin >> ws;
    cin.get(name, 20);

    cout << "\n\n\t\t\t\t\t\t\t\tEnter the quantity  of equipment you would like to order: ";
    cin >> quantity;
    cout << "\n\n\t\t\t\t\t\t\t\tEnter the price of equipment: ";
    cin >> price;
    for (int i = 0; i < quantity; i++)
    {
        fout.open("inventory.dat", ios::binary | ios::app);
        do
        {
            cout << "\n\t\t\t\t\t\t\t\tEnter Equipment ID's for equipment(numeric part only)---->[" << i + 1 << "]: ";
            cin >> ws;
            cin.get(id_num, 20);
            strcpy(idname, "I-");
            strcat(idname, id_num);
            strcpy(id, idname);
            if (inventory.checkid(id, "inventory.dat") == true)
            {
                cout << "\n\t\t\t\t\t\t\t\tID already exists!\n";
                check = true;
            }
            else
            {
                strcpy(inventory.item_id, id);
                strcpy(inventory.item_name, name);
                inventory.price = price;
                check = false;
            }
        } while (check == true);

        inventory.quantity = 1;
        cout << "\n\t\t\t\t\t\t\t\tEquipment ID: " << inventory.item_id;
        fout.write(reinterpret_cast<char *>(&inventory), sizeof(inventory));
        cout << "\n\t\t\t\t\t\t\t\tEquipment added to Inventory !\n";
        fout.close();
    }

    cout << "\n\t\t\t\t\t\t\t\tPress enter to continue\n";
    details.balance -= quantity * price;
    wallet.amount = quantity * price;
    wallet.send = false;
    wallet.recieve = false;
    strcpy(wallet.inventory_item_name, name);
    char buffer[30];
    strcpy(buffer, strcat(inventory.item_id, "4477"));
    wallet.setid(buffer);
    wallet.setdate(getdate());
    wallet.setime(gettime());

    ofstream tfout;
    tfout.open("transaction_history.dat", ios::app);
    tfout.write(reinterpret_cast<char *>(&wallet), sizeof(wallet));
    tfout.close();

    afout.open("Admin.dat", ios::binary | ios::out);
    afout.write(reinterpret_cast<char *>(&details), sizeof(details));
    afout.close();

    getch();
    Inventory_database();
}
void admin::search_inventory()
{
    system("cls");
    char search_id[20];
    ifstream fin;
    bool found = false;
    fin.open("inventory.dat", ios::binary | ios::in);
    if (!(fin))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Search Inventory ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Equipment ID to search : ";
        cin.ignore();
        cin.get(search_id, 20);
        while (fin.read(reinterpret_cast<char *>(&inventory), sizeof(inventory)))
        {
            if (strcmp(search_id, inventory.item_id) == 0)
            {
                cout << "\n\t\t\t\t\t\t\t\tEquipment Name: " << inventory.item_name << endl
                     << "\n\t\t\t\t\t\t\t\tEquipment ID: " << inventory.item_id << endl
                     << "\n\t\t\t\t\t\t\t\tQuantity ordered: " << inventory.quantity << endl
                     << "\n\t\t\t\t\t\t\t\tPrice: " << inventory.price << endl;
                found = true;
            }
        }
        if (found == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tEquipment not found!\n\n";
        }
    }
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    fin.close();
    Inventory_database();
}
void admin::remove_inventory()
{
    system("cls");
    ifstream fin;
    ofstream fout;
    char deleteid[20];
    bool found = false;

    fin.open("inventory.dat", ios::binary | ios::in);

    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Delete Inventory ---------------->";
    cout << "\n\n\t\t\t\t\t\t\t\tEnter the Equipment ID to be deleted: ";
    cin.ignore();
    cin.get(deleteid, 20);

    if (!fin)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        fout.open("tempfile.dat", ios::binary | ios::out);
        while (fin.read(reinterpret_cast<char *>(&inventory), sizeof(inventory)))
        {
            if (strcmp(inventory.item_id, deleteid) != 0)
            {
                fout.write(reinterpret_cast<char *>(&inventory), sizeof(inventory));
            }
            else
            {
                found = true;
            }
        }
        if (found == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tEquipment not found!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\tDeleted successfully!\n";
        }
    }
    fin.close();
    fout.close();
    remove("inventory.dat");
    rename("tempfile.dat", "inventory.dat");
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    Inventory_database();
}

void admin::display_all_inventory()
{
    system("cls");
    ifstream fin;
    bool found = false;
    fin.open("inventory.dat", ios::binary | ios::in);
    if (!(fin))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Display All Inventory ---------------->";
        while (fin.read(reinterpret_cast<char *>(&inventory), sizeof(inventory)))
        {
            cout << "\n\n\t\t\t\t\t\t\t\tEquipment Name: " << inventory.item_name
                 << "\n\t\t\t\t\t\t\t\tEquipment ID: " << inventory.item_id
                 << "\n\t\t\t\t\t\t\t\tQuantity ordered: " << inventory.quantity
                 << "\n\t\t\t\t\t\t\t\tPrice: " << inventory.price << endl;
            cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
        }
    }
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    fin.close();
    Inventory_database();
}

void admin::display_specific()
{
    system("cls");
    char search_name[50];
    ifstream fin;
    bool found = false;
    fin.open("inventory.dat", ios::binary | ios::in);
    if (!(fin))
    {
        cout << "\n\n\t\t\t\t\t\t\t\tFile not created yet!\n";
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Display Specific Inventory ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\tEnter Equipment name to display records of : ";
        cin.ignore();
        cin.get(search_name, 50);
        if (search_name[0] >= 'a' && search_name[0] <= 'z')
        {
            search_name[0] -= 32;
        }
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Displaying " << search_name << " Records ---------------->";
        while (fin.read(reinterpret_cast<char *>(&inventory), sizeof(inventory)))
        {
            if (strcmp(search_name, inventory.item_name) == 0)
            {
                cout << "\n\n\t\t\t\t\t\t\t\tEquipment Name: " << inventory.item_name << endl
                     << "\n\t\t\t\t\t\t\t\tEquipment ID: " << inventory.item_id << endl
                     << "\n\t\t\t\t\t\t\t\tQuantity ordered: " << inventory.quantity << endl
                     << "\n\t\t\t\t\t\t\t\tPrice: " << inventory.price << endl;
                found = true;
            }
        }
        if (found == false)
        {
            cout << "\n\t\t\t\t\t\t\t\tEquipment not found!\n\n";
        }
    }
    cout << "\n\t\t\t\t\t\t\t\tPress Enter to Continue...\n";
    getch();
    fin.close();
    Inventory_database();
}
void admin::update_inventory()
{
    system("cls");
    fstream fin;
    char ID[20];
    int ans;
    bool success = false;
    fin.open("inventory.dat", ios::binary | ios::in | ios::out | ios::ate);

    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Update Inventory ---------------->\n";
    cout << "\n\n\n\n\t\t\t\t\t\t\t\tEnter the ID of the equipment you would like to update: ";
    cin >> ws;
    cin.get(ID, 20);

    fin.seekg(0);
    while (fin.read(reinterpret_cast<char *>(&inventory), sizeof(inventory)))
    {
        if (strcmp(inventory.item_id, ID) == 0)
        {
            do
            {
                success = true;
                cout << "\n\n\n\n\t\t\t\t\t\t\t\tWhich field would you like to update?\n\n";
                cout << "\n\t\t\t\t\t\t\t\t1.Price" << endl
                     << "\n\t\t\t\t\t\t\t\t2.Quantity" << endl;
                cout << "\n\t\t\t\t\t\t\t\tChoice: ";
                cin >> ans;
                switch (ans)
                {
                case 1:
                    cout << "\n\t\t\t\t\t\t\t\tEnter new price: ";
                    cin >> inventory.price;
                    break;
                case 2:
                    cout << "\n\t\t\t\t\t\t\t\tEnter new quantity: ";
                    cin >> inventory.quantity;
                    break;
                default:
                    cout << "Invalid choice...Enter again!\n";
                }
                fin.seekp(-(long)sizeof(inventory), ios_base::cur);
            } while (ans != 1 && ans != 2);
            fin.write(reinterpret_cast<char *>(&inventory), sizeof(inventory));
        }
    }
    if (success == false)
    {
        cout << "\n\t\t\t\t\t\t\t\tEquipment not found!\n";
        cout << "\n\t\t\t\t\t\t\t\tPress Enter to continue!\n";
        getch();
    }
    Inventory_database();
}

void admin::Client_attendance_menu()
{
    int choose;
    while (1)
    {
        system("cls");
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome Admin ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
        cout << "\n\n\t\t\t\t\t\t\t\t<1> Input Attendance" << endl
             << "\n\n\t\t\t\t\t\t\t\t<2> View Attendance" << endl
             << "\n\n\t\t\t\t\t\t\t\t<3> Search A Client's Attendance" << endl
             << "\n\n\t\t\t\t\t\t\t\t<4> Edit a Client's Attendance" << endl
             << "\n\n\t\t\t\t\t\t\t\t<5> Go Back" << endl;
        cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
        cout << "\n\n\t\t\t\t\t\t\t\tChoose your desired option: ";

        cin >> ws;
        cin >> choose;
        switch (choose)
        {
        case 1:

            input_Client_attendance();
            break;
        case 2:
            view_Client_attendance();
            break;
        case 3:
            search_Client_attendance();
            break;
        case 4:
            edit_Client_attendance();
            break;
        case 5:
            menu();
        }
        if (choose > 5 || choose < 1)
            cout << "\n\n\t\t\t\t\t\t\tSelect correct option";
        cout << "\n\n\t\t\t\t\t\t\t\tPress any key to Continue..........";
        getch();
    }
}

void admin::input_Client_attendance()
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Input Attendance ---------------->";
    char c_date[15];
here:
    cin.ignore();
    cout << "\n\n\t\t\t\t\t\t\t\tEnter Current date[dd/mm/yy]: ";
    gets(c_date);

    ofstream fout;
    ifstream fin1, fin2;

    fout.open("Client Attendance.dat", ios::binary | ios::app);
    fin1.open("Client Attendance.dat", ios::binary | ios::in);
    if (!fout || !fin1)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in creating file\n";
    }
    else
    {
        while (fin1.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
        {
            if (strcmp(Client_attendance.date, c_date) == 0)
            {
                cout << "\n\n\t\t\t\t\t\t\t\tAttendance Already Taken. TRY ANOTHER DATE";
                goto here;
            }
        }
    }
    strcpy(Client_attendance.date, c_date);
    fin2.open("Client.dat", ios::binary | ios::in);
    if (!fin2)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in Opening file\n";
    }
    else
    {
        while (fin2.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            cout << "\n\n\t\t\t\t\t\t\t\tClient Name  : " << Client.name;
            cout << "\n\n\t\t\t\t\t\t\t\tClient ID: " << Client.id;
            strcpy(Client_attendance.id, Client.id);
            cout << "\n\n\t\t\t\t\t\t\tPress [P] for present and [A] for absent....";
            cin >> ws;
            cin >> Client_attendance.marked;
            fout.write(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance));
        }
    }
    fout.close();
    fin1.close();
    fin2.close();
    cout << "\n\n\t\t\t\t\t\t\t\tSuccessfully all Attendance are taken";
}

void admin::view_Client_attendance()
{

    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- View A Attendance ---------------->";
    char date[15];
    int flag = 0;
    cout << "\n\n\t\t\t\t\t\t\t\tEnter the date you want to search attendance: ";
    cin.ignore();
    gets(date);
    ifstream fin_client, fin_attendance;
    fin_client.open("Client.dat", ios::binary | ios::in);
    fin_attendance.open("Client Attendance.dat", ios::binary | ios::in);

    if (!fin_client || !fin_attendance)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in opening file!";
    }
    else
    {
        cout << endl
             << endl;
        while (fin_client.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            while (fin_attendance.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
            {
                if (strcmp(Client.id, Client_attendance.id) == 0 && strcmp(date, Client_attendance.date) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                break;
            }
            cout << "\n\t\t\t\t\t\t\t\tClient Name: " << Client.name;
            cout << "\n\t\t\t\t\t\t\t\tClient ID: " << Client.id << endl;
            cout << "\n\t\t\t\t\t\t\t\tAttendance: " << Client_attendance.marked;

            fin_attendance.seekg(0);
            cout << "\n\n\t\t\t\t\t\t\t-----------------------------------------------------------\n";
        }
    }

    if (flag == 0)
    {
        cout << "\t\t\t\t\t\t\t\tAttendance For this Date had not been Taken";
    }
    fin_attendance.close();
    fin_client.close();
}

void admin::search_Client_attendance()
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Search A Client's Attendance ---------------->";
    int total = 0, p = 0, a = 0, flag = 0, i = 1;
    char id[20], ans;

    ifstream fin_client;
    ifstream fin_attendance;

    fin_client.open("client.dat", ios::binary | ios::in);
    // if (!fin_client)
    // {
    //     cout << "\n\n\t\t\t\t\t\t\t\tAttendance or either Records of Students have not been input in the system";
    //     getch();
    //     Client_attendance_menu();
    // }
    // cout << "\n\n\t\t\t\t\t\t\t\tFollwing are the Client's ID which are Currently stored in the System: " << endl;

    // while (fin_client.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
    // {
    //     cout << "\n\t\t\t\t\t\t\t\t   " << i << ". " << Client.id << endl;
    //     i++;
    // }
    cout << "\n\n\t\t\t\t\t\t\t\tEnter the Client ID You Want To Search: ";
    cin >> ws;
    cin.get(id, 20);

    cout << "\n\n\t\t\t\t\t\t\t\t>> Attendance <<";
    fin_attendance.open("Client Attendance.dat", ios::binary | ios::in);

    if (!fin_client || !fin_attendance)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tAttendance or either Records of Client have not been input in the system";
        getch();
        Client_attendance_menu();
    }
    else
    {
        cout << "\n\n";
        while (fin_client.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            if (strcmp(Client.id, id) == 0)
            {

                cout << "\n\n\t\t\t\t\t\t\t\tClient Name  : " << Client.name;
                cout << "\n\t\t\t\t\t\t\t\tClient ID    : " << Client.id << endl;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            cout << "\n\n\t\t\t\t\t\t\tThis Client ID is not available in the System\n\n\t\t\t\t\t\t\tPress any key to continue...";
            getch();
            Client_attendance_menu();
        }
        while (fin_attendance.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
        {

            if ((strcmp(id, Client_attendance.id)) == 0 && Client_attendance.marked != '\0')
            {
                total++;
                if (Client_attendance.marked == 'p' || Client_attendance.marked == 'P')
                    p++;
                else
                    a++;
            }
        }
        fin_client.close();
        fin_attendance.close();

        fin_attendance.open("Client Attendance.dat", ios::binary | ios::in);
        cout << "\n\t\t\t\t\t\t\t\tTotal Days: " << total;
        cout << "\n\t\t\t\t\t\t\t\tPresent: " << p;
        cout << "\n\t\t\t\t\t\t\t\tAbsent: " << a;
        cout << "\n\t\t\t\t\t\t\t\tAttendance Mark(out of 100%): " << ((p * 1.0 / total * 1.0) * 100.0);
        cout << "\n\n\t\t\t\t\t\t\t\tDo You Want To View Attendance Details[y/n]: ";
        char ans2;
        cin >> ans2;
        if (ans2 == 'y' || ans2 == 'Y')
        {
            while (fin_attendance.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
            {
                if ((strcmp(id, Client_attendance.id)) == 0 && (Client_attendance.marked != '\0'))
                {
                    if (Client_attendance.marked == 'p' || Client_attendance.marked == 'P')
                    {
                        cout << "\n\t\t\t\t\t\t\t\t" << Client_attendance.date << " : Present";
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\t\t\t\t" << Client_attendance.date << " : Absent";
                    }
                }
            }
        }
    }
    fin_attendance.close();
}

void admin::edit_Client_attendance()
{

    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Edit A Clients's Attendance ---------------->";
    int flag;
    char id[15], date[15], ans;

    flag = 0;
    cin.ignore();
    cout << "\n\n\t\t\t\t\t\t\t\tEnter Client ID You Want to Edit: ";
    gets(id);
    fflush(stdin);
    cout << "\n\n\t\t\t\t\t\t\t\tEnter Date[dd/mm/yyyy]: ";
    gets(date);
    ifstream fin_client;
    fstream file_attendance;
    fin_client.open("Client.dat", ios::binary | ios::in);
    file_attendance.open("Client Attendance.dat", ios::binary | ios::ate | ios::out | ios::in);
    if (!fin_client || !file_attendance)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tAttendance or either Records of Client have not been input in the system";
        getch();
        Client_attendance_menu();
    }
    else
    {
        cout << "\n\n";
        file_attendance.seekg(0);
        while (fin_client.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            if ((strcmp(id, Client.id)) == 0)
            {
                while (file_attendance.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
                {
                    if ((strcmp(id, Client_attendance.id)) == 0 && (strcmp(date, Client_attendance.date)) == 0)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag == 1)
            {
                break;
            }
        }
    }

    if (flag == 1)
    {
        // fout_attendance.open("Client Attendance.dat", ios::ate | ios::binary);
        cout << "\n\t\t\t\t\t\t\t\tClient Name: " << Client.name;
        cout << "\n\t\t\t\t\t\t\t\tClient ID: " << Client.id << endl;

        cout << "\n\t\t\t\t\t\t\t\tAttendance: " << Client_attendance.marked;
        cout << "\n\n\t\t\t\t\t\t\tPress [P] for present and [A] for absent....";
        cin >> Client_attendance.marked;
        file_attendance.seekp(-(long)sizeof(Client_attendance), ios_base::cur);
        file_attendance.write(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance));
        cout << "\n\n\t\t\t\t\t\t\t\tEdit Successfully";
    }

    else
    {
        cout << "\n\t\t\t\t\t\t\t\tAttendance Date and Clients ID not Matched\n\n\t\t\t\t\t\t\t---------------------------------------------------------------------------------------------------\n\n";
    }

    fin_client.close();
    file_attendance.close();
}

/////////////////////////

void admin::Trainer_attendance_menu()
{
    int choose;
    while (1)
    {
        system("cls");
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome Admin ---------------->";
        cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
        cout << "\n\n\t\t\t\t\t\t\t\t<1> Input Attendance" << endl
             << "\n\n\t\t\t\t\t\t\t\t<2> View Attendance" << endl
             << "\n\n\t\t\t\t\t\t\t\t<3> Search A Trainer's Attendance" << endl
             << "\n\n\t\t\t\t\t\t\t\t<4> Edit a Trainer's Attendance" << endl
             << "\n\n\t\t\t\t\t\t\t\t<5> Go Back" << endl;
        cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
        cout << "\n\n\t\t\t\t\t\t\t\tChoose your desired option: ";

        cin >> ws;
        cin >> choose;
        switch (choose)
        {
        case 1:

            input_Trainer_attendance();
            break;
        case 2:
            view_Trainer_attendance();
            break;
        case 3:
            search_Trainer_attendance();
            break;
        case 4:
            edit_Trainer_attendance();
            break;
        case 5:
            menu();
        }
        if (choose > 5 || choose < 1)
            cout << "\n\n\t\t\t\t\t\t\tSelect correct option";
        cout << "\n\n\t\t\t\t\t\t\t\tPress any key to Continue..........";
        getch();
    }
}

void admin::input_Trainer_attendance()
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Input Attendance ---------------->";
    char c_date[15];
here:
    cin.ignore();
    cout << "\n\n\t\t\t\t\t\t\t\tEnter Current date[dd/mm/yy]: ";
    gets(c_date);

    ofstream fout;
    ifstream fin1, fin2;

    fout.open("Client Attendance.dat", ios::binary | ios::app);
    fin1.open("Client Attendance.dat", ios::binary | ios::in);
    if (!fout || !fin1)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in creating file\n";
    }
    else
    {
        while (fin1.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
        {
            if (strcmp(Client_attendance.date, c_date) == 0)
            {
                cout << "\n\n\t\t\t\t\t\t\t\tAttendance Already Taken. TRY ANOTHER DATE";
                goto here;
            }
        }
    }
    strcpy(Client_attendance.date, c_date);
    fin2.open("Client.dat", ios::binary | ios::in);
    if (!fin2)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in Opening file\n";
    }
    else
    {
        while (fin2.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            cout << "\n\n\t\t\t\t\t\t\t\tClient Name  : " << Client.name;
            cout << "\n\n\t\t\t\t\t\t\t\tClient ID: " << Client.id;
            strcpy(Client_attendance.id, Client.id);
            cout << "\n\n\t\t\t\t\t\t\tPress [P] for present and [A] for absent....";
            cin >> ws;
            cin >> Client_attendance.marked;
            fout.write(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance));
        }
    }
    fout.close();
    fin1.close();
    fin2.close();
    cout << "\n\n\t\t\t\t\t\t\t\tSuccessfully all Attendance are taken";
}

void admin::view_Trainer_attendance()
{

    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- View A Attendance ---------------->";
    char date[15];
    int flag = 0;
    cout << "\n\n\t\t\t\t\t\t\t\tEnter the date you want to search attendance: ";
    cin.ignore();
    gets(date);
    ifstream fin_client, fin_attendance;
    fin_client.open("Client.dat", ios::binary | ios::in);
    fin_attendance.open("Client Attendance.dat", ios::binary | ios::in);

    if (!fin_client || !fin_attendance)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in opening file!";
    }
    else
    {
        cout << endl
             << endl;
        while (fin_client.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            while (fin_attendance.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
            {
                if (strcmp(Client.id, Client_attendance.id) == 0 && strcmp(date, Client_attendance.date) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                break;
            }
            cout << "\n\t\t\t\t\t\t\t\tClient Name: " << Client.name;
            cout << "\n\t\t\t\t\t\t\t\tClient ID: " << Client.id << endl;
            cout << "\n\t\t\t\t\t\t\t\tAttendance: " << Client_attendance.marked;

            fin_attendance.seekg(0);
            cout << "\n\n\t\t\t\t\t\t\t-----------------------------------------------------------\n";
        }
    }

    if (flag == 0)
    {
        cout << "\t\t\t\t\t\t\t\tAttendance For this Date had not been Taken";
    }
    fin_attendance.close();
    fin_client.close();
}

void admin::search_Trainer_attendance()
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Search A Client's Attendance ---------------->";
    int total = 0, p = 0, a = 0, flag = 0, i = 1;
    char id[15], ans;
    cin.ignore();

    ifstream fin_client;
    ifstream fin_attendance;
    fin_client.open("Client.dat", ios::binary | ios::in);
    // if (!fin_client)
    // {
    //     cout << "\n\n\t\t\t\t\t\t\t\tAttendance or either Records of Students have not been input in the system";
    //     getch();
    //     Client_attendance_menu();
    // }
    // cout << "\n\n\t\t\t\t\t\t\t\tFollwing are the Client's ID which are Currently stored in the System: " << endl;

    // while (fin_client.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
    // {
    //     cout << "\n\t\t\t\t\t\t\t\t   " << i << ". " << Client.id << endl;
    //     i++;
    // }
    cout << "\n\n\t\t\t\t\t\t\t\tEnter the Student ID You Want To Search: ";
    gets(id);
    cout << "\n\n\t\t\t\t\t\t\t\t>> Attendance <<";
    fin_attendance.open("Client Attendance.dat", ios::binary | ios::in);

    if (!fin_client || !fin_attendance)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tAttendance or either Records of Students have not been input in the system";
        getch();
        Client_attendance_menu();
    }
    else
    {
        cout << "\n\n";
        while (fin_client.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            if (strcmp(Client.id, id) == 0)
            {

                cout << "\n\n\t\t\t\t\t\t\t\tStudent Name  : " << Client.name;
                cout << "\n\t\t\t\t\t\t\t\tStudent ID    : " << Client.id << endl;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            cout << "\n\n\t\t\t\t\t\t\tThis Student ID is not available in the System\n\n\t\t\t\t\t\t\tPress any key to continue...";
            getch();
            Client_attendance_menu();
        }
        while (fin_attendance.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
        {

            if ((strcmp(id, Client_attendance.id)) == 0 && Client_attendance.marked != '\0')
            {
                total++;
                if (Client_attendance.marked == 'p' || Client_attendance.marked == 'P')
                    p++;
                else
                    a++;
            }
        }
        fin_client.close();
        fin_attendance.seekg(0);

        cout << "\n\t\t\t\t\t\t\t\tTotal Classes: " << total;
        cout << "\n\t\t\t\t\t\t\t\tPresent: " << p;
        cout << "\n\t\t\t\t\t\t\t\tAbsent: " << a;
        cout << "\n\t\t\t\t\t\t\t\tAttendance Mark(out of 100%): " << ((p * 1.0 / total * 1.0) * 100.0);
        cout << "\n\n\t\t\t\t\t\t\t\tDo You Want To View Attendance Details[y/n]: ";
        char ans2;
        cin >> ans2;
        if (ans2 == 'y' || ans2 == 'Y')
        {
            while (fin_attendance.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
            {

                cout << "hello1";
                if ((strcmp(id, Client_attendance.id)) == 0 && (Client_attendance.marked != '\0'))
                {
                    if (Client_attendance.marked == 'p' || Client_attendance.marked == 'P')
                        cout << "\n\t\t\t\t\t\t\t\t" << Client_attendance.date << " : Present";
                    else
                        cout << "\n\t\t\t\t\t\t\t\t" << Client_attendance.date << " : Absent";
                }
            }
        }
    }
    fin_attendance.close();
}

void admin::edit_Trainer_attendance()
{

    system("cls");
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Edit A Clients's Attendance ---------------->";
    int flag;
    char id[15], date[15], ans;

    flag = 0;
    cin.ignore();
    cout << "\n\n\t\t\t\t\t\t\t\tEnter Trainer ID You Want to Edit: ";
    gets(id);
    fflush(stdin);
    cout << "\n\n\t\t\t\t\t\t\t\tEnter Date[dd/mm/yyyy]: ";
    gets(date);
    ifstream fin_client;
    fstream file_attendance;
    fin_client.open("Trainers.dat", ios::binary | ios::in);
    file_attendance.open("Trainers Attendance.dat", ios::binary | ios::ate | ios::out | ios::in);
    if (!fin_client || !file_attendance)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tAttendance or either Records of Trainer have not been input in the system";
        getch();
        Trainer_attendance_menu();
    }
    else
    {
        cout << "\n\n";
        file_attendance.seekg(0);
        while (fin_client.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            if ((strcmp(id, Client.id)) == 0)
            {
                while (file_attendance.read(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance)))
                {
                    if ((strcmp(id, Client_attendance.id)) == 0 && (strcmp(date, Client_attendance.date)) == 0)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag == 1)
            {
                break;
            }
        }
    }

    if (flag == 1)
    {
        // fout_attendance.open("Client Attendance.dat", ios::ate | ios::binary);
        cout << "\n\t\t\t\t\t\t\t\tTrainer Name: " << Client.name;
        cout << "\n\t\t\t\t\t\t\t\tTrainer ID: " << Client.id << endl;

        cout << "\n\t\t\t\t\t\t\t\tAttendance: " << Client_attendance.marked;
        cout << "\n\n\t\t\t\t\t\t\tPress [P] for present and [A] for absent....";
        cin >> Client_attendance.marked;
        file_attendance.seekp(-(long)sizeof(Client_attendance), ios_base::cur);
        file_attendance.write(reinterpret_cast<char *>(&Client_attendance), sizeof(Client_attendance));
        cout << "\n\n\t\t\t\t\t\t\t\tEdit Successfully";
    }

    else
    {
        cout << "\n\t\t\t\t\t\t\t\tAttendance and Trainer ID not Matched\n\n\t\t\t\t\t\t\t---------------------------------------------------------------------------------------------------\n\n";
    }

    fin_client.close();
    file_attendance.close();
}
void admin::Monetary_database()
{
    system("cls");
    int choice;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Welcome ---------------->";
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    cout << "\n\n\t\t\t\t\t\t\t\t<1> View Monetary information" << endl
         << "\n\n\t\t\t\t\t\t\t\t<2> Pay Salary to Trainer " << endl
         << "\n\n\t\t\t\t\t\t\t\t<3> View Transaction History" << endl
         << "\n\n\t\t\t\t\t\t\t\t<4> View Pending Registrations of Clients" << endl
         << "\n\n\t\t\t\t\t\t\t\t<5> Go Back" << endl;
    cout << "\n\n\t\t\t\t\t\t\t\t___________________________________________\n";
    do
    {
        cout << "\n\n\t\t\t\t\t\t\t\tChoose your desired option: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            view_monetary();
            break;
        case 2:
            paysalary();
            break;
        case 3:
            transaction_history();
            break;
        case 4:
            // pending_registration();
            break;
        case 5:
            menu();
            break;
        default:
            cout << "Wrong Choice!\n";
        }
    } while (choice < 1 || choice > 5);
}

void admin::paysalary()
{
    system("cls");
    char id[20];
    int i = 0;
    ifstream fin;
    ofstream fout;
    fin.open("Admin.dat", ios::binary | ios::in);
    fin.read(reinterpret_cast<char *>(&details), sizeof(details));
    fin.close();

    fin.open("trainers.dat", ios::binary | ios::in);
    while (fin.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
    {
        cout << "\n\t\t\t\t\t\t\t\t" << i + 1 << " ID: " << Trainer.id << endl;
        cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
        i++;
    }
    fin.close();

    cout << "\n\n\t\t\t\t\t\t\t\tEnter the ID you would like to pay salary to: ";
    cin >> ws;
    cin.get(id, 20);

    fin.open("trainers.dat", ios::binary | ios::in);
    while (fin.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
    {
        if (details.balance > Trainer.salary)
        {
            if (strcmp(Trainer.id, id) == 0)
            {
                details.balance -= Trainer.salary;
                wallet.amount = Trainer.salary;
                wallet.send = true;
                wallet.recieve = false;
                strcpy(wallet.reciever_id, Trainer.id);
                char buffer[30];
                strcpy(buffer, strcat(Trainer.id, "9911"));
                wallet.setid(buffer);
                wallet.setdate(getdate());
                wallet.setime(gettime());
                ofstream fout;
                fout.open("transaction_history.dat", ios::app);
                fout.write(reinterpret_cast<char *>(&wallet), sizeof(wallet));
                fout.close();
                cout << "\n\n\t\t\t\t\t\t\t\tSalary Paid Successfully!\n";
            }
        }
        else
        {
            cout << "\n\n\t\t\t\t\t\t\t\tSalary cannot be paid\n";
        }
    }
    fin.close();

    fout.open("Admin.dat", ios::binary | ios::out);
    fout.write(reinterpret_cast<char *>(&details), sizeof(details));
    fout.close();

    getch();
    Monetary_database();
}
void admin::transaction_history()
{
    ifstream fin;
    fin.open("transaction_history.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in opening transaction history!";
    }
    else
    {
        while (fin.read(reinterpret_cast<char *>(&wallet), sizeof(wallet)))
        {
            cout << "\n\n\t\t\t\t\t\t\t\tTransaction ID: " << wallet.transaction_id;
            cout << "\n\t\t\t\t\t\t\t\tTransaction Ammount: " << wallet.amount;
            cout << "\n\t\t\t\t\t\t\t\tTransaction Date: " << wallet.transaction_date;
            cout << "\n\t\t\t\t\t\t\t\tTransaction Time: " << wallet.transaction_time;
            if (wallet.recieve == false && wallet.send == false)
            {
                cout << "\n\t\t\t\t\t\t\t\tInventory Item: " << wallet.inventory_item_name << endl;
            }
            else if (wallet.send == true)
            {

                cout << "\n\t\t\t\t\t\t\t\tReciver(Trainer) ID: " << wallet.reciever_id << endl;
            }
            else
            {
                cout << "\n\t\t\t\t\t\t\t\tSender(Client) ID: " << wallet.sender_id << endl;
            }

            cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
        }
    }
    getch();
    fin.close();
    Monetary_database();
}
void admin::view_monetary()
{

    ifstream fin;
    ifstream fin1;
    ifstream fin2;
    ifstream fin3;
    fin2.open("Admin.dat", ios::in | ios::binary);
    fin2.read(reinterpret_cast<char *>(&details), sizeof(details));
    cout << "\n\n\t\t\t\t\t\t\t\tAvailable Balance is " << details.balance << endl;
    fin1.open("trainers.dat", ios::in | ios::binary);
    fin.open("transaction_history.dat", ios::in | ios::binary);
    int paid = 0;
    int not_paid = 0;
    if (!fin)
    {
        cout << "\n\n\t\t\t\t\t\t\t\tError in opening transaction history!";
    }
    else
    {
        cout << "\n\n\t\t\t\t\t\t\t\tList of Trainers ID Who Recieved Salary!";
        while (fin1.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
        {
            while (fin.read(reinterpret_cast<char *>(&wallet), sizeof(wallet)))
            {
                // char buffer[20];
                // strcpy(buffer, strcat(Trainer.id, "911"));
                if (strcmp(Trainer.id, wallet.reciever_id) == 0)
                {
                    cout << "\n\n\t\t\t\t\t\t\t\tTrainer ID: " << Trainer.id;
                    paid++;
                }
            }
        }
        cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
        fin1.close();
        fin.close();

        fin1.open("trainers.dat", ios::in | ios::binary);
        fin.open("transaction_history.dat", ios::in | ios::binary);

        cout << "\n\n\t\t\t\t\t\t\t\tList of Trainers ID Who Not Recieved Salary!";

        while (fin1.read(reinterpret_cast<char *>(&Trainer), sizeof(Trainer)))
        {
            while (fin.read(reinterpret_cast<char *>(&wallet), sizeof(wallet)))
            {
                // char buffer[20];
                // strcpy(buffer, strcat(Trainer.id, "911"));
                if (strcmp(Trainer.id, wallet.reciever_id) != 0)
                {
                    cout << "\n\n\t\t\t\t\t\t\t\tTrainer ID: " << Trainer.id;
                    not_paid++;
                }
            }
        }
        cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
        cout << "\n\t\t\t\t\t\t\t\tNumber of Trainers Paid: " << paid << "\n\n";
        cout << "\n\t\t\t\t\t\t\t\tNumber of Trainers Not Paid: " << not_paid << "\n\n";

        fin.close();
        fin1.close();

        fin3.open("client.dat", ios::in | ios::binary);
        fin.open("transaction_history.dat", ios::in | ios::binary);

        cout << "\n\n\t\t\t\t\t\t\t\tList of Pending Clients ID with their Balance left!";
        int x = 0;

        while (fin3.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
        {
            while (fin.read(reinterpret_cast<char *>(&wallet), sizeof(wallet)))
            {
                // char buffer[20];
                // strcpy(buffer, strcat(Client.id, "2233"));
                if (strcmp(Client.id, wallet.sender_id) == 0)
                {
                    cout << "\n\n\t\t\t\t\t\t\t\tClient ID: " << Client.id;
                    cout << "\n\n\t\t\t\t\t\t\t\tBalance Left: " << Client.due_ammount << endl;
                    x++;
                    break;
                }
            }
        }
        cout << "\n\t\t\t\t\t\t\t\t_______________________\n\n";
        cout << "\n\t\t\t\t\t\t\t\tNumber of Clients with Balance Left: " << x << "\n\n";
    }

    getch();
    fin3.close();
    fin.close();
    Monetary_database();
}

// void admin::view_monetary()
// {

//     ifstream afin, cfin;
//     afin.open("Admin.dat", ios::in | ios::binary);
//     afin.read(reinterpret_cast<char *>(&details), sizeof(details));
//     cout << "Total Balance in account: " << details.balance;
//     cout << "Clients with pending Payements";
//     cfin.open("client.dat", ios::in | ios::binary);
//     while (cfin.read(reinterpret_cast<char *>(&Client), sizeof(Client)))
//     {
//         if ((Client.balance - Client.paid )>0){

//         }
//     }
// }