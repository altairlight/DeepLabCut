#include<iostream>
#include<vector>
#include<string>
#include<sys/types.h>
#include<dirent.h>

using namespace std;
int main(){
	string project_path="C:\\Users\\user\\Desktop\\LinearChamber-KAIST-2018-11-19\\labeled-data\\";
	vector<string> Search_path;
	vector<string> Experiment_Days{"20180906", "20180910", "20180919"};
	vector<string> File_paths;

	/*for(day_index=0;day_index<Experiment_Days.size();day_index++){
		string day= Experiment_Days[day_index];
		for(i=0;i<15;i++){
			Search_path.push_back(project_path + day + "_Trial" + to_string(i));
		}
	}*/

	Search_path.push_back(project_path + Experiment_Days[0] + "_Trial" + "1");

		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir(Search_path[0].c_str())) != NULL) {
		  /* print all the files and directories within directory */
		  while ((ent = readdir (dir)) != NULL) {
		    //printf ("%s\n", ent->d_name);
		    string file_name=ent->d_name;
		    File_paths.push_back(Search_path[0]+"\\"+file_name);
		  }
		  closedir (dir);
		} else {
		  perror ("Could not open directory");
		  return EXIT_FAILURE;
		}
		
		for(int i=0;i<File_paths.size();i++){
			size_t label_found=File_paths[i].find("labeled.png");
			if(label_found!=string::npos){
				cout<< File_paths[i] << endl;
				if(remove(File_paths[i].c_str()) !=0){
					perror("Error deleting file");
				}else{
					cout << "File "<< File_paths[i].substr(File_paths[i].find_last_of("\\/")+1) << " deleted" << endl;
				}
				
				string original_file_path = File_paths[i].substr(0,label_found) + ".png";
				cout<< original_file_path << endl;
				if(remove(original_file_path.c_str()) !=0){
					perror("Error deleting file");
				}else{
					cout << "File "<< original_file_path.substr(original_file_path.find_last_of("\\/")+1) << " deleted" << endl;
				}
				
				File_paths.erase(File_paths.begin()+i);
				i--;
			}
		}
	
	return 0;
}
