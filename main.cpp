/**
 * Program editted with known values
 * User input omitted for this program
**/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>

using std::cout;
using std::cin;
using std::string;
using std::endl;

struct Shooter{
  bool alive;
	int accuracy,	//use int because i'm lazy 
		kills;
	Shooter();
	~Shooter();
};
Shooter::Shooter():
	alive(true),
	accuracy(0),
	kills(0)
{} //Handle accuracy setting in main
Shooter::~Shooter(){}
	//Duel between two shooters
bool duel(Shooter& first, Shooter& target){
	int	
			//Magic number that determines if target is dead
		chance = rand()%100 + 1,
			//Create arbitrary range based on accuracy
		range_max = rand()%100 + 1 + first.accuracy/2,
		range_min = rand()%100 + 1 - first.accuracy/2
	;
		//Check if the range is beyond the 1-100 block
	if(range_max > 100){
		range_max = 100;
		range_min = 100 - first.accuracy;
	}else if(range_max < 0){
		range_max = first.accuracy;
		range_min = 0;
	}else if(range_min < 0){
		range_max = first.accuracy;
		range_min = 0;
	}else if(range_min > 100){
		range_max = 100;
		range_min = 100 - first.accuracy;
	}
		//if chance is within range, target is dead
	if(
		chance >= range_min && 
		chance <= range_max
	){
		target.alive = false;
		first.kills++;
		return true;
	}
		//shooter missed
	return false;
}
	//central function for getting user input to modify number variables
void PromptUserFor(int& tomodify, const string& name, int limit = std::numeric_limits<int>::max()){
	cout << "Please enter in the new " << name << ": ";
	while(!(cin >> tomodify) || tomodify <= 0 || tomodify > limit){
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(),'\n');
		cout << "Enter in a new value: ";
	}
	cout << endl;
}

int main(int argc, char **argv){
	int 
		initial_population(100),
		runs(1e6),
		current_population
	;
		//Have user set up initial values
//	PromptUserFor(initial_population, "Initial Population");
		current_population = initial_population;
//	PromptUserFor(runs, "Number of Runs");
		//Create number of shooters based on user input
	Shooter* person = new Shooter[initial_population];
		//Set up shooter accuracies
	for(int i = 0; i < initial_population; i++)
		cout << "New accuracy: " << (person[i].accuracy = 100-i) << endl;
//		PromptUserFor(person[i].accuracy, "Accuracy of Next Shooter", 100);
		//Start the shoot off
	cout << "Thank you for the information! Please wait while the shooters kill each other..." << endl;
		//Go through number of runs
	for(int run_ = 0; run_ < runs; run_++){
		while(current_population > 1){
					//Pick shooter
			for(int currentshooter = 0; currentshooter < initial_population; currentshooter++){
				if(! person[currentshooter].alive )	continue;	//dead people not allowed to shoot
				//Pick target
				for(int currenttarget = 0; currenttarget < initial_population; currenttarget++){
					if(
						currentshooter == currenttarget ||
						! person[currenttarget].alive
					)	continue;	//avoid shooting himself or shooting corpses
						//The actual shot; no boom sound effects :(
						//Did shooter hit?
//					cout << "PEW ";
					if( duel(person[currentshooter],person[currenttarget]) )
						current_population--;
				}
			}
		}
			//reset alive bools
		for(int I = 0; I < initial_population; I++)
			person[I].alive = true;
		current_population = initial_population;
	}
		//Display number of kills
	cout << endl << "\n\nAll finished killing shooters!" << endl;
	for(int i = 0; i < initial_population; i++){
		cout << "Shooter " << i+1 << " has " << person[i].kills << " kills"
			<< " with a win percentage of "
			<< (double(person[i].kills)/(runs*(initial_population-1)))*100
			<< "%.\n";
	}
	cout << endl;
		//Clean up
	delete[] person;
	return 0;
}
