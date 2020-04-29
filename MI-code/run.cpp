#include<iostream>
#include<cmath>
#include<iostream>
#include<fstream>
#include "heatingFunctions.h"

using namespace std;

//Temp inner pipe
double T0 = 1023.15;
//Temp outer pipe
double T1 = 293.15;
//Temp air
double T2 = 293.15;
//Temp component block
double T3 = 293.15;

//mass of exhaust system
double m0 = 31.4;
//mass of air
double m1 = .049;
//mass of component
double m2 = 7.84;

//specific heat capacity of exhaust
double c0 = 460;
//specific heat capacity of air
double c1 = 750;
//specific heat capacity of component
double c2 = 460;

//thermal conductivity of exhaust
double k0 = 44;
//thermal conductivity of air
double k1 = 0.00059*T1 + 0.008297;
//thermal conductivity of component
double k2 = 44;

//surface area of exhaust
double A0 = .8;
//surface area of air
double A1 = .314;
//surface area of component
double A2 = .06;

//distance from T_0 to T_1
double x0 = .005;
//distance from T_1 to T_2
double x1 = .05;
//distance from T_2 to T_3
double x2 = .05;

//thermal conductivity of insulation
double k_ins = 0.08;
//specific heat capacity of insulation
double c_ins = 8400;
//mass of insulation
double m_ins = 5;
//surface area of insulation
double A_ins = .8;
//thickness of insulation
double x_ins = 0.005;

//external radius of exhaust
double r_1 = .045;
//internal radius of exhaust
double r_0 = .04;
//length of exhaust
double l = 3;



int main() {

	double q_pipe = Q(m0,c0,T0,T1);
	double q_dot_pipe = 0;
	//double q_dot_pipe = Q_dot_cylinder(k0,l,T_0,T_1,r_0,r_1);
	double q_air = Q(m1,c1,T0,T2);
	double q_dot_air = 0;
	double q_component = Q(m2,c2,T0,T3);
	double q_dot_component = 0;
	
	//we open file streams to text files
	ofstream pipe;
	ofstream air;
	ofstream air_insul;
	ofstream component;
	ofstream component_insul;
	ofstream cooling;
    ofstream ins;
    ofstream ins_cool;
	pipe.open("pipe.txt");
	air.open("air.txt");
	component.open("component.txt");
	cooling.open("cooling.txt");
	air_insul.open("air_insul.txt");
	component_insul.open("component_insul.txt");
    ins.open("ins_heating.txt");
    ins_cool.open("ins_cooling.txt");
	
	//our respective times for each part to heat up
	int n0 = 0;
	int n1 = 0;
	int n2 = 0;
	
	//times with insulation
	int n1ins = 0;
	int n2ins = 0;
	
	while (0.99*T0 > T1){
		n0++;
		/*if (0.95*T0 > T2){
			n1++;
		}
		if (0.95*T0 > T1){
			n0++;
		}*/
		T1 = newT(q_pipe,m0,c0,T0);
		//q_dot_pipe = Q_dot_cylinder(k0,l,T0,T1,r_0,r_1);
		q_dot_pipe = Q_dot(k0,A0,T0,T1,x0);
		q_pipe -= q_dot_pipe;
		pipe << T1 << endl;

		/*T2 = newT(q_air,m1,c1,T1);
		q_dot_air = Q_dot(k1,A1,T1,T2,x1);
		q_air -= q_dot_air;
		air << T2 << endl;

		T3 = newT(q_component,m2,c2,T2);
		q_dot_component = Q_dot(k2,A2,T2,T3,x2);
		q_component -= q_dot_component;
		component << T3 << endl;*/
	}
	pipe << "time take is " << n0 << endl;
	//air << "time take is " << n1 << endl;
	//component << "time take is " << n2 << endl;

	//q_air = Q(m1,c1,T1,T2);
	//int n1 = 0;
	
	while (.99*T0 > T2){
		n1++;
		T2 = newT(q_air,m1,c1,T1);
		q_dot_air = Q_dot(k1,A1,T1,T2,x1);
		q_air -= q_dot_air;
		air << T2 << endl;
	}
	air << "time take is " << n1 << endl;
	//q_component = Q(m2,c2,T0,T3);
	//int n2=0;
	while (.99*T0 > T3){
		n2++;
		T3 = newT(q_component,m2,c2,T0);
		q_dot_component = Q_dot(k2,A2,T0,T3,x2);
		q_component -= q_dot_component;
		component << T3 << endl;
	}
	component << "time take is " << n2 << endl;
	T0 = 693.15;
	T2 = 293.15;
	T3 = 293.15;
	q_air = Q(m1,c1,T0,T2);
	q_component = Q(m2,c2,T0,T3);
	
	while (.99*T0 > T2){
		n1ins++;
		T2 = newT(q_air,m1,c1,T0);
		q_dot_air = Q_dot(k1,A1,T0,T2,x1);
		q_air -= q_dot_air;
		air_insul << T2 << endl;
	}
	air_insul << "time take is " << n1ins << endl;
	
	while (.99*T0 > T3){
		n2ins++;
		T3 = newT(q_component,m2,c2,T0);
		q_dot_component = Q_dot(k2,A2,T0,T3,x2);
		q_component -= q_dot_component;
		component_insul << T3 << endl;
	}
    component_insul << "time take is " << n2ins << endl;
    
	double T5 = 673.15;
    double T6 = 293.15;
    int nins = 0;
    double q_ins = Q(m_ins,c_ins,T5,T6);
    double q_dot_ins = 0 ;
    while (.95*T5 > T6){
        nins++;
		T6 = newT(q_ins,m_ins,c_ins,T5);
		q_dot_ins = Q_dot(k_ins,A_ins,T5,T6,x_ins);
		q_ins -= q_dot_ins;
        ins << T6 << endl;
    }
	ins << "time taken is " << nins << endl;
	double n3=0;
	double T4 = 393.15;
	T3 = 673.15;
	q_component = -Q(m1,c1,T3,T4);
	while (0.99*T3 > T4){
		n3++;
		T3 = newT(q_component,m1,c1,T4);
		q_dot_component = Q_dot(k1,A1,T3,T4,x1);
		q_component += q_dot_component;
		cooling << T3 << endl;
	}
    
    double n_ins_cool=0;
	double T7 = 393.15;
	double T8 = 673.15;
	q_ins = -Q(m1,c1,T8,T7);
	while (0.99*T8 > T7){
		n_ins_cool++;
		T8 = newT(q_ins,m1,c1,T7);
		q_dot_ins = Q_dot(k1,A1,T8,T7,x1);
		q_ins += q_dot_ins;
		ins_cool << T8 << endl;
	}
    ins_cool << "time taken is " << n_ins_cool << endl;
	double k = 0.1;
	/*while (0.99*T3>T4){
		cooling << Tcool(T4,T3,k,n3) << endl;
		T3 = Tcool(T4,T3,k,n3);
		n3++;
	}*/
	cooling << "time taken is = " << n3;
	pipe.close();
	air.close();
	component.close();
    ins.close();
}
//switch t1 and t2 keep all variables the same
// stop code at 100c instead of 95%
//