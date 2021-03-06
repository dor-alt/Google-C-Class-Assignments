﻿// oop_database_composers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "database.h"
#include "composer.h"

using namespace std;

void addComposer(Database &myDB) {
	string in_first_name, in_last_name, in_genre, in_fact;
	int in_yob;
	cout << "Please write the following details for the composer to add: " << endl;
	cout << "First name" << endl;
	cin >> in_first_name;
	cout << "Last name" << endl;
	cin >> in_last_name;
	cout << "Genere" << endl;
	cin >> in_genre;
	cout << "Year of birth" << endl;
	cin >> in_yob;
	cout << "Some fact" << endl;
	cin >> in_fact;

	shared_ptr<Composer> newComposer = myDB.AddComposer(in_first_name, in_last_name, in_genre, in_yob, in_fact);
}

void getComposer(Database &myDB) {
	string composer_last_name;
	cout << "What is the composer's last name to search? " << endl;
	cin >> composer_last_name;
	auto ret = myDB.GetComposer(composer_last_name);
	if (ret == nullptr) {
		cout << "We didn't find this composer in the DB" << endl;
	}

}


void promoteDemote(Database &myDB) {
	int index;
	int promote_demote;
	int new_value;
	cout << "Enter the index in the DB of the required composer to promote/demote or -1 to return to main menu" << endl;
	cin >> index;
	if (index == -1)
		return;
	auto ret = myDB.GetComposerByIndex(index);
	if (ret == nullptr) {
		cout << "The index entered wasn't referencing to any composer! " << endl;
		return;
	}
	cout << "Composer " << ret->get_first_name() << " " << ret->get_last_name() << " was chosen" << endl;
	cout << "Do you want to promote or demote the composer? Enter 1 or 2" << endl;
	cout << "Promote - 1" << endl;
	cout << "Demote - 2" << endl;
	cin >> promote_demote;
	cout << "By how much? " << endl;
	cin >> new_value;
	if (promote_demote == 1) {
		ret->Promote(new_value);
		return;
	}
	ret->Demote(new_value);
}

void deleteLastComposer(Database &myDB) {
	myDB.deleteLastComposer();
}

int ui() {
	Database myDB;

	while (true) {
		int chosen;
		cout << "Choose a task" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "1) Add a new composer" << endl;
		cout << "2) Retrieve a composer's data" << endl;
		cout << "3) Promote/demote a composer's rank" << endl;
		cout << "4) List all composers" << endl;
		cout << "5) List all composers by rank" << endl;
		cout << "0) Quit" << endl;
		cin >> chosen;
		if (cin.fail()) {
			cout << "Only digits please!" << endl;
			cin.clear();
			cin.ignore();
			continue;
		}
		switch (chosen)
		{
		case 1: {
			addComposer(myDB);
			continue; 
			}
		case 2: {
			getComposer(myDB);
			continue;
			}
		case 3: {
			promoteDemote(myDB);
			continue; 
		}
		case 4:
			myDB.DisplayAll();
			continue;
		case 5:
			myDB.DisplayByRank();
			continue;
		case 0:
			cout << "Bye Bye!" << endl;
			return 0;
		default:
			break;
		}
	}

}



int main()
{


	cout << "Welcome to the Composers Databse" << endl;
	
	//ui();
	
	Database myDB;
	shared_ptr<Composer> c = myDB.AddComposer("Ludwig van", "Beethoven", "Romantic", 1770,
		"Beethoven was completely deaf during the latter part of his life - he never ");
	shared_ptr<Composer> d = myDB.AddComposer("dor", "alt", "Metal", 2015,
		"Metal bring people together :) ");
	shared_ptr<Composer> e = myDB.AddComposer("aaaa", "bbbb", "Romantic", 1770,
		"Beethoven was completely deaf during the latter part of his life - he never ");

	myDB.GetTotalComposers();

	myDB.deleteLastComposer();
	//call destructor. try from private total ocmposers as well
	

	d->set_ranking(5);
	c->set_ranking(10);

	myDB.DisplayByRank();
	
	shared_ptr<Composer> found = myDB.GetComposer("alt");
	if (found == nullptr)
		cout << "we didn't find this composer in the DB" << endl;

 	cout << "program finished" << endl;

}

