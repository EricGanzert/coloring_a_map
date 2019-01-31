#include <projectTests.h>
#include <colorMap.h>
using namespace map_color_eric;
using namespace std;

namespace
{
	int init(MapColor& the_map, int argc, char** argv)
	{
		if (argc < 3)
		{
			cout << "usage is ./color-map path_to_results path_to_map_img";
			return 1;
		}
		
		string results_path(argv[1]);
		string map_path(argv[2]);
		
		the_map.set_results_dir(results_path);
		the_map.set_map_img(map_path);
		
		try {
			the_map.load();
		}
		
		catch(int e) {
			cout << "caught exception: " << e << "\n";
			return e;
		}
		return 0;
	}
}

int all_tests(int argc, char** argv)
{
	int err;
	if (err = test_load_image(argc, argv))
	{
		cout << "FAILED: load image\n";
		return err;
	}
	cout << "PASSED: load image\n";
	
	if (err = test_paint_map(argc, argv))
	{
		cout << "FAILED: paint map\n";
		return err;
	}
	cout << "PASSED: paint map\n";
}

int test_load_image(int argc, char** argv)
{
	MapColor map;
	return init(map,argc,argv);
}

int test_paint_map(int argc, char** argv)
{
	int err;
	MapColor map;
	if(err = init(map,argc,argv))
	{
		return err;
	}
	map.paint_map();
}
