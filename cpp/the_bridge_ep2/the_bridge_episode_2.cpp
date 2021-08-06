#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// Structure containing necessary information
 struct info{
    int x; 
    vector<int>y;
    int speed;
 };

string::size_type lastHole; // Coordinates of the last hole

int V; // the minimum amount of motorbikes that must survive

vector<string> lanes; // vector containing all the lanes

/**
* @brief Function using a Depth-First Search (dfs) algorithm for every possibility
* @param bikes[IN]:  
* @return a pair containg the number of vehicle still alive and the command to execute
* @remark The "WAIT" command is not included because it could be replaced by a "JUMP" in our case
* Every processing of the commands is contains in a block to avoid stack overuse
**/
pair<int, string>  dfs(struct info& bikes) {

    // If the end is reached or the bikes don't move we have to speed up
    if(bikes.x > lastHole || bikes.speed == 0) {
        return pair<int, string>(bikes.y.size(), "SPEED");
    }

    pair<int, string> resultTemp ;
    pair<int, string> result(0, "JUMP");


    // Check if we SPEED
    {
        info speedUp = bikes;
        speedUp.speed += 1;
        speedUp.x += speedUp.speed;
        
        // For every bike we will check if it will fall in a hole
        for(auto vehicle: bikes.y) {
            for(int i = bikes.x + 1; i <= speedUp.x; i++) {
                // erase the vehicle if in a hole
                if (lanes[vehicle][i] == '0') {

                    speedUp.y.erase(find(speedUp.y.begin(), speedUp.y.end(), vehicle));
                    break;
                }
            }
        }

        // Check if we have always a number of bike sufficient
        if(speedUp.y.size() >= V) {

            resultTemp = dfs(speedUp);

            // If we didn't lose a bike we can return
            if(resultTemp.first == bikes.y.size()) {
                return {resultTemp.first, "SPEED"};
            }
            // Save the result
            result = {resultTemp.first, "SPEED"};
        }
    }

    // Check if JUMP
    {
        info jump = bikes;
        jump.x+= bikes.speed;

        // For every bike, we check if after a jump the bike falls into a hole
        for(auto vehicle: bikes.y) {

            // erase the vehicle if in a hole
            if (lanes[vehicle][jump.x] == '0') {
                    jump.y.erase(find(jump.y.begin(), jump.y.end(), vehicle));
            }            
        }
        

        if (jump.y.size() >= V) {
            resultTemp = dfs(jump);

            if(resultTemp.first == bikes.y.size()) {
                return {resultTemp.first, "JUMP"};
            }

            if(resultTemp.first > result.first) {
                result = {resultTemp.first, "JUMP"};
            }
        }
    }

    // Check if we UP
    {
        info up = bikes;
        vector<int> newPosition;
        up.x+= bikes.speed;

        // For every bike, we will the actual lane and the upper lane
        for(auto moto: bikes.y) {
            bool motoDestroyed = false;

            // erase the moto if out boundaries
            if (moto - 1 < 0) {
                    motoDestroyed = true;

            } else {
                for(int i = bikes.x + 1; i <= up.x - 1; i++) {
                    // erase the vehicle if in a hole
                    if (lanes[moto][i] == '0' || lanes[moto-1][i] == '0') {
                        motoDestroyed = true;
                        break;
                    }
                }

                if(lanes[moto-1][up.x] == '0') {
                    motoDestroyed = true;
                }
        
            }

            if(!motoDestroyed) {
                newPosition.push_back(moto - 1); // modify the position of the moto 
            }             
        }

        if (newPosition.size() >= V) {
            // Save the new position of the bikes
            up.y = newPosition;
            
            resultTemp = dfs(up);

            if(resultTemp.first == bikes.y.size()) {
                return {resultTemp.first, "UP"};
            }

            if( resultTemp.first > result.first) {
                result = {resultTemp.first, "UP"};
            }
        }
    }

    // Check if we DOWN
    {
        info down = bikes;
        vector<int> newDown;
        down.x+= bikes.speed;
        // For every bike we will check the actual lane and the lower lane
        for(auto moto: bikes.y) {
            bool motoDestroyed = false;

            // erase the moto if out boundaries
            if (moto + 1 > 3) {
                    motoDestroyed = true;

            } else {
                for(int i = bikes.x + 1; i <= down.x - 1; i++) {
                    // erase the vehicle if in a hole
                    if (lanes[moto][i] == '0' || lanes[moto+1][i] == '0') {
                        motoDestroyed = true;
                        break;
                    }
                }

                if(lanes[moto+1][down.x] == '0') {
                    motoDestroyed = true;
                }
        
            }

            if(!motoDestroyed) {
                newDown.push_back(moto + 1); // modify the position of the moto 
            }             
        }
        
        if (newDown.size() >= V) {
            // Save the new position of the bikes
            down.y = newDown;
            resultTemp = dfs(down);

            if(resultTemp.first == bikes.y.size()) {
                return {resultTemp.first, "DOWN"};
            }

            if(resultTemp.first > result.first) {
                result = {resultTemp.first, "DOWN"};
            }
        }
    }

    // Check if we SLOW
    {
        if(bikes.speed > 1) {
            info speedSlow = bikes;
            speedSlow.speed -= 1;
            speedSlow.x += speedSlow.speed;
            
            for(auto vehicle: bikes.y) {
                for(int i = bikes.x + 1; i <= speedSlow.x; i++) {
                    // erase the vehicle if in a hole
                    if (lanes[vehicle][i] == '0') {

                        speedSlow.y.erase(find(speedSlow.y.begin(), speedSlow.y.end(), vehicle));
                        break;
                    }
                }
            }


            if(speedSlow.y.size() >= V) {
                resultTemp = dfs(speedSlow);

                if(resultTemp.first == bikes.y.size()) {
                    return {resultTemp.first, "SLOW"};
                }

                if(resultTemp.first > result.first) {
                    result = {resultTemp.first, "SLOW"};
                }
            }
        }
    }

    return result;

}

