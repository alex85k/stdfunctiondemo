#include<iostream>
#include<iomanip>

#include<functional> // std::function

using std::cout; // лучше, чем using namespace std, т.к. в std много чего ещё
using std::endl; //

class Polynom4 {
private:
	// многочлен ax^3+bx^2+cx+d
	double a, b, c, d;
public:		
	Polynom4(double a1, double b1, double c1, double d1):
		a(a1),b(b1),c(c1),d(d1)
	{
       // то же самое, что a=a1,b=b1,c=c1,d=d1
	}

	double value(double x) {
		return d + x*(c + x*(b + x*a)); // всего 3 умножения
		// a*x*x*x + b*x*x+c*x+d - 6 умножений, x*x*x не использует x*x
		// хотя компилятор иногда оптимизирует такие вычисления сам
	}

	double operator() (double x) {
		return value(x);
	}

	double diff(double x) {
		return c + x*(b + 2*x*a); // производная
	}
};

double globalFun(double x) {
	return x*x;
}

int main() {
	setlocale(LC_ALL, "Russian");
	cout << std::setprecision(5)<<std::fixed; //  всегда 5 знаков после запятой
	
											  
    // можно создать объект класса и вызвать метод
	Polynom4 p(1, 0, 0, -1); // x^4-1
	cout << "p.value(0)=" << p.value(0) << endl;
	cout << "p.value(1)=" << p.value(1) << endl;

	// Если вызов с параметрами - основная "работа" класса, 
	// можно сократить обращение и писать p(0)
	// это просто сокращение для p.operator()(0) - переопределение круглых скобок
	
	cout << "p(0)=" << p(0) << endl;
	cout << "p(1)=" << p(1) << endl;
	cout << "p(2)=" << p.operator()(2) << endl;

	// Для хранения объектов, которые можно вызывать, можно использовать
	// специальный тип std::funciton

	std::function<double(double)> f; 
	//cout << f(-1) << endl; // не инициализированная переменная, нельзя!
	
	f = globalFun;
	cout << f(-5) << endl; 

	f = p; // можно присвоить функтор
	cout << f(-2) << endl;

    // а если класс вообще не нужен 
	// (нет данных, которые надо хранить, нет методов, которые удобно сгруппировать)
	// то с С++ 11 можно использовать лямбда-выражения для анонимных функций (без имени)
	f = [](double x) {return x*x*x; };
	cout << f(-2) << endl;

	// можно даже получить доступ к переменным,
	int v = 2;
	//    "захват" переменной v
	f = [&v](double x) { return (x + v)*v; }; //  если [&], то ко всем сразу
	cout << f(1) <<",v="<<v<< endl;
	
	// auto - компилятор сам догадается, что это что-то типа std::function(void())
	auto q = []() { cout << "Все легко и просто!"<<endl;  };
	q();
	q();
	q();

	return 0;
}
