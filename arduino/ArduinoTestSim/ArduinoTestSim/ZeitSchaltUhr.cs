using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoTestSim
{
    public class ZeitSchaltUhr
    {

        struct Zeit
        {
            int h;
            int m;
            int s;

            public Zeit(int _h,int _m, int _s)
            {
                h = _h;
                m = _m;
                s = _s;
            }
        };

        //---------------------------------- ANPASSEN VOR PROGRAMMSTART -------------------------------------------
        Zeit startZeit = new Zeit( 14, 17, 40 );
        Zeit schaltZeiten[] = { { 9, 0, 0 }, { 10, 0, 0 }, { 11, 0, 0 }, { 13, 0, 0 } };
        //---------------------------------------------------------------------------------------------------------

    }
}
