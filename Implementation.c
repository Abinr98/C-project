#include "Interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_item_details(item_details *item)
{
	FILE *fp;
	fp = fopen("item_master.csv", "r");
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    char line[1024];
    char *token;

    int i = 0;
    //fgets(line, sizeof(line), fp);
    while(fgets(line, sizeof(line),fp)!=NULL)
    {
        token = strtok(line, ",");
        strcpy(item[i].item_name, token);
        token = strtok(NULL, ",");
        item[i].item_price = atof(token);
		token = strtok(NULL, ",");
        item[i].quantity = atoi(token);
        ++i;
    }
	/*
	for(int j =0; j < 50; j++)
	{
		printf("SUNAINA");
		printf("%s :%d\t%d\n", item[j].item_name, item[j].item_price,item[j].quantity);
	}
	*/
}
void read_customer_name(cust_name *name)  
{

	FILE* fp;

	fp = fopen("NamesList.txt", "r");
	int i=0;
	while(fgets(name[i].name,49,fp)!=NULL)
	{
			name[i].name[strcspn(name[i].name,"\n")]=0;	
			//printf("%s \t \n",name[i].name);
			++i;
	}

	fclose(fp);
	
	//return 0;
	
}
void input_date(day_details *date)
{
	scanf("%d %d %d", &date->dd, &date->mm, &date->yy);
	//scanf("%d", &date->day);
}

/*
void disp_date(const day_details* start_date,const day_details* end_date)
{
	printf("%d-%d-%d\t %s\n", start_date->dd, start_date->mm, start_date->yy, start_date->day);
	printf("%d-%d-%d\t %s\n", end_date->dd, end_date->mm, end_date->yy, end_date->day);
}
*/
int date_diff(const day_details *start_date,const day_details *end_date)
{
    int res = 0;
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((start_date->yy%4 ==0 && start_date->yy%100 != 0) || (start_date->yy%400 == 0) )
	{
        month[1]=29;
    }
    if(start_date->mm == end_date->mm)
	{
        return end_date->dd - start_date->dd;
    }
    res = res + month[start_date->mm - 1] - start_date->dd;
    for(int i=start_date->mm; i<end_date->mm-1; i++)
	{
        res = res + month[i];
    }
    res = res + end_date->dd;
	//printf("%d", res);
    return res;

}
void print_date(const day_details *start_date,const day_details *end_date,int diff,int day)
{
    int date_count=start_date->dd;
    int month_count=start_date->mm;
	int year_count = start_date->yy;
	int value = diff+day;
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	//int day[7] = {1,2,3,4,5,6,7};
	int count=day;
	int count_2=1;
	int array[diff+1];
	printf("day : %d\n", day);
	for(int i=0; i<=diff; i++)
	{
		if(count > 7)
			count = 1;
		array[i] = count;
		++count;
		/*
		if(count<8)
		{
			array[i]=count;
			count++;
			
		}
		else
		{
			array[i]=count_2;
			if(count_2 > 6)
			{
				count_2 = 1;
			}
			else
			{
				//array[i]=count_2;
				count_2++;
			}
		}
		*/
		//printf("%d\t", array[i]);
	}

    if((start_date->yy%4 ==0 && start_date->yy%100 != 0) || (start_date->yy%400 == 0) )
    {
        month[1]=29;
    }
	int i=0;
	while(i<=diff)
	{	
		
		if(start_date->mm == end_date->mm)
		{
			printf("%d-%d-%d\t %d\n",date_count,start_date->mm,start_date->yy, array[i]);
			++date_count;
			//--diff;
			i++;
		}
		else
		{
			if(month_count<=end_date->mm && date_count<=month[month_count-1])
			{
				
				printf("%d-%d-%d\t %d\n",date_count,month_count,year_count, array[i]);
				++date_count;
				//--diff;
				i++;
					
			}
			else
			{
				++month_count;
				date_count=1;
			}
		}
		
		
	}
	//printf("hi");
	//printf("%d-%d-%d\t %d\n", end_date->dd, end_date->mm, end_date->yy, array[i]);	

}
static void generate_bill_time(int* time){
	int random = 10 + rand()% 13;
	if((time[1] + random) >= 60){
		++time[0];
		if(time[0] == 13){
			time[0] = 16;
		}
		time[1] += random - 60;
	}
	else{
		time[1] += random;
	}
}

