#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <fstream>
using namespace std;

class Ewallet
{
private:
    char transaction_id[20], *transaction_date, *transaction_time;
    bool recieve, send;
    char reciever_id[30];
    char sender_id[20];
    char inventory_item_name[30];
    float amount;
    friend class admin;

public:
    void setid(char id[20])
    {
        strcpy(this->transaction_id, id);
    }
    void setdate(char *date)
    {
        this->transaction_date = date;
    }
    void setime(char *time)
    {
        this->transaction_time = time;
    }
};

class person // for shared features
{
protected:
    char name[50], gender[20], phone_number[20], id[20], password[20];

    char *pass_validation();
    char *id_validation();
    int getchoice();
    bool checkid(char id2[], string filename);

public:
    char *getName()
    {
        return this->name;
    }

    void setName(char name[50])
    {
        strcpy(this->name, name);
    }

    char *getGender()
    {
        return this->gender;
    }

    void setGender(char gender[20])
    {
        strcpy(this->gender, gender);
    }

    char *getPhone_number()
    {
        return this->phone_number;
    }

    void setPhone_number(char phone_number[20])
    {
        strcpy(this->phone_number, phone_number);
    }

    char *getid()
    {
        return this->id;
    }

    void setid(char id[20])
    {
        strcpy(this->id, id);
    }

    char *getPassword()
    {
        return this->password;
    }

    void setPassword(char password[20])
    {
        strcpy(this->password, password);
    }
    void logout()
    {
        cout << "\n\n\t\t\t\t\t\t\t\tLogging out";
        cout << " \n\n\t\t\t\t\t";
        for (int i = 0; i < 65; i++)
        {
            Sleep(20);
            cout << "|";
        }
    };
    void checkbalance();

    void main_page();
    virtual void login_Register() = 0;
};
class Inventory
{
    char item_name[20], item_id[20];
    int quantity;
    float price;
    friend class admin;
    bool checkid(char id2[20], string filename)
    {
        ifstream fin;
        fin.open(filename, ios::binary | ios::in);
        if (!fin)
        {
            cout << "\n\t\t\t\t\t\t\t\tFile not created yet!\n";
        }
        else
        {
            while (fin.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                if (strcmp(id2, item_id) == 0)
                {
                    fin.close();
                    return true;
                }
            }
        }
        fin.close();
        return false;
    }

public:
    Inventory()
    {
        strcpy(this->item_name, "\0");
        strcpy(this->item_id, "\0");
        this->quantity = 0;
        this->price = 0.00;
    };
    void deduct(){};
};

class membership
{
private:
    char membership_id[20], type[20];
    int duration;
    float fees;
    friend class admin;

public:
    membership()
    {
        strcpy(membership_id, "\0");
        strcpy(type, "\0");
        duration = 0;
        fees = 0;
    };
    membership(char type[20], int duration, float fees, char id[20])
    {
        strcpy(this->type, type);
        strcpy(membership_id, id);
        this->fees = fees;
        this->duration = duration;
    };
    void create_membership(char type[], int duration, float fees, char id[])
    {
        strcpy(this->type, type);
        this->fees = fees;
        this->duration = duration;
        strcpy(this->membership_id, id);
        ofstream fout2;
        fout2.open("membership.dat", ios::binary | ios::app);
        fout2.write(reinterpret_cast<char *>(this), sizeof(*this));
        fout2.close();
        strcpy(this->type, "\0");
        this->fees = 0;
        this->duration = 0;
        strcpy(this->membership_id, "\0");
    }
    void cancel_membership(char delete_id[], char id[])
    {
        ifstream fin3;
        ofstream fout2;
        fout2.open("temp2.dat", ios::binary | ios::out);
        while (fin3.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (strcmp(delete_id, id) != 0)
            {
                fout2.write(reinterpret_cast<char *>(this), sizeof(*this));
            }
        }
        remove("membership.dat");
        rename("temp2.dat", "membership.dat");
    };
    void display_membership(char id[])
    {
        ifstream fin2;
        fin2.open("membership.dat", ios::binary | ios::in);

        while (fin2.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (strcmp(id, this->membership_id) == 0)
            {
                cout << (*this);
            }
        }
    };
    friend ostream &operator<<(ostream &out, const membership m1);
};
ostream &operator<<(ostream &out, const membership m1)
{
    out << "\n\t\t\t\t\t\t\t\tMembership ID: " << m1.membership_id << endl
        << "\n\t\t\t\t\t\t\t\tType: " << m1.type << endl
        << "\n\t\t\t\t\t\t\t\tDuration: " << m1.duration << " months" << endl
        << "\n\t\t\t\t\t\t\t\tFees: " << m1.fees << "RS/-" << endl;
    return out;
}
class trainer;

