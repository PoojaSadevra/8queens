#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

typedef struct queens {

	int x,y;
	int count; // no. of clashing queens
} queens;

int * frequency;
time_t start,end;
int count_crossover = 0 ;
int count_attackers (queens * q,int queen) {
	
	int j,count=0;
	
	for ( j = 0 ; j < 8 ; j ++ ) {
		if(j!=queen) {
		int abs_x = abs((q[queen].x - q[j].x));
		int abs_y = abs((q[queen].y - q[j].y));
	 
			if((q[j].x==q[queen].x) || (q[j].y==q[queen].y) || (abs_x==abs_y)) { 
				count++; // no. of clashing queens for ith queen
				//frequency[j]++; // position of clashing queens
			}
		}
	}
	return count;
}
/*
std::pair< int , int >  get_attackers (queens * q,int queen) {
	
	int j,count=0;
	std::pair<int , int > attacker_pair;
	for ( j = 0 ; j < 8 ; j ++ ) {
		if(j!=queen) {
		int abs_x = abs((q[queen].x - q[j].x));
		int abs_y = abs((q[queen].y - q[j].y));
	 
			if((q[j].x==q[queen].x) || (q[j].y==q[queen].y) || (abs_x==abs_y)) {
				return  
				count++; // no. of clashing queens for ith queen
				//frequency[j]++; // position of clashing queens
			}
		}
	}
	return count;
}
*/
int find_quality (queens * q ) {

	
	int i,j,count,quality=0;
	frequency = (int*)calloc(sizeof(int),8);

	for ( i = 0; i < 8 ; i++ ) {
		q[i].count=0;
	}
	for ( i = 0 ; i < 8 ; i++ ) {
		for ( j = 0 ; j < 8 ; j ++ ) {
			if(j!=i) {
			int abs_x = abs((q[i].x - q[j].x));
			int abs_y = abs((q[i].y - q[j].y));
	 
				if((q[j].x==q[i].x) || (q[j].y==q[i].y) || (abs_x==abs_y)) { 
					q[i].count++; // no. of clashing queens for ith queen
					frequency[j]++; // position of clashing queens
				}
			}
		}
		quality = quality + q[i].count - frequency[i]; // h is being calculated
	}
	return quality;
}
//checks if a permutation of string already exists
bool check_duplicate_perm (std::string perm , std::string* temp , int i )
{
	for(int j = 0 ; j < i ; j++){
	if(temp[j] == perm)
	return true;
	}
	return false;
}
bool check_duplicate ( int rand_no , int* temp ) {
	for(int i = 0 ; i < 8 ; i++){
	if(temp[i] == rand_no)
	return true;
	}
	return false;
}

//generates a permutation of 12345678 no two queens are in the same column or row.
std::string generate_permutation ( ) {

		std::string initial_state = "12345678";
		int  temp[8] ;

		for( int i = 0 ; i < 8 ; i++) {
		     temp[i] = -1;
		}
		
	        srand(time(NULL));
    	        int random_number = std::rand()%8;

		for( int i = 0 ; i < 8 ; i++) {
	       // srand(time(NULL));
    	        random_number = (std::rand()%8)+1;
		while( check_duplicate (random_number , temp ) != false ) {
    	        random_number = (std::rand()%8) + 1;
		}	
		temp[i] = random_number;
		}

		char permuted_string[8];
		char abc[1];
		for( int i = 0 ; i < 8 ; i++ ) {
int  		n=sprintf (abc , "%d", temp[i]);
		permuted_string[i] = abc[0];
		}
		string final_state(permuted_string);
		return final_state;
		
}

//creates initial population
std::string*  generate_population(std::string* population ,  int size) {

		 population = new std::string[size];
//generate specified number of unique` permuations of "12345678"

		for( int i = 0 ; i < size ; i++) {
		population[i] = generate_permutation();
//		if(i > 0) {
//		while( check_duplicate_perm (population[i] , population , i  ) != false ) {
//		population[i] = generate_permutation();
//		}
//		}

		cout << population[i] << "\n";	}
	return population ;
}

