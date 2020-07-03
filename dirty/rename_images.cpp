#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
	namespace fs   = std::filesystem;
	using fs_it    = fs::directory_iterator;
	using fs_entry = fs::directory_entry;

	int precision         = 12;
	std::string extension = ".jpg";
	std::string path      = "/Users/gardei/datasets/coco/img";
	std::ostringstream oss;
	std::vector<fs_entry> entries;

	for( auto&& e: fs_it( path ) )
		entries.push_back( e );

	for(struct {
			std::vector<fs_entry>::iterator it;
			int ctr;
			} s = {.it = entries.begin(), .ctr = 1};
			s.it != entries.end(); ++(s.it), ++(s.ctr))
	{
		oss << std::setw( precision ) << std::setfill( '0' ) << s.ctr
		    << extension;
		auto pth     = ( *( s.it ) ).path();
		auto new_pth = pth.replace_filename( oss.str() );
		std::cout << s.ctr << " " << ( *( s.it ) ).path() << "--->" << new_pth
		          << std::endl;
		fs::rename( ( *( s.it ) ).path(), new_pth );
		oss.str( std::string() );
		oss.clear();
	}
}
