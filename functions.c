#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Functions.h"
#include <math.h>

void start_info()																							
{
	printf(" [enter] start date (MM YYYY): ");																//////////////////////////////////////////
	scanf("%d %d", &Start_month, &Start_year);																//										//
																											//		Function gains information		//
	printf(" How many years did you spend at university? ");												//		to start calculations 			//
	scanf("%i", &years);																					//										//
																											//////////////////////////////////////////
	printf("\n Placement(y, n): ");																			
	getchar();
	scanf("%c", &placement);

	
}

void placement_time()
{
	if (placement == 'y' || placement == 'Y')
		duration_year = years + 1;																			// Adds extra year is user chooses to do a placement.
	else (duration_year = years);

	return;
}

void tuition_fee()
{
	if (placement == 'y' || placement == 'Y')
		tutitionfee = (float)(years * 9250.0f) + (9250.0f * 0.2f);											// Calculates Placement fee.
	else (tutitionfee = years * 9250.0f);
}

void maintenance_fee()
{
	tutitionfee = tutitionfee + (8700 * duration_year);														// Adds on Assumed Maintenance loan.
	return;
}

void student_loan()
{
	tuition_fee();																							// Calls function.
	maintenance_fee();																						// Calls function.
	return;
}

void get_extra_info()
{
	Graduation_Date = Start_year + duration_year;															//////////////////////////////////////////
																											//										//
	printf("\n Graduation Date: June %i\n\n", Graduation_Date);												//		Function prints out calculated	//
	printf(" Fee to pay once graduated(GBP): %.2f\n", tutitionfee);											//		values for Graduation date,		//
																											//		tutition fee and first paymant	//
	AnnualSalary = (float)Start_Salary;																		//		date.							//
	First_payment_date = Graduation_Date + 1;																//										//
																											//////////////////////////////////////////
	printf("\n First payment date: 04/%i \n\n", First_payment_date);
	year2 = First_payment_date;

	return;
}

float get_interest()																						//////////////////////////////////////////
{																											//										//
	if (AnnualSalary <= 25000)																				//		Function calculates interest	// 
		interest = 0;																						//		due to current annual salary.	//
	else if (AnnualSalary <= 45000)																			//		If salary is less that 25000	//
		interest = ((AnnualSalary - 25000) / 20000) * 3;													//		interst is 0%. Over 45000		//
	else (interest = 3);																					//		interest is capped at 3%.		//
																											//										//
	return interest;																						//////////////////////////////////////////
}

void loop1()
{
	while (AnnualSalary <= 24999)
	{
		Arraybalance[month] = Fee;																			// Calculates Array values relative to changing months.
		ArraySalary[month] = AnnualSalary;																	// Calculates Array values relative to changing months.
		ArrayThreshold[month] = 0;																			// initialises Array value.
		Arrayinterestrate[month] = 0;																		// initialises Array value.

		if (month2 % 13 == 0)																				
		{																									// Resets 'month2' back to 1 and counts 'year2' up, helps to format csvfile.
			year2++;
			month2 = 1;
		}

		Arraymonth[month] = month2;																			// Calculates Array values relative to changing months.
		month++;																							// 'Month' counts all the way to 360 or resiets once loan is paid off.
		month2++;																							// Counts up to 12 the resets to 1, formats Array date in csvfile.

		Fee = (Fee * (1 + Month_interest));																	// Increeases Fee due to RPI only as earning less than 25000 current interest is not considered.

		if (month % 12 == 0)
		{
			AnnualSalary = (float)Start_Salary * (float)pow(1.04f, ((float)month / 12.0f));					// Each year increases annual salary by 4%
		}
		else if (AnnualSalary > 25000)
		{
			break;																							// Breaks loop once earning more than 25000 a year.
		}
		Arrayyear[month] = First_payment_date + (month / 12);												// Calculates Array value relative to change months.
		ArrayMonthlyinterest[month] = 0;																	// Calculates Array value relative to change months.
		ArrayMonthlyRepay[month] = 0;																		// Calculates Array value relative to change months.
	}
	return;
}

void salary_increase()
{
	if (month % 12 == 0)																					//////////////////////////////////////////
	{																										//										//
		Fee = Fee * (1 + Annual_interest);																	//		function calculates new salary	//
																											//		using annual salary increase	//
		AnnualSalary = (float)Start_Salary * (float)pow(1.04f, ((float)month / 12.0f));						//		of 4%. Also (re)calculates		//
		MonthlySalary = AnnualSalary / 12;																	//		monthly payment, monthly		//
																											//		interest.						//
		MonthlyFee = ((AnnualSalary - 25000) * (RepaymentP / 100) / 12);									//										//
																											//////////////////////////////////////////
		get_interest();
		Month_interest = ((RPI + interest) / 12) / 100;
}
	return;
}

