#include <stdbool.h>
typedef struct login {
	char userName[20];
	char password[7]; // 6 + 1 for null terminator
} login;

bool user_is_allowed(char userName[], char password[]) {
	int numUsers = 3;
	int i; // counter
	FILE* loginFile;
	char validName[20];
	char validPassword[7];
	login users[3];
	login user;

	loginFile = fopen("login.dat", "r");
	for (i = 0; i < numUsers; i++) { // 3 admins allowed
		fscanf(loginFile, "%s %s", validName, validPassword);
		strcpy(user.userName, validName);
		strcpy(user.password, validPassword);
		users[i] = user; // create all valid users
	}
	fclose(loginFile);

	for (i = 0; i < numUsers; i++) {
		if (strcmp(userName, users[i].userName) == 0 && strcmp(password, users[i].password) == 0) {
			return true; // if there is a match in both fields,
			// then the user is allowed access
		}
	}
	return false;
	// if we get here, then there was no match
	//so the user is not authorized
}
