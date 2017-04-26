#include<iostream>
#include<iomanip>

#include<functional> // std::function

using std::cout; // �����, ��� using namespace std, �.�. � std ����� ���� ���
using std::endl; //

class Polynom4 {
private:
	// ��������� ax^3+bx^2+cx+d
	double a, b, c, d;
public:		
	Polynom4(double a1, double b1, double c1, double d1):
		a(a1),b(b1),c(c1),d(d1)
	{
       // �� �� �����, ��� a=a1,b=b1,c=c1,d=d1
	}

	double value(double x) {
		return d + x*(c + x*(b + x*a)); // ����� 3 ���������
		// a*x*x*x + b*x*x+c*x+d - 6 ���������, x*x*x �� ���������� x*x
		// ���� ���������� ������ ������������ ����� ���������� ���
	}

	double operator() (double x) {
		return value(x);
	}

	double diff(double x) {
		return c + x*(b + 2*x*a); // �����������
	}
};

double globalFun(double x) {
	return x*x;
}

int main() {
	setlocale(LC_ALL, "Russian");
	cout << std::setprecision(5)<<std::fixed; //  ������ 5 ������ ����� �������
	
											  
    // ����� ������� ������ ������ � ������� �����
	Polynom4 p(1, 0, 0, -1); // x^4-1
	cout << "p.value(0)=" << p.value(0) << endl;
	cout << "p.value(1)=" << p.value(1) << endl;

	// ���� ����� � ����������� - �������� "������" ������, 
	// ����� ��������� ��������� � ������ p(0)
	// ��� ������ ���������� ��� p.operator()(0) - ��������������� ������� ������
	
	cout << "p(0)=" << p(0) << endl;
	cout << "p(1)=" << p(1) << endl;
	cout << "p(2)=" << p.operator()(2) << endl;

	// ��� �������� ��������, ������� ����� ��������, ����� ������������
	// ����������� ��� std::funciton

	std::function<double(double)> f; 
	//cout << f(-1) << endl; // �� ������������������ ����������, ������!
	
	f = globalFun;
	cout << f(-5) << endl; 

	f = p; // ����� ��������� �������
	cout << f(-2) << endl;

    // � ���� ����� ������ �� ����� 
	// (��� ������, ������� ���� �������, ��� �������, ������� ������ �������������)
	// �� � �++ 11 ����� ������������ ������-��������� ��� ��������� ������� (��� �����)
	f = [](double x) {return x*x*x; };
	cout << f(-2) << endl;

	// ����� ���� �������� ������ � ����������,
	int v = 2;
	//    "������" ���������� v
	f = [&v](double x) { return (x + v)*v; }; //  ���� [&], �� �� ���� �����
	cout << f(1) <<",v="<<v<< endl;
	
	// auto - ���������� ��� ����������, ��� ��� ���-�� ���� std::function(void())
	auto q = []() { cout << "��� ����� � ������!"<<endl;  };
	q();
	q();
	q();

	return 0;
}
