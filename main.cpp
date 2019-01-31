#include <projectTests.h>
#include <colorMap.h>
using namespace map_color_eric;

int main(int argc, char** argv)
{	
	if (argc < 3)
	{
		cout << "usage is ./color-map path_to_results path_to_map_img";
		return 1;
	}
	
	MapColor map;
	string results_path(argv[1]);
	string map_path(argv[2]);
	
	map.set_results_dir(results_path);
	map.set_map_img(map_path);
	
	try {
		map.load();
	}
	
	catch(int e) {
		cout << "could not load the image and/or results\n";
		return e;
	}
	map.paint_map();
	return 0;
}
