#include <iostream> //stdout,stdin
#include <sstream> //parse
#include <string> //parse
#include <math.h> //pow,ceil
#include <unistd.h> //fork
#include <sys/wait.h> //wait

using namespace std;

//used for error checking and parsing input
template <typename T>
T from_string(std::string const & s) {
 	std::stringstream ss(s);
 	T result;
 	ss >> result;    // TODO handle errors
 	return result;
}


//used in child process
long fibbers(int x) {

	long Abra;
	long Kadabra;

	//Explicit Fmla, for anyone wondering :-)
	Abra    = (ceil((1/sqrt(5)) * pow(((1 + sqrt(5))/2),x)));
	Kadabra = (ceil((1/sqrt(5)) * pow(((1 - sqrt(5))/2),x)));

	return Abra-Kadabra;
}

//parent, root process
int main() {

	//holds the PID of the current process, will be 0 when the child is active
	int child;

	//inputs, string and parsed
	string sinput;
	int input;

	//get loop amount
	cout << "Tell us to jump, we say 'How High?': ";
	cin >> sinput;
	if (sinput == "exit") {
		return 0;
	}

	//parse and error check
	input = from_string<int>(sinput);
	while (input < 1) {
		cout << "How many numbers in Fib do you want us to count to?" << endl;
		cin >> sinput;
		if (sinput == "exit") {
			return 0;
		}
		input = from_string<int>(sinput);
	}

	//Start Forking my Child
	child = fork();
	//Child is Active
	if (child == 0) {
		cout << "Inside Child Process" << endl;
		for (int i = 0; i <= input; i++) {
			long Alacazam = fibbers(i);
			long Limit = 7540113804746369024;
			if (Alacazam <= Limit) {
				cout << "Fibonacci #" << i << " = " << Alacazam << endl;
			} else {
				cout << "Alacazam Cannot Hold the Next Numbers!" << endl;
				break;
			}
		}

		cout << "Leaving Child Process" << endl;
	//Parent is Active
	} else {
		cout << "Inside Parent Process" << endl;
		wait(NULL);
		cout << "Leaving Parent Process" << endl;
	}

return 0;
}
