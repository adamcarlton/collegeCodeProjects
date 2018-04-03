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
    Color color(1786, 1344, 13,255 , 248);	
    Checkerboard b1;
    b1.SetInput(reader.GetOutput());
    b1.SetInput2(color.GetOutput());

    Color color2(1786, 1344, 255, 13, 102);
    Checkerboard b2;
    b2.SetInput(reader.GetOutput());
    b2.SetInput2(color2.GetOutput());

    LRConcat l1;
    l1.SetInput(b1.GetOutput());
    l1.SetInput2(b2.GetOutput());
    
    LRConcat l2;
    l2.SetInput(b2.GetOutput());
    l2.SetInput2(b1.GetOutput());

    TBConcat t1;
    t1.SetInput(l1.GetOutput());
    t1.SetInput2(l2.GetOutput()); 
    
    Shrinker s1;
    s1.SetInput(t1.GetOutput());

    Shrinker s2;
    s2.SetInput(t1.GetOutput());

    Shrinker s3;
    s3.SetInput(t1.GetOutput());

    Shrinker s4;
    s4.SetInput(t1.GetOutput());

    Invert i1;
    i1.SetInput(s2.GetOutput());

    Invert i2;
    i2.SetInput(s4.GetOutput());

    LRConcat l3;
    l3.SetInput(s1.GetOutput());
    l3.SetInput2(s2.GetOutput());

    LRConcat l4;
    l4.SetInput(s4.GetOutput());
    l4.SetInput2(s3.GetOutput());

    TBConcat t2;
    t2.SetInput(l3.GetOutput());
    t2.SetInput2(l4.GetOutput());

    Image *finalImage = t2.GetOutput();

    
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
