#include <string>
#include <iostream>
#include <cmath>
#include<stdio.h>
#include <string.h>
#include <vector> 
#include <bits/stdc++.h>
using namespace std;
#define coulumns 4
#define rows 2


void Find_common(string & common,string str1,string str2){
	for(int i=0;i<str1.length();i++){
		char str1_copy_char=str1[i];
		string  str1_copy="";
		str1_copy=str1_copy+str1_copy_char;
		if(i+1<str1.length() && str1[i+1]=='\''){
			i++;
			str1_copy=str1_copy+"\'";
		}
		int wrong=0;
		if (str2.find(str1_copy) != std::string::npos) {
			if(str1_copy.find("\'") == std::string::npos){
				size_t found =-1;
				while(found==string::npos){
					found = str2.find(str1_copy,found+1);
					if (found != string::npos){
						if(str2[found+1]=='\''){
							wrong=1;
						}
					}
						
				}
			}
			if(wrong==0){
    		common=common+str1_copy;
			}
		}
	}
}

void add_to_code(string & Code,string subCode){
	if(Code.length()>0){
		Code=Code+"+"+subCode;
	}else if(Code.length()==0){
		Code=subCode;
	}
}

void error(){
	cout<<"Error!! Please Enter a minterms beteen 0 and 7 separated with commas with no spaces in between";
	exit(0);
}

void swap(int & x, int & y){
	int c;
	c=x;
	x=y;
	y=c;
}

void fill_Code_letters(int x,string & Code,string Rows){
			int c=x;
			char letter=c;
			for(int i=0;i<Rows.length();i++){
				if(Rows[i]=='1'){
					Code=Code+letter;
				}
				else if(Rows[i]=='0'){
					Code=Code+letter+"\'";
				}
				c++;
				letter=c;
			}
}

void fill_array_with_grey_code(vector<string> & greycode_array,int n) 
{
	if (n <= 0) 
		return; 
		
	greycode_array.push_back("0"); 
	greycode_array.push_back("1"); 
	for (int i = 2; i < pow(2,n); i*=2) 
	{ 
		for (int j = i-1 ; j >= 0 ; j--) {
			greycode_array.push_back(greycode_array[j]);
		}
		for (int j = 0 ; j < i ; j++) {
			greycode_array[j] = "0" + greycode_array[j]; 
		}
		for (int j = i ; j < 2*i ; j++) {
			greycode_array[j] = "1" + greycode_array[j]; 
		}
	} 
}