void bill_information(day_details *date,item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day)
{
	for (int i=0; i<(diff+1) ;i++)
	{
		if(day==2){
			i=i-1;
			day=day+1;
			continue;
		}
		if(day!=2)
		{
			d[i].limit= (rand() % (40 - 20 + 1)) + 20;
			if(day==6 || day==7){
			d[i].limit= (rand() % (40 - 35 + 1)) + 35;
			}
			int time[2] = {8,0};
			for(int j=0; j<d[i].limit; ++j)
			{
				int item_amount=0;
				int quantity=0;
				int rand_item=1+rand()%5;
				int ran =rand()%50;
				
				d[i].b[j].rand_item=rand_item;
				generate_bill_time(time);
                d[i].b[j].h.hr = time[0];
                d[i].b[j].h.min = time[1];
				strcpy(d[i].b[j].h.name,name[ran].name);
				d[i].b[j].h.bill_no = j+1;
				int k = 0;
                while(k < d[i].b[j].rand_item){
					int rand_item_name = rand()%50;
					quantity = 1+rand() % (5);
					if(item[rand_item_name].quantity > 0 && quantity <= item[rand_item_name].quantity)
					{
						strcpy(d[i].b[j].h.cus_item_detail[k].items.item_name,item[rand_item_name].item_name);
						d[i].b[j].h.cus_item_detail[k].items.item_price = item[rand_item_name].item_price;
						d[i].b[j].h.cus_item_detail[k].quantity = quantity;
						item_amount = quantity * item[rand_item_name].item_price;
						d[i].b[j].h.amount = d[i].b[j].h.amount + item_amount;
						//printf("%d \t",d[i].b[j].h[j].amount);
						item[rand_item_name].quantity-=quantity;
						k++;
                    }
                    else{
                        --d[i].b[j].rand_item;
                    }
				}
                }
			}
		}
		day= (day%7)+1;
		
	}
	
	/*
	for (int i=0; i<(diff+1) ;i++)
	{	
		
		int index_values[50];
		d[i].limit= (rand() % (40 - 20 + 1)) + 20;
		if(day==6 || day==7){
		d[i].limit= (rand() % (40 - 35 + 1)) + 35;
		}
		int time=0;
		int count= 0;
		for(int j=0; j<d[i].limit; ++j)
		{
			int ran =rand()%50;
			int item_count=0;
			int rand_item=1+rand()%5;
			d[i].b[j].rand_item=rand_item;
			int item_amount=0;
			d[i].b[j].h.amount =0;
			if(count <=3 && item_count<5)
			{
				strcpy(d[i].b[j].h.name,name[ran].name);
				d[i].b[j].h.time = time_slots[time];
				d[i].b[j].h.bill_no = j+1;
				//for(int k = 0; k<rand_item; ++k)
				int k=0;
				while(k<rand_item)
				{
							int rand_item_name = rand()%50;
							int quantity = 1+rand() % (5);
							if(item[rand_item_name].quantity > 0 && quantity <= item[rand_item_name].quantity)
							{
								
								strcpy(d[i].b[j].h.cus_item_detail[k].items.item_name,item[rand_item_name].item_name);
								d[i].b[j].h.cus_item_detail[k].items.item_price = item[rand_item_name].item_price;
								d[i].b[j].h.cus_item_detail[k].quantity = quantity;
								item_amount = quantity * item[rand_item_name].item_price;
								d[i].b[j].h.amount = d[i].b[j].h.amount + item_amount;
								//printf("%d \t",d[i].b[j].h[j].amount);
								item[rand_item_name].quantity-=quantity;
								k++;
							}
							else{
								d[i].b[j].rand_item-=1;
							}
						
					
				}
				
				//d[i].b[j].h[j].amount=(rand() % (5000 - 100 + 1)) + 100;
				++count;
				
			}
			else
			{
				count = 0 ;
				time = time+1;
				strcpy(d[i].b[j].h.name,name[ran].name);
				d[i].b[j].h.time = time_slots[time];
				d[i].b[j].h.bill_no = j+1;
				int k=0;
				while(k<rand_item)
				{
					int rand_item_name = rand()%50;
					int quantity = 1+rand() % (5);
					if(item[rand_item_name].quantity > 0 && quantity <= item[rand_item_name].quantity)
					{
						strcpy(d[i].b[j].h.cus_item_detail[k].items.item_name,item[rand_item_name].item_name);
						d[i].b[j].h.cus_item_detail[k].items.item_price = item[rand_item_name].item_price;
						d[i].b[j].h.cus_item_detail[k].quantity = quantity;
						item_amount = d[i].b[j].h.cus_item_detail[k].quantity * item[rand_item_name].item_price;
						d[i].b[j].h.amount = d[i].b[j].h.amount + item_amount;
						//printf("%d \t",d[i].b[j].h.amount);
						item[rand_item_name].quantity-=quantity;
						k++;
					}
					else
					{
						d[i].b[j].rand_item-=1;
					}
				}
				
				//d[i].b[j].h.amount=(rand() % (5000 - 100 + 1)) + 100;
				
				++count;
			}
			
		}
	day= (day%7)+1;
	}	
}


void display_amount_per_day(detail *d,int diff, int sum[], int day)
{
	int current_day=day;
	printf("\nTOTAL AMOUNT PER DAY\n");
	for (int i=0; i<(diff+1) ;i++)
	{
		//printf("day:%d\n",i+1);
		int sum[diff+1];
		
		for(int j=0; j<d[i].limit; ++j)
		{
			
			sum[i] = sum[i] + d[i].b[j].h.amount;
		}
		if(current_day!=2)
		{
			printf("Total for day %d : %d\n", current_day, sum[i]);
		}
		else
		{
			printf("TUESDAY IS A HOLIDAY\n");
		}
		
		current_day=(current_day+1)%7;
		if(current_day==0)
		{
			current_day = current_day + 1;
		}
	}
	int max = sum[0] ;
	for(int k=0; k<(diff+1); ++k)
	{
		if(sum[k+1] > max)
		{
			max = sum[k+1];
		}
	}
	//printf("Highest sales vales is %d\n" , max);
}
/*
void display_customer_amount(item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day)
{	
	int current_day=day;
	printf("\nBilling information for each day\n");
	printf("DURATION\n MORNING\t 8AM to 9AM=>8\t9AM-10AM=>9\t10AM-11AM=>10\t11AM-12PM=>11\t12PM-1PM=>12\nAFTERNOON\t4PM-5PM=>16\t5PM-6PM=>17\t6PM-7PM=>18\t7PM-8PM=>19\t8PM-9PM=>20\t9PM-10PM=>21\n");
	for (int i=0; i<(diff+1) ;i++)
	{	
		printf("Day:%d\n",i+1);
		if(current_day == 0)
		{
			current_day=7;
		}
		if(current_day == 2)
		{
			printf("\tTuesday is a HOLIDAY\n");
		}
		
		for(int j=0; j<d[i].limit; ++j)
		{	
			if(current_day!=2)
			{
				printf("%d\t %s\n  TIME:- %d \n",d[i].b[j].h.bill_no,d[i].b[j].h.name,d[i].b[j].h.time);
				printf("Item Name\tPrice\tQuantity\tAmount\n");
				for(int k=0; k<(d[i].b[j].rand_item);++k)
				{
					//printf("Sunaina");
					printf("%s \t %d \t %d \t\t %d\n",d[i].b[j].h.cus_item_detail[k].items[k].item_name,d[i].b[j].h.cus_item_detail[k].items[k].item_price,d[i].b[j].h.cus_item_detail[k].quantity,(d[i].b[j].h.cus_item_detail[k].items[k].item_price*d[i].b[j].h.cus_item_detail[k].quantity)); 
				}
				printf("Total amount:%d\n\n",d[i].b[j].h.amount);
					
			}
		}
		printf("\n");
		current_day=(current_day+1)%7;
		
	}
}
*/

