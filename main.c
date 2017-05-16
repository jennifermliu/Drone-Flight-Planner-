#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define NORMAL  "\x1b[0m"

//MAP CONSTANTS
#define EMPTY 1
#define PIZZA 1
#define CUSTOMER 2
#define RIVAL 3

//DIRECTION CONSTANTS
#define SOUTH 1
#define WEST 2
#define NORTH 3
#define EAST 4

//ACTION CONSTANTS
#define EXIT 0
#define SOFF 1
#define WOFF 2
#define NOFF 3
#define EOFF 4
#define SON 5
#define WON 6
#define NON 7
#define EON 8

void print_map(int **map , float **V);
float **init_values();

#include "student_code.c"

int **init_map();

void set_map(int **, char *);
void set_values(float **map, float *data);
bool check_policies(int **map,int **map_gold, bool show);
bool check_values(float **map,float *map_gold, bool show);
bool run_experiment(char data[], float value_gold, char p_gold[], float values[], float delivery_fee, float battery_drop_cost, float dronerepair_cost, float discount_per_cycle);
void set_policies(int **map, char *data);


int main(int n, char **args)
{
	char data1[] = "000000"
                   "010030"
                   "000000"
                   "000000"
                   "003000"
                   "000020";
				   
	char p_gold1[] = "ssssns"
                     "esSwXS"
                     "eEEsSs"
                     "eeneSs"
                     "swXeSs"
                     "eEEEXW";
					 
	float values_gold1[] = { 38.73, 42.33, 45.72, 42.87, 32.49, 40.52,
	                         42.38, 47.06, 52.00, 49.21,-100.00,46.80,
							 46.05, 52.05, 59.02, 66.80, 72.33, 70.86,
							 44.93, 49.73, 55.85, 73.82, 80.60, 77.37,
							 44.15, 43.34,-100.00,82.10, 89.78, 84.00,
							 49.14, 55.41, 63.20, 90.39, 100.00,90.59};
	printf("\nMap1:\n");
	bool exp1 = run_experiment(data1, 46.68, p_gold1, values_gold1, 100, 1, 100, .05);

	char data2[] = "000000"
                   "000010"
                   "000300"
                   "000000"
                   "020030"
                   "000000";
				   
	char p_gold2[] = "sswwww"
                     "sswnww"
                     "sswXen"
                     "sswsWw"
                     "eXwwXe"
                     "nnwwWw";
					 
	float values_gold2[] = {  4.25, 4.44,-1.38,  -9.08, -16.31,-22.89,
	                         12.05,13.58, 6.06, -13.12, -20.68,-26.55,
							 20.14,24.06,15.62,-200.00, -32.50,-31.82,
							 28.33,36.04,26.33,  10.90, -23.80,-30.81,
							 36.33,50.00,36.04,  23.37,-200.00,-38.24,
							 28.38,36.33,28.33,  20.03, -15.23,-23.99};
	printf("\nMap2:\n");
	bool exp2 = run_experiment(data2, -20.683084, p_gold2, values_gold2, 50, 5, 200, .05);

	char data3[] = "203000"
                   "003000"
                   "003000"
                   "003000"
                   "000000"
                   "000001";
				   
	char p_gold3[] = "XWXeSS"
                     "NWXESS"
                     "NWXESS"
                     "NWXeSS"
                     "NWsWWW"
                     "NwWWWW";
					 
	float values_gold3[] = { 200.00,196.92,-500.00,159.76,161.72,161.35,
	                         196.92,194.19,-500.00,162.05,164.30,163.59,
							 193.89,191.22,-500.00,164.74,167.00,165.82,
							 190.90,188.27,-500.00,168.04,169.79,168.02,
							 187.95,185.40,178.24,175.16,172.62,170.18,
							 185.08,182.85,180.09,177.33,174.62,171.97};
	printf("\nMap3:\n");
	bool exp3 = run_experiment(data3, 171.97, p_gold3, values_gold3, 200, .1, 500, .01);

	char data4[] = "000000"
                   "000000"
                   "000000"
                   "003000"
                   "100002"
                   "003000";
				   
	char p_gold4[] = "eeeesS"
                     "eeeesS"
                     "eeEesS"
                     "sSXEES"
                     "EEEEEX"
                     "nNXeeN";
					 
	float values_gold4[] = { 2118.28,2571.48,3076.57,3631.31,4230.25,4816.32,
	                         2313.14,2859.95,3507.49,4266.84,5063.20,5836.30,
							 2410.35,2985.84,3733.60,5087.40,6030.60,7021.31,
							 2348.09,2574.66,-500.00,6015.52,7136.40,8398.10,
							 2830.99,3622.68,4665.61,6882.79,8300.06,10000.00,
							 2348.09,2574.66,-500.00,6281.71,7308.73,8415.15};
	printf("\nMap4:\n");
	bool exp4 = run_experiment(data4, 2830.98, p_gold4, values_gold4, 10000, 100, 500, .10);

	char data5[] = "000000"
                   "000000"
                   "000000"
                   "003000"
                   "100002"
                   "003000";
				   
	char p_gold5[] = "EEEESS"
                     "EEEESS"
                     "EEnESS"
                     "NwXEES"
                     "NWEEEX"
                     "NWXEEN";
					 
	float values_gold5[] = { 8942.09,9051.30,9159.50,9265.89,9369.73,9458.43,
	                         8973.70,9101.96,9235.63,9373.09,9490.18,9589.20,
							 8887.70,9004.64,9146.99,9492.33,9612.52,9722.90,
							 8766.02,8680.07,-500.00,9610.81,9735.37,9859.71,
							 8643.62,8539.54,7587.67,9705.65,9848.88,10000.00,
							 8524.10,8430.97,-500.00,9636.97,9750.31,9861.36};
	printf("\nMap5:\n");
	bool exp5 = run_experiment(data5, 8643.62, p_gold5, values_gold5, 10000, .1, 500, .01);

	
	char data6[] = "000000"
                   "000000"
                   "000000"
                   "003000"
                   "100002"
                   "003000";
				   
	char p_gold6[] = "ssssss"
                     "ssssss"
                     "esssss"
                     "eeXwss"
                     "eeseeX"
                     "eeXwen";
					 
	float values_gold6[] = { -26070.68,-23496.14,-20933.07,-21617.33,-20863.11,-18937.84,
	                         -22824.06,-19286.73,-15623.42,-17420.39,-16489.15,-13594.78,
							 -19268.41,-14438.60,-8996.75,-12833.64,-11590.64,-7195.96,
							 -15487.75,-8925.09,-500.00,-8022.77,-6169.28,540.05,
							 -16768.20,-12302.80,-7951.10,-7223.90,-252.56,10000.00,
							 	-14270.99,-8064.60,-500.00,-7271.94,-5331.16,670.86};
	printf("\nMap6:\n");
	bool exp6 = run_experiment(data6, -16768.19, p_gold6, values_gold6, 10000, 5000, 500, .1);

	
	return !(exp1 || exp2 || exp3);
}

