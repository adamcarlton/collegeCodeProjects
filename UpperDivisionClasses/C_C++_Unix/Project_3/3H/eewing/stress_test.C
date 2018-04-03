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

    PNMreader hank("../images/hank.pnm");
    PNMreader deschutes("../images/deschutes.pnm");
    PNMreader gnu("../images/gnu.pnm");

    Crop crop1;
    crop1.SetRegion(30, 279, 25, 349);
    crop1.SetInput(hank.GetOutput());

    Color red(250, 325, 128, 0, 0);
    Color green(250, 325, 0, 128, 0);
    Color blue(250, 325, 0, 0, 128);

    Checkerboard redHank;
    redHank.SetInput(red.GetOutput());
    redHank.SetInput2(crop1.GetOutput());

    Checkerboard greenHank;
    greenHank.SetInput(green.GetOutput());
    greenHank.SetInput2(crop1.GetOutput());

    Checkerboard blueHank;
    blueHank.SetInput(blue.GetOutput());
    blueHank.SetInput2(crop1.GetOutput());

    Invert evil;
    evil.SetInput(crop1.GetOutput());

    LRConcat step1;
    step1.SetInput(redHank.GetOutput());
    step1.SetInput2(greenHank.GetOutput());
    
    LRConcat step2;
    step2.SetInput(blueHank.GetOutput());
    step2.SetInput2(evil.GetOutput());

    LRConcat finalStep;
    finalStep.SetInput(step1.GetOutput());
    finalStep.SetInput2(step2.GetOutput());

    Crop gnuCrop;
    gnuCrop.SetRegion(0+125, 398+125, 0+25, 395+25);
    gnuCrop.SetInput(gnu.GetOutput());

    LRConcat middle;
    middle.SetInput(deschutes.GetOutput());
    middle.SetInput2(gnuCrop.GetOutput());
    
    TBConcat full;
    full.SetInput(finalStep.GetOutput());
    full.SetInput2(middle.GetOutput());

    Color correction(1001, 1, 83, 65, 5);
    Color correctionY(1, 721, 0, 0, 0);

    LRConcat firstCorrection;
    firstCorrection.SetInput(full.GetOutput());
    firstCorrection.SetInput2(correctionY.GetOutput());

    TBConcat finalConcat;
    finalConcat.SetInput(firstCorrection.GetOutput());
    finalConcat.SetInput2(correction.GetOutput());

    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = finalConcat.GetOutput();

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
