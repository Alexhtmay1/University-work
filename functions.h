void start_info();
void placement_time();																	//////////////////////////////////
																						//								//
void student_loan();																	//		Prototype functions		//
void tuition_fee();																		//								//
void maintenance_fee();																	//////////////////////////////////

void salary_increase();
void get_extra_info();
float get_interest();

void loop1();
void loop2();
void mloop();

extern int Start_month, Start_year;														//////////////////////////////////////
extern int month, years, duration_year;													//									//
extern int First_payment_date, Graduation_Date;											//		Extern all declarations		//
extern int years, year2;																//		in header file so all		//
extern int Finish_date;																	//		initiated values carry		//
																						//		over across all files		//
extern char placement, maintenance;														//									//
																						//////////////////////////////////////
extern float Fee, tutitionfee;
extern float RepaymentP;
extern float MonthlyFee, MonthlySalary;

extern float AnnualSalary;
extern float interest, Month_interest, TotalFeepayed, Totalinterest;
extern int Min_Salary, Max_Salary, Salary_Inc, Start_Salary;

extern float TotalFeepayed, Totalinterest;
extern int month2;
extern float Salary_above_threshold;

extern float RPI, Annual_interest, Monthlyinterest;

extern float Month_interest;

extern float ArraySalary[361];															//////////////////////////////////
extern int Arrayyear[361];																//								//
extern int Arraymonth[361];																//		Arrays initialised		//
extern float ArrayThreshold[361];														//								//
extern float Arrayinterestrate[361];													//////////////////////////////////
extern float ArrayMonthlyinterest[361];
extern float ArrayMonthlyRepay[361];
extern float Arraybalance[361];

extern FILE* txtfile;
extern FILE*csvfile;


