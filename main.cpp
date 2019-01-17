#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <map>
#include <time.h>
#include <math.h>

using namespace std;

int octave = 0;
int mode = 0;

// Note/Sound object
class PianoKey {
	public:
		string m_name0;
		string m_name1;
		string m_filename;
		string m_syscommand;
		void setcommand() {
			m_syscommand.resize(6);
			if (mode == 0) {
				m_filename[2] = char(octave+48);
			}
			for (int i = 0; i < 7; i++) {
				m_syscommand += m_filename[i+(7*mode)];
			}
		}
		PianoKey() {
		}
		PianoKey(string name0, string name1, string filename) {
			m_syscommand += 'a';
			m_syscommand += 'p';
			m_syscommand += 'l';
			m_syscommand += 'a';
			m_syscommand += 'y';
			m_syscommand += ' ';
			m_name0 = name0;
			m_name1 = name1;
			m_filename = filename;
		}
		void playnote() {
			setcommand();
			system(m_syscommand.c_str());
			cout << m_syscommand << endl; 
		}
};

void swap(int * array) {
	if (array[0] > array[1]) {
		int tmp = array[0];
		array[0] = array[1];
		array[1] = tmp;
	}
}

void MergeSort(int array[], int size) {
	if (size == 1) {
		return;
	}
	if (size == 2) {
		swap(array);
		return;
	}
	const int midpoint = size/2;
	int lower[midpoint];
	int upper[size-midpoint];
	for (int i = 0; i < size; i++) {
		if (i < midpoint)
			lower[i] = array[i];
		else
			upper[i-midpoint] = array[i];
	}
	MergeSort(lower, midpoint);
	MergeSort(upper, (size-midpoint));
	int mergearray[size];
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < midpoint or j < (size-midpoint)) {
		if (i >= midpoint) 
			mergearray[k++] = upper[j++];
		else if (j >= (size-midpoint))
			mergearray[k++] = lower[i++];			
		else if (lower[i] <= upper[j])
			mergearray[k++] = lower[i++];
		else 
			mergearray[k++] = upper[j++];	
	}
	for (int n = 0; n < size; n++) 
		array[n] = mergearray[n];	
}

void resize(int* pointer, int& size){//resizes array if array is insufficiently large
	int index = size;
	size *= 2; // doubles size of new array
	int *newarray = new int[size];
	for (int i=0;i<index;i++){
		newarray[i] = pointer[i];
	}
	int *tmp = pointer;
	pointer = newarray;
	delete[] tmp; //clears previous, smaller array
  
}


const string currentDateTime() {
  
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d @ %X", &tstruct);

    return buf;
}

bool statistics(int* interModes, int& numIntermodes, int& minimum, int& maximum, const int size, const int dataset[]){
	if (size>0){
		int datasett[size]; //Initialize temporary dataset
		minimum = 99;
		maximum = -99;

		for(int i=0; i<size;i++){ //finds maximum interval, minimum interval
			//Finds maximum and minimum intervals
			if (dataset[i]>maximum)
				maximum = dataset[i];
			if (dataset[i]<minimum)
				minimum = dataset[i];
			//copying data onto separate array
			datasett[i] = (abs(dataset[i])%12);
			if (dataset[i]<0)
				datasett[i]*=-1;
		}
		
		MergeSort(datasett,size);
		//Mode calculation
		int possibleModes[size];
		int counterArray[size];
		int counter = 0;
		possibleModes[0] = datasett[0];
		counterArray[0] = 1;
		
		for(int i=1;i<size;i++){
			if (datasett[i]==possibleModes[counter])
				counterArray[counter] +=1;
			else{
				counter +=1;
				possibleModes[counter] = datasett[i];
				counterArray[counter] = 1;
			}
		}
    
		int max = counterArray[0];
    
		for (int i=1;i<=counter;i++){
			if (counterArray[i]>max)
				max = counterArray[i];
		}
    
		int numModes = 0;
    
		for(int i = 0; i<counter + 1; i++){
			if (counterArray[i] == max){
				interModes[numModes] = possibleModes[i];
				numModes +=1;
			}
		}

		numIntermodes = numModes;
		return true;
	}
	else
		return false;
}





