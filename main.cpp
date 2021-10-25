#include "menu.h"
using namespace std;

int main() {
     cout << "Input the type of data:" << endl << "1. Int" << endl << "2. Person" << endl << "3. Float" << endl << "0. Exit" << endl;
     int choice0;
     cin >> choice0;
     if (choice0 < 0 || choice0 > 3) {
         return -1;
     } else if (choice0 == 0) {
         return 0;
     } else {
         switch (choice0) {
             case 1:
                 menuInt();
                 break;
             case 2:
                 menuStud();
                 break;
             case 3:
                 menuFloat();
                 break;
         }
     }
    return 0;
}
