#include<cmath>

const double pi = 3.14159265358979323846;

double Q(double &m, double &c, double &T_0, double &T_1){
	return m*c*(T_0-T_1);
}
double Q_dot(double &k, double &A, double &T_0, double &T_1, double &x){
	return ((-k)*A*(T_1 - T_0))/(x);
}
double Q_dot_cylinder(double &k, double &l, double &T_0, double &T_1, double &r_0, double &r_1){
	return (2*k*pi*l*(T_1 - T_0))/log(r_1/r_0);
}
double newT(double &Q, double &m, double &c, double &T_0){
	return T_0 - (Q/(m*c));
}
double Tcool(double &T_a, double &T_0, double &k, double &t){
	return T_a + (T_0-T_a)*exp(-k*t);
}

