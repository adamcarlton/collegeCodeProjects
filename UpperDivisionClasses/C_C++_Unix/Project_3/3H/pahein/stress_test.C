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
	
	Color white(1, 1, 255, 255, 255);
	Color red(1, 1, 255, 0, 0);
	Color brown(1, 1, 155, 79, 0);
	Color tan(1, 1, 254, 183, 0);
	
	// row 1
	
	LRConcat a;
	a.SetInput(white.GetOutput());
	a.SetInput2(white.GetOutput());
	
	LRConcat b;
	b.SetInput(a.GetOutput());
	b.SetInput2(white.GetOutput());
	
	LRConcat c;
	c.SetInput(b.GetOutput());
	c.SetInput2(red.GetOutput());
	
	LRConcat d;
	d.SetInput(c.GetOutput());
	d.SetInput2(red.GetOutput());
	
	LRConcat e;
	e.SetInput(d.GetOutput());
	e.SetInput2(red.GetOutput());
	
	LRConcat f;
	f.SetInput(e.GetOutput());
	f.SetInput2(red.GetOutput());
	
	LRConcat g;
	g.SetInput(f.GetOutput());
	g.SetInput2(red.GetOutput());
	
	LRConcat h;
	h.SetInput(g.GetOutput());
	h.SetInput2(white.GetOutput());
	
	LRConcat i;
	i.SetInput(h.GetOutput());
	i.SetInput2(white.GetOutput());
	
	LRConcat j;
	j.SetInput(i.GetOutput());
	j.SetInput2(white.GetOutput());
	
	LRConcat ONE;
	ONE.SetInput(j.GetOutput());
	ONE.SetInput2(white.GetOutput());
	
	// row 2
	
	LRConcat a1;
	a1.SetInput(white.GetOutput());
	a1.SetInput2(white.GetOutput());
	
	LRConcat b1;
	b1.SetInput(a1.GetOutput());
	b1.SetInput2(red.GetOutput());
	
	LRConcat c1;
	c1.SetInput(b1.GetOutput());
	c1.SetInput2(red.GetOutput());
	
	LRConcat d1;
	d1.SetInput(c1.GetOutput());
	d1.SetInput2(red.GetOutput());
	
	LRConcat e1;
	e1.SetInput(d1.GetOutput());
	e1.SetInput2(red.GetOutput());
	
	LRConcat f1;
	f1.SetInput(e1.GetOutput());
	f1.SetInput2(red.GetOutput());
	
	LRConcat g1;
	g1.SetInput(f1.GetOutput());
	g1.SetInput2(red.GetOutput());
	
	LRConcat h1;
	h1.SetInput(g1.GetOutput());
	h1.SetInput2(red.GetOutput());
	
	LRConcat i1;
	i1.SetInput(h1.GetOutput());
	i1.SetInput2(red.GetOutput());
	
	LRConcat j1;
	j1.SetInput(i1.GetOutput());
	j1.SetInput2(red.GetOutput());
	
	LRConcat TWO;
	TWO.SetInput(j1.GetOutput());
	TWO.SetInput2(white.GetOutput());
	
	// row 3
	
	
	LRConcat a3;
	a3.SetInput(white.GetOutput());
	a3.SetInput2(white.GetOutput());
	
	LRConcat b3;
	b3.SetInput(a3.GetOutput());
	b3.SetInput2(brown.GetOutput());
	
	LRConcat c3;
	c3.SetInput(b3.GetOutput());
	c3.SetInput2(brown.GetOutput());
	
	LRConcat d3;
	d3.SetInput(c3.GetOutput());
	d3.SetInput2(brown.GetOutput());
	
	LRConcat e3;
	e3.SetInput(d3.GetOutput());
	e3.SetInput2(tan.GetOutput());
	
	LRConcat f3;
	f3.SetInput(e3.GetOutput());
	f3.SetInput2(tan.GetOutput());
	
	LRConcat g3;
	g3.SetInput(f3.GetOutput());
	g3.SetInput2(brown.GetOutput());
	
	LRConcat h3;
	h3.SetInput(g3.GetOutput());
	h3.SetInput2(tan.GetOutput());
	
	LRConcat i3;
	i3.SetInput(h3.GetOutput());
	i3.SetInput2(white.GetOutput());
	
	LRConcat j3;
	j3.SetInput(i3.GetOutput());
	j3.SetInput2(white.GetOutput());
	
	LRConcat THREE;
	THREE.SetInput(j3.GetOutput());
	THREE.SetInput2(white.GetOutput());
	
	// row 4
	
	
	LRConcat a4;
	a4.SetInput(white.GetOutput());
	a4.SetInput2(brown.GetOutput());
	
	LRConcat b4;
	b4.SetInput(a4.GetOutput());
	b4.SetInput2(tan.GetOutput());
	
	LRConcat c4;
	c4.SetInput(b4.GetOutput());
	c4.SetInput2(brown.GetOutput());
	
	LRConcat d4;
	d4.SetInput(c4.GetOutput());
	d4.SetInput2(tan.GetOutput());
	
	LRConcat e4;
	e4.SetInput(d4.GetOutput());
	e4.SetInput2(tan.GetOutput());
	
	LRConcat f4;
	f4.SetInput(e4.GetOutput());
	f4.SetInput2(tan.GetOutput());
	
	LRConcat g4;
	g4.SetInput(f4.GetOutput());
	g4.SetInput2(brown.GetOutput());
	
	LRConcat h4;
	h4.SetInput(g4.GetOutput());
	h4.SetInput2(tan.GetOutput());
	
	LRConcat i4;
	i4.SetInput(h4.GetOutput());
	i4.SetInput2(tan.GetOutput());
	
	LRConcat j4;
	j4.SetInput(i4.GetOutput());
	j4.SetInput2(tan.GetOutput());
	
	LRConcat FOUR;
	FOUR.SetInput(j4.GetOutput());
	FOUR.SetInput2(white.GetOutput());
	
	// row 5
	
	
	LRConcat a5;
	a5.SetInput(white.GetOutput());
	a5.SetInput2(brown.GetOutput());
	
	LRConcat b5;
	b5.SetInput(a5.GetOutput());
	b5.SetInput2(tan.GetOutput());
	
	LRConcat c5;
	c5.SetInput(b5.GetOutput());
	c5.SetInput2(brown.GetOutput());
	
	LRConcat d5;
	d5.SetInput(c5.GetOutput());
	d5.SetInput2(brown.GetOutput());
	
	LRConcat e5;
	e5.SetInput(d5.GetOutput());
	e5.SetInput2(tan.GetOutput());
	
	LRConcat f5;
	f5.SetInput(e5.GetOutput());
	f5.SetInput2(tan.GetOutput());
	
	LRConcat g5;
	g5.SetInput(f5.GetOutput());
	g5.SetInput2(tan.GetOutput());
	
	LRConcat h5;
	h5.SetInput(g5.GetOutput());
	h5.SetInput2(brown.GetOutput());
	
	LRConcat i5;
	i5.SetInput(h5.GetOutput());
	i5.SetInput2(tan.GetOutput());
	
	LRConcat j5;
	j5.SetInput(i5.GetOutput());
	j5.SetInput2(tan.GetOutput());
	
	LRConcat FIVE;
	FIVE.SetInput(j5.GetOutput());
	FIVE.SetInput2(tan.GetOutput());
	
	// row 6
	
	
	LRConcat a6;
	a6.SetInput(white.GetOutput());
	a6.SetInput2(brown.GetOutput());
	
	LRConcat b6;
	b6.SetInput(a6.GetOutput());
	b6.SetInput2(brown.GetOutput());
	
	LRConcat c6;
	c6.SetInput(b6.GetOutput());
	c6.SetInput2(tan.GetOutput());
	
	LRConcat d6;
	d6.SetInput(c6.GetOutput());
	d6.SetInput2(tan.GetOutput());
	
	LRConcat e6;
	e6.SetInput(d6.GetOutput());
	e6.SetInput2(tan.GetOutput());
	
	LRConcat f6;
	f6.SetInput(e6.GetOutput());
	f6.SetInput2(tan.GetOutput());
	
	LRConcat g6;
	g6.SetInput(f6.GetOutput());
	g6.SetInput2(brown.GetOutput());
	
	LRConcat h6;
	h6.SetInput(g6.GetOutput());
	h6.SetInput2(brown.GetOutput());
	
	LRConcat i6;
	i6.SetInput(h6.GetOutput());
	i6.SetInput2(brown.GetOutput());
	
	LRConcat j6;
	j6.SetInput(i6.GetOutput());
	j6.SetInput2(brown.GetOutput());
	
	LRConcat SIX;
	SIX.SetInput(j6.GetOutput());
	SIX.SetInput2(white.GetOutput());
	
	// row 7
	
	
	LRConcat a7;
	a7.SetInput(white.GetOutput());
	a7.SetInput2(white.GetOutput());
	
	LRConcat b7;
	b7.SetInput(a7.GetOutput());
	b7.SetInput2(white.GetOutput());
	
	LRConcat c7;
	c7.SetInput(b7.GetOutput());
	c7.SetInput2(tan.GetOutput());
	
	LRConcat d7;
	d7.SetInput(c7.GetOutput());
	d7.SetInput2(tan.GetOutput());
	
	LRConcat e7;
	e7.SetInput(d7.GetOutput());
	e7.SetInput2(tan.GetOutput());
	
	LRConcat f7;
	f7.SetInput(e7.GetOutput());
	f7.SetInput2(tan.GetOutput());
	
	LRConcat g7;
	g7.SetInput(f7.GetOutput());
	g7.SetInput2(tan.GetOutput());
	
	LRConcat h7;
	h7.SetInput(g7.GetOutput());
	h7.SetInput2(tan.GetOutput());
	
	LRConcat i7;
	i7.SetInput(h7.GetOutput());
	i7.SetInput2(tan.GetOutput());
	
	LRConcat j7;
	j7.SetInput(i7.GetOutput());
	j7.SetInput2(white.GetOutput());
	
	LRConcat SEVEN;
	SEVEN.SetInput(j7.GetOutput());
	SEVEN.SetInput2(white.GetOutput());
	
	// top bottom concats
	
	TBConcat uno;
	uno.SetInput(ONE.GetOutput());
	uno.SetInput2(TWO.GetOutput());
	
	TBConcat dos;
	dos.SetInput(uno.GetOutput());
	dos.SetInput2(THREE.GetOutput());
	
	TBConcat tres;
	tres.SetInput(dos.GetOutput());
	tres.SetInput2(FOUR.GetOutput());
	
	TBConcat quatro;
	quatro.SetInput(tres.GetOutput());
	quatro.SetInput2(FIVE.GetOutput());
	
	TBConcat cinco;
	cinco.SetInput(quatro.GetOutput());
	cinco.SetInput2(SIX.GetOutput());
	
	TBConcat seis;
	seis.SetInput(cinco.GetOutput());
	seis.SetInput2(SEVEN.GetOutput());

	
	
	Image *finalImage = seis.GetOutput();

    //PNMreader reader("../images/puddles.pnm");
    //Shrinker s1;
    //s1.SetInput(reader.GetOutput());
    
    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    //Image *finalImage = s1.GetOutput();

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
