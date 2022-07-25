//////////////////////////////////////
//////////////////////////////////////
//									//
//		Alex May: B829343			//
//			Assumptions:			//
//		Annunal Sal increase = 4%	//
//		RPI = 3.3%(constant)		//
//		Maintenance loan = £8700	//
//			(per year)				//
//									//
//		All tasks completed			//
//									//
//////////////////////////////////////



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"
#include <math.h>

float tutitionfee;																//////////////////////////////////
int month, years, duration_year;												//								//
int Start_month, Start_year;													//		All variables used		//
char placement, maintenance;													//		defined. 				//
float interest, RPI, Month_interest, Annual_interest;							//		All globalized so  		//
float RepaymentP;																//		extern can	transfer 	//
float AnnualSalary;																//		between files.			//
int First_payment_date, Graduation_Date;										//								//
float MonthlyFee, MonthlySalary;												//////////////////////////////////
float Fee;
float TotalFeepayed, Totalinterest;
int Salary_Inc;
int Max_Salary, Min_Salary, Start_Salary;
int Finish_date;
int month2, year2;
float Salary_above_threshold;
float Monthlyinterest;

int Arrayyear[361] = { 0 };														//////////////////////////////////
int Arraymonth[361] = { 0 };													//								//
float ArraySalary[361] = { 0.0 };												//		All Arrays declared		//
float ArrayThreshold[361] = { 0.0 };											//		and initialised.		//
float Arrayinterestrate[361] = { 0.0 };											//								//
float ArrayMonthlyinterest[361] = { 0.0 };										//////////////////////////////////
float ArrayMonthlyRepay[361] = { 0.0 };
float Arraybalance[361] = { 0.0 };

FILE*txtfile;
FILE*csvfile;

main()
{
	month = 0;																	//////////////////////////////////
	RepaymentP = 9.0;															//								//
	AnnualSalary = 0.0;															//	initialises values to be	//
	Start_Salary = 20000;														//	externed.					//
	Salary_Inc = 10000;															//								//
	Max_Salary = 70000;															//////////////////////////////////
	Min_Salary = 20000;

	for (int i = 0; i <= 360; i++)
	{
		Arrayyear[i] = 0;														//////////////////////////////////
		Arraymonth[i] = 0;														//								//
		ArraySalary[i] = 0.0;													//	Resets all Array values to	//
		ArrayThreshold[i] = 0.0;												//	zero once loan has finished	//
		Arrayinterestrate[i] = 0.0;												//								//
		ArrayMonthlyinterest[i] = 0.0;											//////////////////////////////////
		ArrayMonthlyRepay[i] = 0.0;												
		Arraybalance[i] = 0.0;													
	}

	txtfile = fopen("loancalc.txt", "w");										// Writes to txtfile.

	if (txtfile == NULL)														//////////////////////////////////
	{																			//								//
		printf("\n\n file not open\n\n");										//	Checks if txtfile has saved.//
	}																			//								//
	else(printf("\n\n file open\n\n"));											//////////////////////////////////

	txtfile = fopen("loancalc.txt", "a");										// Appends to txtfile.
	csvfile = fopen("loancalc.csv", "w");										// Writes to csvfile.

	start_info();																// Gain information from user function.
	placement_time();															// Placement function.
	student_loan();																// Loan function.

	mloop();																	// Calls main function.

	fclose(txtfile);															// Stops writting to txtfile.
	fclose(csvfile);															// Stops writting to csvfile.

	scanf("%*s");																// Pauses.
}