void display_customer_total_amount(cust_name *name, detail *d,int diff)
{
	printf("\n\nAMOUNT PER PERSON: \n");
	int sum;
	//for(int i =0; i< 50; i++)
	
	double total_c[50]={0};
	
		//total[m].total_person=0;
	for (int j=0; j<(diff+1) ;j++)
	{
		for(int k=0; k<d[j].limit; ++k)
		{
			//printf("hello");
			//printf("%s",name[m].name);
			for(int m=0;m<50;++m)
			{
				if(!strcmp(d[j].b[k].h.name,name[m].name))
				{
					total_c[m]+=d[j].b[k].h.amount;
					//printf("%d",d[j].b[k].h.amount);
				}
				
			}
	
		}
	}
	printf("Sl.No.\t\t\tNAME\t\t\t\tTOTAL AMOUNT\n");
	for (int i=0;i<50;++i)
	{
		printf("%d \t\t\t %-15s \t\tRs.%.2f \n",i+1, name[i].name,total_c[i]);
	}	
}



void compare_sales_per_day(detail *d,int diff, int day)
{
	/*
	int current_day=day;
	printf("\nTOTAL AMOUNT PER DAY\n");
	for (int i=0; i<(diff+1) ;i++)
	{
		//printf("day:%d\n",i+1);
		int sum[diff+1];
		
		for(int j=0; j<d[i].limit; ++j)
		{
			
			sum[i] = sum[i] + d[i].b[j].h.amount;
		}
		if(current_day!=2)
		{
			printf("Total for day %d : %d\n", current_day, sum[i]);
		}
		else
		{
			printf("TUESDAY IS A HOLIDAY\n");
		}
		
		current_day=(current_day+1)%7;
		if(current_day==0)
		{
			current_day = 7;
		}
	}
	*/
	int current_day=day;
	double total[7]={0};
	char day_name[7][10]={{"Monday"},{"Tuesday"},{"Wednesday"},{"Thursday"},{"Friday"},{"Saturday"},{"Sunday"}};
	
	for(int i=0;i<(diff+1);++i)
	{
		for(int j=0; j<d[i].limit; ++j)
		{
	
		total[current_day-1]+=d[i].b[j].h.amount;
		}
		current_day=(current_day+1)%7;
		if(current_day==0)
		{
			current_day = 7;
		}
		
	}
	printf("Sale Per Day:\n");
	printf("\tDAY\tTOATAL AMOUNT\n");
	for(int i=0;i<7;++i)
	{
		if(i==1)
		{
			printf("%d . %-10s : HOLIDAY\n",i+1,day_name+i);
		}
		else if(total[i]==0)
		{
			printf("%d . %-10s : -------\n",i+1,day_name+i);
		}
		else
			printf("%d . %-10s : Rs %.2f\n",i+1,day_name+i,total[i]);
	}
	printf("\n");
	/*
	int max = sum[0] ;
	for(int k=0; k<(diff+1); ++k)
	{
		if(sum[k+1] > max)
		{
			max = sum[k+1];
		}
	}*/
	//printf("Highest sales vales is %d\n" , max);
	
	//printf("Highest sales is on %d with sales = %d\n", day, max);
}

