// 3 different stats we want
# define SMOKE 1
# define EXERCISE 2
# define ALCOHOL 3

# define INCOME 1
# define AGE 2
# define GENDER 3

float track_stat(node* list, int bracketType, int bracket, int category, int from, int to) {
// from and to are the choices in the survey, they vary based on category

	float totalPercent = 0;
	node* curr = list; // start at head of the list
	survey s;
	int surveysInBracket = 0;
	int inThisCategory = 0;

	while (curr != NULL) {
		s = curr->data; // current survey

		if (bracketType == AGE) {
			if (s.ageBracket == bracket) {
				// this survey is valid for this particular category
				surveysInBracket++;

				switch (category) {
				case SMOKE:
					if (s.cigsPerWeek >= from && s.cigsPerWeek <= to) {
						inThisCategory++;
					}
					break;
				case EXERCISE:
					if (s.exercise >= from && s.exercise <= to) {
						inThisCategory++;
					}
					break;
				case ALCOHOL:
					if (s.alcohol >= from && s.alcohol <= to) {
						inThisCategory++;
					}
					break;
				}
			} // other wise the record isn't in the age bracket
		} else if (bracketType == INCOME) { // then it's an income
			if (s.incBracket == bracket) {
				// this survey is valid for this particular category
				surveysInBracket++;

				switch (category) {
				case SMOKE:
					if (s.cigsPerWeek >= from && s.cigsPerWeek <= to) {
						inThisCategory++;
					}
					break;
				case EXERCISE:
					if (s.exercise >= from && s.exercise <= to) {
						inThisCategory++;
					}
					break;
				case ALCOHOL:
					if (s.alcohol >= from && s.alcohol <= to) {
						inThisCategory++;
					}
					break;
				}
			}
		} else if (bracketType == GENDER) {
			if (s.gender == bracket) {
				surveysInBracket++;
				switch (category) {
				case SMOKE:
					if (s.cigsPerWeek >= from && s.cigsPerWeek <= to) {
						inThisCategory++;
					}
					break;
				case EXERCISE:
					if (s.exercise >= from && s.exercise <= to) {
						inThisCategory++;
					}
					break;
				case ALCOHOL:
					if (s.alcohol >= from && s.alcohol <= to) {
						inThisCategory++;
					}
					break;
				}
			}
		}

		curr = curr->next; // move onto next one

	}
	if (surveysInBracket == 0) {
		totalPercent = 0; // prevent division by 0
	} else {
		totalPercent = (inThisCategory * 100.00) / surveysInBracket;
		// the amount of surveys that fall into this category as a percentage of the total in that age bracket
	}
	return totalPercent;
}

// 5 different categories
/*
  EIGHTEEN_TO_TWENTY 1
  TWENTY_TO_THIRTY 2
  THIRTY_TO_FIFTY 3
  FIFTY_TO_SIXTYFIVE 4
  SIXTYFIVE_PLUS 5
 */

