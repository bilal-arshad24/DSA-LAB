//#include<iostream>
//using namespace std;
//template<typename T>
//class course {
//public:
//	virtual T duration() = 0;
//};
//template<typename T>
//class onlinecourse :public course<T> {
//private:
//	T weeks;
//	T hoursperweek;
//public:
//	onlinecourse(T w, T hw) {
//		weeks = w;
//		hoursperweek = hw;
//	}
//	T duraion() {
//		return weeks * hoursperweek;
//	}
//};
//template<typename T>
//class offlinecourse :public course<T> {
//private:
//	T months;
//	T hoursperday;
//public:
//	offlinecourse(T m, T hd) {
//		months = m;
//		hoursperday = hd;
//	}
//	T duraion() {
//		return months*30* hoursperday;
//	}
//};
//int main()
//{
//    int weeks;
//    int hoursperweek;
//    int months;
//	int hoursperday;
//
//    cout << "Enter number of weeks for online course: ";
//    cin >> weeks;
//
//    cout << "Enter hours per week for online course: ";
//    cin >> hoursperweek;
//
//    cout << "Enter number of months for offline course: ";
//    cin >> months;
//
//	cout << "Enter hours per day for online course: ";
//	cin >> hoursperday;
//
//    onlinecourse<int> n(weeks,hoursperweek);
//    offlinecourse<int> f(months, hoursperday);
//
//    cout << "\nduration of online course: "
//        << n.duration() << endl;
//
//    cout << "duration of offline course: "
//        << f.duration() << endl;
//
//    return 0;
//}