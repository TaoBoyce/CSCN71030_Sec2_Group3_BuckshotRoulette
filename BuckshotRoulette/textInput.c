#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_INPUT_LENGTH 100

// Function to get text input from the user
char* getTextInput(const char* prompt) {
	printf("%s: ", prompt);

	// Allocate memory for the input string
	char* input = (char*)malloc(MAX_INPUT_LENGTH * sizeof(char));
	if (input == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	// Read input from the user
	fgets(input, MAX_INPUT_LENGTH, stdin);

	// Remove newline character if present
	char* newlinePos = strchr(input, '\n');
	if (newlinePos != NULL)
		*newlinePos = '\0';

	return input;
}

// Function to get integer input from the user
int getIntInput(const char* prompt) {
	char* inputStr;
	int num;
	do {
		inputStr = getTextInput(prompt); // Get input string
	} while (sscanf_s(inputStr, "%d", &num) != 1); // Repeat until a valid integer is read
	free(inputStr); // Free the memory allocated for input string
	return num;
}

// Function to get a single character input from the user
char getCharInput(const char* prompt) {
	char* inputStr = getTextInput(prompt);
	char ch = inputStr[0];
	free(inputStr);
	return ch;
}