int main() {
  
	//Initializing keys as PianoKey instances (set of 7 whole notes and 5 sharps, octaves handled separately)
	PianoKey C("C","Kick","cc0.wavki1.wav");
	PianoKey D("D","Clap","dd0.wavcl1.wav");
	PianoKey E("E","Snare","ee0.wavsn1.wav");
	PianoKey F("F","Shaker","ff0.wavsh1.wav");
	PianoKey G("G","HiHat","gg0.wavCH1.wav");
	PianoKey A("A","Buildup","aa0.wavBD1.wav");
	PianoKey B("B","Explosion","bb0.wavEX1.wav");
	PianoKey CS("C#","Kick","cs0.wavki1.wav");
	PianoKey DS("D#","Clap","ds0.wavcl1.wav");
	PianoKey FS("F#","Shaker","fs0.wavsh1.wav");
	PianoKey GS("G#","HiHat","gs0.wavCH1.wav");
	PianoKey AS("A#","Buildup","as0.wavBD1.wav");
	
	//initializing statistics data variables
	int modeCounter = 0;
	int octaveCounter = 0;
  
	int iASize = 100;
	int* intervalArray = new int[iASize];
	int iAIndex = 0;
  
	int pNote = -1;
	int cNote = -1;
	
	//putting into array for easy access;
	PianoKey keys[12];
	keys[0] = C;
	keys[1] = CS;
	keys[2] = D;
	keys[3] = DS;
	keys[4] = E;
	keys[5] = F;
	keys[6] = FS;
	keys[7] = G;
	keys[8] = GS;
	keys[9] = A;
	keys[10] = AS;
	keys[11] = B;
  
	int octaveHistogram[2][3];
	int histogramNotes[2][12];
	for (int i=0; i<2; i++){
		for (int j=0; j<12; j++){
			histogramNotes[i][j] = 0;
		}
		for (int k=0; k<3; k++){
			octaveHistogram[i][k] = 0;
		}
	}
  
	map <string, int> index;
	index["C"] = 0;
	index["C#"] = 1;
	index["D"] = 2;
	index["D#"] = 3;
	index["E"] = 4;
	index["F"] = 5;
	index["F#"] = 6;
	index["G"] = 7;
	index["G#"] = 8;
	index["A"] = 9;
	index["A#"] = 10;
	index["B"] = 11;
  
  
	//Initializing read file
	ifstream readfile;
	readfile.open("inputfile.txt");
	//Initializing log file
	fstream fs;
	fs.open("Log.txt", fstream::app);
	fs << "New session initialized: ";
	fs << currentDateTime(); 
	fs << '\n';  
	
	int curindex;
	//begin reading from file
	while (true) {
		if (readfile.eof()) //reading stops when end of file is reached
			break;
		string currentnote;
		getline(readfile,currentnote);
		currentnote.resize(currentnote.length()-1);
		if (currentnote.length() == 0)
			break;
    		
		if (index.count(currentnote)){
			//incrementing values within map for statistics
			curindex = index[currentnote];
			octaveHistogram[mode][octave]++;
			histogramNotes[mode][curindex]++;
      
			//playing the note via PianoKey class method
			keys[curindex].playnote();
      
			//logging the note being played
      
			if (mode == 1) {
				fs << "Drum Played: ";
				fs << keys[curindex].m_name1;
			}
			else {
				fs << "Note played: ";
				fs << currentnote;
			}
			fs << '\n';
			if (!mode){
				cNote = curindex + octave*12;
				if ((pNote+1)){

					if (iAIndex ==iASize)
						resize(intervalArray, iASize);
						intervalArray[iAIndex] = cNote - pNote;
						iAIndex++;
				}

				pNote = cNote;
			}
		}
		else if(currentnote[0]=='R'){
			fs << "Rest.\n" ;
		}
		else if(currentnote[0] == 'O'){ //if we've pressed an octave key
			octaveCounter ++;
			if (currentnote[1] == 'U') {//if we've raised the octave
				octave++;
				fs << "Octave Raised.\n";
			}
			else{
				octave--;
				fs << "Octave Lowered.\n";
			}
			octave %= 3;
		}
		else if (currentnote[0] == 'M') {//if we've pressed the change mode key (keys to drums & vice versa)
			mode++;
			modeCounter++;
			mode %= 2;
			if (mode == 0)
				fs << "Mode Changed to: Piano Keys\n";
			else
				fs << "Mode changed to: Drumkit\n";
		}
    
	}
	int minInter;
	int maxInter;
	int numInterModes;
	int* interModes;
	statistics(interModes,  numInterModes, minInter, maxInter, iAIndex, intervalArray);//Statistics function run
	//Note histogram
	fs<< "C"<<"\t"<<"C#"<<"\t"<< "D"<<"\t"<<"D#"<<"\t"<< "E"<<"\t"<< "F"<<"\t"<<"F#"<<"\t"<< "G"<<"\t"<<"G#"<<"\t"<< "A"<<"\t"<<"A#"<<"\t"<< "B"<<"\n";
	for (int i=0;i<2;i++){
		for (int j=0;j<12;j++){
			fs<<histogramNotes[i][j]<<"\t";
		}
		fs<<"\n";
	}
	//Octave histogram
	fs<<"Octave1"<<"\t"<<"Octave2"<<"\t"<<"Octave3"<<"\n";
	for (int i=0;i<2;i++){
		for (int j=0;j<3;j++){
			fs<<octaveHistogram[i][j]<<"\t\t";
		}
		fs<<"\n";
	}
	//Interval statistics
	fs<<"Minimum interval "<<minInter<<"\n";
	fs<<"Maximum interval "<<maxInter<<"\n";
	fs<<"Number of mode changes: "<<modeCounter<<"\n";
	fs<<"Number of octave changes: "<<octaveCounter<<"\n";
	fs<<"Number of Modes "<<numInterModes<<"\n";
	fs<<"Modes: ";
	for (int i=0;i<numInterModes;i++){
		fs<<interModes[i]<<" ";
	}
	fs<<"\n";
	readfile.close();
	fs << "Session Terminated\n\n";
	fs.close();
}
