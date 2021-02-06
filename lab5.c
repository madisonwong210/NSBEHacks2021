#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*void delchar(char *line, int first, int second){
	if ((first+second-1)<=strlen(line))
	{
		strcpy(&line[second-1], &line[first+second-1]);
		puts(line);
	}
}*/

char interpret(char seq1,char seq2, char seq3){
	char value = '4';
	if (seq1 == 'T'){
		if (seq2 == 'T'){
			if ((seq3 == 'T') || (seq3 == 'C')){
				value = 'F';
			}
			if ((seq3 == 'A') || (seq3 == 'G')){
				value = 'L';
			}

		}
		if (seq2 == 'C'){
			value = 'S';
		}
		if (seq2 == 'A'){
			if ((seq3 == 'T') || (seq3 == 'C')){
				value = 'Y';
			}
			if ((seq3 == 'A') || (seq3 == 'G')){
				value = '*';
			}
		}
		if (seq2 == 'G'){
			if (seq3 == 'A'){
				value = '*';
			}
			if (seq3 == 'G'){
				value = 'W';
			}
			if ((seq3 == 'T') || (seq3 == 'C')){
				value = 'C';
			}
		}
	}
	if (seq1 == 'C'){
		if (seq2 == 'T'){
			value = 'L';
		}
		if (seq2 == 'C'){
			value = 'P';
		}
		if (seq2 == 'A'){
			if ((seq3 == 'T') || (seq3 == 'C')){
				value = 'H';
			}
			if ((seq3 == 'A') || (seq3 == 'G')){
				value = 'Q';
			}
		}
		if (seq2 == 'G'){
			value = 'R';
		}
	}
	if (seq1 == 'A'){
		if (seq2 == 'T'){
			if (seq3 == 'G'){
				value = 'M';
			}
			if ((seq3 == 'T') || (seq3 == 'C') || (seq3 == 'A')){
				value = 'I';
			}
		}
		if (seq2 == 'C'){
			value = 'T';
		}
		if (seq2 == 'A'){
			if ((seq3 == 'T') || (seq3 == 'C')){
				value = 'N';
			}
			if ((seq3 == 'A') || (seq3 == 'G')){
				value = 'K';
			}
		}
		if (seq2 == 'G'){
			if ((seq3 == 'C') || (seq3 == 'T')){
				value = 'S';
			}
			if ((seq3 == 'A') || (seq3 == 'G')){
				value = 'R';
			}
		}
	}
	if (seq1 == 'G'){
		if (seq2 == 'T'){
			value = 'V';
		}
		if (seq2 == 'C'){
			value = 'A';
		}
		if (seq2 == 'A'){
			if ((seq3 == 'A') || (seq3 == 'G')){
				value = 'E';
			}
			if ((seq3 == 'T') || (seq3 == 'C')){
				value = 'D';
			}
		}
		if (seq2 == 'G'){
			value = 'G';
		}
	}
	return value;
}

void encodeNuc(char *filename){ // add the fputs into the output stream and close the pointer
	FILE* input_stream = fopen(filename, "r");
	char output [strlen(filename)+1];

	for (int i = 0; i<=strlen(filename);i++){
		output[i+1] = filename[i];
	}
	output[0] = 'b';

	FILE* output_stream = fopen(output, "w");

	char c =  'c';
	int count = 0;
	while(c!= EOF){
		c = fgetc(input_stream); 
		count++;
	}

	char final[(count-1)*2];

	rewind(input_stream);
	c = 'c';
// --------------------------
	int i = 0;
	int j = 1;

	while(c != EOF){
		c = (char)fgetc(input_stream);

		if (c == 'A'){
			final[i] = '0' ;
			final[j] = '0' ;
		}
		else if (c == 'C'){
			final[i] = '0';
			final[j] = '1';		
		}
		else if (c == 'G'){
			final[i] = '1';
			final[j] = '0';
		}
		else if (c == 'T'){
			final[i] = '1';
			final[j] = '1';
		}
		i++;
		i++;
		j++;
		j++;
	}
	final[(count-1)*2] = '\0';


	fputs(final, output_stream);

	fclose(output_stream);
	fclose(input_stream);

}


