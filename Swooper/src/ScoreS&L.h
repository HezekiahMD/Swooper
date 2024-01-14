#ifndef ScoreSL_HPP
#define ScoreSL_HPP

#include <fstream>
#include <string>


namespace SL {

	//Saves Score to File
	void SaveScore(int& Score,const std::string FileName) {

		//OpenFile
		std::ofstream File;
		File.open(FileName.c_str());

		//If File Doesnt Exist
		if (File.is_open() == false) {
			File.close();
			return;
		}

		//Writes Score To File
		File.write(reinterpret_cast<char*>(&Score), sizeof(Score));

		//Closes File
		File.close();
	}


	//Loads Score From File
	int LoadScore(const std::string& FileName) {

		int LoadedScore = 0;

		//OpenFile
		std::ifstream File;
		File.open(FileName.c_str());

		//If File Cant Open
		if (File.is_open() == false) {
			File.close();
			return LoadedScore;
		}

		//Reads Score from File
		File.read(reinterpret_cast<char*>(&LoadedScore), sizeof(LoadedScore));

		//Closes File
		File.close();

		//Returns Loaded Score
		return LoadedScore;
	}


}







#endif // !ScoreSL_HPP

