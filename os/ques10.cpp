#include<bits/stdc++.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>

using namespace std;

int level = 3;

void init(){
}

vector<string> split(string str){
	string word = "";
	vector<string> words;
	int i = 0;
	while(i < str.length()){
		if(str[i] == ' '){
			if(word.length() != 0)
				words.push_back(word);
			word = "";
		} else word += str[i];
		i++;
	}

	if(word.length() != 0)
		words.push_back(word);

	while(words.size() < 2)
		words.push_back("");
	
	return words;
}

class FileSystem{
	
	int *arr;
	string pwd;
	string root;
	int currDepth;

public:
	FileSystem(){
		root = ".";
		pwd = "/";
		currDepth = 0;
	}

	void printPwd(){
		cout<<">>"<<pwd<<endl;
	}

	bool exists(string dir){

		if(dir[0] == '/')
			return opendir((root + dir).c_str()) != NULL;
		else
			return opendir((root + "/" + pwd + "/" + dir).c_str()) != NULL;
	}

	int getPathDepth(string path){
		int depth = 1;
		if(path == "/")
			return 0;
		else if(path.length() == 1)
			return 1;
		else if(path == "..")
			return -1;
		else if(path[0] == '.' && path[1] == '.')
			depth = -1;
		for(int i=1; i<path.length() - 1; i++)
			if(path[i] == '/' || path[i] == '\\')
				depth++;
			else if(path[i] == '.' && path[i+1] == '.')
				depth--;
		return depth;
	}

	void makeDirectory(string dir){

		if(level == 1){
			cout<<"Can't create directory in Single Level mode.";
			return;
		} else if(level == 2 && getPathDepth(dir) + currDepth >= 2){
			cout<<"Can't create directory. Current selection of Level=2 doesn't allow directories at this depth.";
			return;
		}

		if(exists(dir)){
			cout<<">>Directory/File with that name already exists.\n";
		} else {

			if(dir[0] == '/')
				dir = root + "/" + dir;
			else dir = root + "/" + pwd + "/" + dir;

			if(mkdir(dir.c_str(), 0777) == -1)
				cout<<">>Unable to create directory "<<dir<<endl;
		}
	}

	void changePwd(string dir){

		if(level == 1){
			cout<<"Can't change directory in Single Level mode.";
			return;
		}

		else if(getPathDepth(dir) + currDepth < 0 || (level == 2 && getPathDepth(dir) + currDepth >= 2)){
			cout<<"Invalid request";
			return;
		}

		DIR *dirp;
		if(exists(dir)){

			currDepth += getPathDepth(dir);
			
			if(dir[0] == '/')
				pwd = dir;
			else 
				pwd += "/" + dir;	
		} else {
			cout<<">>Directory doesn't exist.\n";
		}
	}

	void listDirectory(string dir){
		
		if(exists(dir)){
			if(dir != "" && dir[0] == '/')
				dir = root + dir;
			else
				dir = root + pwd + dir;
				
			DIR *dirp = opendir(dir.c_str());

			if(dirp != NULL){
				dirent *ent;
				while((ent = readdir(dirp)) != NULL)
					cout<<ent->d_name<<endl;
			} else 
				cout<<">>Directory doesn't exist.\n";
			
		} else 
			cout<<">>Directory doesn't exist.\n";
	}

	void createFile(string file){
		ofstream out((root + "/" + pwd + "/" + file).c_str());
	}

	int getCurrDepth(){
		return currDepth;
	}
};

void start_cmd(){

	cout<<"Level:";
	cin>>level;
	
	map<string, int> commandMap;
	FileSystem *fs = new FileSystem();
	commandMap["help"] = 1;
	commandMap["ls"] = 2;
	commandMap["mkdir"] = 3;
	commandMap["rmdir"] = 4;
	commandMap["pwd"] = 5;
	commandMap["pdepth"] = 8;
	commandMap["touch"] = 7;
	commandMap["cd"] = 6;

	string str;


	while(true){

		cout<<"\n>>";
		getline(cin, str);
		vector<string> strs = split(str);
		if(commandMap.find(strs[0]) != commandMap.end()){
			switch(commandMap[strs[0]]){
				case 1: break;
				case 2: fs->listDirectory(strs[1]); break;
				case 3: fs->makeDirectory(strs[1]); break;
				case 6: fs->changePwd(strs[1]); break;
				case 5: fs->printPwd(); break;
				case 7: fs->createFile(strs[1]); break;
				case 8: cout<<fs->getCurrDepth(); break;
			}
		} else {
			cout<<"Command "<<strs[0]<<" not found.";
		}
	}
}
int main(){

	start_cmd();
}
