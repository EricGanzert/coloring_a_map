#ifndef COLOR_MAP_H
#define COLOR_MAP_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <dirent.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
using namespace cv;
using namespace std;

namespace map_color_eric
{
	class MapColor {
	public:
		MapColor();
		MapColor(std::string results_dir_path, std::string map_img_filepath);
		
		void load();
		bool set_map_img(std::string new_map_path);
		bool set_results_dir(std::string new_results_dir);
		
		void paint_map();
	private:
		bool is_test_dir(std::string directory_name, std::pair<int,int>& coordinates);
		bool get_score(std::string directory_name, int& score);
		bool get_score_internal(std::string results_file, int& score);
	
		std::string map_path;
		std::string results_path;
		Mat map;
		int max_x;
		int max_y;
		std::map<std::pair<int,int>, int> results;
	};	
}

#endif //COLOR_MAP
