#include <iostream>
#include <string>
using namespace std;

class myCarStack
{
    string cars[8];
    int count;
public:
    myCarStack() 
    {
        count = 0;
    }
    void parkCar(string car)
    {
        if (count == 8) {
            cout << "Parking lot is full!\n";
            return;
        }
        cars[count++] = car;
        cout << "Car parked successfully.\n";
    }
    void removeCar(string car)
    {
        int i;
        for (i = 0; i < count; i++)
        {
            if (cars[i] == car)
                break;
        }
        if (i == count) {
            cout << "Car not found!\n";
            return;
        }
        for (int j = i; j < count - 1; j++)
            cars[j] = cars[j + 1];
        count--;
        cout << "Car removed successfully.\n";
    }
    void searchCar(string car)
    {
        for (int i = 0; i < count; i++)
        {
            if (cars[i] == car) {
                cout << "Car found!\n";
                return;
            }
        }
        cout << "Car not found!\n";
    }
    void display()
    {
        if (count == 0)
        {
            cout << "Parking lot is empty.\n";
            return;
        }
        cout << "Parked cars (top to bottom)=\n";
        for (int i = count - 1; i >= 0; i--)
            cout << cars[i] << endl;
    }
    void totalCars()
    {
        cout << "Total cars= " << count << endl;
    }
};
int main()
{
    myCarStack parking;
    int choice;
    string car;
    do {
        cout << "\n1. Park a car\n";
        cout << "2. Remove a car\n";
        cout << "3. View parked cars\n";
        cout << "4. Total cars\n";
        cout << "5. Search a car\n";
        cout << "6. Exit\n";
        cout << "Enter choice = ";
        cin >> choice;
        switch (choice) 
        {
        case 1:
            cout << "Enter car number =";
            cin >> car;
            parking.parkCar(car);
            break;

        case 2:
            cout << "Enter car number to remove= ";
            cin >> car;
            parking.removeCar(car);
            break;

        case 3:
            parking.display();
            break;

        case 4:
            parking.totalCars();
            break;

        case 5:
            cout << "Enter car number to search= ";
            cin >> car;
            parking.searchCar(car);
            break;

        case 6:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