void compare_sales_per_hour(detail *d, int diff,int day)
{
	printf("\nSALES PER HOUR\n");
	/*for(int l=0; l<11;++l)
	{
		for (int i=0; i<(diff+1) ;i++)
		{
			for(int j=0; j<d[i].limit; ++j)
			{
				if(time_slots[l] == d[i].b[j].h.time)
				{
					sum[l] = sum[l] + d[i].b[j].h.amount;
					//printf("%d \t" ,sum[l]);
				}
			}	
		
		}

		if((l + 1) == 11)
		{
			printf(" %d - 22  \t: Total Amount : %d \n",time_slots[l], sum[l]);
		}
		else if(l == 4)
		{
			printf(" %d - 13 \t: Total Amount : %d \n",time_slots[l], sum[l]);
		}
		else
		{
			printf(" %d - %d  \t: Total Amount : %d \n",time_slots[l],time_slots[l+1], sum[l]);
		}
		
	}
	*/
	
	double total[11]={0};
	char time[11][20]={{" 08:00 am-09:00 am"},{" 09:00 am-10:00 am"},{" 10:00 am-11:00 am"},{" 11:00 am-12:00 pm"},{" 12:00 pm-01:00 pm"},{" 04:00 pm-05:00 pm"},{" 05:00 pm-06:00 pm"},{" 06:00 pm-07:00 pm"},{" 07:00 pm-08:00 pm"},{"08:00 pm-09:00 pm"},{"09:00 pm-10:00 pm"}};
	for(int i=0;i<(diff+1);++i)
	{
		for(int j=0; j<d[i].limit; ++j)
		{
			int interval=0;
			if(d[i].b[j].h.hr>12)
			{
				interval=(d[i].b[j].h.hr%10)-1;
			}
			else{
				interval=d[i].b[j].h.hr%8;
			}
			
			total[interval]+=d[i].b[j].h.amount;
		}
	}
	printf("\tTIME\t\tAMOUNT\n");
	for(int i=0;i<11;++i)
	{
		printf("%d . %s : Rs %.2f\n",i+1,time+i,total[i]);
	}
	printf("\n");
	
	/*int max = sum[0] ;
	for(int k=0; k<11; ++k)
	{

		if(sum[k+1] > max)
		{
			max = sum[k+1];
		}
	}
	//printf("Highest sales vales is %d\n" , max);
	*/

}

