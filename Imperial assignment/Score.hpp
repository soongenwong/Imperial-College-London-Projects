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

int main(){

  std::string s = "01700";
  std::vector<int> values = {2, 4, -1, 5, -6, 1, 0, -10, 100, -3};
  
  std::cout << score(s, values) << std::endl;

  
}