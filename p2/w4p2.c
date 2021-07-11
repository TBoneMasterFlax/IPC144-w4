/*
	==================================================
	Workshop #4 (Part-2):
	==================================================
	Name   : Tuan Nguyen
	ID     : 109062166
	Email  : tnguyen140@myseneca.ca
	Section: NFF
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MIN_NET_INCOME 500.00
#define MAX_NET_INCOME 400000.00
#define MIN_LIST 1
#define MAX_LIST 10
#define MIN_COST 100.00

int main(void)
{
	int flag = 1, flagFO;
	double income;
	int listSize;
	int selection;

	int item, itemList[MAX_LIST];
	double cost, costList[MAX_LIST], totalCost = 0, totalCostP1 = 0, totalCostP2 = 0, totalCostP3 = 0;
	int priority, priorityList[MAX_LIST];
	char financeOptions, financeOptionsList[MAX_LIST];

	int years;
	double months;

	printf("+--------------------------+\n");
	printf("+   Wish List Forecaster   |\n");
	printf("+--------------------------+\n");
	do
	{
		printf("\nEnter your monthly NET income: $");
		scanf("%lf", &income);
		if (income < MIN_NET_INCOME)
			printf("ERROR: You must have a consistent monthly income of at least $500.00\n");
		else if (income > MAX_NET_INCOME)
			printf("ERROR: Liar! I'll believe you if you enter a value no more than $400000.00\n");
		else
			flag = 0;
	} while (flag);



	flag = 1;
	do
	{
		printf("\nHow many wish list items do you want to forecast?: ");
		scanf("%d", &listSize);
		if (listSize < MIN_LIST || listSize > MAX_LIST)
			printf("ERROR: List is restricted to between 1 and 10 items.\n");
		else
			flag = 0;
	} while (flag);



	for (item = 0; item < listSize; item++)
	{
		printf("\nItem-%d Details:\n", item + 1);
		flag = 1;
		do
		{
			printf("   Item cost: $");
			scanf("%lf", &cost);
			if (cost < MIN_COST)
				printf("      ERROR: Cost must be at least $100.00\n");
			else
			{
				totalCost += cost;
				costList[item] = cost;
				flag = 0;
			}
		} while (flag);



		flag = 1;
		do
		{
			printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
			scanf("%d", &priority);
			if (priority < 1 || priority > 3)
				printf("      ERROR: Value must be between 1 and 3\n");
			else
			{
				priorityList[item] = priority;
				switch (priority)
				{
				case 1:
					totalCostP1 += costList[item];
					break;
				case 2:
					totalCostP2 += costList[item];
					break;
				case 3:
					totalCostP3 += costList[item];
					break;
				default:
					break;
				}
				flag = 0;
			}
		} while (flag);



		flag = 1;
		do
		{
			scanf("%*c");
			printf("   Does this item have financing options? [y/n]: ");
			scanf("%c", &financeOptions);
			switch (financeOptions)
			{
			case 'y':
			case 'n':
				financeOptionsList[item] = financeOptions;
				flag = 0;
				break;
			default:
				printf("      ERROR: Must be a lowercase 'y' or 'n'\n");
			}
		} while (flag);
		itemList[item] = item + 1;
	}


	printf("\nItem Priority Financed        Cost\n");
	printf("---- -------- -------- -----------\n");
	for (item = 0; item < listSize; item++)
		printf("%3d  %5d    %5c    %11.2lf\n", itemList[item], priorityList[item], financeOptionsList[item], costList[item]);
	printf("---- -------- -------- -----------\n");
	printf("                      $%11.2lf\n\n", totalCost);



	flag = 1;
	do
	{
		printf("How do you want to forecast your wish list?\n");
		printf(" 1. All items (no filter)\n");
		printf(" 2. By priority\n");
		printf(" 0. Quit/Exit\n");
		printf("Selection: ");
		scanf("%d", &selection);



		if (selection == 0)
			flag = 0;



		else if (selection == 1)
		{
			printf("\n====================================================\n");
			printf("Filter:   All items\n");
			printf("Amount:   $%1.2lf\n", totalCost);
			totalCost *= 100;
			income *= 100;
			years = (int)totalCost / (int)(income * 12);
			months = ((int)totalCost % (int)(income * 12)) / income;
			printf("Forecast: %d years, %.0lf months\n", years, months);
			totalCost /= 100;
			income /= 100;
			flagFO = 0;
			for (item = 0; item < listSize; item++)
				if (financeOptionsList[item] == 'y')
					flagFO = 1;
			if (flagFO)
			{
				printf("NOTE: Financing options are available on some items.\n");
				printf("      You can likely reduce the estimated months.\n");
			}
			printf("====================================================\n\n");
		}



		else if (selection == 2)
		{
			printf("\nWhat priority do you want to filter by? [1-3]: ");
			scanf("%d", &priority);
			printf("\n====================================================\n");
			printf("Filter:   by priority (%d)\n", priority);
			flagFO = 0;
			switch (priority)
			{
			case 1:
				printf("Amount:   $%1.2lf\n", totalCostP1);
				totalCostP1 *= 100;
				income *= 100;
				years = (int)totalCostP1 / (int)(income * 12);
				months = ((int)totalCostP1 % (int)(income * 12)) / income;
				printf("Forecast: %d years, %.0lf months\n", years, months);
				totalCostP1 /= 100;
				income /= 100;
				for (item = 0; item < listSize; item++)
					if (priorityList[item] == priority)
						if (financeOptionsList[item] == 'y')
							flagFO = 1;
				break;
			case 2:
				printf("Amount:   $%1.2lf\n", totalCostP2);
				totalCostP2 *= 100;
				income *= 100;
				years = (int)totalCostP2 / (int)(income * 12);
				months = (((int)totalCostP2 % (int)(income * 12)) / income) + 1;
				printf("Forecast: %d years, %.0lf months\n", years, months);
				totalCostP2 /= 100;
				income /= 100;
				for (item = 0; item < listSize; item++)
					if (priorityList[item] == priority)
						if (financeOptionsList[item] == 'y')
							flagFO = 1;
				break;
			case 3:
				printf("Amount:   $%1.2lf\n", totalCostP3);
				totalCostP3 *= 100;
				income *= 100;
				years = (int)totalCostP3 / (int)(income * 12);
				months = ((int)totalCostP3 % (int)(income * 12)) / income;
				printf("Forecast: %d years, %.0lf months\n", years, months);
				totalCostP3 /= 100;
				income /= 100;
				for (item = 0; item < listSize; item++)
					if (priorityList[item] == priority)
						if (financeOptionsList[item] == 'y')
							flagFO = 1;
				break;
			default:
				break;
			}
			if (flagFO)
			{
				printf("NOTE: Financing options are available on some items.\n");
				printf("      You can likely reduce the estimated months.\n");
			}
			printf("====================================================\n\n");
		}



		else
			printf("\nERROR: Invalid menu selection.\n\n");



	} while (flag);
	printf("\nBest of luck in all your future endeavours!");
	return 0;
}