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
    Shrinker s2;
    LRConcat lrconcat1;
    LRConcat lrconcat2;
    TBConcat tbconcat1;
    TBConcat tbconcat2;
    Checkerboard  blender;
    
    s1.SetInput(reader.GetOutput());
    s1.SetInput(reader.GetOutput());

    lrconcat1.SetInput(s1.GetOutput());
    lrconcat1.SetInput2(s1.GetOutput());

    tbconcat1.SetInput(lrconcat1.GetOutput());
    tbconcat1.SetInput2(lrconcat1.GetOutput());

    s2.SetInput(tbconcat1.GetOutput());

    lrconcat2.SetInput(s2.GetOutput());
    lrconcat2.SetInput2(s1.GetOutput());

    tbconcat2.SetInput(lrconcat2.GetOutput());
    tbconcat2.SetInput2(s1.GetOutput());

    blender.SetInput(tbconcat2.GetOutput());
    blender.SetInput2(reader.GetOutput());

    
    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = blender.GetOutput();

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
