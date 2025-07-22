#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib> // for system("cls")
using namespace std;

class TourBus {
    int bid;
    char destination[200];
    char time[50];
    int max_seats;
    int booked;
    int fare;

public:
    TourBus() {
        bid = 0;
        max_seats = 50;
        booked = 0;
        fare = 0;
        strcpy(time, "9:10am");
        strcpy(destination, "");
    }

    void input();
    void show();
    void display();
    int getid() { return bid; }
    void book() { booked++; }
    char* getDestination() { return destination; }
    char* getTime() { return time; }
    int getBooked() { return booked; }
    int getMax() { return max_seats; }
    int getFare() { return fare; }
};

class Ticket {
    char name[50];
    TourBus bus;

public:
    void generate(char cname[], TourBus tb) {
        strcpy(name, cname);
        bus = tb;
    }

    void display() {
        cout << "Customer Name: " << name << endl;
        cout << "Details of Bus:" << endl;
        bus.show();
    }
};

void TourBus::input() {
    cout << "Enter bus id: ";
    cin >> bid;
    cin.ignore(); // clear newline before getline
    cout << "Enter bus destination: ";
    cin.getline(destination, 200);
    cout << "Enter time of bus: ";
    cin.getline(time, 50);
    cout << "Enter fare of the bus: ";
    cin >> fare;
}

void TourBus::display() {
    cout << bid << "\t" << destination << "\t" << time << "\t" << max_seats << "\t" << booked << "\t" << fare << "\n";
}

void TourBus::show() {
    cout << "Bus Id: " << bid << endl;
    cout << "Destination: " << destination << endl;
    cout << "Time: " << time << endl;
    cout << "No. of seats remaining: " << max_seats - booked << endl;
}

int main() {
    int ch;
    fstream F, G;
    TourBus b;
    Ticket t;

    do {
        system("cls");
        cout << "Press 1 - Add a New Tour Bus\n";
        cout << "Press 2 - Show Selected Bus\n";
        cout << "Press 3 - Display All Buses\n";
        cout << "Press 4 - Delete a Bus\n";
        cout << "Press 5 - Book a ticket\n";
        cout << "Press 6 - Display Booked Tickets\n";
        cout << "Press 7 - Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        cin.ignore();

        switch (ch) {
        case 1:
            F.open("tour.dat", ios::app | ios::binary);
            b.input();
            F.write(reinterpret_cast<char*>(&b), sizeof(b));
            F.close();
            cout << "Bus added Successfully\n";
            system("pause");
            break;

        case 2: {
            int id, chk = 0;
            cout << "Enter the bus id to be displayed: ";
            cin >> id;
            F.open("tour.dat", ios::in | ios::binary);
            if (F.fail()) {
                cout << "Can't open file\n";
            } else {
                while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                    if (b.getid() == id) {
                        b.show();
                        chk = 1;
                        break;
                    }
                }
                if (chk == 0)
                    cout << "Bus not Found\n";
            }
            F.close();
            system("pause");
            break;
        }

        case 3:
            F.open("tour.dat", ios::in | ios::binary);
            if (F.fail()) {
                cout << "Can't open file\n";
            } else {
                while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                    b.display();
                }
            }
            F.close();
            system("pause");
            break;

        case 4: {
            int id, chk = 0;
            cout << "Enter the bus id to be deleted: ";
            cin >> id;
            F.open("tour.dat", ios::in | ios::binary);
            G.open("temp.dat", ios::out | ios::binary);
            if (F.fail()) {
                cout << "Can't open file\n";
            } else {
                while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                    if (b.getid() != id) {
                        G.write(reinterpret_cast<char*>(&b), sizeof(b));
                    } else {
                        b.show();
                        chk = 1;
                    }
                }
                if (chk == 0)
                    cout << "Bus not Found\n";
                else
                    cout << "Bus Deleted\n";
            }
            F.close();
            G.close();
            remove("tour.dat");
            rename("temp.dat", "tour.dat");
            system("pause");
            break;
        }

        case 5: {
            char dest[70], cname[50];
            int chk = 0;
            cout << "Enter the destination: ";
            cin.getline(dest, 70);
            F.open("tour.dat", ios::in | ios::out | ios::binary);
            if (F.fail()) {
                cout << "Can't open file\n";
            } else {
                while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                    if (strcmp(b.getDestination(), dest) == 0) {
                        b.show();
                        chk = 1;
                        cout << "Enter the customer name: ";
                        cin.getline(cname, 50);
                        b.book();
                        t.generate(cname, b);
                        G.open("tickets.dat", ios::app | ios::binary);
                        G.write(reinterpret_cast<char*>(&t), sizeof(t));
                        G.close();

                        F.seekp(F.tellg() - static_cast<streampos>(sizeof(b)));
                        F.write(reinterpret_cast<char*>(&b), sizeof(b));
                        cout << "Ticket booked\n";
                        break;
                    }
                }
                if (chk == 0)
                    cout << "No Bus Found\n";
            }
            F.close();
            system("pause");
            break;
        }

        case 6:
            cout << "Booked Tickets\n";
            G.open("tickets.dat", ios::in | ios::binary);
            if (G.fail()) {
                cout << "Can't open file\n";
            } else {
                while (G.read(reinterpret_cast<char*>(&t), sizeof(t))) {
                    t.display();
                }
            }
            G.close();
            system("pause");
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice\n";
            system("pause");
        }

    } while (ch != 7);

    return 0;
}
