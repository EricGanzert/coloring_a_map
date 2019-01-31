#include <colorMap.h>
using namespace std;
using namespace cv;

namespace map_color_eric
{
	MapColor::MapColor()
		: results_path("no results directory"), map_path("no map img filepath"), max_x(0), max_y(0)
	{
		//empty
	}
	
	MapColor::MapColor(std::string results_dir_path, std::string map_img_filepath)
		: results_path(results_dir_path), map_path(map_img_filepath), max_x(0), max_y(0)
	{
		//empty
	}
	
	void MapColor::load()
	{
		map = imread(map_path, CV_LOAD_IMAGE_COLOR);   // Read the file

		if(!map.data)                              // Check for invalid input
		{
			cout <<  "Could not open or find the image" << endl ;
			throw 1;
		}
		
		DIR *dir_ptr;
		struct dirent *entry;
		pair<int,int> coordinates;
		int cam_score;
		
		if ( dir_ptr = opendir( results_path.c_str() ) )
		{
			while( entry = readdir(dir_ptr) )
			{
				string directory_name = entry->d_name;
				if (is_test_dir(directory_name, coordinates))
				{
					string results_folder = results_path + "/" + directory_name; 
					if (get_score(results_folder, cam_score))
					{
						results.insert(make_pair(coordinates, cam_score));
					}
				}
			}			
		}
		else
		{
			cout <<  "Could not open or find the results directory" << endl;
			throw 1;
		}
		
		if (results.empty())
		{
			throw 1;
		}
	}
	
	bool MapColor::set_map_img(string new_map_path)
	{
		map_path = new_map_path;
	}
		
	bool MapColor::set_results_dir(string new_results_dir)
	{
		results_path = new_results_dir;
	}
	
	bool MapColor::is_test_dir(string directory_name, pair<int,int>& coordinates)
	{
		if (directory_name.find_first_not_of("_0123456789") != string::npos)
		{
			return false;
		}
	
		vector<int> numbers;
		
		string substr;
		size_t index=0;
		while (index = directory_name.find_first_not_of("0123456789") != string::npos)
		{
			if (index != 0)
			{
				substr = directory_name.substr(0,index);
				numbers.push_back(stoi(substr));
			}
			//cut out the substring we just saved plus the non-alpha character
			directory_name.erase(0,index+1);
		}
		
		//get last remaining substring
		if (directory_name.length() > 0)
		{
			substr = directory_name;
			numbers.push_back(stoi(substr));
		}
		
		if (numbers.size() != 2)
		{
			return false;
		}
		
		int x = numbers[0];
		int y = numbers[1];
		
		coordinates.first = x;
		if (x > max_x)
		{
			max_x = x;
		}
		
		coordinates.second = y;
		if (y > max_y)
		{
			max_y = y;
		}
		//cout << "got coordinates(x,y): (" << x << ", " << y << ")\n";
		return true;
	}
	
	bool MapColor::get_score(string directory_name, int& score)
	{
		DIR *dir_ptr;
		struct dirent *entry;
		
		if ( dir_ptr = opendir( directory_name.c_str() ) )
		{
			while( entry = readdir(dir_ptr) )
			{
				string filename = entry->d_name;
				//cout << filename << "\n";
				if (filename.find("result") != string::npos)
				{
					string results_file = directory_name + "/" + filename;
					return get_score_internal(results_file, score);
				}
			}			
		}
		return true;
	}
	
	bool MapColor::get_score_internal(string results_file, int& score)
	{
		//cout << "getting score from " << results_file << "\n";
		ifstream ins;
		ins.open(results_file);
		if (ins.fail())
		{
			cout << "cant open stream\n";
			return false;
		}
		string line;
		while(getline(ins,line))
		{
			if (line.find("rating") != string::npos)
			{
				string score_str;
				for (int i=0;i<line.length();i++)
				{
					if (isdigit(line[i]) || line[i] == '-' )
					{
						score_str += line[i];
					}
				}
				score = stoi(score_str);
				//cout << "score is " << score << "\n";
				return true;
			}
		}
		
		ins.close();
	}
	
	void MapColor::paint_map()
	{
		int size_x = map.cols;
		int size_y = map.rows;
		
		cout << "picture size(x,y): (" << size_x << ", " << size_y << ")\n";
		cout << "coordinate max(x,y): (" << max_x << ", " << max_y << ")\n";
		
		std::map<std::pair<int,int>, int>::iterator it;
		for (it=results.begin(); it != results.end(); ++it)
		{
			cout << "coordinate(x,y): (" << it->first.first << ", " << it->first.second << ") : score " << it->second << "\n";
			Point p = get_circle_center(it->first.first, it->first.second);
			cout << "point for circle(x,y): (" << p.x << ", " << p.y << ")\n\n";
		}
	}
	
	cv::Point MapColor::get_circle_center(int x, int y)
	{
		cv::Point p;
		if (max_x == 0)
			p.x = 0;
		else
			p.x = floor((x/static_cast<double>(max_x))*map.cols);
		
		if (max_y == 0)
			p.y = 0;
		else
			p.y = floor((y/static_cast<double>(max_y))*map.rows);
		
		return p;
	}
}
