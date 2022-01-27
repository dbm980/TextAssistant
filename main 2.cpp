//
//  main.cpp
//  textAss
//
//  Created by Period 1 on 2021-09-29.
//  Copyright © 2021 Cyber1. All rights reserved.
//


/*
 Plans:
 -help
 -simple calculations
 -contacs
 -joke
 -how are you?
 -calendars
 -timers or alarms? https://www.geeksforgeeks.org/multithreading-in-cpp/
 -*DONE* If all else fails, google it
 
 
 */

#include <iostream>
#include <vector>
#include <regex>

using namespace std;


string input;
string useless;
char letter;
bool doRepeat;
int numMatches;

//the first regular expression matches with the last word in a string, and the space that precedes it. The second regex matches with the first word of a string and the following space.
regex regexr("\\s+\\w+$");
regex regexp("^\\w+\\s+");

//used to store information about different user commands
struct infos {
    string name, description, tutorial, credit;
};


// used for stringFixerUpper
struct findReplace {
    char find, replace;
};

findReplace unused;

// function to edit strings, by removing characters, replacing characters, and making characters lowercase
string stringFixerUpper (string input, string unwantedChars, bool swapAndReplace, findReplace swap, bool allLowerCase){
    
    //LIMITATION: only swaps and replaces one set of chars
    
    char inputCharArray[int(input.length())];
    strcpy(inputCharArray, input.c_str());
    
    char unwantedCharArray[int(unwantedChars.length())];
    strcpy(unwantedCharArray, unwantedChars.c_str());
    
    
    
    for (int i = 0; i < int(input.length()); i++){
        for (int j = 0; j < int(unwantedChars.length()); j++){
            if (inputCharArray[i] == unwantedCharArray[j]){
                inputCharArray[i] = NULL;
            }
        }
        if (swapAndReplace){
            if (inputCharArray[i] == swap.find){
                inputCharArray[i] = swap.replace;
            }
        }
        
        if(allLowerCase){
            inputCharArray[i]=tolower(inputCharArray[i]);
        }
    }
    
    int k;
    string s = "";
    int arrSize = int(sizeof(inputCharArray)/sizeof(inputCharArray[0]));
    for (k = 0; k < arrSize; k++) {
        s = s + inputCharArray[k];
    }
    
    k = 0;
    
    return s;
}



//contacts stuff
struct contact {
    string firstName,lastName;
    long int num;
};


//class for everything to do with contacts
class contactButClass {
    contact inUse;
    int inUseID;
    
    //vector to store contacts
    vector<contact> contactMem;
    
public:
    
    //create a contact with name and phone number
    void createContact(string first, string last, long int num){
        inUse.firstName = first;
        inUse.lastName = last;
        inUse.num = num;
        
        contactMem.push_back(inUse);
        
        
        cout << "Contact created for " << inUse.firstName << " " << inUse.lastName << ".\n";
    }
    
    //search through contacts with name
    void recallContact(string first, string last){
        numMatches = 0;
        
        if (first.length() > 0){
            for( int i = 0; i < contactMem.size(); i++) {
                            }
            
        }
        
        for( int i = 0; i < contactMem.size(); i++) {
            if (last.length() > 1){
                if(stringFixerUpper(last, " ", false, unused, true) == stringFixerUpper(contactMem[i].lastName, " ", false, unused, true) && stringFixerUpper(first, " ", false, unused, true) == stringFixerUpper(contactMem[i].firstName, " ", false, unused, true)){
                    numMatches++;
                    inUseID = i;
                    
                    cout << "\tContact found! Contact ID: " << inUseID << endl;
                    cout << "\tFirst name: " << contactMem[inUseID].firstName << endl;
                    cout << "\tLast name: " << contactMem[inUseID].lastName << endl;
                    cout << "\tPhone Number: " << contactMem[inUseID].num << endl;
                }
                
            } else if (first.length() > 1){
                if(stringFixerUpper(first, " ", false, unused, true) == stringFixerUpper(contactMem[i].firstName, " ", false, unused, true)){
                    numMatches++;
                    inUseID = i;
                    
                    cout << "\tContact found! Contact ID: " << inUseID << endl;
                    cout << "\tFirst name: " << contactMem[inUseID].firstName << endl;
                    cout << "\tLast name: " << contactMem[inUseID].lastName << endl;
                    cout << "\tPhone Number: " << contactMem[inUseID].num << endl;
                }

            }
            
        }
        if (numMatches < 1){
            cout << "\tHmm, I couldn't find a contact saved under that name. Would you like to create one?\n\t";
            getline(cin, input);
            cin.sync();
            if (stringFixerUpper(input, " ", false, unused, true).find("ye") != string::npos){
                if (first.length() > 0){
                    inUse.firstName = first;
                } else {
                    cout << "\tPlease input the first name of this contact.\n\t";
                    getline(cin, inUse.firstName);
                    cin.sync();
                }
                if (last.length() > 0){
                    inUse.lastName = last;
                } else {
                    cout << "\tPlease input the last name of this contact.\nt";
                    getline(cin, inUse.lastName);
                    cin.sync();
                }
                cout << "\tPlease enter " + inUse.firstName + "'s phone number. Do not put spaces in the number.\n\t";
                input = "";
                getline(cin, input);
                cin.sync();
                input = stringFixerUpper(input, "abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+<>?,./", false, unused, false);
                inUse.num = stol(input, nullptr, 10);
                contactMem.push_back(inUse);
                cout << "\tContact created for " << inUse.firstName << " " << inUse.lastName << ".\n";
            }
        }
    }
    