void print_detailed_bill(item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day)
{
	int current_day=day;
	printf("\nBilling information for each day\n");
	printf("DURATION\n MORNING\t 8AM to 9AM=>8\t9AM-10AM=>9\t10AM-11AM=>10\t11AM-12PM=>11\t12PM-1PM=>12\nAFTERNOON\t4PM-5PM=>16\t5PM-6PM=>17\t6PM-7PM=>18\t7PM-8PM=>19\t8PM-9PM=>20\t9PM-10PM=>21\n");
	for (int i=0; i<(diff+1) ;i++)
	{	
		printf("Day:%d\n",i+1);
		if(current_day == 0)
		{
			current_day=7;
		}
		if(current_day == 2)
		{
			printf("\tTuesday is a HOLIDAY\n");
		}
		
		for(int j=0; j<d[i].limit; ++j)
		{	
		
			if(current_day!=2)
			{
				printf("%d\t %s\n  TIME:- %d:%d\n",d[i].b[j].h.bill_no,d[i].b[j].h.name,d[i].b[j].h.hr,d[i].b[j].h.min);
				printf("Item Name\tPrice\tQuantity\tAmount\n");
				for(int k=0; k<(d[i].b[j].rand_item);++k)
				{
					//printf("Sunaina");
					printf("%s \t %d \t %d \t\t %d\n",d[i].b[j].h.cus_item_detail[k].items.item_name,d[i].b[j].h.cus_item_detail[k].items.item_price,d[i].b[j].h.cus_item_detail[k].quantity,(d[i].b[j].h.cus_item_detail[k].items.item_price*d[i].b[j].h.cus_item_detail[k].quantity)); 
				
				}
				printf("Total amount:%d\n\n",d[i].b[j].h.amount);
					
			}
		}
		for(int k=0;k<50;++k)
		{
			printf("-");
		}
		printf("\n");
		current_day=(current_day+1)%7;
	}	

}

void print_item_detailed_bill(item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day)
{
	//int current_day=day;
	double total_amt[50]={0};
	int total_quan[50]={0}; 
	//for (int i=0; i<(diff+1) ;i++)
	for(int j=0; j<diff+1 ; ++j)
	{	
		for(int k=0; k<d[j].limit; ++k)
		{
			for(int l=0; l<(d[j].b[k].rand_item); l++)
			{
			
				for(int m=0; m<50; ++m)
				{
					//printf("%s\n",d[m].b[k].h.cus_item_detail[l].items[l].item_name);
					if(!strcmp(d[j].b[k].h.cus_item_detail[l].items.item_name,item[m].item_name))
					{
						
						total_quan[m] = total_quan[m] + d[j].b[k].h.cus_item_detail[l].quantity;
						total_amt[m] += (total_quan[m] * d[j].b[k].h.cus_item_detail[l].items.item_price);
						//total_amt[l]+=d[l].b[k].h.amount;
						//printf("%d",d[l].b[k].h.amount);
						//printf("Sunaina - 2\t");
					}
				}
			}
		}
	}

	printf("\n ");
	printf("SL no \t\t \t ITEM NAME \t\t\t QUANTITY \t \t \t TOTAL AMOUNT\n");
	for (int i=0;i<50;++i)
	{
		
		
		printf("%d \t\t\t %s \t\t\t %d\t\t\t\t Amount: %.2f \n",i+1, item[i].item_name,total_quan[i],total_amt[i]);
	}
		
}


void print_remaining_item(item_details *item, cust_name *name, detail *d,detail_file *info,int diff,int *time_slots, int day)
{
	//int current_day=day;
	double total_amt[50]={0};
	int total_quan[50]={0}; 
	//for (int i=0; i<(diff+1) ;i++)
	for(int j=0; j<diff+1 ; ++j)
	{	
		for(int k=0; k<d[j].limit; ++k)
		{
			for(int l=0; l<(d[j].b[k].rand_item); l++)
			{
			
				for(int m=0; m<50; ++m)
				{
					//printf("%s\n",d[m].b[k].h.cus_item_detail[l].items[l].item_name);
					if(!strcmp(d[j].b[k].h.cus_item_detail[l].items.item_name,item[m].item_name))
					{
						
						total_quan[m] = total_quan[m] + d[j].b[k].h.cus_item_detail[l].quantity;
						total_amt[m] += (total_quan[m] * d[j].b[k].h.cus_item_detail[l].items.item_price);
						//total_amt[l]+=d[l].b[k].h.amount;
						//printf("%d",d[l].b[k].h.amount);
						//printf("Sunaina - 2\t");
					}
				}
			}
		}
		
	}

	printf("\n ");
	printf("SL no \t\t \t ITEM NAME \t\t\t QUANTITY SOLD \t \t \tREMAINING QUANTITY\t TOTAL AMOUNT\n");
	for (int i=0;i<50;++i)
	{
		
		
		printf("%d \t\t\t %s \t\t\t %d\t\t\t\t%d\t\t\t Amount: %.2f \n",i+1, item[i].item_name,total_quan[i],item[i].quantity,total_amt[i]);
	}
		
}