void decodeBin(char *filename){ //add the fputs into the output stream and close the pointer
	int length = strlen(filename);
	char output2 [strlen(filename)+1];

	for (int i = 0; i<=strlen(filename);i++){
		output2[i+1] = filename[i];
	}

	output2[0] = 'n';

	FILE* input_stream = fopen(filename, "r");
	FILE* output_stream = fopen(output2,"w");

	char c =  '1';
	int count = 0;

	while(c!= EOF){
		c = (char)fgetc(input_stream);
		count++;
	}


	char final_seq[(count - 1 ) / 2];
	char final_bin[count];
	rewind(input_stream);
	c = '1';


	fgets(final_bin, count, input_stream);


	int i = 0;
	int j = 0;
	while (i < count-1){
		if (final_bin[i] == '0' && final_bin[i+1] == '0'){
			final_seq[j] = 'A';
		}
		else if (final_bin[i] == '0' && final_bin[i+1] == '1'){
			final_seq[j] = 'C';
		}
		else if (final_bin[i] == '1' && final_bin[i+1] == '0'){
			final_seq[j] = 'G';
		}
		else if (final_bin[i] == '1' && final_bin[i+1] == '1'){
			final_seq[j] = 'T';
		}
		i++;
		i++;
		j++;

}
	final_seq [(count -1) / 2] = '\0';

	fputs(final_seq, output_stream);
	fclose(output_stream);
	fclose(input_stream);
}
void findProtein(char *filename, int checkPos, int proteinInfo[]){
	decodeBin(filename);
	char input[strlen(filename)+1];

	for (int i = 0; i<=strlen(filename);i++){
		input[i+1] = filename[i];
	}
	input[0] = 'n';
	input[strlen(input)+1] = '\0';

	FILE* input_stream = fopen(input, "r");
	char c =  '1';
	int count = 0;

	while(c!= EOF){
		c = (char)fgetc(input_stream); 
		count++;
	}

	char final_seq[count];
	rewind(input_stream);

	fgets(final_seq, count, input_stream);
// -------------------------------------------------
	int i = checkPos;
	int position;
	int new_count = 0;
	int inbetween = 0;

	while(i+3 < count){
		if (final_seq[i] == 'A' && final_seq[i+1] == 'T' && final_seq[i+2] == 'G'){
			position = i;
			inbetween = 1;
		}
		if (inbetween == 1){
			new_count++;
			i++;
			i++;
			i++;
		}
		if (((final_seq[i] == 'T' && final_seq[i+1] == 'A' && final_seq[i+2] == 'A') || (final_seq[i] == 'T' && final_seq[i+1] == 'A' && final_seq[i+2] == 'G') ||
			(final_seq[i] == 'T' && final_seq[i+1] == 'G' && final_seq[i+2] == 'A')) && inbetween == 1){
			break;
		}
		if (inbetween!=1){
		i++;
		i++;
		i++;
	}
	}
	proteinInfo[0] = position;
	proteinInfo[1] = (new_count+1)*3;
	if (inbetween == 0){
		proteinInfo[0] = 0;
		proteinInfo[1] = 0;
	}
	fclose(input_stream);
}

