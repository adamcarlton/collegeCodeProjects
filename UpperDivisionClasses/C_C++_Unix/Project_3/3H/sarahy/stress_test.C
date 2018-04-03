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
    
    Shrinker s2;
    s2.SetInput(s1.GetOutput());
    
    LRConcat lr;
    lr.SetInput(s2.GetOutput());
    lr.SetInput2(s2.GetOutput());
    
    TBConcat tb;
    tb.SetInput(lr.GetOutput());
    tb.SetInput2(lr.GetOutput());
    
    TBConcat tb2;
    tb2.SetInput(tb.GetOutput());
    tb2.SetInput2(lr.GetOutput());

    TBConcat tb3;
    tb3.SetInput(tb2.GetOutput());
    tb3.SetInput2(lr.GetOutput());

    Color color(1, 1344, 50, 90, 255);
    
    LRConcat lr3;
    lr3.SetInput(color.GetOutput());
    lr3.SetInput2(tb3.GetOutput());
    
    TBConcat tb4;
    tb4.SetInput(s1.GetOutput());
    tb4.SetInput2(s1.GetOutput());

    
    Checkerboard b;
    b.SetInput(tb4.GetOutput());
    b.SetInput2(lr3.GetOutput());
    
    Crop c;
    c.SetRegion(0, 467, 0, 1343);
    c.SetInput(b.GetOutput());
    
    Transpose t;
    t.SetInput(c.GetOutput());
    
    Color color2(1344, 50, 50, 90, 255);
    
    TBConcat tb5;
    tb5.SetInput(t.GetOutput());
    tb5.SetInput2(color2.GetOutput());

    Color color3(1344, 50, 255, 90, 50);
    
    TBConcat tb6;
    tb6.SetInput(tb5.GetOutput());
    tb6.SetInput2(color3.GetOutput());
    
    Invert i;
    i.SetInput(tb6.GetOutput());
    
    Crop c2;
    c2.SetRegion(20, 700, 200, 551);
    c2.SetInput(i.GetOutput());
    
    PNMreader reader2("../images/question_marks.pnm");
    
    LRConcat lr4;
    lr4.SetInput(c2.GetOutput());
    lr4.SetInput2(reader2.GetOutput());
    
    Transpose t2;
    t2.SetInput(lr4.GetOutput());
    
    Color color4(352, 10, 70, 0, 70);
    
    TBConcat tb7;
    tb7.SetInput(color4.GetOutput());
    tb7.SetInput2(t2.GetOutput());

    
    
    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = tb7.GetOutput();

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