void loop2()
{
	if (AnnualSalary > 25000)																				// Enters if statement once you earn more than 25000 a year.
	{
		MonthlySalary = AnnualSalary / 12;																	// Calculates how much you earn a month relative to your current Annual salary.
		MonthlyFee = ((AnnualSalary - 25000) * (RepaymentP / 100) / 12);									// Calculates how much you repay a month due to your salary above the 25000 threshold.

		while ((Fee > 0) && (month < 360))																	// While loop stops once either loan amount has hit zero or loan length has hit 30 year max.
		{
			Arraybalance[month] = Fee;																		// Calculates Array value relative to change months.

			get_interest();																					// Calls function for interest.

			ArraySalary[month] = AnnualSalary;																// Calculates Array value relative to change months.
			ArrayMonthlyinterest[month] = MonthlySalary * ((interest / 100) / 12);							// Calculates Array value relative to change months.
			ArrayMonthlyRepay[month] = MonthlyFee;															// Calculates Array value relative to change months.

			if (month2 % 13 == 0)																			//////////////////////////////////////////
			{																								//										//
				year2++;																					//		Calculates Array value for		//
				month2 = 1;																					//		month in year.					//
			}																								//										//
			Arraymonth[month] = month2;																		//////////////////////////////////////////
			
			Fee = Fee - MonthlyFee;																			// Deduces Monthly fee from loan left.

			TotalFeepayed = TotalFeepayed + MonthlyFee;
			Totalinterest = Totalinterest + (TotalFeepayed * Month_interest);
			if (Fee > 0)
			{
				Monthlyinterest = (Fee * (Annual_interest)) / 12;											// Calculates monthly interest.
				salary_increase();																			// Calls function.
			}
			else (Monthlyinterest = 0);
																											//////////////////////////////////////////
			Arrayyear[month] = First_payment_date + (month / 12);											//										//
			ArrayThreshold[month] = AnnualSalary - 25000;													//		Calculates Array values			//
			Arrayinterestrate[month] = interest;															//		relative to changing months.	//
																											//										//
			month++;																						//////////////////////////////////////////
			month2++;
		}
																										
		if (month == 360)																					//////////////////////////////////////////
		{																									//										//
			printf("\n You have reached the maximum loan length of 30 years");								//		Once 30 years has been			//
			printf("\n Fee remaining(GBP) = 0");															//		reached, program informs		//
		}																									//		user maxmium loan time has		//
		else																								//		reached, loan remaining has		//
		{																									//		wiped.							//
			printf("\n");																					//										//
		}																									//////////////////////////////////////////
																										
		
																											
		printf(" \n Total Payed(GBP) = %.2f", TotalFeepayed);												// prints total Fee payed for each starting salary. 
		Finish_date = ((month) / 12) + First_payment_date;													// Calculates final year of repayment.
		printf("\n Total interest = %.2f \n", Totalinterest);												// prints total interest paid for each starting salary.
																										

		int m = (month) % 12;																				//initialises 'm' as random variable to workout final month.

		switch (m)																							//////////////////////////////////////////
		{																									//										//
		case 1:																								//										//
			printf("\n\n Finish date: January %i", Finish_date);											//		Switch function is to use		//
			break;																							//		variable 'm' to print a			//
		case 2:																								//		final month as well as			//
			printf("\n\n Finish date: February %i", Finish_date);											//		printing the final year of		//
			break;																							//		the repayment. whether it		//
		case 3:																								//		cuts after 30 years or is		//
			printf("\n\n Finish date: March %i", Finish_date);												//		paid off early.					//
			break;																							//										//
		case 4:																								//////////////////////////////////////////
			printf("\n\n Finish date: April %i", Finish_date);
			break;
		case 5:
			printf("\n\n Finish date: May %i", Finish_date);
			break;
		case 6:
			printf("\n\n Finish date: June %i", Finish_date);
			break;
		case 7:
			printf("\n\n Finish date: July %i", Finish_date);
			break;
		case 8:
			printf("\n\n Finish date: August %i", Finish_date);
			break;
		case 9:
			printf("\n\n Finish date: September %i", Finish_date);
			break;
		case 10:
			printf("\n\n Finish date: October %i", Finish_date);
			break;
		case 11:
			printf("\n\n Finish date: November %i", Finish_date);
			break;
		case 0:
			printf("\n\n Finish date: December %i", Finish_date);											
			break;
		default:
			printf("\n\n ERROR");
			break;
		}
	}
	return;
}

