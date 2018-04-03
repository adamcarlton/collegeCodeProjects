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

    PNMreader reader1("../images/deschutes.pnm");
    PNMreader reader2("../images/question_marks.pnm");
    PNMreader reader3("../images/puddles.pnm");
    Color color1(75, 352, 200, 0, 0);
    Color color2(75, 352, 0, 0, 200);
    Color color3(1433, 100, 100, 0, 100);

    Crop crop1;
    crop1.SetRegion(0, 356, 0, 351);
    crop1.SetInput(reader1.GetOutput());

    LRConcat LRCon1;
    LRCon1.SetInput(crop1.GetOutput());
    LRCon1.SetInput2(color1.GetOutput());

    LRConcat LRCon2;
    LRCon2.SetInput(color2.GetOutput());
    LRCon2.SetInput2(reader2.GetOutput());

    Checkerboard blend1;
    blend1.SetInput(LRCon1.GetOutput());
    blend1.SetInput2(LRCon2.GetOutput());

    Checkerboard blend2;
    blend2.SetInput(LRCon1.GetOutput());
    blend2.SetInput2(LRCon2.GetOutput());

    TBConcat TBCon1;
    TBCon1.SetInput(blend1.GetOutput());
    TBCon1.SetInput2(blend2.GetOutput());

    Crop crop2;
    crop2.SetRegion(0, 1000, 100, 803);
    crop2.SetInput(reader3.GetOutput());

    LRConcat LRCon3;
    LRCon3.SetInput(TBCon1.GetOutput());
    LRCon3.SetInput2(crop2.GetOutput());

    TBConcat TBCon2;
    TBCon2.SetInput(LRCon3.GetOutput());
    TBCon2.SetInput2(color3.GetOutput());

    Invert invert;
    invert.SetInput(TBCon2.GetOutput());

    TBConcat s1;
    s1.SetInput(color3.GetOutput());
    s1.SetInput2(invert.GetOutput());

    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = s1.GetOutput();

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
