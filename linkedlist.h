typedef struct survey {
	int pps; // pps number, unique
	char firstName[20];
	char lastName[20];
	char address[40];
	char email[40];
	// answers to questions
	int gender;
	int ageBracket;
	int incBracket;
	int exercise;
	int alcohol;
	int cigsPerWeek;
} survey;

typedef struct node {
	struct survey data; // the survey
	struct node* next; // the next node
} node;

void add_to_start(node** list, node* newNode) {
	node* curr = *list; // head node
	if (curr == NULL) {
		*list = newNode;
	} else {
		newNode->next = curr;
		*list = newNode;
	}
}

void add_in_order(node** list, survey s) { // maintains sorted list;
	node* prev = NULL; // the previous node
	node* curr = *list; // start at head of list
	node* newNode; // the node we want to add
	newNode = malloc(sizeof(node));
	newNode->data = s; // survey we gave it
	newNode->next = NULL; // next one is null
	// have new node we want to add

	if (curr == NULL) {
		add_to_start(list, newNode); // make it the head of the list
	} else if (curr->next == NULL) {
		if (s.pps > curr->data.pps) { // greater than so goes after
			curr->next = newNode;
		} else { // less than so goes before
			add_to_start(list, newNode);
		}
	} else { // more than 2 elements, keep going until the end
		while (curr != NULL) { // keep going until last element
			if (s.pps < (*list)->data.pps) {
				add_to_start(list, newNode); // add to the front
				return; // exit
			}
			if (s.pps < curr->data.pps) {
				prev->next = newNode; // insert it into position
				newNode->next = curr;
				return; // exit
			}
			prev = curr;
			curr = curr->next;
			// keep progressing through thet list
		}
		// If we've gotten to end, add it as last
		prev->next = newNode;
	}
} // add_in_order

void print_survey(survey s, FILE* file) {
	fprintf(file, "======================================\n");
	fprintf(file, "PPS No: %d\n", s.pps);
	fprintf(file, "Name: %s %s\n", s.firstName, s.lastName);
	fprintf(file, "Address: %s\n", s.address);
	fprintf(file, "Email: %s\n", s.email);

	fprintf(file, "Gender: ");
	switch (s.gender) {
	case 1:
		fprintf(file, "Male\n");
		break;
	case 2:
		fprintf(file, "Female\n");
		break;
	}

	fprintf(file, "Age Bracket: ");
	switch (s.ageBracket) {
	case 1:
		fprintf(file, "18 - 20 years old\n");
		break;
	case 2:
		fprintf(file, "20 - 30 years old\n");
		break;
	case 3:
		fprintf(file, "30 - 50 years old\n");
		break;
	case 4:
		fprintf(file, "50 - 65 years old\n");
		break;
	case 5:
		fprintf(file, "65+ years old\n");
		break;
	default:
		fprintf(file, "Invalid Option\n");
		break;
	}

	fprintf(file, "Income Bracket: ");
	switch (s.incBracket) {
	case 1:
		fprintf(file, "No income\n");
		break;
	case 2:
		fprintf(file, "Less than €20,000\n");
		break;
	case 3:
		fprintf(file, "Less than €40,000\n");
		break;
	case 4:
		fprintf(file, "Less than €60,000\n");
		break;
	case 5:
		fprintf(file, "Less than €80,000\n");
		break;
	case 6:
		fprintf(file, "Less than €100,000\n");
		break;
	case 7:
		fprintf(file, "More than €100,000\n");
		break;
	default:
		fprintf(file, "Invalid Option\n");
		break;
	}

	fprintf(file, "Exercise Amount: ");
	switch (s.exercise) {
	case 1:
		fprintf(file, "Never\n");
		break;
	case 2:
		fprintf(file, "Less than three times per week\n");
		break;
	case 3:
		fprintf(file, "Less than five times per week\n");
		break;
	case 4:
		fprintf(file, "More than five times per week\n");
		break;
	default:
		fprintf(file, "Invalid Option\n");
		break;

	}

	fprintf(file, "Alcohol consumption: ");
	switch (s.alcohol) {
	case 1:
		fprintf(file, "None\n");
		break;
	case 2:
		fprintf(file, "Less than 2 units\n");
		break;
	case 3:
		fprintf(file, "Less than 4 units\n");
		break;
	case 4:
		fprintf(file, "More than 4 units\n");
		break;
	default:
		fprintf(file, "Invalid Option\n");
		break;
	}

	fprintf(file, "Cigarettes per week: ");
	switch (s.cigsPerWeek) {
	case 1:
		fprintf(file, "None\n");
		break;
	case 2:
		fprintf(file, "Less than 20\n");
		break;
	case 3:
		fprintf(file, "Less than 40\n");
		break;
	case 4:
		fprintf(file, "More than 40\n");
		break;
	default:
		fprintf(file, "Invalid Option\n");
		break;
	}
	fprintf(file, "\n");
}

void print_single_survey(node* list, FILE* file) {
	char* searchTerm;
	searchTerm = (char*) malloc(sizeof(char) * 50);
	char ppsAsString[20];
	char fullName[50];
	int found = 0;

	printf("Enter pps or name to search for: ");
	getch();
	searchTerm = fgets(searchTerm, 50, stdin);
	strtok(searchTerm, "\n"); // remove new line char from string

	node* curr = list; // head node
	while (curr != NULL) {
		survey s = curr->data;

		sprintf(ppsAsString, "%d", s.pps); // convert pps to string for string comparison
		strcpy(fullName, s.firstName);
		strcat(fullName, " ");
		strcat(fullName, s.lastName);
		// build full name as string to search for

		if (strcmp(ppsAsString, searchTerm) == 0 // if pss is what we're looking for
		|| strcmp(fullName, searchTerm) == 0) { // if name is what we're looking for
			print_survey(s, file); // print it
			found++;
		}
		curr = curr->next;
	}

	if (found == 0) {
		printf("Sorry, that survey doesn't exist!\n");
	}

}

