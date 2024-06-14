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

   int nd = 0, ns = 0;
   //nd = number of occurrences of digits, ns = number of occurrences of sequence. 

   for(int n = 0; n < 9; n ++){

      for(int i = 0; i < Vdigits.size(); i++){

        if (Vdigits[i] == n){
          nd++;
        }
      }
     for (int j = 0; j < Vsequence.size(); j++){
       if (Vsequence[j] == n){
         ns++;
       }
     }
     if (nd < ns){
       return false;
     }
     else {
       nd = 0;
       ns = 0;
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
  std::string digits = "01700";
  std::vector<std::string>allowed = {"476234", "017", "70", "100", "770", "00", "3443", "01", "653", "1268", "7001", "111111", "56356"};
  std::vector<int> values = {2, 4, -1, 5, -6, 1, 0, -10, 100, -3};
  std::string best_sequence;

  int best_score = get_best_sequence(digits, allowed, values, best_sequence);
  
  std::cout << "best sequence: " << best_sequence << std::endl;
  std::cout << "best score :" << best_score << std::endl;
}