    //if the user searched for a contact (and found one), delete the result
    void deleteContact(){
        string confirm;
        if (numMatches == 1){
            cout << "\tAre you sure you want to erase your contact stored for " << inUse.firstName << " " << inUse.lastName << "?\n\t";
            getline(cin, confirm);
            if (confirm == "yes"){
                contactMem.erase(contactMem.begin()+inUseID);
                cout << "\tContact erased.\n";
            } else {
                cout << "\tOk, cancelled.\n";
            }
        
        } else {
            cout << "\tPlease find a contact to erase first.\n";
        }
    
    }
    //prints a list of all contacts
    void listContacts(){
        for( int i = 0; i < contactMem.size(); i++) {
            cout << "\tContact found! Contact ID: " << i << endl;
            cout << "\tFirst name: " << contactMem[i].firstName << endl;
            cout << "\tLast name: " << contactMem[i].lastName << endl;
            cout << "\tPhone Number: " << contactMem[i].num << endl;
        }
        if (contactMem.size() < 1){
            cout << "\tYou have no stored contacts.\n";
        }
    }
};

//initializes the contact class. May as well do it here.
contactButClass init;



//google search
void googleSearch(string input) {
    
    findReplace spaceToPlus;
    spaceToPlus.find = ' ';
    spaceToPlus.replace = '+';
    
    string myString = "open https://google.com/search?q=" + stringFixerUpper(input, "?/!@#$%^&*()'", true, spaceToPlus, true);
    
    
    char cmd[64];
    strcpy(cmd, myString.c_str());
    system(cmd);
}

// the main function for the text assistant. Depends on the above functions
void siri(){
    
    bool repeatSiri = true;
    do{
        cin.clear();
        input = "";
        cout << "\t";
        getline(cin, input);
        
        
        long int num = 0;
        string firstName = "";
        string lastName = "";
        
        if (stringFixerUpper(input, " ", false, unused, true).find("create") != string::npos || stringFixerUpper(input, " ", false, unused, true).find("add") != string::npos){
            
            if(stringFixerUpper(input, " ", false, unused, true).find("contact") != string::npos){
                cout << "\tPlease enter first name, last name, and phone number. Do not put spaces in the number.\n";
                
                cout << "\t";
                cin >> firstName;
                cout << "\t";
                cin >> lastName;
                cin >> num;
                init.createContact(firstName, lastName, num);
                
                cin.sync();
                getline(cin, useless);
            } else {
                cout << "\tBruh. Try adding something else.\n";
            }
            
        } else if(stringFixerUpper(input, " ", false, unused, true).find("retrieve") != string::npos || stringFixerUpper(input, " ", false, unused, true).find("find") != string::npos|| stringFixerUpper(input, " ", false, unused, true).find("recall") != string::npos) {
            
            if(stringFixerUpper(input, " ", false, unused, true).find("contact") != string::npos){
                
                cout << "\tPlease enter first name.\n\t";
                getline(cin, firstName);
                cout << "\tPlease enter last name, or hit enter to ignore.\n\t";
                getline(cin, lastName);
                init.recallContact(firstName, lastName);
                
                
            }
            
        } else if(stringFixerUpper(input, " ", false, unused, true).find("list") != string::npos) {
            
            if(stringFixerUpper(input, " ", false, unused, true).find("contact") != string::npos){
                init.listContacts();
            }
            
        }else if(stringFixerUpper(input, " ", false, unused, true).find("remove") != string::npos || stringFixerUpper(input, " ", false, unused, true).find("erase") != string::npos|| stringFixerUpper(input, " ", false, unused, true).find("delete") != string::npos) {
            
            if(stringFixerUpper(input, " ", false, unused, true).find("contact") != string::npos){
                init.deleteContact();
            }
            
        } else if (stringFixerUpper(input, " ", false, unused, true).find("search") != string::npos || stringFixerUpper(input, " ", false, unused, true).find("lookup") != string::npos || stringFixerUpper(input, " ", false, unused, true).find("look up") != string::npos || stringFixerUpper(input, " ", false, unused, true).find("google") != string::npos){
            
            
            string stringy = regex_replace(input, regexp, "");
            
            googleSearch(stringy);
        } else if (stringFixerUpper(input, " ", false, unused, true) == "quit"){
            repeatSiri = false;
            cout << "\tToodles. :)\n";
        } else if (stringFixerUpper(input, " ", false, unused, true) == "bruh"){
            cout << "\tIndeed.\n";
        } else if (stringFixerUpper(input, " ", false, unused, true).find("thank") != string::npos){
            cout << "\tYou're wecome!\n";
        } else {
            cout << "\tSorry, I didn't catch that.\n";
            
        }
        cout << endl;
        
    
    }while (repeatSiri);
    
    
}

