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

int main() {
  std::string digits = "01700";
  std::string sequence = "700001";
  if (possible_sequence(digits, sequence)) {
    std::cout << "Sequence is possible" << std::endl;
  } else {
    std::cout << "Sequence is not possible" << std::endl;
  }
  return 0;
}