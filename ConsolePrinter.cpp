#include "ConsolePrinter.h"
#include "rang.h"
#include <iostream>
#include <cmath>
#include <iomanip>

/* 
To be finished
*/

using namespace std;

std::string operator*(std::string const & string, std::string::size_type times)
{
	std::string sum;

	for(size_t count = 0; count < times; ++count)
	{
		sum.append(string);
	}

	return sum;
}

std::string operator*(std::string::size_type times, std::string const & string)
{
	return string * times;
}

// set colors used in the drawing
#define FG_COLOR_LINE rang::fgB::green << rang::style::reset
#define FG_COLOR_LABEL rang::fg::reset
#define FG_COLOR_SCORE rang::fg::gray
#define FG_COLOR_LETTER rang::fg::reset << rang::style::bold
#define FG_COLOR_MULTIPLIER rang::fg::gray
#define FG_COLOR_HEADING rang::fgB::blue << rang::style::bold

#define BG_COLOR_NORMAL_SQUARE rang::bgB::black
#define BG_COLOR_START_SQUARE rang::bg::cyan
#define BG_COLOR_OUTSIDE_BOARD rang::bg::reset
#define BG_COLOR_WORD_MULTIPLIER_2X rang::bg::red
#define BG_COLOR_WORD_MULTIPLIER_3X rang::bgB::red
#define BG_COLOR_LETTER_MULTIPLIER_2X rang::bg::blue
#define BG_COLOR_LETTER_MULTIPLIER_3X rang::bgB::blue
#define BG_COLOR_PLAYER_HAND rang::bg::green

// Unicode line-drawing character constants
// from https://en.wikipedia.org/wiki/Box-drawing_character
const std::string horizLine("\u2500");
const std::string vertLine("\u2502");
const std::string topLeftCorner("\u250c");
const std::string topRightCorner("\u2510");
const std::string bottomLeftCorner("\u2514");
const std::string bottomRightCorner("\u2518");
const std::string downwardsT("\u252c");
const std::string upwardsT("\u2534");
const std::string rightFacingT("\u251c");
const std::string leftFacingT("\u2524");
const std::string cross("\u253c");

const std::string space(" ");

void printBoard (const Board &gameboard)
{
	
}