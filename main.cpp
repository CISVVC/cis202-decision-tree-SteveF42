/*
   This program will create a decision tree for an animal
   guessing game.

   
   Pseudocode has been added as a hint to help with developing this
   program
*/

#include <iostream>
#include <fstream>
#include <string>
#include<algorithm>
#include "binary_tree.h"
#include<queue>
#include<sstream>

std::string splitWord(std::string word)
{
    std::stringstream ss(word);
    std::string temp;
    std::string substr;
    int cntr = 0;
    while(ss >> temp)
    {
        if(cntr == 0){cntr = 1; continue;}

        substr += temp + " ";
    }
    //std::cout << word;
    return substr;
}

Binary_tree read(std::ifstream& in)
{
    std::string data;
    int level = 0;
    std::getline(in,data);
    level = std::atoi(data.c_str());
    data = splitWord(data);

    if(level == -1)
        return Binary_tree();

    Binary_tree left = read(in);

    Binary_tree right = read(in);

    return Binary_tree(data, left,right);
}

void write(std::ostream& out, const Binary_tree& tree, int level)
{
    if(tree.empty())
    {
        out << -1 << '\n';
        return;
    }

    out << level << ' ' << tree.data() << '\n';
    write(out,tree.left(),level+1);
    write(out, tree.right(),level+1);
}

/*
 * helper function that will help with definite or indefinite 
 * articles in a string
 */
std::string article(const std::string& entry)
{
    std::string article = "a";
    if (std::string("aeiou").find(entry[0]) != std::string::npos)
    {
        article =  "an";
    }
    return article;
}

int main(int argc,char *argv[])
{

    Binary_tree root;

    if(argc > 1)
    {  
        std::ifstream file(argv[1]);
        root = read(file);
    }
    Binary_tree questionTree = root;
    std::queue<char> pos;
    while(true)
    {

        std::string input;

        if(questionTree.left().empty() && questionTree.right().empty())
        {
            std::string question = "";

            std::cout <<"I GOT IT! ";
            std::cout << questionTree.data(); //PRINTS ANSWER
            std::cin >> input;

            if(input == "y")
            {
                std::cout << "I guessed it!\n" << "Would you like to play a again? ";
                std::cin >> input;
                std::cout << '\n';
                if(input == "y") {questionTree = root; continue;} 
                else if(input == "n"){break;}
            }
            std::cout << "I give up. What is it? ";
            std::cin >> input;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Please give me a question that is true for " << input <<  " and false for " << questionTree.data() << " ";
            getline(std::cin, question);
            root.addQuestion(question,input,pos);

            std::cout << "Would you like to play again? ";
            std::cin >> input;
            if(input == "y"){ questionTree = root; continue;}
            else{break;}
        }
        else
        {

            do
            {
                std::cout << questionTree.data();
                std::cin >> input;

            }while(input != "y" && input!= "n");
            
            if(input == "y")
            {
                pos.push('y');
                questionTree = questionTree.left();
            }
            else if(input == "n")
            {
                pos.push('n');
                questionTree = questionTree.right();
            }
        }
        
    }
    if(argc > 1)
    {
        std::ofstream out(argv[1]);
        write(out,root,0);
    }

}
