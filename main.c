#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "login.h"
#include "conio.h" // for getch()
#include "linkedlist.h" // for custom linked list
#include "stats.h" // statistic functions

void initList(node** list); // read in file and populate list of surveys
void save_database(node** list); // save to file before quitting
void update_survey(node* list, int pps); // update details of individual survey

void main() {
	// before doing anything, check if user is authorised
	char password[7];
	char userName[20];
	int i; // counter
	int searchPps;
	FILE* file;

	printf("Enter user name:");
	scanf("%s", userName);
	printf("Enter password: ");
	getch();
	for (i = 0; i < 6; i++) {
		password[i] = getch();
		// get character without echoing
		printf("*"); // show * for each key press
	}

	getch(); // swallow character
	printf("\n");
	if (!user_is_allowed(userName, password)) {
		printf("I'm sorry, you're not authorised. The program will now close.\n");
		exit(0); // quit the program
	}

	printf("Welcome %s", userName); // at this stage the user is authorised
	///////////////////////////////////////////////////////////////

	node* list = NULL; // empty list
	initList(&list); // load up all surveys from the file

	int choice;
	survey s; // survey that will be created and added
	do {
		printf("\nPlease Select An Option: \n");
		printf(" 1) Add a new survey.\n");
		printf(" 2) Display all surveys to screen.\n");
		printf(" 3) Display individual survey details. (enter PPS/Full Name)\n");
		printf(" 4) Update individual survey. (enter PPS)\n");
		printf(" 5) Delete survey. (enter PPS)\n");
		printf(" 6) Generate statistics.\n");
		printf(" 7) Print all surveys/stats to report.\n");
		printf("-1) Save and Quit.\n");

		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1: // add new survey
			s = create_survey(list);
			add_in_order(&list, s);
			break;
		case 2: // print all
			print_all_surveys(list, stdout);
			break;
		case 3:
			print_single_survey(list, stdout);
			break;
		case 4: // update survey
			printf("Enter PPS: ");
			scanf("%d", &searchPps);
			update_survey(list, searchPps);
			break;
		case 5: // delete survey
			printf("Enter PPS: ");
			scanf("%d", &searchPps);
			delete_survey(&list, searchPps);
			break;
		case 6: // generate stats
			print_stats(list, stdout);
			break;
		case 7: // print all to report

			file = fopen("survey-report.txt", "w");
			if (file != NULL) {
				fprintf(file, "============= SURVEYS ================\n\n");
				print_all_surveys(list, file);
				fprintf(file, "============= STATISTICS ================\n\n");
				print_stats(list, file);
				fclose(file);
				printf("Survey Report Successfully created!\n");
			} else {
				printf("There was an error creating the report.\n");
			}
			break;
		case -1:
			// save before the program closes
			save_database(&list);
			break;
		default:
			printf("Please enter a valid option! (-1 to exit)\n");
		}
	} while (choice != -1); // -1 to exit
}

void update_survey(node* list, int pps) {

	node* curr = list; // head of list
	int innerChoice;
	survey* s;

	while (curr != NULL) {
		if (curr->data.pps == pps) { // found it

			printf("\nFound %s %s\n\n", curr->data.firstName, curr->data.lastName);

			s = &curr->data; // survey we're going to change
			do {
				printf("Change What?\n");
				printf(" 1) PPS No.\n");
				printf(" 2) First Name.\n");
				printf(" 3) Last Name.\n");
				printf(" 4) Address.\n");
				printf(" 5) Email.\n");
				printf(" 6) Gender\n");
				printf(" 7) Age Bracket.\n");
				printf(" 8) Income Bracket.\n");
				printf(" 9) Exercise.\n");
				printf("10) Alcohol.\n");
				printf("11) Cigs Per Week.\n");
				printf("-1) Done editing.\n");

				scanf("%d", &innerChoice);
				switch (innerChoice) {
				case 1:
					update_pps(list, s);
					break;
				case 2:
					update_first_name(s);
					break;
				case 3:
					update_last_name(s);
					break;
				case 4:
					update_address(s);
					break;
				case 5:
					update_email(s);
					break;
				case 6:
					update_gender(s);
					break;
				case 7:
					update_age_bracket(s);
					break;
				case 8:
					update_inc_bracket(s);
					break;
				case 9:
					update_exercise(s);
					break;
				case 10:
					update_alcohol(s);
					break;
				case 11:
					update_cigs(s);
					break;
				case -1: // done editing
					break;
				}
			} while (innerChoice != -1);
			return;
		} // if found
		curr = curr->next;
	} // outer while

} //update_survey

void save_database(node** list) {
	// print all to survey file
	FILE* file = fopen("./surveys.txt", "w");
	survey s;
	node* curr = *list;
	int size = size_of(curr); // number of surveys
	int i;
	if (file == NULL) {
		printf("There was an error saving the database.");
	} else { // okay to save to the file

		node* curr = *list; // start off at the head of the list

		for (i = 0; i < size; i++) {
			s = curr->data;
			fprintf(file, "%d %s %s %s %d %d %d %d %d %d %s", s.pps, s.firstName, s.lastName,
					s.email, s.gender, s.ageBracket, s.incBracket, s.exercise, s.alcohol,
					s.cigsPerWeek, s.address);

			if (i < size - 1) { // don't print last newline character
				fprintf(file, "\n");
			}
			curr = curr->next;
		}
		printf("Successfully saved the database\n");
		fclose(file);
	}
}

void initList(node** list) {
	FILE* file; // file pointer
	char* add; // store address
	add = (char*) (malloc(sizeof(char) * 40));

	file = fopen("./surveys.txt", "r"); // open surveys in read mode
	survey s; // survey to be added

	while (!feof(file)) { // until end of file)
		fscanf(file, "%d %s %s %s %d %d %d %d %d %d ", &s.pps, s.firstName, s.lastName, s.email,
				&s.gender, &s.ageBracket, &s.incBracket, &s.exercise, &s.alcohol, &s.cigsPerWeek);

		add = fgets(add, 40, file); // read remainder of file
		strtok(add, "\n"); // remove new line char from address

		strcpy(s.address, add);
		// fill up are values from the file
		add_in_order(list, s);
		// add the struct to the list in sorted order
	}
	fclose(file); // close the file
}
