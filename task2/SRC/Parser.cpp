#include "Parser.h"

Vector* Parser::ParseVector(string raw)
{ 
	string firsInbraceString = raw.substr(
		raw.find_first_of('[') + 1,
		raw.find_first_of(']') - raw.find_first_of('[') - 1
	);
	string lastInbraceString = raw.substr(
		raw.find_last_of('[') + 1,
		raw.find_last_of(']') - raw.find_last_of('[') - 1
	);
	
	return new Vector(ParsePoint(firsInbraceString), ParsePoint(lastInbraceString));
}

Entity* Parser::ParseInputString(string raw)
{
	Vector* line = NULL;
	Sphere* sphere = NULL;
	string str = ignoreBaseBraces(raw);
	int firstBracePos = str.find_first_of('}');
	string firstObjectDescription = str.substr(0, firstBracePos + 1);
	string secondObjectDescription = str.substr(
		str.find_first_not_of(',', firstBracePos + 1)
	);
	string firstObjectTag = GetTag(firstObjectDescription);
	string secondObjectTag = GetTag(secondObjectDescription);

	if (firstObjectTag.compare(LINE) == 0)
	{
		string sphereDescription = secondObjectDescription.substr(
			secondObjectDescription.find_first_of('{') + 1,
			secondObjectDescription.find_last_of('}') - secondObjectDescription.find_first_of('{') - 1

		);
		line = ParseVector(firstObjectDescription);
		sphere = ParseSphere(secondObjectDescription);
	}
	else
	{
		string sphereDescription = firstObjectDescription.substr(
			firstObjectDescription.find_first_of('{') + 1,
			firstObjectDescription.find_last_of('}') - firstObjectDescription.find_first_of('{') - 1

		);
		sphere = ParseSphere(firstObjectDescription);
		line = ParseVector(secondObjectDescription);
	}

	return new Entity(line, sphere);
}
Sphere* Parser::ParseSphere(string raw)
{
	Sphere* sphere = NULL;
	raw = ignoreBaseBraces(raw);
	string firstTag = GetTag(raw);
	if (firstTag.compare(CENTER) == 0)
	{
		int posAfterComma = raw.find_first_of(']') + 2;
		string firstSubString = raw.substr(raw.find_first_of('{') + 1, raw.find_first_of(']') - raw.find_first_of('{'));
		string secondSubString = raw.substr(posAfterComma, raw.length() - posAfterComma - 1);
		sphere = new Sphere(
			ParsePoint(firstSubString), 
			Radius(ParseDouble(
				secondSubString.substr(secondSubString.find_first_of(':') + 1, 
					secondSubString.length() - secondSubString.find_first_of(':')
			)
			)));
	}
	else
	{
		int commaPos = raw.find_first_of(',');
		int firstColonPos = raw.find_first_of(':');
		string firstSubString = raw.substr(firstColonPos + 1, commaPos - firstColonPos - 1);
		int firstBracePos = raw.find_first_of('[');
		string secondSubString = raw.substr(firstBracePos + 1, raw.length() - firstBracePos - 2);
		sphere = new Sphere(
			ParsePoint(secondSubString),
			Radius(ParseDouble(
				firstSubString.substr(firstSubString.find_first_of(':') + 1,
					firstSubString.length() - firstSubString.find_first_of(':')
				)
			)));
	}
	return sphere;
}

Point Parser::ParsePoint(string raw)
{
	double parsedVals[3];
	raw = raw.substr(
		raw.find_first_of('[') + 1,
		raw.length() - raw.find_first_of('[') - 1
	);
	for (int i = 0; i < 3; i++)
	{
		int firstCommaPos = raw.find_first_of(',');
		string sub = raw.substr(0, firstCommaPos);
		parsedVals[i] = ParseDouble(sub);
		raw = raw.substr(firstCommaPos + 1, raw.length() - firstCommaPos);
	}
	return Point(parsedVals[0], parsedVals[1], parsedVals[2]);
}

double Parser::ParseDouble(string raw)
{
	char** end = NULL;
	return strtod(raw.c_str(), end);
}

string Parser::GetTag(string raw)
{
	if (raw.find_first_of('{') == 0) return PARENT;
	else
	{
		string tag = raw.substr(0, raw.find_first_of(':'));
		if (tag.compare(SPHERE) != 0 &&
			tag.compare(CENTER) != 0 &&
			tag.compare(RADIUS) != 0 &&
			tag.compare(LINE) != 0)
		{
			throw std::runtime_error("Tag not defined!\n");
		}
		return tag;
	}
}

string Parser::ignoreBaseBraces(string raw)
{
	return raw.substr(
		raw.find_first_of('{') + 1,
		raw.find_last_of('}') - raw.find_first_of('{') - 1
	);
}

string Parser::GetInbraceString(string raw, char openingBrace, char clothingBrace)
{
	string inbraceString;
	int openingBracePos = 0;
	int closingBracePos = 0;
	openingBracePos = raw.find_first_of(openingBrace);
	closingBracePos = raw.find_last_of(clothingBrace);
	inbraceString = raw.substr(openingBracePos + 1, closingBracePos - openingBracePos - 1);
	return inbraceString;
};