class client : public person
{
private:
    friend class admin;
    float paid, due_ammount;
    bool is_member, feespaid;
    membership Membership;
    trainer *Train;
    char trainer_id[20];
    struct BodyStats
    {
        double height;
        double weight;
        double bodyFatPercentage;
        double waist;
        double neck;
        double hips;
        double BMI;
    } stats;

    double calculateBodyFatPercentage()
    {
        double log10waist, log10neck, log10hip;
        char isMale = toupper(gender[0]);
        if (isMale == 'M')
        {
            log10waist = log10(stats.waist - stats.neck);
            log10neck = log10(stats.neck);
            log10hip = 0.0;
        }
        else
        {
            log10waist = log10(stats.waist + stats.hips - stats.neck);
            log10neck = log10(stats.neck);
            log10hip = log10(stats.hips);
        }
        double log10height = log10(stats.height);
        double bf = 495.0 / 20 * (1.0 - 0.00257 * (log10waist + log10neck - log10hip) - 0.1336 * log10height);
        return bf;
    }
    double calculateBMI()
    {
        return stats.weight / (stats.height * stats.height);
    }

public:
    client()
    {
        strcpy(name, "\0");
        strcpy(gender, "\0");
        strcpy(phone_number, "\0");
        strcpy(id, "\0");
        due_ammount = 0; // gym charges
        is_member = false;
        feespaid = false;
    };
    void enter_body_stats(char id2[])
    {
        system("cls");
        cout << "\n\n\n\n\t\t\t\t\t\t\t\t<-------------- Client's Body Statistics---------------->";
        cout << "\n\t\t\t\t\t\t\t\tEnter Client's weight in kilograms: ";
        cin >> stats.weight;
        cout << "\n\t\t\t\t\t\t\t\tEnter Client's height in meters: ";
        cin >> stats.height;
        cout << "\n\t\t\t\t\t\t\t\tEnter Client's waist measurements in inches: ";
        cin >> stats.waist;
        cout << "\n\t\t\t\t\t\t\t\tEnter Client's neck measurements in inches: ";
        cin >> stats.neck;
        cout << "\n\t\t\t\t\t\t\t\tEnter Client's hip measurements in inches: ";
        cin >> stats.hips;
        stats.BMI = calculateBMI();
        stats.bodyFatPercentage = calculateBodyFatPercentage();
        cout << "\n\t\t\t\t\t\t\t\tClient's details have been saved succesfully\n";
        cout << "\n\t\t\t\t\t\t\t\tPress enter to continue\n";
        getch();
    }
    void view_body_stats(char[]);
    void payfees(){};
    void view_workout_schedule(){};
    void view_profile(char[]);
    void login_Register();
    void clientregister();
    void customer_menu(char[]);
    friend ostream &operator<<(ostream &out, const client *m1);
};
ostream &operator<<(ostream &out, const client *m1)
{
    out << "\n\t\t\t\t\t\t\t\tID: " << m1->id << endl
        << "\n\t\t\t\t\t\t\t\tName: " << m1->name << endl;
    return out;
}

