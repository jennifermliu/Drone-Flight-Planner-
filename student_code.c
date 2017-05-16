// determine if the new location will be in a 6x6 map
bool validmove(int y, int x)
{
    if(x<6 && x>-1 && y<6 &&y>-1)
    {
        return true;
    }
    return false;
}


// convert to the valid coordinate
int convert(int x_or_y)
{
    if(x_or_y>5)
    {
        return 5;
    }
    else if(x_or_y<0)
    {
        return 0;
    }
    else
    {
        return x_or_y;
    }
}

// determine if there is a rival at this location
bool rival(int y, int x, int **map)
{
    if(map[y][x]==3)
    {
        return true;
    }
    return false;
}

// calculate for expected utility for each possible action
float expected_utility(int possible_action,int y, int x, float **values, float gamma, float battery_drop_cost)
{
    float utility=0;
    switch (possible_action) {
        // the first 4 cases are when propulsion is OFF
        case 1:
        utility = values[convert(y+1)][x]*0.7+values[y][convert(x-1)]*0.15+values[y][convert(x+1)]*0.15;
        break;
        
        case 2:
        utility = values[y][convert(x-1)]*0.7+values[convert(y-1)][x]*0.15+values[convert(y+1)][x]*0.15;
        break;
        
        case 3:
        utility = values[convert(y-1)][x]*0.7+values[y][convert(x-1)]*0.15+values[y][convert(x+1)]*0.15;
        break;
        
        case 4:
        utility = values[y][convert(x+1)]*0.7+values[convert(y-1)][x]*0.15+values[convert(y+1)][x]*0.15;
        break;
        
        // the next 4 cases are when propulsion is ON
        case 5:
        utility = values[convert(y+1)][x]*0.8+values[y][convert(x-1)]*0.1+values[y][convert(x+1)]*0.1;
        break;
        
        case 6:
        utility = values[y][convert(x-1)]*0.8+values[convert(y-1)][x]*0.1+values[convert(y+1)][x]*0.1;
        break;
        
        case 7:
        utility = values[convert(y-1)][x]*0.8+values[y][convert(x-1)]*0.1+values[y][convert(x+1)]*0.1;
        break;
        
        case 8:
        utility = values[y][convert(x+1)]*0.8+values[convert(y-1)][x]*0.1+values[convert(y+1)][x]*0.1;
        break;
        
        
        // default shouldn't be called
        default:
        utility = values[y][x];
        break;
    }
//    printf("utility at map[%d][%d] is %f", y,x,utility);
    
    float living_cost = battery_drop_cost;
    
    // if propulsion OFF, twice living cost
    if(possible_action>4)
    {
        living_cost=2*living_cost;
    }
    
    //original utility value times (1-discount_per_cycle)- the cost to live
    utility = utility*gamma-living_cost;
    
    return utility;
    
}




float drone_flight_planner (int **map, int **policies, float **values, float delivery_fee, float battery_drop_cost, float dronerepair_cost, float discount_per_cycle)
{
    
    // PUT YOUR CODE HERE
    // access the map using "map[y][x]"
    // access the policies using "policies[y][x]"
    // access the values using "values[y][x]"
    // y between 0 and 5
    // x between 0 and 5
    // function must return the value of the cell corresponding to the starting position of the drone
    //
    
    
    //determine where the customer and the shop are located
    int customer_x=-1;
    int customer_y=-1;
    int shop_x=-1;
    int shop_y=-1;
    
    
    
//    printf("discount_per_cycle is: %f \n", discount_per_cycle);
    float gamma = 1-discount_per_cycle;
    
    
    for(int y = 0; y<6; y++)
    {
        for(int x = 0; x<6; x++)
        {
            if(map[y][x]==2)
            {
                values[y][x] = delivery_fee;
                customer_y=y;
                customer_x=x;
//                printf("customer at this location: [%d][%d] \n", y,x);
//                printf("utility of customer at location[%d][%d] is %f \n", y,x,values[y][x]);

            }
            else if(map[y][x]==3)
            {
                values[y][x]= -dronerepair_cost;
//                printf("repair cost is %f \n", dronerepair_cost);
//                printf("enemy at this location: [%d][%d] \n", y,x);
//                printf("utility of enemy at location[%d][%d] is %f \n", y,x,values[y][x]);
                
            }
            else if(map[y][x]==1)
            {
                shop_y=y;
                shop_x=x;
//                printf("pizza shop at this location: [%d][%d] \n", y,x);
            }
        }
    }
    
    // initilialize a 3d array to record utility after given action
    float Q[9][6][6];
    for(int a=0; a<9; a++)
    {
        for(int y = 0; y<6; y++)
        {
            for(int x = 0; x<6; x++)
            {
                Q[a][y][x]=0.0;
//                printf("Q[%d][%d][%d]: %f", a, y, x, Q[a][y][x] );
            }
        }
    }
    
    
    
    bool convergence = false;
    
    float threshold=0.0001;
//    printf("threshold is %f \n", threshold);
    
    
    while(!convergence)
    {
        
        for(int y = 0; y<6; y++)
        {
            for(int x = 0; x<6; x++)
            {
                // if the current location is not pizza shop or rival
                if(map[y][x]<2)
                {
                    for(int a=1; a<9; a++)
                    {
                        Q[a][y][x]= expected_utility(a,y,x,values,gamma,battery_drop_cost);
                    }
                }
            }
        }
        
        
        float accum=0;
        
        
        for(int y = 0; y<6; y++)
        {
            for(int x = 0; x<6; x++)
            {
                
                if(map[y][x]<2)
                {
                    // find the action with the maximum utility
                    float bv=Q[1][y][x];
                    int bp=1;
                    
                    for(int i=2; i<9; i++)
                    {
                        if(bv<Q[i][y][x])
                        {
                            bv=Q[i][y][x];
                            bp=i;
                        }
                    }
                    
                    // find absolute value of the difference then add to accum
                    if((values[y][x]-bv)<0)
                    {
                        accum=accum-(values[y][x]-bv);
                    }
                    else
                    {
                        accum=accum+values[y][x]-bv;
                    }
                    // update the V and P at this location
                    values[y][x]=bv;
                    policies[y][x]=bp;
                    
//                    printf("accum is %f at map[%d][%d]: ", accum, y,x);
                }
            }
        }
        
        
        // if the sum of differences for all is lower than threshold, exit while loop
        if(accum<threshold)
        {
            convergence=true;
        }
        
    }
    
//    printf("value at map[%d][%d] is %f \n", shop_y,shop_x,values[shop_y][shop_x]);
    return values[shop_y][shop_x];
}
