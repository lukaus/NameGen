// Luke Stanley
// 	Name generator
//	copyright 2015

#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <fstream>
#include <time.h>
#include "nameGen.h"

using namespace std;

		NameGen::NameGen()
{
	for(int i = 0; i < 43; i++)
	{
		vowels[i] = i;
	}
	for(int i = 0; i < 75; i++)
	{
		consonants[i] = i;
	}

	random_shuffle(&vowels[0], &vowels[43]);
	random_shuffle(&consonants[0], &consonants[74]);
	buildList();
	buildPattern();
}

void	NameGen::buildList()
{
	ifstream inC;
	ifstream inV;
	inC.open("phoneme_consonants.dat");

	int i = 0;
	while(inC.peek() != EOF)
	{
		string temp;
		inC >> temp;
		temp.erase(temp.size()-1);
		g_consonants[i] = temp;
		i++;
	}
	int count = 0;
	inV.open("phoneme_vowels.dat");
	while(inV.peek() != EOF)
	{
		string temp;
		inV >> temp;
		temp.erase(temp.size()-1);
		g_vowels[count] = temp;
		count++;
	}

}


void 	NameGen::buildPattern()
{
	bool vFlag = false;						// flags to ensure there is a vowel and a consonant
	bool cFlag = false;
	avgPhonemes = 2 + (rand() % 6 - 2);		// Makes it 2 - 6 phonemes long												--- make this MAX_PHONEMES ?
	pattern[0] = rand() % 2;				// sets first block to vowel (0) or consonant (1) 
	if(pattern[0])							// and sets flag so we know there is at least 1 of whichever it is set to
		vFlag = true;					
	else
		cFlag = true;
	for(int j = 1; j < avgPhonemes; j++)	// then, until avgPhonemes is reached, increment excluding the one just set
	{
		if(pattern[j-1] == 2)				// if the last one set was a double consonant, make sure this is a vowel
		{	
			pattern[j] = 0;		
			vFlag = true;					// and set vFlag that there is at least one vowel
		}
		else								// otherwise
		{
			pattern[j] = rand() % 2;		// set it as randomly a vowel or consonant
			if(pattern[0])
				vFlag = true;				// and set our flags to indicate as much
			else
				cFlag = true;
			if(pattern[j-1] == 1)			// but if the last one set was a consonant,
			{
				int really = rand() % 100;	// do we really want another consonant?	
				if(really > 89)				// 90% of the time will be vowel, not double consonant						--- make this DOUBLE_CONSONANT_PERCENTAGE ?
				{
					pattern[j] = 2;		// set as double consonant
					cFlag = true;			// and set cflag to indicate at least 1 consonant (though ths should never be neccesary)
				}
				else
				{
					pattern[j] = 0;			// otherwise, its a vowel
					vFlag = true;
				}
			}
			if(j > 1 && (pattern[j-1] == 0 && pattern[j-2] == 0))	// if we are on the third or greater element and the last two have been vowels
			{
				pattern[j] = 1;				// make this one a consonant
				cFlag = true;				// and update cFlag to show we have at least one
			}
		}			
	}
	if(vFlag && cFlag)						// do we have at least 1 vowel and at least 1 consonant?
		return;								// good
	buildPattern();							// otherwise, regenerate
}

string	NameGen::getName()
{
	string name = "";
	int r = rand() % 100;
	for(int i = 0; i < avgPhonemes; i++)		// make name
	{
		r = rand() % 10;
		if(pattern[i] == 1 || pattern[i] == 2)
			name = name + g_consonants[consonants[r]];
		else
			name = name + g_vowels[vowels[r]];
	}
	if(pattern[0] == 1 && (name[0] == name[1]))	// make sure name doesnt start with the same letter twice (unless its a vowel)
	{
		for(unsigned int i = 0; i < name.size(); i ++)
		{
			name[i] = name[i+1];
		}
	}

	
	char illegal[] = {'a','f','h','i','j','n','q','r','u','v','w','x','y','z'};		// removes certain repeated characters --- find a way to remove all instances 3+
	bool doubleFlag = true;
	while(doubleFlag)
	{
		doubleFlag = false;
		for(unsigned int i = 0; i < name.size(); i++)
		{
			if(name[i] == name[i+1])
			{
				bool illegalF = false;
				for(unsigned int j = 0; j < 14; j++)
				{
					if(name[i] == illegal[j])
						illegalF = true;
				}
				if(illegalF)
				{
					doubleFlag = true;
					name.erase(name.begin() + i);
				}
			}
		}
	}

	bool multiFlag = true;
	while(multiFlag)
	{
		multiFlag = false;
		for(unsigned int k = 0; k < name.size()-1; k++)
		{
			if(name[k] == name[k+1] && name[k] == name[k+2])
			{
				multiFlag = true;
				name.erase(name.begin() + k + 1);
			}
		}
	}
	return name;
}

void NameGen::reshuffle()
{
	random_shuffle(&vowels[0], &vowels[43]);
	random_shuffle(&consonants[0], &consonants[74]);
	buildList();
	buildPattern();
	return;
}

string NameGen::getInfo()
{
	return to_string(avgPhonemes);
}