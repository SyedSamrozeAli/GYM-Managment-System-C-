#include "Client_trainer.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <fstream>

using namespace std;

int main()
{
    char name[] = "Admin ";
    char gender[] = "male";
    char number[] = "03567892212";
    char ID[] = "A-12";
    try
    {
        person *p = new admin(name, gender, number, ID);
        system("color f0");
        p->main_page();
        delete p;
    }
    catch (const bad_alloc &e)
    {
        cout << "Error: Failed to allocate memory\n";
    }
    return 0;
}