void proteinReport(char *filename){
	decodeBin(filename);
	char input[1000];

	for (int i = 0; i<=strlen(filename);i++){
		input[i+1] = filename[i];
	}
	input[0] = 'n';
	input[strlen(input)+1] = '\0';

	FILE* input_stream = fopen(input, "r");

	char *output = input;
	output[0] = 'r';
	FILE* output_stream = fopen(output, "w");

	char c =  '1';
	int count = 0;

	while(c!= EOF){
		c = (char)fgetc(input_stream); 
		count++;
	}
// ---------------------------------
	int proteinInfo[2] = {1,1};
	int checkPos = 0; 
	char temp1[20];
	char temp2[20];
	char temp3[20];
	while (proteinInfo[0] != 0 && proteinInfo[1] != 0){
		findProtein(filename, checkPos, proteinInfo);
		itoa(proteinInfo[0],temp1, 10);
		itoa(proteinInfo[1],temp2, 10);

		if (checkPos == proteinInfo[0]){
		fputs (temp1, output_stream);
		fputc (',', output_stream);
		fputs (temp2, output_stream);
		fputs ("\n", output_stream);}
		checkPos +=3;

	}
	checkPos = 1;
	proteinInfo[0] = 1;
	proteinInfo[1] = 1;
	while (proteinInfo[0] != 0 && proteinInfo[1] != 0){
		findProtein(filename, checkPos, proteinInfo);
		itoa(proteinInfo[0],temp1, 10);
		itoa(proteinInfo[1],temp2, 10);

		if (checkPos == proteinInfo[0]){
		fputs (temp1, output_stream);
		fputc (',', output_stream);
		fputs (temp2, output_stream);
		fputs ("\n", output_stream);}
		checkPos +=3;
	}
	proteinInfo[0] = 1;
	proteinInfo[1] = 1;
	checkPos = 2;
	while (proteinInfo[0] != 0 && proteinInfo[1] != 0){
		findProtein(filename, checkPos, proteinInfo);
		itoa(proteinInfo[0],temp1, 10);
		itoa(proteinInfo[1],temp2, 10);

		if (checkPos == proteinInfo[0]){
		fputs (temp1, output_stream);
		fputc (',', output_stream);
		fputs (temp2, output_stream);
		fputs ("\n", output_stream);}
		checkPos +=3;
	}

fclose(output_stream);
fclose(input_stream);
}
void isolateProtein(char *filename, int proteinInfo[]){
	decodeBin(filename);
	char input[1000];

	for (int i = 0; i<=strlen(filename);i++){
		input[i+1] = filename[i];
	}
	input[0] = 'n';
	input[strlen(input)] = '\0';
//---------------------------------
	char input2[1000];

	for (int i = 0; i<=strlen(filename);i++){
		input2[i+1] = filename[i];
	}
	input2[0] = 'r';
	input2[strlen(input2)] = '\0';
	FILE* input_stream2 = fopen(input2, "r");

//---------------------------------

	FILE* input_stream = fopen(input, "r");


	char *output = input;
	output[0] = 'p';
	FILE* output_stream = fopen(output, "w");

	char c =  '1';
	int count = 0;

	while(c!= EOF){
		c = (char)fgetc(input_stream); 
		count++;
	}

	char final_seq[count];
	rewind(input_stream);
	fgets(final_seq, count, input_stream);
	fclose(input_stream);
	proteinReport(input);

char single_protein;
int length;
int position;
int upper;
while (fscanf(input_stream2, "%d,%d\n", &position, &length) != EOF){
	upper = position+length;
while(position<upper){
	single_protein = interpret(final_seq[position], final_seq[position+1], final_seq[position+2]);
	fputc(single_protein, output_stream);
	position+=3;
}
}

fclose(input_stream2);
fclose(output_stream);
}


int genMutant(char *filename, int mutation[]){// same fucking thing
	int works = 0;
	char input[1000];

	for (int i = 0; i<=strlen(filename);i++){
		input[i+1] = filename[i];
	}
	input[0] = 'n';
	input[strlen(input)+1] = '\0';

	FILE* input_stream = fopen(input, "r");

	char *output = input;
	output[0] = 'm';
	FILE* output_stream = fopen(output, "w");

	char c =  '1';
	int count = 0;

	while(c!= EOF){
		c = (char)fgetc(input_stream); 
		count++;
	}
	rewind(input_stream);

	char final_seq[count];
	fgets(final_seq, count, input_stream);
//-----------------------------------------------
	int i;
	if (mutation[1] == 0){
		char mutate[count -1];
		int j = 0;
		for(i = 0; i < count; i++){

			if (i == mutation[0]){
				continue;
			}
			mutate[j] = final_seq[i];
			j++;
		}
		fputs(mutate, output_stream);
		works = 1;
	}

	if (mutation[1] == 2){
		char mutate[count];
		int leap = 0;
		char insert;
		for(i = 0; i <count; i++){
			if (i == mutation[0]){
				if (mutation[2] == 0) insert = 'A';
				if (mutation[2] == 1) insert = 'C';
				if (mutation[2] == 2) insert = 'G';
				if (mutation[2] == 3) insert = 'T';
				mutate[i] = insert;
				leap = 1;
				continue;
			}
			mutate[i] = final_seq[i];

		fputs(mutate, output_stream);
		works = 1;
	}
	}

	if (mutation[1] == 1){
		char mutate[count+1];
		int leap = 0;
		char insert;
		for(i = 0; i <count; i++){
			if (i == mutation[0]){
				if (mutation[2] == 0) insert = 'A';
				if (mutation[2] == 1) insert = 'C';
				if (mutation[2] == 2) insert = 'G';
				if (mutation[2] == 3) insert = 'T';
				mutate[i] = insert;
				leap = 1;
	
			}
			if (leap == 0)
			mutate[i] = final_seq[i];
			if (leap == 1){
			mutate[i+1] = final_seq[i-1];
			}

		}
		mutate[count+1] = '\0';

		fputs(mutate, output_stream);
		works = 1;
	}
fclose(output_stream);
fclose(input_stream);
return works;
}
int main(){
	printf("hi");
	return 0;
}