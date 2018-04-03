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

    //PNMreader reader("../images/puddles.pnm");
    PNMreader reader("../images/deschutes.pnm");
    Shrinker s1;
    s1.SetInput(reader.GetOutput());

    Color black(300, 198, 0, 0, 0);
    Color red(300, 198, 255, 0, 0);
    Color green(300, 198, 0, 255, 0);
    Color blue(300, 198, 0, 0, 255);
    Color white(300, 198, 255, 255, 255);

    Checkerboard b0;
    b0.SetInput(s1.GetOutput());
    b0.SetInput2(black.GetOutput());

    Checkerboard b1;
    b1.SetInput(s1.GetOutput());
    b1.SetInput2(red.GetOutput());

    Checkerboard b2;
    b2.SetInput(s1.GetOutput());
    b2.SetInput2(green.GetOutput());

    Checkerboard b3;
    b3.SetInput(s1.GetOutput());
    b3.SetInput2(blue.GetOutput());

    Checkerboard b4;
    b4.SetInput(s1.GetOutput());
    b4.SetInput2(white.GetOutput());

    LRConcat lr1;
    lr1.SetInput(b0.GetOutput());
    lr1.SetInput2(b4.GetOutput());

    TBConcat tb1;
    tb1.SetInput(b1.GetOutput());
    tb1.SetInput2(b2.GetOutput());

    TBConcat tb2;
    tb2.SetInput(tb1.GetOutput());
    tb2.SetInput2(b3.GetOutput());

    Invert i;
    i.SetInput(reader.GetOutput());

    Crop crop;
    crop.SetRegion(0, 599, 0, 395);
    crop.SetInput(i.GetOutput());

    TBConcat tb3;
    tb3.SetInput(lr1.GetOutput());
    tb3.SetInput2(crop.GetOutput());

    LRConcat lr2;
    lr2.SetInput(tb3.GetOutput());
    lr2.SetInput2(tb2.GetOutput());

    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = lr2.GetOutput();

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