bool run_experiment(char data[], float value_gold, char p_gold[], float values_gold[], float delivery_fee, float battery_drop_cost, float dronerepair_cost, float discount_per_cycle)
{
	bool result=true;

	int **map;
	map = init_map();
	set_map(map, data);

	int **pp;
	pp = init_map();

	float **vv;
	vv = init_values();
	
	
	float value = drone_flight_planner (map, pp, vv, delivery_fee, battery_drop_cost, dronerepair_cost, discount_per_cycle);

	int **pp_gold;
	pp_gold = init_map();
	set_policies(pp_gold, p_gold);
	

	if (!check_policies(pp,pp_gold,false))
	{
		printf("Policies results: %sFAIL%s\n", RED, NORMAL);
		check_policies(pp,pp_gold,true);
		result=false;
	}
	else
	{
		printf("Policies results: %sSUCCESS%s\n", GREEN, NORMAL);
	}

	if (!check_values(vv,values_gold,false))
	{
		printf("Values results: %sFAIL%s\n", RED, NORMAL);
		check_values(vv,values_gold,true);
		result=false;
	}
	else
	{
		printf("Values results: %sSUCCESS%s\n", GREEN, NORMAL);
	}

	float margin = value_gold*.01;
	margin = margin<0?-margin:margin;
	
	if (value<value_gold - margin || value>value_gold + margin)
	{
		printf("Delivery job value: %f (%sFAIL%s) - correct value (%f)\n", value, RED, NORMAL,value_gold);
		result=false;
	}
	else
	{
		printf("Delivery job value: %f (%sSUCCESS%s)\n", value, GREEN, NORMAL);
	}
	return result;
}

