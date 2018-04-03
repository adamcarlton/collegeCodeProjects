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
    Shrinker four;
    Shrinker sixteen;
    Shrinker sixtyfour;
    LRConcat lr;
    TBConcat tb;
    Checkerboard blender1;
    Checkerboard blender2;
      Checkerboard blender3;
    Checkerboard blender4;
     LRConcat lr2;
    LRConcat lr3;
    TBConcat tb2;
    TBConcat tb4;
    LRConcat lr4;
    four.SetInput(reader.GetOutput());
    sixteen.SetInput(four.GetOutput());
    sixtyfour.SetInput(sixteen.GetOutput());

    lr.SetInput(sixtyfour.GetOutput());
    lr.SetInput2(sixtyfour.GetOutput());
     tb.SetInput(lr.GetOutput());
    tb.SetInput2(lr.GetOutput());

    blender1.SetInput(tb.GetOutput());
    blender1.SetInput2(sixteen.GetOutput());   
    
    lr2.SetInput(blender1.GetOutput());
    lr2.SetInput2(blender1.GetOutput());
    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput2(lr2.GetOutput());
    Color color(1, 672, 0, 0, 0);   
     lr3.SetInput(tb2.GetOutput());
    lr3.SetInput2(color.GetOutput());
    
    blender2.SetInput(lr3.GetOutput());
    blender2.SetInput2(four.GetOutput());   

    Color color2(1786, 1344, 0, 0, 128);        

    lr4.SetInput(blender2.GetOutput());
    lr4.SetInput2(blender2.GetOutput());
    tb4.SetInput(lr4.GetOutput());
    tb4.SetInput2(lr4.GetOutput());
    
    blender3.SetInput(tb4.GetOutput());
    blender3.SetInput2(reader.GetOutput());   

   blender4.SetInput(blender3.GetOutput());
    blender4.SetInput2(color2.GetOutput());   

    Image *finalImage = blender4.GetOutput();

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
