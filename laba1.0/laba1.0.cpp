#include "pch.h"
#include "vector"
#include "math.h"
#include <iostream>
#include<thread>

//using namespace System;
using namespace std;
//using namespace System::Threading;


vector<int> fromIntToBool(int intNumber)
{
	int workNumber = intNumber, counter = 0, j = 0;

	vector<int> boolNumber, answer;

	while (workNumber != 0)
	{
		counter++;
		boolNumber.push_back(workNumber % 2);
		workNumber = workNumber / 2;
	}

	answer.resize(counter);

	for (int i = counter - 1; i >= 0; i--)
	{
		//cout<< boolNumber[j];
		answer[i] = boolNumber[j];
		j++;
	}

	if (answer.size() < 6)
	{
		int index = answer.size();
		for (int i = 0; i < 6 - index; i++)
		{
			answer.insert(answer.begin(), 0);
		}
	}
	return(answer);
}

int fromBoolToInt(vector<int> boolNumber)
{
	int answer = 0, index = 0;

	for (int i = boolNumber.size() - 1; i >= 0; i--)
	{
		if (boolNumber[index] == 1)
			answer += pow(2, i);

		index++;
	}

	return answer;
}

vector<int> boolSum(vector<int> tempFirstTerm, vector<int> tempSecondTerm)
{
	vector<int>firstTerm = tempFirstTerm, secondTerm = tempSecondTerm, answer;
	int firstTermIndex = firstTerm.size() - 1, secondTermIndex = secondTerm.size() - 1;

	if (firstTermIndex >= secondTermIndex)
	{
		while (secondTermIndex >= 0)
		{
			firstTerm[firstTermIndex] += secondTerm[secondTermIndex];
			secondTermIndex--;
			firstTermIndex--;
		}
		answer = firstTerm;
	}
	else
	{
		while (firstTermIndex >= 0)
		{
			secondTerm[secondTermIndex] += firstTerm[firstTermIndex];
			firstTermIndex--;
			secondTermIndex--;
		}
		answer = secondTerm;
	}

	int cheak = 1;
	while (cheak == 1)
	{

		cheak = 0;
		if (answer[0] == 2)
		{
			answer[0] = 0;
			answer.insert(answer.begin(), 1);
			cheak = 1;
		}

		for (int i = 1; i < answer.size(); i++)
		{
			if (answer[i] == 2)
			{
				answer[i] = 0;
				answer[i - 1] += 1;
				cheak = 1;
			}
		}

	}

	return answer;
}

vector<int> stageOfMultiplication(int stage, vector<int> firstTerm, vector<int> secondTerm, vector<int> tempAnswer)
{
	vector<int> answer = tempAnswer;
	if (firstTerm[stage - 1] == 1)
	{
		vector<int> newTerm = secondTerm;
		for (int i = 0; i < 6 - stage; i++)
			newTerm.push_back(0);
		answer = boolSum(newTerm, tempAnswer);
	}
	return answer;
}

void Stage(int stage, vector<int> firstTerm[3], vector<int>secondTerm[3], vector<int> tempAnswer[3], int change[3])
{
	if (stage <= 6)
	{
		int index = 0;
		thread newStage;
		for (int i = 0; i < 3; i++)
		{
			while (change[i] != stage)
			{

			}
			tempAnswer[i] = stageOfMultiplication(stage, firstTerm[i], secondTerm[i], tempAnswer[i]);
			change[i]++;
			if (index == 0)
			{
				newStage = thread(Stage, stage + 1, firstTerm, secondTerm, tempAnswer, change);
				index = 1;
			}
		}
		if (newStage.joinable())
		{
			newStage.join();
		}
	}
}

void main()
{
	vector<int> tempTerm[3], firstNumb[3], secondNumb[3];
	int firstIntNumb[3], secondIntNumb[3], changes[3] = { 1,1,1 };

	for (int i = 0; i < 3; i++)
		cin >> firstIntNumb[i];

	for (int i = 0; i < 3; i++)
		cin >> secondIntNumb[i];
	for (int i = 0; i < 3; i++)
	{
		firstNumb[i] = fromIntToBool(firstIntNumb[i]);
		secondNumb[i] = fromIntToBool(secondIntNumb[i]);
	}

	Stage(1, firstNumb, secondNumb, tempTerm, changes);

	for (int i = 0; i < 3; i++)
		cout << fromBoolToInt(tempTerm[i]);
}