void mloop()
{
	for ((int)AnnualSalary = Min_Salary; Start_Salary <= Max_Salary; Start_Salary = Start_Salary + Salary_Inc)	// initialises loop, Gives start salary and a rage from 20000 to 70000 & increments by 10000
	{
		for (int i = 0; i <= 360; i++)																		// initialises loop for array to me reset
		{
			Arrayyear[i] = 0;																				//////////////////////////////////////
			Arraymonth[i] = 0;																				//									//
			ArraySalary[i] = 0.0;																			//		Resists all array values	//
			ArrayThreshold[i] = 0.0;																		//		to zero once finished		//
			Arrayinterestrate[i] = 0.0;																		//		calculating					//
			ArrayMonthlyinterest[i] = 0.0;																	//									//
			ArrayMonthlyRepay[i] = 0.0;																		//									//
			Arraybalance[i] = 0.0;																			//////////////////////////////////////
		}

		month2 = 1;

		fprintf(txtfile, "Start salary: %d\n", Start_Salary);												//prints to txtfile

		AnnualSalary = (float)Start_Salary;
		printf("\n\n\t\t\t\t Start: %.2f\n\n", AnnualSalary);

		get_extra_info();																					// Calls function.

		RPI = 3.3f;			
		get_interest();																						// Calls function.

		Month_interest = ((RPI + interest) / 12) / 100;
		Annual_interest = (RPI + interest) / 100;

		MonthlySalary = AnnualSalary / 12;
		MonthlyFee = ((AnnualSalary - 25000) * (RepaymentP / 100) / 12);

		printf("\n Annual total interest rate: 3.3%% (RPI) + %.2f%% (current interest)", interest);

		Fee = tutitionfee * (1 + Annual_interest);
		Arrayyear[month] = First_payment_date;

		loop1();

		Totalinterest = 0;
		TotalFeepayed = 0;

		loop2();

		fprintf(txtfile, "final salary: %.2f\n", AnnualSalary);												//prints to txtfile
		fprintf(txtfile, "Total loan: %.2f\n", tutitionfee);												//prints to txtfile
		fprintf(txtfile, "Last payment date: %d/%d\n", month2, Finish_date);								//prints to txtfile
		if (Fee > 0)
		{
			fprintf(txtfile, "Closing balance: %.2f\n", Fee);												//prints to txtfile
		}
		else(fprintf(txtfile, "Closing balance: 0\n"));														//prints to txtfile
		fprintf(txtfile, " Total interest: %.2f\n", Totalinterest);											//prints to txtfile
		fprintf(txtfile, "Total paid: %.2f\n\n", TotalFeepayed);											//prints to txtfile

		month = 0;
		Fee = 0;

		printf("\n\n\t\t\t\t\t\t\t final: %.2f\n\n", AnnualSalary);

		fprintf(csvfile, "Date:, ");
		for (int i = 0; i <= 360; i++)																		//////////////////////////////////////////////
		{																									//											//
			fprintf(csvfile, "%i/%i, ", Arraymonth[i], Arrayyear[i]);										//		For loops below print all			//
			Arrayyear[i] = 0;																				//		Calculated Array values in to		//
			Arraymonth[i] = 0;																				//		csvfile in excel.					//
		}																									//											//
																											//////////////////////////////////////////////
		fprintf(csvfile, "\n");
		fprintf(csvfile, "Salary:, ");
		for (int i = 0; i <= 360; i++)
		{
			fprintf(csvfile, "%.2f, ", ArraySalary[i]);
		}

		fprintf(csvfile, "\n");
		fprintf(csvfile, "Salary above threshold:, ");
		for (int i = 0; i <= 360; i++)
		{
			fprintf(csvfile, "%.2f, ", ArrayThreshold[i]);
		}

		fprintf(csvfile, "\n");
		fprintf(csvfile, "Interest:, ");
		for (int i = 0; i <= 360; i++)
		{
			fprintf(csvfile, "%.2f%%, ", Arrayinterestrate[i]);
		}

		fprintf(csvfile, "\n");
		fprintf(csvfile, "Monthly interest:, ");
		for (int i = 0; i <= 360; i++)
		{
			fprintf(csvfile, "%.2f, ", ArrayMonthlyinterest[i]);
		}

		fprintf(csvfile, "\n");
		fprintf(csvfile, "Monthly repayment:, ");
		for (int i = 0; i <= 360; i++)
		{
			fprintf(csvfile, "%.2f, ", ArrayMonthlyRepay[i]);
		}

		fprintf(csvfile, "\n");
		fprintf(csvfile, "Balance:, ");
		for (int i = 0; i <= 360; i++)
		{
			fprintf(csvfile, "%.2f, ", Arraybalance[i]);
		}

		fprintf(csvfile, "\n\n\n");
	}
	return;
}