int main() {
	string Code="";
	vector<string> Horizontal_greycode_array; 
	vector<string> Vertical_greycode_array; 
	fill_array_with_grey_code(Horizontal_greycode_array,2); 
	fill_array_with_grey_code(Vertical_greycode_array,1); 
	char Input[15];
	int min_array[15];
	cout<<"Please enter the minterms separated with commas without any spaces:\n";
	cin>>Input;
   char * token = strtok(Input, ",");
   int count=0;
   while( token != NULL ) {
      min_array[count]=atoi(token);
      count++;
      if(count>=15){
      	error();
      }
      token = strtok(NULL, ",");
   }
  
	int array[rows][coulumns];
	 for(int i=0;i<rows;i++){
	 	for(int j=0;j<coulumns;j++){
	 		array[i][j]=0;
	 	}
	 }
	 for(int k=0;k<count;k++){
	 	int i=0;
	 	int j=min_array[k];
	 	if(j<0 || j>=8){
	 		error();
	 	}
	 	if(j>coulumns-1){
	 		while(j>coulumns-1){
	 			j=j-coulumns;
	 			i++;
	 		}
	 	}
	 	if(i<0 || i>=2 || j<0 || j>=4){
	 		error();
	 	}
	 	array[i][j]=1;
	 }
	 
	 cout<<"The enterd k-map is:\n";
	 
	 swap(array[0][2],array[0][3]);
	 swap(array[1][2],array[1][3]);
	 
	for(int i=0;i<2;i++){
		for(int j=0;j<4;j++){
			cout<<array[i][j];
		}
		cout<<endl;
	}
	int array_checks[rows][coulumns];
	for(int i=0;i<rows;i++){
		for(int j=0;j<coulumns;j++){
			array_checks[i][j]=array[i][j];
		}
	}
	
	for(int i=0;i<rows;i++){
		int counter=0;
		for(int j=0;j<coulumns;j++){
			if(array_checks[i][j]==1){
				counter++;
			}
		}
		if(counter==coulumns){
			
			for(int j=0;j<coulumns;j++){
				array_checks[i][j]=0;
			}
			string subCode="";
			fill_Code_letters(65,subCode,Vertical_greycode_array[i]);
			add_to_code(Code,subCode);
		}
	}
	
	for(int i=0;i<rows;i++){
		int counter=0;
		int planB=0;
		int planC=0;
		int planD=0;
		int planE=0;
		int planF=0;
		for(int j=0;j<coulumns;j++){
			counter=0;
			planB=0;
			planC=0;
			planD=0;
			planE=0;
			planF=0;
			if(array_checks[i][j]==1){
				if(i+1<=rows-1 && array[i+1][j]==1){ //down cell
					counter++;
					planC=1;
				}
				
				if(i-1>=0 && array[i-1][j]==1 && planC!=1){ //up cell
					counter++;
					planC=2;
				}
				
				if(coulumns-j-1>=0 && array[i][coulumns-j-1]==1 ){ //right reflection cell
					counter++;
					planD=1;
					planC=planC*-1;
				}
				if(rows-i-1>=0 && coulumns-j-1>=0 && array[rows-i-1][coulumns-j-1]==1){ //right down reflection cell
						counter++;
						if(counter>=3){
							planD=2;
							planC=planC>0?planC*-1:planC;
						}
					}
					
				if(j+1<=coulumns-1 && array[i][j+1]==1 && planD==0 && !((coulumns-j-1)==(j+1)) ){ //right cell
					planE=1;
					if(array[i+1][j+1]==1 && (planC==1 || planC==-1)){ //rigth down
						planE=2;
						planC=-1;
					}
					if(array[i-1][j+1]==1 && (planC==2 || planC==-2)){ //rigth up
						planE=3;
						planC=-2;
					}
					planC=planC>0?planC*-1:planC;
				}
				if(planC==1 && planD==0 && j-1>=0 && i+1<=rows-1 && array[i+1][j-1]==1 && array[i][j-1]==1){ //left down cell with left cell
					planB=3;
					planC=planC>0?planC*-1:planC;
				}
				
				if(planC==2 && planD==0 && j-1>=0 && i-1>=0 && array[i-1][j-1]==1 && j-1>=0 && array[i][j-1]==1){ //left up cell with left cell
					planB=2;
					planC=planC>0?planC*-1:planC;
				}
				if(planC==0 && planD==0 && j-1>=0 && array[i][j-1]==1){ //left cell
					planB=1;
				}
				if(planB==0 && planC==0 && planD==0 && planE==0){ //one cell
					planF=1;
				}
				
				if(planC==1){//down cell
					
					string subCode="";
					fill_Code_letters(65+1,subCode,Horizontal_greycode_array[j]);
					string str1="";
					string str2="";
					fill_Code_letters(65,str1,Vertical_greycode_array[i]);
					fill_Code_letters(65,str2,Vertical_greycode_array[i+1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i+1][j]=0;
				}
				
				if(planC==2){//up cell
					
					string subCode="";
					fill_Code_letters(65+1,subCode,Horizontal_greycode_array[j]);
					string str1="";
					string str2="";
					fill_Code_letters(65,str1,Vertical_greycode_array[i]);
					fill_Code_letters(65,str2,Vertical_greycode_array[i-1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i-1][j]=0;
				}
				
				if(planD==1){//right reflection cell
					
					string subCode="";
					fill_Code_letters(65,subCode,Vertical_greycode_array[i]);
					string str1="";
					string str2="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					fill_Code_letters(65+1,str2,Horizontal_greycode_array[coulumns-j-1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i][coulumns-j-1]=0;
					
				}
				
				if(planD==2){//right down reflection cell
					
					string subCode="";
					
					string str1="";
					string str2="";
					fill_Code_letters(65,str1,Vertical_greycode_array[i]);
					fill_Code_letters(65,str2,Vertical_greycode_array[rows-i-1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
				
					
					str1="";
					str2="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					fill_Code_letters(65+1,str2,Horizontal_greycode_array[coulumns-j-1]);
					common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i][coulumns-j-1]=0;
					array_checks[rows-i-1][j]=0;
					array_checks[rows-i-1][coulumns-j-1]=0;
				}
				
				if(planE==1){//right cell
					
					string subCode="";
					fill_Code_letters(65,subCode,Vertical_greycode_array[i]);
					string str1="";
					string str2="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					fill_Code_letters(65+1,str2,Horizontal_greycode_array[j+1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i][j+1]=0;
					
					
				}
				
				if(planE==2){//right down cell
					
					string subCode="";
					
					string str1="";
					string str2="";
					fill_Code_letters(65,str1,Vertical_greycode_array[i]);
					fill_Code_letters(65,str2,Vertical_greycode_array[i+1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
				
					
					str1="";
					str2="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					fill_Code_letters(65+1,str2,Horizontal_greycode_array[j+1]);
					common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i][j+1]=0;
					array_checks[i+1][j]=0;
					array_checks[i+1][j+1]=0;
				}
				
				if(planE==3){//right up cell
					
					string subCode="";
					
					string str1="";
					string str2="";
					fill_Code_letters(65,str1,Vertical_greycode_array[i]);
					fill_Code_letters(65,str2,Vertical_greycode_array[i-1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
				
					
					str1="";
					str2="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					fill_Code_letters(65+1,str2,Horizontal_greycode_array[j+1]);
					common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i][j+1]=0;
					array_checks[i-1][j]=0;
					array_checks[i-1][j+1]=0;
				}
				
				if(planB==3){//left down cell with left cell
					
					string subCode="";
					
					string str1="";
					string str2="";
					fill_Code_letters(65,str1,Vertical_greycode_array[i]);
					fill_Code_letters(65,str2,Vertical_greycode_array[i+1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
				
					
					str1="";
					str2="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					fill_Code_letters(65+1,str2,Horizontal_greycode_array[j-1]);
					common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i][j-1]=0;
					array_checks[i+1][j]=0;
					array_checks[i+1][j-1]=0;
				}
				
				if(planB==2){//right up cell
					
					string subCode="";
					
					string str1="";
					string str2="";
					fill_Code_letters(65,str1,Vertical_greycode_array[i]);
					fill_Code_letters(65,str2,Vertical_greycode_array[i-1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
				
					
					str1="";
					str2="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					fill_Code_letters(65+1,str2,Horizontal_greycode_array[j-1]);
					common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i][j-1]=0;
					array_checks[i-1][j]=0;
					array_checks[i-1][j-1]=0;
				}
				
				if(planB==1){//left cell
				
					string subCode="";
					fill_Code_letters(65,subCode,Vertical_greycode_array[i]);
					string str1="";
					string str2="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					fill_Code_letters(65+1,str2,Horizontal_greycode_array[j-1]);
					string common="";
					Find_common(common,str1,str2);
					subCode=subCode+common;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
					array_checks[i][j-1]=0;
					
				}
				
				if(planF==1){//one cell
				
					string subCode="";
					fill_Code_letters(65,subCode,Vertical_greycode_array[i]);
					string str1="";
					fill_Code_letters(65+1,str1,Horizontal_greycode_array[j]);
					subCode=subCode+str1;
					add_to_code(Code,subCode);
					array_checks[i][j]=0;
				}
				
				
					
				}
				
				
			}
		}
	cout<<"The simplified Boolean expression for this k-map is:\n";
	cout<<Code;
	return 0;
}