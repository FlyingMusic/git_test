#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
class Date {
    public:
        int year;
        int mon;
        int day;
};
class ployee {
    public:
        string P_name;
        int P_id;
        Date P_birthdate;
        double P_salary;
    public:
        ployee() {};
        ~ployee() {};
        ployee(string p, int a) {
            this->P_name = p;
            this->P_id = a;
        }
    public:
        virtual void salarysum(double a, double b, double c, double d, double e) = 0;//a为周薪水或小时薪水，b为工作时长，c为销售量，d为销售佣金，e为底薪
    public:
        virtual void print() = 0;
};
class SalariedEmployee :public ployee {
    public:
        SalariedEmployee(string p, int c, int a = 2021, int b = 01, int e = 01) {
            P_name = p;
            P_id = c;
            this->P_birthdate.year = a;
            this->P_birthdate.mon = b;
            this->P_birthdate.day = e;
        }
        SalariedEmployee() {};
        ~SalariedEmployee() {};
        void salarysum(double a=0, double b = 0, double c = 0, double d = 0, double e = 0) {
            P_salary = P_salary+a;
        }
    public:
        void print() {
            cout << "雇员类别：周薪雇员" << endl;
            cout << "雇员姓名：" << P_name << endl;
            cout << "雇员编号：" << P_id << endl;
            cout << "雇员工资：" << P_salary << endl;
        }
};
int jud(ployee&p,int n) {
    if (p.P_birthdate.mon == n) {
        p.P_salary +=100;
    }
    return p.P_salary;
}
int main() {
    string s;
    int id = 0, mon = 0, day = 0, year = 0,t=0;
    cout << "请输入雇员姓名" << endl;
    cin >> s;
    cout << "请输入雇员编号" <<  endl;
    cin >> id;
    cout << "请输入雇员生日" << endl;
    cin >> year >> mon >> day;
    SalariedEmployee p = SalariedEmployee(s, id); 
    cout << "请输入雇员周薪" << endl; 
    double a;
    cin >> a; 
    p.salarysum(a);
    cout << "请输入当前月份" << endl; 
    cin >> t;
    p.print();
    return 0;
}