int get_fitness ( std::string state ) {

	char abc[1];
	int  x , y ;

	queens eightqueens[8];
	for( int i = 0 ; i < 8 ; i++){
	
	abc[0] = state[i];
	eightqueens[i].x = i + 1;
	eightqueens[i].y  = atoi(abc);
	
	}
	return (28 - find_quality(eightqueens)  );	
}
// returns children pair from merger
std::pair <string, string> merge_strings(std::string state1 , std::string state2 )  {
		int temp[8];
		for( int i = 0 ; i < 8 ; i++ ){
		temp[i] = 0;
		}
		int temp_int , i , j , k ;
	       // srand(time(NULL));
//		std::string merged_string;
    rand(); rand(); rand();
    	        int random_number = (std::rand()%6)+1;
		char abc[1];
		cout << "random no " << random_number << "\n" ;
// from i to random_no keep part of first string
		for(  i = 0 ; i < random_number ; i++){
		abc[0] = state1[i];
		temp[i] = atoi(abc);	
		}	

		j = 8 - random_number;
		k = random_number;

// get remaining part from second string
		for( i = 0  ; i < 8   ; i++){
		if(k > 7)
		break;
		abc[0] = state2[i];
		temp_int = atoi(abc);	
		if(check_duplicate(temp_int , temp))
		   continue;
		else {		
		temp[k] = temp_int;
		k = k+1;}	
		}


		char merged_string[8];		
		for( int i = 0 ; i < 8 ; i++ ) {
		int n=sprintf (abc , "%d", temp[i]);
		merged_string[i] = abc[0];
//		cout << temp[i] ;
		}
		string final_state(merged_string);


		for(  i = 0 ; i < random_number ; i++){
		abc[0] = state2[i];
		temp[i] = atoi(abc);	
		}	
		j = 8 - random_number;
		k = random_number;
		for( i = 0  ; i < 8   ; i++){
		if(k > 7)
		break;
		abc[0] = state1[i];
		temp_int = atoi(abc);	
		if(check_duplicate(temp_int , temp))
		continue;
		else {
		
		temp[k] = temp_int;
		k = k+1;}	
		}
		for( int i = 0 ; i < 8 ; i++ ) {
		int n=sprintf (abc , "%d", temp[i]);
		merged_string[i] = abc[0];
//		cout << temp[i] ;
		}
		string final_state2(merged_string);
		std::pair <string , string > children = std::make_pair(final_state , final_state2) ;
		return children;
}

std::string mutate(std::string state ) {
	cout << "entering mutate \n";
	char abc[1];
	int  x , y , n , i , initial_quality;
	int temp[8] = { -1 };
	queens eightqueens[8];
	for( i = 0 ; i < 8 ; i++){
	
	abc[0] = state[i];
	eightqueens[i].x = i + 1;
	eightqueens[i].y  = atoi(abc);
	}
	int j = 0 ;	
	initial_quality = find_quality(eightqueens);
	
       // srand(time(NULL));
    rand(); rand(); rand();
    	int random_number = (std::rand()%7)+1;
	int random_number2 = (std::rand()%7)+1;	
	while(random_number2 == random_number ) {
	random_number2 = (std::rand()%7)+1;	
	}
	
	j = eightqueens[random_number].y ;
	 eightqueens[random_number].y = eightqueens[random_number2].y;
	 eightqueens[random_number2].y = j ;
		char merged_string[8];
		for( int i = 0 ; i < 8 ; i++ ) {
		int n=sprintf (abc , "%d", eightqueens[i].y);
		merged_string[i] = abc[0];
		}
		
	string mutated_state(merged_string);
	if(mutated_state == state) {
	mutated_state =  generate_permutation(); 
	}
	return mutated_state;
}

std::pair<int,string> get_best_fitness(std::string* population , int size ) {
  int best_fitness = -1 ;
  std::pair <int , string > fs;
  for ( int i = 0 ; i < size ; i++) {
  if( get_fitness(population[i]) > best_fitness ) {
  fs = make_pair(get_fitness(population[i]) , population[i]) ;
  best_fitness = fs.first ;}
}
  return fs;
}

std::pair<int,string> get_worst_fitness(std::string* population , int size ) {
  int worst_fitness = 29 ;
  std::pair <int , string > fs;
  for ( int i = 0 ; i < size ; i++) {
  if( get_fitness(population[i]) < worst_fitness )
  {fs = make_pair(get_fitness(population[i]) , population[i]) ;
  worst_fitness = fs.first;
  }
  else 
  continue;
}
  cout << "done\n" ;
  return fs;
}