class trainer : public person
{
private:
    friend class admin;
    float salary;
    int numberofClients;
    client array_of_clients[10];
    char expertise[20], time[20];

public:
    trainer()
    {
        strcpy(name, "\0");
        strcpy(gender, "\0");
        strcpy(time, "\0");
        strcpy(expertise, "\0");
        strcpy(phone_number, "\0");
        strcpy(id, "\0");
    }
    void request_inventory(){};
    void request_updatedetails(){};
    void view_schedule(){};
    void show_clients();

    void login_Register();
    void view_profile(char[]);
    void deleteclients(char id[])
    {
        char *id2;
        for (int i = 0; i < numberofClients; i++)
        {
            id2 = array_of_clients[i].getid();
            if (strcmp(id, id2) == 0)
            {
                array_of_clients[i] = array_of_clients[i + 1];
                --numberofClients;
            }
        }
    }
    void trainer_menu(char[]);
};

class admin : public person
{
private:
    Ewallet wallet;
    client Client;
    trainer Trainer;
    Inventory inventory;
    struct info
    {
        int number_of_client;
        int number_of_trainers;
        float balance;
    };
    info details;
    struct attendance_info
    {
        char marked;
        char id[20];
        char date[20];
    };
    attendance_info Client_attendance;
    attendance_info Trainer_attendance;
    const int maximum_client_number;
    char *gettime()
    {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        static char buffer[20];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", ltm);
        // cout << "\n\n\t\t\t\t\t\t\t\tThe current time is " << buffer << endl;
        return buffer;
    }
    char *getdate()
    {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        static char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
        // cout << "\n\n\t\t\t\t\t\t\t\tThe current date is " << buffer << endl;
        return buffer;
    }

public:
    admin(char name[50], char gender[50], char phone_number[50], char id[50]) : maximum_client_number(100)
    {
        strcpy(this->name, name);
        strcpy(this->gender, gender);
        strcpy(this->phone_number, phone_number);
        strcpy(this->id, id);
        details.number_of_client = 0;
        details.number_of_trainers = 0;
        ifstream fin;
        fin.open("Admin.dat", ios::in);
        fin.read(reinterpret_cast<char *>(&details), sizeof(details));
        if (!fin)
        {
            ofstream fout;
            fout.open("Admin.dat", ios::binary | ios::out);
            this->details.balance = 1000000;
            fout.write(reinterpret_cast<char *>(&details), sizeof(details));
            fout.close();
        }
        else
        {
            fin.open("Admin.dat", ios::binary | ios::out);
            fin.read(reinterpret_cast<char *>(&details), sizeof(details));
            fin.close();
        }
    }
    admin() : maximum_client_number(100)
    {
        strcpy(name, "\0");
        strcpy(gender, "\0");
        strcpy(phone_number, "\0");
        strcpy(id, "\0");
    }
    ~admin() {}
    void add_client();
    void allot_trainer();
    void update_client();
    void remove_client();
    void search_client();
    void display_all_clients();
    void gettotalclient();
    void Client_attendance_menu();
    void input_Client_attendance();
    void view_Client_attendance();
    void search_Client_attendance();
    void edit_Client_attendance();

    void add_trainer();
    void remove_trainer();
    void update_trainer();
    void search_trainer();
    void gettotaltrainers();

    void Trainer_attendance_menu();
    void search_Trainer_attendance();
    void input_Trainer_attendance();
    void view_Trainer_attendance();
    void edit_Trainer_attendance();
    trainer *client_alloted(client *, char[]);
    void display_all_trainers();

    void add_inventory();
    void remove_inventory();
    void update_inventory();
    void search_inventory();
    void display_all_inventory();
    void display_specific();

    void paysalary();
    void transaction_history();
    void view_monetary();

    void login_Register();
    void menu();
    void client_database();
    void trainer_database();
    void Inventory_database();
    void Monetary_database(); // yet to be added
};
