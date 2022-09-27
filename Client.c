#include <stdio.h>
#include <stdlib.h>
#include "Interface.h"

int main()
{
	day_details start_date;
	day_details end_date;
	day_details date;
	
	cust_name name[50];
	item_details item[50];
	detail_file info[50];
	int day;

	printf("Enter the start date : \n");
	input_date(&start_date);
	printf("Enter the start day : \n1 - Mon \n2 - Tues\n3 - Wed\n4 - Thurs\n5 - Fri\n6 - Sat \n7 -Sun \n CHOOSE THE DAY :\t");
	scanf("%d",&day);
	printf("Enter the end date : \n");
	input_date(&end_date);
	//disp_date(&start_date, &end_date);
	read_customer_name(name);
	read_item_details(item);
   
	
	int diff = date_diff(&start_date,&end_date);
	//printf("%d\n", diff);
	
	//print_date(&start_date,&end_date,diff,day);
	detail d[diff+1];
	printf("%d",day);
	//summary_file s[40];
	//int sum[1000] = {0};
	int time_slots[11] = {8,9,10,11,12,16,17,18,19,20,21}; 
	//bill_information(&date,item,name,d,info,diff,time_slots,day);
	
	switch(day)
	{
		case 1:case 3:case 4:case 5:case 6:case 7:
		bill_information(&date,item,name,d,info,diff,time_slots,day);
		print_detailed_bill(item, name, d,info,diff,time_slots,day);
													
													break;
		case 2://printf("\nTuesday is a HOLIDAY\n");
												bill_information(&date,item,name,d,info,diff,time_slots,day);
												print_detailed_bill(item, name, d,info,diff,time_slots,day);
													
								break;
		
		default:printf("INVALID DAY");
					break;
		
	}
	//compare_sales_per_day(d,diff,day);
	//compare_sales_per_hour(d,diff,day);
	print_item_detailed_bill(item, name, d,info,diff,time_slots,day);
	print_remaining_item(item, name, d,info,diff,time_slots,day);
	//total_sales_per_day(d,sum,diff+1);
	//display_amount_per_day(d,diff,sum,day);
	//disp_date(&start_date, &end_date);
	//display_customer_total_amount(name,d,diff);

	
	//printf("\n");
	int exit_num;
	printf("PRESS 1 to exit");
	scanf("%d",&exit_num);
	switch(exit_num)
	{
		case 1: exit(0);
		default : break;
	}
}
