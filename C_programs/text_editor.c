#include <string.h>
#include <stdio.h>

void edit_line(char* buffer, int current_line){
	// first locate the line we want to go to inside the buffer
	// strchr to locate a char in a string --> returns a pointer to the matched character
	// keeps searching for a new line 

	for(int i = 0; i < current_line; i++){
		buffer = strchr(buffer, '\n') + 1; // ahead of the new line
	}

	// save a pointer until the line ends

	char* line_end = strchr(buffer, '\n');
	char saved[1024] = { 0 }; // save the rest of the buffer
	strcpy(saved, line_end);
	scanf("%s", buffer);
	strcpy(buffer + strlen(buffer), saved);

}

void main(int argc, char** argv){

	// retrieve the path name
	FILE* f = fopen(argv[1], "r"); 
	// to read file content
	char buffer[1024] = {0};
	fread(buffer, 1024, 1, f); 
	fclose(f);

	// Now we have the buffer content, so now we will start editing
	// which line do we want to edit?

	printf("Contents:\n%s\n", buffer);
	int current_line = 0;
	scanf("%d", &current_line); // scan format
	edit_line(buffer, current_line);
	f = fopen(argv[1], "w");
	fwrite(buffer, strlen(buffer), 1, f);
	fclose(f);

}