void print_stats(node* list, FILE* file) {

	char ageBrackets[5][10] =
	{{ "18 - 20" },
	{ "20 - 30" },
	{ "30 - 50" },
	{ "50 - 65" },
	{ "65 + " }};
	char incBrackets[7][25] =
	{{ "No Income" },
	{ "Less Than €20,000" },
	{ "Less Than €40,000" },
	{ "Less Than €60,000" },
	{ "Less Than €80,000" },
	{ "Less Than €100,000" },
	{ "More Than €100,000" }};

	char genderBrackets[2][10] =
	{{ "Male" },
	{ "Female" }};

	int i; // counter

// print based on age bracket
	for (i = 1; i <= 5; i++) { // 5 age brackets
		fprintf(file, "=============== Age Bracket: %s ===============\n", ageBrackets[i - 1]);
		fprintf(file, "People Who Smoke: %.2f%c\n", track_stat(list, AGE, i, SMOKE, 2, 4), '%');
		// options 2, 3 and 4 indicate a smoker

		fprintf(file, "People Who Smoke Less Than 20 A Day: %.2f%c\n",
				track_stat(list, AGE, i, SMOKE, 1, 2), '%');
		// options 1 and 2 indicate less than 20
		fprintf(file, "People Who Smoke Less Than 40 A Day: %.2f%c\n",
				track_stat(list, AGE, i, SMOKE, 1, 3), '%');
		// 1, 2 and 3 for less than 40
		fprintf(file, "People Who Smoke More Than 40 A Day: %.2f%c\n",
				track_stat(list, AGE, i, SMOKE, 4, 4), '%');
		// just option 4 is more than 40
		fprintf(file, "People Who Never Exercise: %.2f%c\n",
				track_stat(list, AGE, i, EXERCISE, 1, 1), '%');
		// only option 1 is never exercise
		fprintf(file, "People Who Exercise Less Than Three Times Per Week: %.2f%c\n",
				track_stat(list, AGE, i, EXERCISE, 1, 2), '%');
		// options 1 and 2 are < 3 times
		fprintf(file, "People Who Exercise Less Than Five Times Per Week: %.2f%c\n",
				track_stat(list, AGE, i, EXERCISE, 1, 3), '%');
		// options 1,2 and 3
		fprintf(file, "People Who Exercise More Than Five Times Per Week: %.2f%c\n",
				track_stat(list, AGE, i, EXERCISE, 4, 4), '%');
		// only option 4
		fprintf(file, "People Who Do Not Consume Alcohol: %.2f%c\n",
				track_stat(list, AGE, i, ALCOHOL, 1, 1), '%');
		// only option 1 is no alcohol
		fprintf(file, "People Who Consume Less Than 2 Units: %.2f%c\n",
				track_stat(list, AGE, i, ALCOHOL, 1, 2), '%');
		// 1 and 2 are less than 2 units
		fprintf(file, "People Who Consume Less Than 4 Units: %.2f%c\n",
				track_stat(list, AGE, i, ALCOHOL, 1, 3), '%');
		// options 1,2 and 3 are < 4 units
		fprintf(file, "People Who Consume More Than 4 Units: %.2f%c\n\n",
				track_stat(list, AGE, i, ALCOHOL, 4, 4), '%');
		// only option that is >4 is option 4
	}

// print based on income
	for (i = 1; i <= 7; i++) {
		fprintf(file, "=============== Income Bracket: %s ===============\n", incBrackets[i - 1]);
		fprintf(file, "People Who Smoke: %.2f%c\n", track_stat(list, INCOME, i, SMOKE, 2, 4), '%');
		// options 2, 3 and 4 indicate a smoker
		fprintf(file, "People Who Smoke Less Than 20 A Day: %.2f%c\n",
				track_stat(list, INCOME, i, SMOKE, 1, 2), '%');
		// options 1 and 2 indicate less than 20
		fprintf(file, "People Who Smoke Less Than 40 A Day: %.2f%c\n",
				track_stat(list, INCOME, i, SMOKE, 1, 3), '%');
		// 1, 2 and 3 for less than 40
		fprintf(file, "People Who Smoke More Than 40 A Day: %.2f%c\n",
				track_stat(list, INCOME, i, SMOKE, 4, 4), '%');
		// just option 4 is more than 40
		fprintf(file, "People Who Never Exercise: %.2f%c\n",
				track_stat(list, INCOME, i, EXERCISE, 1, 1), '%');
		// only option 1 is never exercise
		fprintf(file, "People Who Exercise Less Than Three Times Per Week: %.2f%c\n",
				track_stat(list, INCOME, i, EXERCISE, 1, 2), '%');
		// options 1 and 2 are < 3 times
		fprintf(file, "People Who Exercise Less Than Five Times Per Week: %.2f%c\n",
				track_stat(list, INCOME, i, EXERCISE, 1, 3), '%');
		// options 1,2 and 3
		fprintf(file, "People Who Exercise More Than Five Times Per Week: %.2f%c\n",
				track_stat(list, INCOME, i, EXERCISE, 4, 4), '%');
		// only option 4
		fprintf(file, "People Who Do Not Consume Alcohol: %.2f%c\n",
				track_stat(list, INCOME, i, ALCOHOL, 1, 1), '%');
		// only option 1 is no alcohol
		fprintf(file, "People Who Consume Less Than 2 Units: %.2f%c\n",
				track_stat(list, INCOME, i, ALCOHOL, 1, 2), '%');
		// 1 and 2 are less than 2 units
		fprintf(file, "People Who Consume Less Than 4 Units: %.2f%c\n",
				track_stat(list, INCOME, i, ALCOHOL, 1, 3), '%');
		// options 1,2 and 3 are < 4 units
		fprintf(file, "People Who Consume More Than 4 Units: %.2f%c\n\n",
				track_stat(list, INCOME, i, ALCOHOL, 4, 4), '%');
		// only option that is >4 is option 4
	}

// print based on gender
	for (i = 1; i <= 2; i++) {
		fprintf(file, "=============== Gender: %s ===============\n", genderBrackets[i - 1]);
		fprintf(file, "People Who Smoke: %.2f%c\n", track_stat(list, GENDER, i, SMOKE, 2, 4), '%');
		// options 2, 3 and 4 indicate a smoker
		fprintf(file, "People Who Smoke Less Than 20 A Day: %.2f%c\n",
				track_stat(list, GENDER, i, SMOKE, 1, 2), '%');
		// options 1 and 2 indicate less than 20
		fprintf(file, "People Who Smoke Less Than 40 A Day: %.2f%c\n",
				track_stat(list, GENDER, i, SMOKE, 1, 3), '%');
		// 1, 2 and 3 for less than 40
		fprintf(file, "People Who Smoke More Than 40 A Day: %.2f%c\n",
				track_stat(list, GENDER, i, SMOKE, 4, 4), '%');
		// just option 4 is more than 40
		fprintf(file, "People Who Never Exercise: %.2f%c\n",
				track_stat(list, GENDER, i, EXERCISE, 1, 1), '%');
		// only option 1 is never exercise
		fprintf(file, "People Who Exercise Less Than Three Times Per Week: %.2f%c\n",
				track_stat(list, GENDER, i, EXERCISE, 1, 2), '%');
		// options 1 and 2 are < 3 times
		fprintf(file, "People Who Exercise Less Than Five Times Per Week: %.2f%c\n",
				track_stat(list, GENDER, i, EXERCISE, 1, 3), '%');
		// options 1,2 and 3
		fprintf(file, "People Who Exercise More Than Five Times Per Week: %.2f%c\n",
				track_stat(list, GENDER, i, EXERCISE, 4, 4), '%');
		// only option 4
		fprintf(file, "People Who Do Not Consume Alcohol: %.2f%c\n",
				track_stat(list, GENDER, i, ALCOHOL, 1, 1), '%');
		// only option 1 is no alcohol
		fprintf(file, "People Who Consume Less Than 2 Units: %.2f%c\n",
				track_stat(list, GENDER, i, ALCOHOL, 1, 2), '%');
		// 1 and 2 are less than 2 units
		fprintf(file, "People Who Consume Less Than 4 Units: %.2f%c\n",
				track_stat(list, GENDER, i, ALCOHOL, 1, 3), '%');
		// options 1,2 and 3 are < 4 units
		fprintf(file, "People Who Consume More Than 4 Units: %.2f%c\n\n",
				track_stat(list, GENDER, i, ALCOHOL, 4, 4), '%');
		// only option that is >4 is option 4
	}
}
