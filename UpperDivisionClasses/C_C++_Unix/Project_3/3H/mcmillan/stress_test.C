#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <username>" << endl;
        exit(EXIT_FAILURE);
    }

    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);

    /* START STUDENT MODIFIABLE SECTION */

    PNMreader reader("../images/puddles.pnm");

	Shrinker s1;
	s1.SetInput(reader.GetOutput());

	Transpose t1;
	t1.SetInput(s1.GetOutput());	    
	
	LRConcat lr1;
	lr1.SetInput(t1.GetOutput());
	lr1.SetInput2(t1.GetOutput());

	TBConcat tb1;
	tb1.SetInput(lr1.GetOutput());
	tb1.SetInput2(lr1.GetOutput());

	Checkerboard b;
	b.SetInput(tb1.GetOutput());
	b.SetInput(reader.GetOutput());


	PNMreader reader2("../images/tux.pnm");
	
	Shrinker s2;
	s2.SetInput(reader2.GetOutput());
		
	TBConcat tb2;
	tb2.SetInput(s2.GetOutput());
	tb2.SetInput(tb1.GetOutput());

	PNMreader reader3("../images/deschutes.pnm");
	
	Crop crop;
	crop.SetRegion(100, 500, 25, 1);
	crop.SetInput(reader3.GetOutput());

	PNMreader reader4("../images/hank.pnm");
	
	Invert i;
	i.SetInput(reader4.GetOutput());

	Crop crop2;
	crop2.SetRegion(300, 100, 400, 25);
	crop.SetInput(i.GetOutput());

	LRConcat lr3;
	lr3.SetInput(crop.GetOutput());

	TBConcat tb3;
	tb3.SetInput(lr3.GetOutput());
	tb3.SetInput2(i.GetOutput());

	Checkerboard b2;
	b2.SetInput(tb3.GetOutput());

    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */

    Image *finalImage = b2.GetOutput();

    /* END STUDENT MODIFIABLE SECTION */

    try 
    {
        finalImage->Update();
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
             cerr << "Something is wrong ... can't open my_exception"
                  << " for opening" << endl;
             exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
