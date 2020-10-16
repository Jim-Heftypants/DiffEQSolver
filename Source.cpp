#include <iostream>
#include <string>

using namespace std;

string findVariablePower(string integrand, char variable) {
	int pLocation = 0;
	bool checker = false;
	bool check2 = false;
	while (integrand[pLocation] != '(' && pLocation < integrand.length()) {
		if (integrand[pLocation] == variable) {
			checker = true;
			if (pLocation == integrand.length() - 1) {
				check2 = true;
			}
		}
		pLocation++;
	}
	if (checker == false) {
		return "0";
	}
	if (check2) {
		return "1";
	}
	pLocation++;
	int secLocation = pLocation;
	while (integrand[secLocation] != ')' && secLocation < integrand.length()) {
		secLocation++;
	}
	return integrand.substr(pLocation, (secLocation - pLocation));
}

string findVariableCoefficient(string integrand, char variable) {
	if (integrand.length() == 1) {
		return "1";
	}
	int varLocation = 0;
	while (integrand[varLocation] != variable) {
		varLocation++;
	}
	return integrand.substr(0, varLocation);
}

string add(string leftSide, string rightSide) { // no wrap () input
	int leftDegree = 0;
	int rightDegree = 0;

	int i = 0;
	if (leftSide[0] == '-') {
		i = 1;
	}
	if (isdigit(leftSide[i])) {
		i = 1;
		while (isdigit(leftSide[i])) {
			i++;
		}
		leftDegree = stoi(leftSide.substr(0, i));
	}
	else {
		leftDegree = 1;
	}
	string leftBody = leftSide.substr(i, (leftSide.length() - 1) - i);

	if (leftSide[0] == '-') {
		i = 1;
	}
	if (isdigit(rightSide[i])) {
		i = 1;
		while (isdigit(rightSide[i])) {
			i++;
		}
		rightDegree = stoi(rightSide.substr(0, i));
	}
	else {
		rightDegree = 1;
	}
	string rightBody = rightSide.substr(i, (rightSide.length() - 1) - i);;

	if (leftBody == rightBody) {
		if (leftDegree + rightDegree == 0) {
			return "0";
		}
		else if (leftDegree + rightDegree == 1) {
			return leftBody;
		}
		else {
			return to_string(leftDegree + rightDegree) + leftBody;
		}
	}
	return leftSide + rightSide;
}

