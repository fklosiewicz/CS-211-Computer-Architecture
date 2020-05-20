/* CS 211 PA4
 * Created for: fk206
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int negate(int input) {
	if(input == 1 || input == 0) {
		if (input == 1) {
			return 0;
		} else if (input == 0) {
			return 1;
		}
	}
	return 999; // Redundant return value, since program is to be sorted anyways, and we assume it's formatted correctly (with only 0s and 1s).
}

void NOT(int *arrayofresult, int input, int output) {
	int boolean;
	boolean = negate(arrayofresult[input]);
	arrayofresult[output] = boolean;
	return;
}

void AND(int *arrayofresult, int input1, int input2, int output) {
	int LogicalAND;
	LogicalAND = arrayofresult[input1] * arrayofresult[input2];
	arrayofresult[output] = LogicalAND;
	return;
}

// Computes the actual integer value of the 'AND' operation. Used for NAND.
int ANDOperator(int *arrayofresult, int input1, int input2, int output) {
	int LogicalAND;
	LogicalAND = arrayofresult[input1] * arrayofresult[input2];
	return LogicalAND;
}	

void NAND(int *arrayofresult, int input1, int input2, int output) {
	int LogicalNAND;
	LogicalNAND = ANDOperator(arrayofresult, input1, input2, output);
	LogicalNAND = negate(LogicalNAND);
	arrayofresult[output] = LogicalNAND;
	return;
}

void OR(int *arrayofresult, int input1, int input2, int output) {
	int LogicalOR;
	if(arrayofresult[input1] == 1 || arrayofresult[input2] == 1) {
		LogicalOR = 1;
	} else {
		LogicalOR = 0;
	}
	arrayofresult[output] = LogicalOR;
	return;
}

// Computes the actual integer value of the 'OR' operation. Used for NOR.
int OROperator(int *arrayofresult, int input1, int input2, int output) {
	int LogicalOR;
	if(arrayofresult[input1] == 1 || arrayofresult[input2] == 1) {
		LogicalOR = 1;
	} else {
		LogicalOR = 0;
	}
	return LogicalOR;	
}

void NOR(int *arrayofresult, int input1, int input2, int output) {
	int LogicalNOR;
	LogicalNOR = OROperator(arrayofresult, input1, input2, output);
	LogicalNOR = negate(LogicalNOR);
	arrayofresult[output] = LogicalNOR;
	return;
}	

void XOR(int *arrayofresult, int input1, int input2, int output) {
	int LogicalXOR;
	if((arrayofresult[input1] == 1 && arrayofresult[input2] == 0) || (arrayofresult[input1] == 0 && arrayofresult[input2] == 1)) {
		LogicalXOR = 1;
	} else {
		LogicalXOR = 0;
	}
	arrayofresult[output] = LogicalXOR;
	return;
}

void PASS(int *arrayofresult, int input, int output) {
	int LogicalPASS; // A little redundant, but it helps with readability of code.
	LogicalPASS = arrayofresult[input];
	arrayofresult[output] = LogicalPASS;
	return;
}

int decode(int inputs) {
	int decodingpower = 0;
	decodingpower = pow(2, inputs);
	return decodingpower;
}

void MULTIPLEXER(int *arrayofresult, int inputnums, int *arrayofinputs, int *arrayofselectors, int output) {
	int decoder;
	int selector = 0;
	int product = 0;
	int output_s;
	for(int i = 0; i < inputnums; i++) {
		int offset = inputnums - i - 1; // This creates an offset that we want to start traversing the array at.
		output_s = arrayofselectors[i];
		decoder = decode(offset);
		product = arrayofresult[output_s] * decoder;
		selector = selector + product;
	}
	output_s = arrayofinputs[selector];
	arrayofresult[output] = arrayofresult[output_s];
	return;
}

void DECODER(int *arrayofresult, int inputnums, int *arrayofinputs, int *arrayofoutputs) {
	int decoder = decode(inputnums);
	int output_a;
	for(int i = 0; i < decoder; i++) {
		output_a = arrayofoutputs[i];
		arrayofresult[output_a] = 0;
		output_a = 0;
	}
	int selector = 0;
	int product = 0;
	for(int i = 0; i < inputnums; i++) {
		int offset = inputnums - i - 1; // This creates an offset that we want to start traversing the array at.
		output_a = arrayofinputs[i];
		decoder = decode(offset);
		product = arrayofresult[output_a] * decoder;
		selector = selector + product;
	}
	output_a = arrayofoutputs[selector];
	arrayofresult[output_a] = 1;
	return;
}	

typedef struct LogicGate {
	int NumberOfDecodingInputs;
	int NumberOfInputs;
	int *ArrayOfInputs;
	int NumberOfSelectingInputs;
	int *ArrayOfSelectors;
	int NumberOfOutputs;
	int *ArrayOfOutputs;
	char directivetype[17];
} gate; // Provides readability of the program.	

typedef struct Node {
	int index;
	char variable[17];
	struct Node* next;
} Node;

struct Node* newNode(int index, char *variable) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node) * 3);
		newNode->index = index;
		newNode->next = NULL;
		strcpy(newNode->variable, variable);
	return newNode;
}

void InsertNode(struct Node** head, struct Node* newNode) {
	if(*head == NULL) {
		newNode->next = *head;
		*head = newNode;
		return;
	}
	Node* current = *head;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = newNode;
	return;
}

int SequentialSearchNode(struct Node* head, char *variable) {
	struct Node* node = head;
	int present = 999; // Again, this is just the value we use if something isn't found.
	while (node != NULL) {
		int boolean;
		boolean = strcmp(variable, node->variable);
		if(boolean == 0) {
			present = node->index;
			return present;
		}
		node = node->next;
	}
	return present;
}

int main(int argc, char **argv) {

	if(argc > 2) {
		perror("Too many or too little arguments --> Number of Required Arguments: 1");
		return EXIT_FAILURE;
	}
	FILE *fp = fopen(argv[1], "r");

	int inputnums;
	char tempvar[17]; // 16 fails to work since 1 of the characters is the \0 (null) character, so if you input 16, 
	char buffer[17];  // you really only get 15 available blocks of memory for characters.
	fscanf(fp, " %16s", tempvar);
	fscanf(fp, " %16s", buffer);
	inputnums = atoi(buffer);

	Node *VARHEAD = NULL;
	InsertNode(&VARHEAD, newNode(0, "0"));
	InsertNode(&VARHEAD, newNode(1, "1"));
	
	int offset = 2;
	for(int i = 2; i < inputnums + 2; i++) {
		fscanf(fp, " %16s", tempvar);
		InsertNode(&VARHEAD, newNode(i, tempvar));
		offset++;
	}
	
	int length = 2 + inputnums;

	int outputnums;	
	char tempvar2[17];
	fscanf(fp, " %16s", tempvar2);
	fscanf(fp, " %16s", buffer);
	outputnums = atoi(buffer);

	for(int i = length; i < outputnums + length; i++) {
		fscanf(fp, " %16s", tempvar2);
		InsertNode(&VARHEAD, newNode(i, tempvar2));
	}

	// This creates a linked list of variables, numbered. 0(0) --> 1(1) --> A(2) --> B(3) --> C(4) --> . . .
	// The numbering helpes us categorize variables into fixed indices later on in the program.

	length = length + outputnums;

	gate *LogicGates = NULL; // We essentially set an array of objects that hold our logic gates, they will inputted in order of occurrance.
	int LogicGateCount = 0; // We will use the number of these gates later when we traverse each gate and compute their values.

	while (true) {
			 // If we worked with a constant number of inputs/outputs we could put the "fscanf" in the while loop, but because the number varies,
			// we essentially have the program run the loop until it reaches "EOF", or end of the file.
	
		gate LogicGate;
	
		if(fscanf(fp, " %16s", LogicGate.directivetype) == EOF) {
			break;
		}

		 // Create a logic gate, increment the number of overall gates if the above condition stands, and initialize the components of this gate to 0/NULL.
		LogicGateCount = LogicGateCount + 1;
		LogicGate.NumberOfDecodingInputs = 0;
		LogicGate.NumberOfSelectingInputs = 0;
		LogicGate.NumberOfOutputs = 0;
		LogicGate.ArrayOfInputs = NULL;
		LogicGate.ArrayOfSelectors = NULL;
		LogicGate.ArrayOfOutputs = NULL;

		int inputs;
		int outputs;
		int selectors;
		int boolean;
	
		// Once we calculate the inputs and the outputs, we must set the length of each sub-array of the directive type, with the
		// corresponding inputs and outputs. The selector inputs only change for MULTIPLEXER.

		char buffer_2[17];

		boolean = strcmp("PASS", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have a PASS\n");
			inputs = 1;
			outputs = 1;
			selectors = 0;
			LogicGate.NumberOfDecodingInputs = inputs;
			LogicGate.NumberOfOutputs = outputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
                        LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));
                        LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));		
		}
	
		boolean = strcmp("AND", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have an AND\n");
			inputs = 2;
			outputs = 1;
			selectors = 0;
			LogicGate.NumberOfDecodingInputs = inputs;
			LogicGate.NumberOfOutputs = outputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
			LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));
			LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));
		}
		
		boolean = strcmp("OR", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have an OR\n");
			inputs = 2;
			outputs = 1;
			selectors = 0;
			LogicGate.NumberOfDecodingInputs = inputs;
			LogicGate.NumberOfOutputs = outputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
			LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));
			LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));
		}
		
		boolean = strcmp("NAND", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have a NAND\n");
			inputs = 2;
			outputs = 1;
			selectors = 0;
			LogicGate.NumberOfDecodingInputs = inputs;
			LogicGate.NumberOfOutputs = outputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
			LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));
			LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));
		}

		boolean = strcmp("NOR", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have a NOR\n");
			inputs = 2;
			outputs = 1;
			selectors = 0;
			LogicGate.NumberOfDecodingInputs = inputs;
			LogicGate.NumberOfOutputs = outputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
			LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));
			LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));
		}

		boolean = strcmp("XOR", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have a XOR\n");
			inputs = 2;
			outputs = 1;
			selectors = 0;
			LogicGate.NumberOfDecodingInputs = inputs;
			LogicGate.NumberOfOutputs = outputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
			LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));
			LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));
		}

		boolean = strcmp("NOT", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have a NOT\n");
			inputs = 1;
			outputs = 1;
			selectors = 0;
			LogicGate.NumberOfDecodingInputs = inputs;
			LogicGate.NumberOfOutputs = outputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
			LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));
			LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));
		}


		boolean = strcmp("DECODER", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have a DECODER\n");
			selectors = 0;
			LogicGate.NumberOfDecodingInputs = 0; // This seems redundant but we never initialized this integer beforehand.
			fscanf(fp, " %16s", buffer_2);
			inputs = atoi(buffer_2);
			LogicGate.NumberOfDecodingInputs = inputs;
			int decoder = decode(inputs);
			outputs = decoder;			// For pure readability of the program.
			LogicGate.NumberOfOutputs = outputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
			LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));
			LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));	
		}


		boolean = strcmp("MULTIPLEXER", LogicGate.directivetype);
		if (boolean == 0) {
			//printf("We have a MULTIPLEXER\n");
			outputs = 1;
			LogicGate.NumberOfSelectingInputs = 0;
			fscanf(fp, " %16s", buffer_2);
			inputs = atoi(buffer_2);
			LogicGate.NumberOfSelectingInputs = inputs;
			int decoder = decode(inputs);
			inputs = decoder;
			selectors = LogicGate.NumberOfSelectingInputs;
			LogicGate.ArrayOfInputs = malloc(inputs * sizeof(int));
                        LogicGate.ArrayOfOutputs = malloc(outputs * sizeof(int));	
			LogicGate.ArrayOfSelectors = malloc(selectors * sizeof(int));			
		}


		// After we have our gate with the specified number of inputs, outputs, and selectors for multiplexer,
		// we find their position in the general 2D array of variables using sequential search.
		
		// Once we find that position, we input that position for the first block of memory of inputs for this specific gate.
			// ex: AND has an input array of 2, output array of 1, no selectors.
				// Given a directive: AND a b c, we find the position of "a" in the variable 2D array and store it in the first block of memory
				// of the input array of AND. Then, we find the positon of "b" likewise, and store "b" in the second block of memory of the input array.
				// Then, we move onto outputs (in this case 1) and we perform the same procedure.
			

		// Therefore, the actual inputs in the input array of the gate are refered to by their indices of the 2D array of variables. 

		char tempvar3[17];
		for (int i = 0; i < inputs; i++) {
			int position;
			fscanf(fp, " %16s", tempvar3);
			position = SequentialSearchNode(VARHEAD, tempvar3);
			if (position == 999) {
				InsertNode(&VARHEAD, newNode(length, tempvar3));   // Non-working extra credit attempt.
                                LogicGate.ArrayOfInputs[i] = length;
                                length = length + 1;
                                continue;
			}
			else if (position != 999) {
				LogicGate.ArrayOfInputs[i] = position;
			}
		}

	if(selectors != 0) { // Only runs if the value of selectors aren't 0, else we just skip over this.
		char tempvar4[17];
		for (int i = 0; i < selectors; i++) {	
			int position;
			fscanf(fp, " %16s", tempvar4);
			position = SequentialSearchNode(VARHEAD, tempvar4);
			LogicGate.ArrayOfSelectors[i] = position;
		}
	}

		char tempvar5[17];
		for (int i = 0; i < outputs; i++) {
			int position;
			fscanf(fp, " %16s", tempvar5);
			position = SequentialSearchNode(VARHEAD, tempvar5);
			if (position == 999) {		 // SequentialSearch returns 999, so no output value found. Must be a temporary variable.
				InsertNode(&VARHEAD, newNode(length, tempvar5));			 // Increment your 2D Variable array by 1.
				LogicGate.ArrayOfOutputs[i] = length;
				length = length + 1;
				continue;
			}
			else if (position != 999) {
				LogicGate.ArrayOfOutputs[i] = position;
			}

		}
		
		if(LogicGates == NULL) {
			LogicGates = malloc(1 * sizeof(gate));
		}
		if(LogicGates != NULL) {
			gate *temp = realloc(LogicGates, LogicGateCount * sizeof(gate));
			temp[LogicGateCount - 1] = LogicGate;
			LogicGates = temp;
		}

		// We could use a fixed array, but the write-up doesn't specify the maximum number of gates.
		// For all we know, there could be thousands of gates and if we used a fixed array the program would crash.
		// Rellocation of the array solves the problem.		

	}	

		// This is the array that will hold the individual boolean values of every single variable as it is calculated. Therefore, it's an array of integers.

		int *resultingarray = malloc(length * sizeof(int));
		for (int i = 0; i < length; i++) {
			resultingarray[i] = 0;
		}
		resultingarray[1] = 1; // <-- This is because we can't forget the "0" and "1" inputs. The "1" input lies in the second block of memory at index 1.
					// This will always be "1" and will never change, we treat this as a constant value.		
	int breakpoint = 1;
	while(breakpoint != 0) {
		
		// Remember that our array of results looks like [0][1][0][0][0] . . . [0].
		// Where the indices are as follows:		  0  1  2  3  4        outputnums - 1.
		// So our actual inputs start from index 2 (including 2) and run to "inputnums + 2" (including "inputnums + 2")

		int offset2 = 2; // Here I created an offset of 2 since that is where my inputs start.
		for(int i = 0; i < inputnums; i++) { // The number of inputs doesn't change, so you run the loop until you run out of inputs you calculated earlier.
			printf("%d ", resultingarray[offset2]); // You always take the boolean value in the offset, and you increment offset.
			offset2 = offset2 + 1;
		}
		printf("|");
	
		for(int i = 0; i < LogicGateCount; i++) { // Gate traversal.

			// For each of these functions, there must always be an output. Compute the boolean value of given inputs in the resultingarray, and store it back
			// into the resultingarray at the output index.
			
			// This will continue looping the gates, taking the previously computed boolean values, and store them back into the array.
				// ex: if we have "AND a b c" and "AND a c z", the value of "a" remains constant since it's an input.
				// We calculate "c", we store it at the same index of the resultingarray. Then in the second gate, we have access to THAT exact
				// boolean value of "c" and we can use it to compute "z".

			// PASS and NOT are nearly alike, except NOT negates the value.

			int boolean;

			boolean = strcmp("PASS", LogicGates[i].directivetype);
			if (boolean == 0) {
				int input_a = LogicGates[i].ArrayOfInputs[0];
				int output_a = LogicGates[i].ArrayOfOutputs[0];
				PASS(resultingarray, input_a, output_a);
			}
			
			boolean = strcmp("DECODER", LogicGates[i].directivetype);
			if (boolean == 0) {
				int inputnums = LogicGates[i].NumberOfDecodingInputs;
				int *arrayofinputs = LogicGates[i].ArrayOfInputs;
				int *arrayofoutputs = LogicGates[i].ArrayOfOutputs;
				DECODER(resultingarray, inputnums, arrayofinputs, arrayofoutputs);
			}
			
			boolean = strcmp("MULTIPLEXER", LogicGates[i].directivetype);
			if (boolean == 0) {
				int selectors = LogicGates[i].NumberOfSelectingInputs;
				int output_a = LogicGates[i].ArrayOfOutputs[0];
				int *arrayofinputs = LogicGates[i].ArrayOfInputs;
				int *arrayofselectors = LogicGates[i].ArrayOfSelectors;
				MULTIPLEXER(resultingarray, selectors, arrayofinputs, arrayofselectors, output_a);
			}
		
			boolean = strcmp("NOT", LogicGates[i].directivetype);
			if (boolean == 0) {
				int input_a = LogicGates[i].ArrayOfInputs[0];
                       		int output_a = LogicGates[i].ArrayOfOutputs[0];
				NOT(resultingarray, input_a, output_a);
			}

			boolean = strcmp("AND", LogicGates[i].directivetype);
                        if (boolean == 0) {
				int input_a = LogicGates[i].ArrayOfInputs[0];
                        	int input_b = LogicGates[i].ArrayOfInputs[1];
                       		int output_a = LogicGates[i].ArrayOfOutputs[0];
                                AND(resultingarray, input_a, input_b, output_a);
                        }				

			boolean = strcmp("NAND", LogicGates[i].directivetype);
                        if (boolean == 0) {
				int input_a = LogicGates[i].ArrayOfInputs[0];
                      		int input_b = LogicGates[i].ArrayOfInputs[1];
                        	int output_a = LogicGates[i].ArrayOfOutputs[0];
                                NAND(resultingarray, input_a, input_b, output_a);
                        }

			boolean = strcmp("OR", LogicGates[i].directivetype);
                        if (boolean == 0) {
				int input_a = LogicGates[i].ArrayOfInputs[0];
                        	int input_b = LogicGates[i].ArrayOfInputs[1];
                        	int output_a = LogicGates[i].ArrayOfOutputs[0];
                                OR(resultingarray, input_a, input_b, output_a);
                        }			

			boolean = strcmp("NOR", LogicGates[i].directivetype);
                        if (boolean == 0) {
				int input_a = LogicGates[i].ArrayOfInputs[0];
                        	int input_b = LogicGates[i].ArrayOfInputs[1];
                        	int output_a = LogicGates[i].ArrayOfOutputs[0];
                                NOR(resultingarray, input_a, input_b, output_a);
                        }

			boolean = strcmp("XOR", LogicGates[i].directivetype);
                        if (boolean == 0) {
                                int input_a = LogicGates[i].ArrayOfInputs[0];
                                int input_b = LogicGates[i].ArrayOfInputs[1];
                                int output_a = LogicGates[i].ArrayOfOutputs[0];
                                XOR(resultingarray, input_a, input_b, output_a);
                        }			
	
		}
		
		int offset3 = offset;
		for(int i = 0; i < outputnums; i++) {
			printf(" %d", resultingarray[offset3]);
			offset3 = offset3 + 1;
		}
		printf("\n");

		// One way to increment values in terms of binary.
		
		for(int i = inputnums + 1; i > 1; i--) {
			breakpoint = 0;
			if(resultingarray[i] == 1) {
				resultingarray[i] = 0;
			}
			else if (resultingarray[i] == 0) {
				resultingarray[i] = 1;
				breakpoint = 1;
				break;
			}
		}
		
				      // If 000 -> 001 -> 010 -> 011 -> 100 -> 101 -> 110 -> 111 -> 000. If we set all values to 0, breakpoint remains 0, we break out of the loop
				      // since it signifies that we have tried every binary permutation for a number of inputs. In the above example, we assume 3 inputs.
				      // Classic case of overflow.
	

		for(int i = inputnums + 2; i < length; i++) {	// Resets the output values --> It accounts for the two constant inputs "0" and "1", starts checking at first output.
			resultingarray[i] = 0;
		}									

	}

	return EXIT_SUCCESS;
}