bool check_values(float **map, float *map_gold, bool show)
{
	char s[]="XswneSWNE";
	bool result=true;
	for (int y=0;y<6;y++)
	{
		for (int x=0;x<6;x++)
		{
			float value = map[y][x];
			float margin = map_gold[y*6+x]*.01;
			margin = margin<0?-margin:margin;
			if (map_gold[y*6+x]-margin<value && map_gold[y*6+x]+margin>value)
			{
				if (show)
					printf("%s%2.2f\t",GREEN,value);
			}
			else
			{
				result = false;
				if (show)
					printf("%s%2.2f\t",RED,value);
			}
		}
		if (show)
			printf("%s\n",NORMAL);
	}
	return result;
}

bool check_policies(int **map, int **map_gold, bool show)
{
	char s[]="XswneSWNE";
	bool result=true;
	for (int y=0;y<6;y++)
	{
		for (int x=0;x<6;x++)
		{
			int value = map[y][x];
			if (map_gold[y][x]==value)
			{
				if (show)
					printf("%s%c",GREEN,s[value]);
			}
			else
			{
				result = false;
				if (show)
					printf("%s%c",RED,s[value]);
			}
		}
		if (show)
			printf("%s\n",NORMAL);
	}
	return result;
}

int **init_map()
{
	int **map;
	map = (int **) malloc(sizeof(int*)*6);
	for (int i=0 ; i < 6; i++)
	{
		map[i]=(int *) malloc(sizeof(int) * 6);
	}
	return map;
}

float **init_values()
{
	float **map;
	map = (float **) malloc(sizeof(float*)*6);
	for (int i=0 ; i < 6; i++)
	{
		map[i]=(float *) malloc(sizeof(float) * 6);
	}
	for (int y=0;y<6;y++)
		for (int x=0;x<6;x++)
			map[y][x]=0;
	return map;
}

void set_map(int **map, char *data)
{
	for (int y=0;y<6;y++)
		for (int x=0;x<6;x++)
			map[y][x]=data[y*6+x]-'0';
}

int get_policy_value(char c)
{
	switch (c)
	{
		case 's': return SOFF;
		case 'w': return WOFF;
		case 'n': return NOFF;
		case 'e': return EOFF;
		case 'S': return SON;
		case 'W': return WON;
		case 'N': return NON;
		case 'E': return EON;
	}
	return EXIT;
}

void set_policies(int **map, char *data)
{
	for (int y=0;y<6;y++)
		for (int x=0;x<6;x++)
			map[y][x]=get_policy_value(data[y*6+x]);
}

void set_values(float **map, float *data)
{
	for (int y=0;y<6;y++)
		for (int x=0;x<6;x++)
			map[y][x]=data[y*6+x];
}

void print_map(int **map , float **V)
{
	char s[]="XswneSWNE";
	printf("\n");
	for (int y=0;y<6;y++)
	{
		for (int x=0;x<6;x++)
		{
			printf("%c",s[map[y][x]]);
		}
		printf("\t");
		for (int x=0;x<6;x++)
		{
			printf("%2.2f,",V[y][x]);
		}

		printf("\n");
	}
}
