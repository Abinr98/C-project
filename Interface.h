#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer_name{
	char name[50];		
};
typedef struct customer_name cust_name;

struct date
{
	int dd;
	int mm;
	int yy;
	
};
typedef struct date day_details;

struct item_detail
{
	char item_name[30];
	int item_price;
	int quantity;
};
typedef struct item_detail item_details;	

struct item
{
	int sl_no;
	item_details items;
	int quantity;
};
typedef struct item detail_file;

struct hour_wise_info
{
	int hr;
	int min;
	char name[40];
	int amount;
	int bill_no;
	detail_file cus_item_detail[5];
	
	
};
typedef struct hour_wise_info hour_details;
 

struct billing_info{
	day_details date;
	hour_details h;
	int rand_item;
};
 
typedef struct billing_info bill;

struct day_wise_Detail
{
	bill b[40];
	int limit;
};
typedef struct day_wise_Detail detail;
/*
struct bill_1
{
	
	bill b[40];
};
typedef struct bill summary_file;*/




void input_date(day_details *date);
//void disp_date(const day_details* start_date,const day_details* end_date);
void read_customer_name(cust_name *name);
void read_item_details(item_details *item);
int date_diff(const  day_details* start_date,const day_details* end_date);
void print_date(const day_details *start_date,const day_details *end_date,int diff,int day);
void bill_information(day_details *date,item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day);
void display_amount_per_day(detail *d,int diff, int *sum, int day);
//void display_customer_amount(item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day);
void display_customer_total_amount(cust_name *name, detail *d,int diff);
void compare_sales_per_day(detail *d,int diff, int day);
void compare_sales_per_hour(detail *d,int diff, int day);
void print_detailed_bill(item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day);
void print_item_detailed_bill(item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day);
void print_remaining_item(item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day);