std::pair<string,string> crossover_pair(std::string* population , int size) {

	int original_fitness , original_fitness2 , minfit ;
	int temp[size];
       // srand(time(NULL));
//    	int random_number = (std::rand()%(size)) ;
//	int random_number2 = (std::rand()%(size));	
	std::pair<string , string > final_pair;
	
//	while(random_number2 == random_number ) {
//	random_number2 = (std::rand()%(size));	
//	}
	int best_fitness = -1 ,queen1 ,  queen2 ;
	std::string best_queen = get_best_fitness( population , size).second;
	for(int i = 0 ; i < size ; i++) {
	if(population[i] == best_queen){
	queen1 = i;
	}
  	if( get_fitness(population[i]) > best_fitness && (population[i] != best_queen )) {
	best_fitness = get_fitness(population[i]);
	queen2 = i;
	}
	}
	int j = 0; 
	original_fitness = get_fitness(population[queen1]);
	original_fitness2 = get_fitness(population[queen2]);
	cout << "crossing over " << population[queen1] << " " << population[queen2] << "\n";	
	std::pair<string, string> cross_over = merge_strings (population[queen1], population[queen2]);	
	
//	if( original_fitness < get_fitness(cross_over.first))	
	final_pair.first = cross_over.first;
//	else
//	{
//	final_pair.first = mutate(cross_over.first);
//	}
//	final_pair.first = cross_over.first;
//	if( original_fitness < get_fitness(cross_over.second))	
	final_pair.second = cross_over.second;
//	else
//	{
//	final_pair.second = mutate(cross_over.second);
//	}
	cout << final_pair.first << " " << final_pair.second << " \n";
	count_crossover++;
	if( count_crossover > 100000)
	exit(EXIT_FAILURE);
	return final_pair; 
}
 

void maintain_population( std::string* population , int size , std::pair<string,string>csp ) { 

	std::pair <int , string > id_state = get_worst_fitness ( population , size );
	for( int i = 0 ; i < size ; i++) {
	if(population[i] == id_state.second )
	{
	population[i] = csp.first;
	break;
	}
	}
	
	 id_state = get_worst_fitness ( population , size );
	for( int i = 0 ; i < size ; i++) {
	if(population[i] == id_state.second )
	{
	population[i] = csp.second;
	break;
	}
	}
}

void maintain_population( std::string* population , int size , std::string mutated_string ) { 

	std::pair <int , string > id_state = get_worst_fitness ( population , size );
	for( int i = 0 ; i < size ; i++) {
	if(population[i] == id_state.second )
	{
	population[i] = mutated_string;
	break;
	}
	}
	
}
void print_board (std::string state) {
        
	char abc[1];
	int temp[8] = { -1 };
	queens q[8];
	for( int i = 0 ; i < 8 ; i++){
	
	abc[0] = state[i];
	q[i].x = i + 1;
	q[i].y  = atoi(abc);
	}
        int i,j;
	char ** arr = (char**)calloc(sizeof(char*),8);
	for ( i = 0 ; i < 8 ; i++) {
		arr[i] = (char*)calloc(sizeof(char),8);
	}
	
	for ( i = 0 ; i < 8 ; i++ ) {
		for ( j = 0 ; j < 8 ; j++ ) {
			arr[i][j] = ' ';
		}
	} 
	for ( i = 0 ; i < 8 ; i++ ) {
		arr[q[i].x][q[i].y] = 'x';
	}
	for ( i = 0 ; i < 8 ; i++ ) {
		printf("+---+---+---+---+---+---+---+---+\n");
		for ( j = 0 ; j < 8 ; j++ ) {
			printf("| %c ",arr[i][j]);
		}
		printf("|\n");
	}
	printf("+---+---+---+---+---+---+---+---+\n\n");
}
int main(){
std::string* pop;
pop = new std::string[2];
int size = 100;
pop  = generate_population(pop , size );

//time_t thistime; thistime=time(null);
//thistime=thistime+60*2; 




while(get_best_fitness(pop , size ).first != 28 ) {
int cur_fit = get_best_fitness(pop,size).first;
std::pair <string , string > fsp = crossover_pair(pop , size);
maintain_population(pop , size , fsp); 
 	int random_number = (std::rand()%(11)) ;
if(random_number < 9 )
{
//while ( get_best_fitness(pop , 10 ).first < cur_fit )
maintain_population(pop , size , mutate(get_best_fitness(pop , size).second) );
}

std::pair<int , string > state = get_best_fitness(pop,size);
int k = state.first;
std::string kw = state.second;
if(k==28)
{std::cout << kw  << " Final best configuration \n" ;
std::cout << count_crossover << "\n";
exit(EXIT_SUCCESS);}
}
//}

return 0;}