void print_all_surveys(node* list, FILE* file) {
	node* curr = list; // head of list
	survey s;
	while (curr != NULL) {
		s = curr->data; // the current survey
		print_survey(s, file);
		curr = curr->next; // move onto next survey
	}
}

bool validate_pps(node* list, int pps) {
	if (pps < 0) {
		return false; // no negative numbers allowed
	}

	node* curr = list; // start at the head of the list
	while (curr != NULL) {
		if (curr->data.pps == pps) {
			return false; // the number is already used
		}
		curr = curr->next;
	}
	return true; // not used, so valid
}

void update_pps(node* list, survey* s) {
	do {
		printf("Enter unique PPS number: "); // validate
		scanf("%d", &s->pps);
	} while (!validate_pps(list, s->pps));
	// keep prompting for pps until they enter a valid value
	//return s;
}

void update_first_name(survey* s) {
	char fName[20];
	printf("Enter First Name: ");
	scanf("%s", fName);
	strcpy(s->firstName, fName);

}

void update_last_name(survey* s) {
	char lName[20];
	printf("Enter Last Name: ");
	scanf("%s", lName);
	strcpy(s->lastName, lName);
}

void update_address(survey* s) {
	char* address;
	address = (char*) (malloc(sizeof(char) * 40));
	printf("Enter Address: ");
	getch();
	address = fgets(address, 40, stdin); // read full line
	strtok(address, "\n"); // remove end of line
	strcpy(s->address, address);
}

void update_email(survey* s) {
	char email[40];
	do {
		printf("Enter Email (must have a '.', a '@' and a '.com'): ");
		scanf("%s", email); // validate
	} while (strchr(email, '@') == NULL // no @
	|| strchr(email, '.') == NULL // no .
	|| strstr(email, ".com") == NULL); // no .com);
	strcpy(s->email, email);
}

void update_gender(survey* s) {
	do {
		printf("Enter gender: \n");
		printf("1) Male\n");
		printf("2) Female\n");
		scanf("%d", &s->gender);
	} while (s->gender != 2 && s->gender != 1);
}

void update_age_bracket(survey* s) {
	// keep prompting until they enter valid email
	do {
		printf("Enter Age Bracket (1-5): \n");
		printf("1) 18 - 20 years old\n");
		printf("2) 20 - 30 years old\n");
		printf("3) 30 - 50 years old\n");
		printf("4) 50 - 65 years old\n");
		printf("5) 65+ years old\n");
		scanf("%d", &s->ageBracket); // choice for age bracket
	} while (s->ageBracket < 1 || s->ageBracket > 5);

}

void update_inc_bracket(survey* s) {
	do {
		printf("Enter Income Bracket (1-7): \n");
		printf("1) No income\n");
		printf("2) Less than €20,000\n");
		printf("3) Less than €40,000\n");
		printf("4) Less than €60,000\n");
		printf("5) Less than €80,000\n");
		printf("6) Less than €100,000\n");
		printf("7) More than €100,000\n");
		scanf("%d", &s->incBracket);
	} while (s->incBracket < 1 || s->incBracket > 7);
}

void update_exercise(survey* s) {
	do {
		printf("How often do you exercise: \n");
		printf("1) Never\n");
		printf("2) Less	than three times per week\n");
		printf("3) Less than five times per week\n");
		printf("4) More than five times per week\n");
		scanf("%d", &s->exercise);
	} while (s->exercise < 1 || s->exercise > 4);
}

void update_alcohol(survey* s) {
	do {
		printf("How much alcohol do you consume per week: \n");
		printf("1) None\n");
		printf("2) Less than 2 units\n");
		printf("3) Less than 4 units\n");
		printf("4) More than 4 units\n");
		scanf("%d", &s->alcohol);
	} while (s->alcohol < 1 || s->alcohol > 4);
}

void update_cigs(survey* s) {
	do {
		printf("How may cigarettes do you smoke per week: \n");
		printf("1) None\n");
		printf("2) Less than 20\n");
		printf("3) Less than 40\n");
		printf("4) More than 40\n");
		scanf("%d", &s->cigsPerWeek);
	} while (s->cigsPerWeek < 1 || s->cigsPerWeek > 4);
}

survey create_survey(node* list) {
	survey s; // new survey to be created
	update_pps(list, &s);
	update_first_name(&s);
	update_last_name(&s);
	update_address(&s);
	update_email(&s);
	update_gender(&s);
	update_age_bracket(&s);
	update_inc_bracket(&s);
	update_exercise(&s);
	update_alcohol(&s);
	update_cigs(&s);
	return s; // final survey
}

void delete_survey(node** list, int pps) {
	node* curr = *list; // head of the list
	node* prev = NULL;
	node* temp;

	while (curr != NULL) {
		if (curr->data.pps == pps) {

			if (prev == NULL) {
				// then we're at the head node
				*list = curr->next; // head is now the second element
				free(curr); // free memory
				printf("Deleted %s %s.\n", curr->data.firstName, curr->data.lastName);
				return;
			}

			// found the one we want to delete
			temp = curr;
			prev->next = curr->next;
			free(temp);
			printf("Deleted %s %s.\n", curr->data.firstName, curr->data.lastName);
			return;
		}

		prev = curr;
		curr = curr->next;
	}
	printf("%d couldn't be found.\n", pps);
}

int size_of(node* list) {
	// give back the size of the list
	int size = 0;
	node* curr = list;
	while (curr != NULL) {
		size++;
		curr = curr->next;
	}
	return size;
}
