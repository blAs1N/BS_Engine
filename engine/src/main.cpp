#include "System.h"

int main()
{
	BE::System sys;

	if (sys.Initialize())
		sys.RunLoop();
	
	/// @todo If init return false, log
	
	sys.Release();
	return 0;
}