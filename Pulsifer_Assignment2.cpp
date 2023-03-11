// Name: Talia Pulsifer
// Date: 02-21-23
//Collaborators: Zoe

#include <iostream>
#include<ctype.h>
using namespace std;

//Name: Robot
//Parameters: N/A 
//Side Effects: N/A
//Create a struct robot that holds all necessary identifiers
struct Robot {
	string name;
	int currentX;
	int currentY;
	int distanceTraveled;
	int currentSpeed;
	char lastCommand;
	Robot() {
		currentX = 0;
		currentY = 0;
		currentSpeed = 0;
		distanceTraveled = 0;
		lastCommand = 'Z';
	}
};

//Name: findRobot
//Parameters: Array of Robots pointers robotList[], unique identifier name, size of array
//Side Effects: N/A should not cause any side effects
//Create a function findRobot that given a list of robots and an identifier, you find and 
// return the index of the target robot.
int findRobot(Robot** robotList, string name, int size) {
	//Use sequential search to find the Robot in the unordered array
	for (int i = 0; i < size; i++) {
		if (robotList[i]->name == name) {
			return i;
		}
	}
	return -1;
}

//Name:moveRobot
//Parameters:A Robot pointer, char direction the direction that you want to move in
//Side Effects: Always updates the position of target robot and total distance traveled, sometimes update the speed
//Create a function moveRobot that updates the position of the specified robot by current speed.
void moveRobot(Robot* robot, char direction) {
	//If this command is the same as the last command, speed increases

	if (toupper(direction) == toupper(robot->lastCommand) && robot->currentSpeed <= 4) {
		robot->currentSpeed += 1;
	}
	else {
		robot->currentSpeed = 1;
	}
	switch (toupper(direction)) {
		//Check the command and move accordingly
	case 'U':
		robot->currentY += robot->currentSpeed;
		break;
	case 'D':
		robot->currentY -= robot->currentSpeed;
		break;
	case 'L':
		robot->currentX -= robot->currentSpeed;
		break;
	case 'R':
		robot->currentX += robot->currentSpeed;
		break;
	default:
		cout << "Sorry, that was an invalid direction. Please try again" << endl;
	}
	//Update the distance traveled based on speed
	robot->distanceTraveled += robot->currentSpeed;
	//update lastcommand for the robot
	robot->lastCommand = direction;
	//Print Robot's location (X, Y)
	cout << robot->name << "'s current position is: " << "(" << robot->currentX << "," << robot->currentY << ")" << endl;
}

void sortRobotList(Robot** robotList, int arraySize) {
	//Sort array of Robots using selection sort
	for (int i = 0; i < arraySize; i++) {
		Robot* smallestValue = robotList[i];
		for (int j = 0; j < arraySize; j++) {
			if (robotList[j]->distanceTraveled < smallestValue->distanceTraveled) {
				smallestValue = robotList[j];
			}
		}
		//Swap values
		if (smallestValue->distanceTraveled != i) {
			Robot* temp = robotList[i];
			robotList[i] = smallestValue;
			smallestValue = temp;

		}
	}
}

Robot** makeRobotList(int numRobos) {
	Robot** robotList = new Robot*[numRobos];
	for (int i = 0; i < numRobos; i++) {
		robotList[i] = new Robot;
	}
	return robotList;
}

int main()
{
	//declare all the variables needed
	char command;
	char direction;
	bool running = true;
	bool moving = true;
	int arraySize;
	int robotIndex;
	string robotIdentifier;
	//User enters the # of robots that they will name
	cout << "Please enter a size: " << endl;
	cin >> arraySize;
	//Create an array with the same size as the user entered
	//Robot** robotList[] = makeRobotList(arraySize);
	//Robot* robotList = new Robot[arraySize];
	Robot** robotList = makeRobotList(arraySize);
	//For each Robot in the array, the user enters a name. 
	cout << "Please enter " << arraySize << " names." << endl;
	for (int i = 0; i < arraySize; i++) {
		string robotName;
		cin >> robotName;
		robotList[i]->name = robotName;
	}

	//Check that all names are added to list
	//for (int k = 0; k < arraySize; k++) {
	//	cout << robotList[k].name << endl;
	//}

	//While the user has not entered Q
	while (running) {
		//Display main Menu
		cout << "M - Move a Robot" << endl
			<< "D - Print all Robots and their distances" << endl
			<< "Q - Quit the program" << endl;
		cin >> command;
		//Change command to upper case before comparing
		switch (toupper(command)) {
		case 'M':
			//Find the Robot that the user wants to move
			cout << "You want to move a Robot! Which Robot would you like to move?" << endl;
			cin >> robotIdentifier;
			//set the index that is returned from findRobot to a variable
			robotIndex = findRobot(robotList, robotIdentifier, arraySize);
			//If the robot is not found
			if (robotIndex == -1) {
				cout << "Sorry! That Robot wasn't found. Please try again." << endl;
				break;
			}
			//If the robot is found
			else {
				//While the user wants to move display the movement options
				cout << "Great! We are moving the Robot " << robotIdentifier << endl;
				//Displaying the current pos for the target robot
				cout << robotList[robotIndex]->name << "'s current position is "
					<< "(" << robotList[robotIndex]->currentX << ","
					<< robotList[robotIndex]->currentY << ")" << endl;
				//Menu for moving the robot
				cout << "Here are your options to move the Robot: " << endl
					<< "U - Move the Robot up" << endl
					<< "D - Move the Robot down" << endl
					<< "L - Move the Robot left" << endl
					<< "R - Move the Robot right" << endl
					<< "Which direction would you like to move?" << endl;
				cin >> direction;
				//Move robot with the direction provided by user
				moveRobot(robotList[robotIndex], direction);
				//moveRobot(robotList+robotIndex, direction);

				break;
			}
		case 'D':
			//for each robot in the array, print the robot name and the distance it has traveled
			//Sort robotList first
			sortRobotList(robotList, arraySize);
			for (int j = 0; j < arraySize; j++) {
				cout << robotList[j]->name << " " << robotList[j]->distanceTraveled << endl;
			}
			break;
		case 'Q':
			running = false;
			cout << "Thanks for playing, bye!" << endl;
			break;
		default:
			cout << "Sorry, that was an invalid command" << endl;
		}
	}
	//Have to delete when using keyword 'new'
	delete[] robotList;
	//Main always returns 0
	return 0;
}

// :)