int main()
{
    int M; // the amount of motorbikes to control
    cin >> M; cin.ignore();
    cin >> V; cin.ignore();
    string L0; // L0 to L3 are lanes of the road. A dot character . represents a safe space, a zero 0 represents a hole in the road.
    cin >> L0; cin.ignore();
    lanes.push_back(L0);
    string L1;
    cin >> L1; cin.ignore();
    lanes.push_back(L1);
    string L2;
    cin >> L2; cin.ignore();
    lanes.push_back(L2);
    string L3;
    cin >> L3; cin.ignore();
    lanes.push_back(L3);
    lastHole = 0;

    cerr << L0 << endl;
    cerr << L1 << endl;
    cerr << L2 << endl;
    cerr << L3 << endl;

    lastHole = max(lastHole, (L0.find_last_of('0') == string::npos)? 0 : L0.find_last_of('0')); 
    lastHole = max(lastHole, (L1.find_last_of('0') == string::npos)? 0 : L1.find_last_of('0')); 
    lastHole = max(lastHole, (L2.find_last_of('0') == string::npos)? 0 : L2.find_last_of('0'));
    lastHole = max(lastHole, (L3.find_last_of('0') == string::npos)? 0 : L3.find_last_of('0'));


    // game loop
    while (1) {
        struct info infoInit;
        int S; // the motorbikes' speed
        cin >> S; cin.ignore();
        infoInit.speed = S;

        for (int i = 0; i < M; i++) {
            int X; // x coordinate of the motorbike
            int Y; // y coordinate of the motorbike
            int A; // indicates whether the motorbike is activated "1" or detroyed "0"
            cin >> X >> Y >> A; cin.ignore();
            if (A == 1) {
                infoInit.x = X;
                infoInit.y.push_back(Y);
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // A single line containing one of 6 keywords: SPEED, SLOW, JUMP, WAIT, UP, DOWN.
        cout << dfs(infoInit).second << endl;
    }
}
