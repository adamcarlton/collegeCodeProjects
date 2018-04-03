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
    PNMreader reader2("../images/hank.pnm");
    PNMwriter writer;
    
    Invert i1;
    i1.SetInput(reader2.GetOutput());
    
    LRConcat lr1; 
    lr1.SetInput(i1.GetOutput());
    lr1.SetInput2(reader2.GetOutput());

    LRConcat lr2;
    lr2.SetInput(reader2.GetOutput());
    lr2.SetInput2(i1.GetOutput());

    TBConcat tb1;
    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(lr2.GetOutput());
    
    Shrinker s1;
    s1.SetInput(tb1.GetOutput());

    LRConcat lr3;
    lr3.SetInput(s1.GetOutput());
    lr3.SetInput2(s1.GetOutput());

    LRConcat lr4;
    lr4.SetInput(s1.GetOutput());
    lr4.SetInput2(s1.GetOutput());

    TBConcat tb2;
    tb2.SetInput(lr3.GetOutput());
    tb2.SetInput2(lr4.GetOutput());
   
    Invert i2;
    i2.SetInput(tb2.GetOutput());
   
    Transpose t1;
    t1.SetInput(i2.GetOutput());

    Transpose t2;
    t2.SetInput(t1.GetOutput());

    Color color(652, 968, 0, 255, 0);

    Checkerboard blender;
    blender.SetInput(t2.GetOutput());
    blender.SetInput2(color.GetOutput());
    
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
