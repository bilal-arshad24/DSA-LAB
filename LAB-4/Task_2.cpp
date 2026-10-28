//
//#include <iostream>
//using namespace std;
//
//template <typename T>
//class employee
//{
//public:
//    virtual T calculateSalary() = 0;
//};
//
//template <typename T>
//class FullTimeEmployee : public employee<T>
//{
//private:
//    T fixedSalary;
//
//public:
//    FullTimeEmployee(T salary)
//    {
//        fixedSalary = salary;
//    }
//
//    T calculateSalary()
//    {
//        return fixedSalary;
//    }
//};
//
//template <typename T>
//class PartTimeEmployee : public employee<T>
//{
//private:
//    T hoursworked;
//    T hourlyrate;
//
//public:
//    PartTimeEmployee(T hours, T rate)
//    {
//        hoursworked = hours;
//        hourlyrate = rate;
//    }
//
//    T calculateSalary()
//    {
//        return hoursworked * hourlyrate;
//    }
//};
//
//int main()
//{
//    float salary;
//    float hours;
//    float rate;
//
//    cout << "Enter Full-Time Employee Salary: ";
//    cin >> salary;
//
//    cout << "Enter Part-Time Employee Hours Worked: ";
//    cin >> hours;
//
//    cout << "Enter Part-Time Employee Hourly Rate: ";
//    cin >> rate;
//
//    FullTimeEmployee<float> f(salary);
//    PartTimeEmployee<float> p(hours, rate);
//
//    cout << "\nFull-Time Employee Salary: "
//        << f.calculateSalary() << endl;
//
//    cout << "Part-Time Employee Salary: "
//        << p.calculateSalary() << endl;
//
//    return 0;
//}