//terminal simulation, intro into the text assistant
//makes it easier to use (I think) and includes a tutorial by typing help
int main(){
    
    //creates a vector to store and organize information about the different teminal commands
    
    vector<infos> infovector;
    
    infos help;
    help.description = "Shows information about the console version, as well as a description for each command.";
    help.tutorial = "Type help to list possible commands.";
    help.name = "help";
    help.credit = "Written by James Green in Fall 2021. Registered under GNU GPL.";
    infovector.push_back(help);
    
    
    infos quit;
    quit.description = "Exits the program.";
    quit.tutorial = "Type quit to exit the terminal.";
    quit.name = "quit";
    quit.credit = "Written by James Green in Fall 2021. Registered under GNU GPL.";
    infovector.push_back(quit);
    
    
    infos textass;
    textass.description = "Text assistant for managing contacts and searching the web. More features coming soon.";
    textass.tutorial = "Text assistant can:\n\n\t- Search the internet by tying 'search', 'lookup', or 'google' superceded by the search\n\n\t- Create contacts by typing 'create contact' or 'add contact'\n\n\t- Find contacts by typing 'find contact', 'recall contact', or 'retrieve contact'\n\n\t- Delete contact recently searched with the above command. Will ask for confirmation.";
    textass.name = "textass";
    textass.credit = "Written by James Green in Fall 2021. Registered under GNU GPL.";
    infovector.push_back(textass);
    
    
    infos clear;
    clear.description = "Clears the screen.";
    clear.tutorial = "Type 'clear' to print new lines, freeing up screen space.";
    clear.name = "clear";
    clear.credit = "Written by James Green in Fall 2021. Registered under GNU GPL.";
    infovector.push_back(clear);
    
    // The simulated terminal, which repeats until quit
    do{
        cout << "Period1@EARL-R308-M009:~$ ";
        
        //inputs a string
        getline(cin, input);
        cin.sync();
        
        //removes unrecognized characters from input string
        input = stringFixerUpper(input, "", false, unused, false);
        
        //checks if the input string is a command
        if(stringFixerUpper(input, "", false, unused, false) == "help") {
            cout << "GNU bash, version 4.4.20(1)-release (x86_64-pc-osx-gnu)\nThese shell commands are defined internally. Type 'help' to see this list.\nType man 'command' to see a tutorial for 'command'.\n\nPossible commands:\n\n";
            for(int l = 0; l < 4; l++){
                cout << infovector[l].name << ": " << infovector[l].description << "\n\n";
            }
            doRepeat=true;
        } else if(input == "quit") {
            cout << "Goodbye.\n";
            doRepeat = false;
        } else if(input == "textass") {
            cout << "\n\tHi, I'm TextAss. What can I do for you?\n\n";
            siri();
            doRepeat = true;
        } else if(input == "clear") {
            for(int x; x < 32; x++){
                cout << "\n";
            }
            doRepeat = true;
        } else if(regex_replace(input, regexr, "") == "man") {
            
            for(int l = 0; l < (sizeof(infovector)-1); l++){
                
                if(regex_replace(input, regexp, "") == infovector[l].name){
                    cout << infovector[l].name << ":\n" << infovector[l].tutorial << "\n\n" << infovector[l].credit << endl;
                }
                
            }
            
            doRepeat = true;
            //If the input does not match with anything
        } else {
            cout << "Sorry, unrecognized command. Please try again.\n";
            cout << "Your entered command was:\n'" << input << "'\n";
            doRepeat=true;
        }
        
        cout << endl;
        
    }while(doRepeat);
    
    return 0;
}
