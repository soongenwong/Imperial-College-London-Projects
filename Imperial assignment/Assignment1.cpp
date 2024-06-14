#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string> 

std::vector<int> string_to_digits(std::string s){

    std::vector<int> out; 

    for(int i = 0; i < s.size(); i++){

       std::string digit_string;
       digit_string.push_back(s[i]);

       int digit_int = std::stoi(digit_string);

       out.push_back(digit_int);

    }

    return out;

    //the function returns the vector 'out' containing the individual digits. 

}

bool possible_sequence(std::string digits, std::string sequence){

   std::vector<int> Vdigits = string_to_digits(digits);
   std::vector<int> Vsequence = string_to_digits(sequence);

   int numberd = 0, numbers = 0;
   //numberd = number of times digit appears in digits, numbers = number of times digit appears in sequence. 

   for(int n = 0; n < 9; n ++){

      for(int i = 0; i < Vdigits.size(); i++){

        if (Vdigits[i] == n){
          numberd++;
        }
      }
     for (int j = 0; j < Vsequence.size(); j++){
       if (Vsequence[j] == n){
         numbers++;
       }
     }
     if (numberd < numbers){
       return false;
     }
     else {
       numberd = 0;
       numbers = 0;
     }
   }
   return true;
}

int score(std::string s, const std::vector<int>& values){
    int score = 0, consecutive_count = 1, consecutive_score = 0;

    std::vector<int> v = string_to_digits(s);

    for(int i = 0; i < v.size() - 1; i++){

      consecutive_score = consecutive_score + values[v[i]];

      if(v[i] == v[i+1] - 1){

        consecutive_count = consecutive_count + 1;
      }

      else{

        score = score + consecutive_score * consecutive_count;

        consecutive_count = 1;
        consecutive_score = 0;
      }
    }

  consecutive_score = consecutive_score + values[v[v.size() - 1]];
  score = score + consecutive_score * consecutive_count;

  return score;

}
int get_best_sequence(std::string digits, const std::vector<std::string>& allowed, const std::vector<int>& values, std::string& best_sequence){


  std::vector<int> Vdigits = string_to_digits(digits);
  std::vector<std::string> Vallowed = allowed;
  std::vector<std::string> Vbest_sequence;
  
  int current_score = 0, best_score = 0;

  for (int i = 0; i < Vallowed.size(); i++){

    if(possible_sequence(digits, allowed[i])){
      Vbest_sequence.push_back(allowed[i]);
    }
  }

  for (int j = 0; j < Vbest_sequence.size(); j++){

    current_score =  score(Vbest_sequence[j], values);

    if(current_score > 0){
      
      if(current_score > best_score){
        best_score = current_score;
        best_sequence = Vbest_sequence[j];
      }
    }
    else{
      best_sequence = Vbest_sequence[j];
      best_score = current_score;
    }
  }
  return best_score;
}

int main(){

//first input file

    std::string inputfilename1;
    
    std::cout << "enter name of first input file" << std::endl;

    std::cin >> inputfilename1;

    std::ifstream infile1; 
    infile1.open("allowed.txt");

    if(!infile1.is_open()){
      std::cout << "error opening file" << std::endl;
      return EXIT_FAILURE;
    }

    int tmp1;
    std::vector<int>v1;

    while (infile1 >> tmp1){
      v1.push_back(tmp1);
    }

    infile1.close();

//second input file


    std::string inputfilename2;

    std::cout << "enter name of second input file" << std::endl;

    std::cin >> inputfilename2;
  
    std::ifstream infile2; 
    infile2.open("values.txt");

    if(!infile2.is_open()){
      std::cout << "error opening file" << std::endl;
      return EXIT_FAILURE;
    }

    int tmp2;
    std::vector<int>v2;

    while (infile2 >> tmp2){
      v2.push_back(tmp2);
    }

    infile2.close();

//third input file

    std::string inputfilename3;

    std::cout << "enter name of third input file" << std::endl;

    std::cin >> inputfilename3;
  
    std::ifstream infile3; 
    infile3.open("rounds.txt");

    if(!infile3.is_open()){
      std::cout << "error opening file" << std::endl;
      return EXIT_FAILURE;
    }

    int tmp3;
    std::vector<int>v3;

    while (infile3 >> tmp3){
      v3.push_back(tmp3);
    }

    infile3.close();

//output file

    std::string outputfilename;

    std::cout << "enter name of output file" << std::endl;

    std::cin >> outputfilename;

    std::ofstream outfile;
    outfile.open("output.txt");

    if(!outfile.is_open()){
      std::cout << "error opening file" << std::endl;
      return EXIT_FAILURE;
    }

    std::string digits;
    
    std::vector<std::string> allowed;
    for(int i = 0; i < v1.size(); i++){
      allowed.push_back(std::to_string(v1[i]));
    }
  
    std::vector<int> values = v2;
  
    std::string best_sequence;

    for(int i=0; i<v3.size(); i++){
      int best_score = get_best_sequence(digits, allowed, values, best_sequence);
      outfile << v3[i] << " " << best_sequence << " " << best_score << std::endl;
    }
    outfile << std::endl;

    outfile.close();
}