string multiply(string leftSide, string rightSide) {
	//cout << "Unedited string pass to multiply -- Left: " + leftSide << endl;
	//cout << "Unedited string pass to multiply -- Right: " + rightSide << endl;

	leftSide.replace(0, 1, "");
	leftSide.replace(leftSide.length() - 1, 1, "");
	rightSide.replace(0, 1, "");
	rightSide.replace(rightSide.length() - 1, 1, "");

	string openTemp = "";
	if (!isdigit(leftSide[0]) && isdigit(rightSide[0])) {
		openTemp = leftSide;
		leftSide = rightSide;
		rightSide = openTemp;
	}

	/*
	bool isFirstNeg = false;
	bool isSecondNeg = false;
	for (int i = 0; i < leftSide.length(); i++) {
		if (leftSide[i] == '-') {
			isFirstNeg = true;
			leftSide.replace(i, 1, "");
			i--;
		}
	}
	for (int j = 0; j < rightSide.length(); j++) {
		if (rightSide[j] == '-') {
			isSecondNeg = true;
			rightSide.replace(j, 1, "");
			j--;
		}
	}
	*/

	//cout << "Left Side: " + leftSide << endl;
	//cout << "Right Side: " + rightSide << endl;

	bool firstChecker = true;
	bool secondChecker = true;
	bool finalChecker = true;

	bool isFirstDigit = false;
	bool isSecondDigit = false;

	int firstPlacement = 0;
	int secondPlacement = 0;

	int k = 0;
	int w = 0;

	int firstPowPar = 0;
	int secondPowPar = 0;

	string firstString;
	string secondString;
	string finalString = "";

	string firstPower = "";
	string secondPower = "";
	string finalPower = "";

	string test[5];
	for (int i = 0; i < 5; i++) {
		test[i] = " ";
	}
	bool firstTime = true;
	int newIterator = 0;

	for (int i = 0; i < leftSide.length(); i++) {
		if (i == firstPlacement) {
			firstChecker = true;
		}
		if (firstChecker) {
			if (isdigit(leftSide[i])) {
				k = i + 1;
				while (isdigit(leftSide[k])) {
					k++;
				}
				firstPower = "0";
			}
			else {
				k = i + 1;
				if (i < leftSide.length() - 1) {
					if (leftSide[i + 1] == '^') {
						k = i + 3;
						firstPowPar = 1;
						while (firstPowPar > 0) {
							if (leftSide[k] == '(') {
								firstPowPar++;
							}
							else if (leftSide[k] == ')') {
								firstPowPar--;
							}
							k++;
						}
						k++;
						//cout << "First Pow k: " + to_string(k) << endl;
						//cout << "First Pow i: " + to_string(i) << endl;
						firstPower = leftSide.substr(i + 3, k - (i + 5));
					}
				}
				else { firstPower = "1"; }
			}
			isFirstDigit = true;
			//cout << "First Power: " + firstPower << endl;
			for (int y = 0; y < firstPower.length(); y++) {
				if (!isdigit(firstPower[y])) {
					isFirstDigit = false;
				}
			}
			firstString = leftSide.substr(i, k - i);
			//cout << "First String at " + to_string(i) + " is: " + firstString << endl;
			firstPlacement = k;
			firstChecker = false;
			finalChecker = true;
			secondChecker = true;
			newIterator = 0;
			for (int j = 0; j < rightSide.length(); j++) {
				if (j == secondPlacement) {
					secondChecker = true;
				}
				if (secondChecker) {
					if (isdigit(rightSide[j])) {
						w = j + 1;
						while (isdigit(rightSide[w])) {
							w++;
						}
						secondPower = "0";
					}
					else {
						w = j + 1;
						if (j < rightSide.length() - 1) {
							if (rightSide[j + 1] == '^') {
								w = j + 3;
								secondPowPar = 1;
								while (secondPowPar > 0) {
									if (rightSide[w] == '(') {
										secondPowPar++;
									}
									else if (rightSide[w] == ')') {
										secondPowPar--;
									}
									w++;
								}
								w++;
								secondPower = rightSide.substr(j + 3, w - (j + 5)); // potential error zone -- check indicies
							}
						}
						else { secondPower = "1"; }
					}
					secondString = rightSide.substr(j, w - j);
					//cout << "Second String at " + to_string(j) + " is: " + secondString << endl;
					secondPlacement = w;
					secondChecker = false;
					if (firstTime) {
						test[newIterator] = secondString;
					}
					//cout << "Second Power: " + secondPower << endl;
					isSecondDigit = true;
					for (int z = 0; z < secondPower.length(); z++) {
						if (!isdigit(secondPower[z])) {
							isSecondDigit = false;
						}
					}

					if (isdigit(firstString[0]) && isdigit(secondString[0])) {
						finalString += to_string(stoi(firstString) * stoi(secondString));
						finalChecker = false;
						test[newIterator] = " ";
					}
					else if (firstString[0] == secondString[0]) {
						finalChecker = false;
						/*
						if (isFirstDigit && isSecondDigit) {
							finalPower = to_string(stoi(firstPower) + stoi(secondPower));
						}
						else if (isFirstDigit) {
							finalPower = firstPower + '+' + secondPower;
						}
						else if (isSecondDigit) {
							finalPower = secondPower + '+' + firstPower;
						}
						else {
						*/
						finalPower = add(firstPower, secondPower); // maybe impliment actual multiplication, rip
						//}
						
						if (finalPower != "1" && finalPower != "0") {
							finalString += firstString[0];
							finalString += "^(" + finalPower + ')';
						}
						else if (finalPower == "1") {
							finalString += firstString[0];
						}
						else {
							if (finalString == "") {
								finalString += "1";
							}
						}
						test[newIterator] = " ";
					}
					newIterator++;
				}
				
			}
			firstTime = false;
			if (finalChecker) {
				finalString += firstString;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (test[i] != " ") {
			finalString += test[i];
		}
	}
	//cout << "String created by Multiply: " + finalString << endl;
	return finalString;
}

string multiplyTerms(string term1, string term2) {
	string currentFirstString;
	string currentSecondString;
	string answer = "";
	int k = 0;
	int w = 0;
	int powCheck1 = 0;
	int powCheck2 = 0;

	int firstPlacement = -1;
	int secondPlacement = -1;
	bool firstChecker = true;
	bool secondChecker = true;

	//cout << "Opening multiplyTerms leftSide: " + term1 << endl;
	//cout << "Opening multiplyTerms rightSide: " + term2 << endl;

	for (int i = 0; i < term1.length(); i++) {
		if (i == firstPlacement) {
			firstChecker = true;
		}
		else if (term1[i] == '(' && firstChecker) { // first part could be removed -- maybe
			firstChecker = false;
			w = i + 1;
			powCheck1 = 1;
			while (powCheck1 > 0) {
				if (term1[w] == '(') {
					powCheck1++;
				}
				else if (term1[w] == ')') {
					powCheck1--;
				}
				w++;
			}
			currentFirstString = term1.substr(i, w - i);
			firstPlacement = w;
			for (int j = 0; j < term2.length(); j++) {
				if (j == secondPlacement) {
					secondChecker = true;
				}
				if (term2[j] == '(' && secondChecker) {
					secondChecker = false;
					k = j + 1;
					powCheck2 = 1;
					while (powCheck2 > 0) {
						if (term2[k] == '(') {
							powCheck2++;
						}
						else if (term2[k] == ')') {
							powCheck2--;
						}
						k++;
					}
					secondPlacement = k;
					//cout << "Main Run placement 1: " + to_string(firstPlacement) << endl;
					//cout << "Main Run placement 2: " + to_string(secondPlacement) << endl;
					currentSecondString = term2.substr(j, k - j);
					//cout << "Current First String at  "+ to_string(i) + ": " << currentFirstString << endl;
					//cout << "Current Second String at " + to_string(j) + ": " << currentSecondString << endl;
					//cout << "Multiply Result: " + multiply(currentFirstString, currentSecondString) << endl;
					answer += '(' + multiply(currentFirstString, currentSecondString) + ")+"; // need to deal with negatives vs positives (i.e. term 1 - term 2)
				}

			}
		}

	}
	answer.replace(answer.length() - 1, 1, "");
	return answer;
}


string exponentDerivative(string integrand, char variable) {
	int power = stoi(findVariablePower(integrand, variable));
	int coefficient = stoi(findVariableCoefficient(integrand, variable));
	if (power == 1) {
		return to_string(coefficient);
	}
	if (power == 0) {
		return "0";
	}
	coefficient = coefficient * power;
	power--;
	return coefficient + variable + "^(" + power + ')';
}

string integrateEPower(string integrand, char variable) {
	string power = findVariablePower(integrand, 'e');
	string coefficient = findVariableCoefficient(integrand, 'e');
	string divisor = exponentDerivative(power, variable);
	string answer = "";

	answer += coefficient;
	answer += "e^(" + power + ')';
	if (divisor[0] != '1') {
		answer += "/(" + divisor + ')';
	}
	return answer;
}

string integrateTrig(string integrand, char variable) {
	// yawn
	return "";
}



string eliminateSpaces(string input) {
	int i = 0;
	while (i < input.length()) {
		if (input[i] == ' ') {
			input.replace(i, 1, "");
		}
		i++;
	}
	return input;
}

string integrateInverse(string integrand, char variable) {
	int divPos = 0;
	int xPos = 0;
	bool hasPlus = false;
	for (int i = 0; i < integrand.length(); i++) {
		if (integrand[i] == '/') {
			divPos = i;
		}
		if (integrand[i] == variable) {
			xPos = i;
		}
		if (integrand[i] == '+' || integrand[i] == '-') {
			hasPlus = true;
		}
	}
	string firstHalf = integrand.substr(0, divPos);
	string secondHalf;
	string divVar = "1";
	integrand[xPos] = ' ';
	//integrand[divPos + 1] = '\0';
	//integrand[integrand.length() - 1] = '\0';
	xPos--;
	if (integrand[divPos + 2] != ' ') {
		secondHalf = integrand.substr(divPos + 2, integrand.length() - divPos - 4);

		if (xPos - divPos != 1) {
			divVar = integrand.substr(divPos + 2, xPos - (divPos + 2));
		}
	}
	else {
		secondHalf = "1";
	}
	string temp;
	if (hasPlus == false) {
		if (secondHalf == "1") {
			temp = firstHalf + "ln(" + variable + ')';
		}
		else {
			temp = "(" + firstHalf + " / " + secondHalf + ") ln(" + variable + ')';
		}
	}
	else {
		secondHalf[xPos] = 'x';
		if (divVar == "1") {
			temp = firstHalf + "ln(" + secondHalf + ')';
		}
		else {
			temp = '(' + firstHalf + " * ln(" + secondHalf + ")) / " + divVar;
		}
	}
	temp = eliminateSpaces(temp);
	return temp;
}



string integrateExponent(string integrand, char variable) {
	int degree;
	string bodyTerm;
	
	for (int i = 0; i < integrand.length(); i++) {
		if (integrand[i] == variable) {
			if (integrand[i+1] == '^') {
				degree = stoi(integrand.substr(i + 3, integrand.length() - 2));
			}
			else { degree = 1; }
			if (i > 0) { bodyTerm = integrand.substr(0, i); }
			else {
				bodyTerm = "1";
			}
			degree++;
			return ('(' + bodyTerm + '/' + to_string(degree) + ')' + "x^(" + to_string(degree) + ')');
		}
	}
	return integrand + variable;
}

string findProperIntegral(string currentTerm, char variable) {
	if (currentTerm[0] == '(') {
		currentTerm = currentTerm.substr(1, currentTerm.length() - 2);
	}

	bool anotherChecker = true;
	string abomination = "";
	int j = 0;
	int k = 0;
	while (j < currentTerm.length() && anotherChecker) {
		k = 0;
		if (currentTerm[j] == 'e' && anotherChecker) {
			k = j + 2;
			while (currentTerm[k] != variable && currentTerm.length() - 1 != k) {
				k++;
			}
			if (k != currentTerm.length() - 1) {
				abomination += integrateEPower(currentTerm, variable);
				anotherChecker = false;
			}
		}
		if (currentTerm[j] == '/' && anotherChecker) {
			k = j + 1;
			while (currentTerm[k] != variable && currentTerm.length() - 1 != k) {
				k++;
			}
			if (k != currentTerm.length() - 1) {
				abomination += integrateInverse(currentTerm, variable);
				anotherChecker = false;
			}
		}
		j++;
	}
	if (anotherChecker) {
		abomination += integrateExponent(currentTerm, variable);
	}
	abomination += '+';

	return abomination;
} 

string takeTermIntegral(string yTerm, char variable) {
	string currentTerm = "";
	string abomination = "";
	int plusLocation = 0;
	bool wasNegative = false;
	bool hasMultipleTerms = false;
	for (int i = 0; i < yTerm.length(); i++) {
		if (yTerm[i] == '+' || yTerm[i] == '-') {
			hasMultipleTerms = true;
			if (wasNegative == false) {
				currentTerm = yTerm.substr(plusLocation, i);
			}
			else {
				currentTerm = '-' + yTerm.substr(plusLocation, i);
			}
			plusLocation = i + 1;

			if (yTerm[i] == '-') {
				wasNegative = true;
			}
			abomination += findProperIntegral(currentTerm, variable);
		}
	}
	if (hasMultipleTerms) {
		if (wasNegative == false) {
			currentTerm = yTerm.substr(plusLocation, yTerm.length() - 1);
		}
		else {
			currentTerm = '-' + yTerm.substr(plusLocation, yTerm.length() - 1);
		}
		abomination += findProperIntegral(currentTerm, variable);
	}
	else {
		abomination += findProperIntegral(yTerm, variable);
	}
	
	abomination.replace(abomination.length() - 1, 1, "");
	return abomination;
}

bool isDigit(string str) {
	bool isDigit = true;
	for (int y = 0; y < str.length(); y++) {
		if (!isdigit(str[y])) {
			isDigit = false;
		}
	}
	return isDigit;
}

string solveEPowerIntegralType(string yPrimeTerm, string yTerm, string cTerm, char indepVariable, char depVariable) {
	string answer;

	string tempIntStr;
	string tempPowStr;
	string ePowerTerm = "e^(" + takeTermIntegral(yTerm, indepVariable); + ')';

	ePowerTerm = '(' + eliminateSpaces(ePowerTerm) + ')';
	//cout << "ePowerTerm Prior: " + ePowerTerm << endl;
	int tempIntCounter = 0;
	for (int i = 0; i < ePowerTerm.length(); i++) {
		if (ePowerTerm[i] == 'l') {
			int j = i + 3;
			int z = i - 1;
			tempIntCounter = 1;
			while (tempIntCounter > 0) {
				if (ePowerTerm[j] == '(') {
					tempIntCounter++;
				}
				else if (ePowerTerm[j] == ')') {
					tempIntCounter--;
				}
				j++;
			}
			j--;
			
			while (ePowerTerm[z] != '+' && ePowerTerm[z] != '-') {
				z--;
			}
			tempPowStr = ePowerTerm.substr(z + 1, i - (z + 1));
			tempIntStr = ePowerTerm.substr(i + 3, j - (i + 3));
			ePowerTerm.replace(z, j - z, "");
			i -= j - i;

			if (tempPowStr.length() == 0 || tempPowStr == "1") {
				//cout << "Replaced " << ePowerTerm[0] << " with " + tempIntStr << ePowerTerm[0] << endl;
				ePowerTerm.replace(0, 1, tempIntStr + ePowerTerm[0]);
			}
			else {
				ePowerTerm.replace(0, 1, '(' + tempIntStr + ")^(" + tempPowStr + ')' + ePowerTerm[0]);
			}
		}
	}
	//cout << "ePowerTerm Post: " + ePowerTerm << endl;
	ePowerTerm.insert(0, "(");
	ePowerTerm += ')';

	//cout << "ePowerTerm Post 2: " + ePowerTerm << endl;

	// yPrimeTerm multiplied by ePowerTerm = Integral(cTerm * ePowerTerm) + c
	yPrimeTerm = '(' + yPrimeTerm + ')';
	cTerm = '(' + cTerm + ')';
	//cout << "yPrimeTerm: " + yPrimeTerm << endl;
	yPrimeTerm = multiplyTerms(ePowerTerm, yPrimeTerm);
	//cout << "yPrimeTerm: " + yPrimeTerm << endl;
	//cout << "cTerm: " + cTerm << endl;
	cTerm = multiplyTerms(ePowerTerm, cTerm);
	//cout << "cTerm: " + cTerm << endl;

	cTerm = takeTermIntegral(cTerm, indepVariable);
	//cout << "cTerm: " + cTerm << endl;

	string rightSide = '(' + cTerm + '/' + yPrimeTerm + ')' + '+' + "(c/" + yPrimeTerm + ')';

	answer = "y = " + rightSide;
	return answer;
}

string solveEquation(string yPrimeTerm, string yTerm, string cTerm, char indepVariable, char depVariable) {
	string answer;

	answer = solveEPowerIntegralType(yPrimeTerm, yTerm, cTerm, indepVariable, depVariable);


	return answer;
}


int main() {
	string yPrimeTerm = "2";
	string yTerm = "3+(1/(x))";
	string cTerm = "e^(-3x)";
	char indepVariable = 'x';
	char depVariable = 'y';

	//string temp = "4/(2x + 1)";
	//string temp2 = "4e^(3x)";
	//cout << integrateExponent("x^(3)", 'x');
	//cout << integrateInverse(temp, 'x');
	//cout << integrateEPower(temp2, 'x');
	//cout << "e^(" + takeTermIntegral(yTerm, indepVariable) + ')';
	//cout << multiply("(4x^(2)y)", "(8x^(4)y^(2))") << endl;
	//cout << multiplyTerms("(4x)+(2)", "(4x)+(2)");

	//string test = "(e ^ (2x + 1ln(x)))";
	//test = eliminateSpaces(test);
	//cout << "Test: " + test << endl;
	//cout << "Final Answer: " + multiplyTerms(test, "(1)+(x^(2))+(e^(3))") << endl;

	cout << "Input String: (" + yPrimeTerm + ")y' + (" + yTerm + ")y = " + cTerm << endl;
	cout << solveEquation(yPrimeTerm, yTerm, cTerm, indepVariable, depVariable);
}