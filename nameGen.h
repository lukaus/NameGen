// Luke Stanley
// Creates an object to generate a cultural group of phonemes to generate names with

#ifndef NAMEGEN_H
#define NAMEGEN_H
#include <string>

using std::string;

class NameGen
{
public:
	NameGen();

	void 	buildList();
	void 	buildPattern();
	void	reshuffle();
	string	getInfo();
	string 	getName();

private:
	void setSeed();
	int avgPhonemes;
	string g_vowels[43];
	string g_consonants[74];
	int vowels[43];
	int consonants[74];
	int pattern[10];	// o for vowel, 1 for consonant, 3 for double consonant (which always is preceded by a vowel)
};
#endif